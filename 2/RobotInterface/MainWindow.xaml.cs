using System;
using System.Collections.Generic;
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
using System.IO.Ports;
using ExtendedSerialPort;

namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        ReliableSerialPort serialPort1;
        public MainWindow()
        {
            InitializeComponent();

            serialPort1 = new ReliableSerialPort("COM5", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();
           
 
        }
        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            textBoxReception.Text += Encoding.UTF8.GetString(e.Data , 0 , e.Data.Length ) ;
        }
        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {

            if (buttonEnvoyer.Background == Brushes.RoyalBlue)
                buttonEnvoyer.Background = Brushes.Beige;
            else
                buttonEnvoyer.Background = Brushes.RoyalBlue;
            SendMessage();
        }
        private void SendMessage()
        {

            textBoxReception.Text = "Reçu : " + textBoxEmission.Text + "\n" + textBoxReception.Text;
            textBoxEmission.Text = null;
            serialPort1.WriteLine(textBoxEmission.Text);
        }
        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
{
                SendMessage();
            }

        }
    }
}
