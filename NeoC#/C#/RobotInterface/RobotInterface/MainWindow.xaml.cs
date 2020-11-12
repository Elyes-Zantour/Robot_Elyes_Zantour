using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using ExtendedSerialPort;
using System.Threading;

namespace RobotInterface
{
    public partial class MainWindow : Window
    {
        private Queue<byte> byteListReceived = new Queue<byte>();
        Robot robot = new Robot();
        DispatcherTimer timerAffichage;
        private ReliableSerialPort serialPort1;

        public MainWindow()
        {
            InitializeComponent();

            serialPort1 = new ReliableSerialPort("COM5", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 250);
            timerAffichage.Tick += TimerAffichageTick;
            timerAffichage.Start();
        }

        private void TimerAffichageTick(object sender, EventArgs e)
        {
            while (byteListReceived.Count > 0)
            {
                byte b = byteListReceived.Dequeue();
                DecodeMessage(b);

                //textBoxReception.Text = null;
                //textBoxReception.Text += "Payload =" + msgDecodedPayloadLength;
                //textBoxReception.Text += "0x" + byteListReceived.Dequeue().ToString("X2") + " ";

                if (decodedFlag)
                {
                    string stringPayload = " ";

                    for (int i = 0; i < msgDecodedPayloadLength; i++)
                    {
                        stringPayload += msgDecodedPayload[i].ToString("X2") + " ";
                    }

                    TextBoxData.Text = null;
                    TextBoxData.Text = "Fonction = " + msgDecodedFunction + " LongeurPayload = " + msgDecodedPayloadLength + " Payload = " + stringPayload + " Checksum = " + isCkecksumOk;
                }
            }
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            SendMessage();
        }

        private void SendMessage()
        {
            serialPort1.Write(textBoxEmission.Text);
            textBoxEmission.Text = null;
        }

        private void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            //receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);

            for (int i = 0; i < e.Data.Length; i++)
            {
                byteListReceived.Enqueue(e.Data[i]);
            }
        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            textBoxReception.Text = null;
        }

        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            //byte[] byteList = new byte[20];
            //for (int i = 0; i < 20; i++)
            //{
            //    byteList[i] = (byte)(2 * i);
            //}
            //serialPort1.Write(byteList, 0, byteList.Count());

            string TestString = "AAA";
            byte[] array = Encoding.ASCII.GetBytes(TestString);
            UartEncodeAndSendMessage(0x0080, 3, array);
        }
    
        byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
            byte cheksum = 0xFE;

            cheksum = (byte)(cheksum ^ msgFunction);
            cheksum = (byte)(cheksum ^ msgPayloadLength);

            for (int i = 0; i < msgPayloadLength; i++)
                cheksum ^= msgPayload[i];

            return cheksum;
        }

       void UartEncodeAndSendMessage(ushort msgFunction, ushort msgPayloadLength, byte[] msgPayload)
        {
            int i = 0, j = 0;
            byte[] msg = new byte[ 6 + msgPayloadLength];

            msg[i++] = 0xFE;

            msg[i++] = (byte)(msgFunction >> 8);
            msg[i++] = (byte)msgFunction;

            msg[i++] = (byte)(msgPayloadLength >> 8);
            msg[i++] = (byte)msgPayloadLength;

            for (j = 0; j < msgPayloadLength; j++)
                msg[i++] = msgPayload[j];

            msg[i++] = CalculateChecksum(msgFunction, msgPayloadLength, msgPayload);

            serialPort1.Write(msg, 0, msg.Length);
        }

        public enum StateReception
        {
            Waiting,
            FunctionMSB,
            FunctionLSB,
            PayloadLengthMSB,
            PayloadLengthLSB,
            Payload,
            CheckSum
        }

        //Definitions
        StateReception rcvState = StateReception.Waiting;

        byte[] msgDecodedPayload;
        byte msgDecodedChecksum;
        byte msgCalculatedChecksum;

        int msgDecodedFunction = 0;
        int msgDecodedPayloadLength = 0;
        int msgDecodedPayloadIndex = 0;
        int isCkecksumOk = -1;

        bool decodedFlag = false;

        
        private void DecodeMessage(byte c)
        {
            Console.Write("0x" + c.ToString("X2") + " ");
            switch (rcvState)
            {
                
                case StateReception.Waiting:
                    if (c == 0xFE)
                    {
                        msgDecodedPayloadLength = 0;
                        msgDecodedPayloadIndex = 0;
                        msgDecodedChecksum = 0;
                        msgCalculatedChecksum = 0;
                        msgDecodedFunction = 0;

                        rcvState = StateReception.FunctionMSB;
                        decodedFlag = false;
                    }
                    break;

                case StateReception.FunctionMSB:
                    msgDecodedFunction += c;
                    msgDecodedFunction <<= 8;
                    rcvState = StateReception.FunctionLSB;
                    break;

                case StateReception.FunctionLSB:
                    msgDecodedFunction += c;
                    rcvState = StateReception.PayloadLengthMSB;
                    break;

                case StateReception.PayloadLengthMSB:
                    msgDecodedPayloadLength += c;
                    msgDecodedPayloadLength <<= 8;
                    rcvState = StateReception.PayloadLengthLSB;
                    break;

                case StateReception.PayloadLengthLSB:
                    msgDecodedPayloadLength += c;
                    msgDecodedPayload = new byte[msgDecodedPayloadLength];
                    if (msgDecodedPayloadLength == 0)
                        rcvState = StateReception.CheckSum;
                    else
                        rcvState = StateReception.Payload;

                    break;

                case StateReception.Payload:
                    msgDecodedPayload[msgDecodedPayloadIndex++] = c;
                    if (msgDecodedPayloadIndex == msgDecodedPayloadLength)
                        rcvState = StateReception.CheckSum;
                   
                    break;


                case StateReception.CheckSum:
                    
                   msgDecodedChecksum = c;
                   msgCalculatedChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    decodedFlag = true;
                    Console.WriteLine("CHECKSUM : " + msgCalculatedChecksum.ToString("X2"));
                    if (msgDecodedChecksum == msgCalculatedChecksum)
                    {
                        isCkecksumOk = 1;

                    }
                    else
                        isCkecksumOk = 0;
                    rcvState = StateReception.Waiting;
                    break;

                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }
    }
}
 

