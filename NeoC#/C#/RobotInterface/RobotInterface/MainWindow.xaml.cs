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

            serialPort1 = new ReliableSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 20);
            timerAffichage.Tick += TimerAffichageTick;
            timerAffichage.Start();

        }

        private void TimerAffichageTick(object sender, EventArgs e)
        {
            if (byteListReceived.Count > 0)
            {

                byte b = byteListReceived.Dequeue();
                DecodeMessage(b);
                textBoxReception.Text = "Fonction = " + msgDecodedFunction + " ";

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
            string TestString = "Bonjour";
            byte[] array = Encoding.ASCII.GetBytes(TestString);
            UartEncodeAndSendMessage(0x0080, 7, array);
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

            msg[i++] = (byte)msgFunction;
            msg[i++] = (byte)(msgFunction >> 8);

            msg[i++] = (byte)msgPayloadLength;
            msg[i++] = (byte)(msgPayloadLength >> 8);
            
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
        int msgDecodedFunction = 0;
        int msgDecodedPayloadLength = 0;
        byte[] msgDecodedPayload;
        byte msgDecodedChecksum;
        byte msgCalculatedChecksum;
        int msgDecodedPayloadIndex = 0;
        int toto = -1;

        private void DecodeMessage(byte c)
        {
            switch (rcvState)
            {
                case StateReception.Waiting:
                    if (c == 0xFE)
                        rcvState = StateReception.FunctionMSB;
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
                    msgDecodedFunction += c;
                    msgDecodedFunction <<= 8;
                    rcvState = StateReception.PayloadLengthLSB;
                    break;
                case StateReception.PayloadLengthLSB:
                    msgDecodedFunction += c;
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
                    if (msgCalculatedChecksum == msgDecodedChecksum)
                        toto = 1;
                    else
                        toto = 0;
                    break;
                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }

    }
}
 

