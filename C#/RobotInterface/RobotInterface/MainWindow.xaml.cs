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
using ExtendedSerialPort;

namespace RobotInterface
{
	/// <summary>
	/// Logique d'interaction pour MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{

		SerialPort serialPort1;

		private void SendMessage()
		{

			textBoxReception.Text = "Reçu : " + textBoxEmission.Text + "\n" + textBoxReception.Text;
			textBoxEmission.Text = null;
			serialPort1.WriteLine(textBoxEmission.Text);
		}

		public MainWindow()
		{
			
			serialPort1 = new ReliableSerialPort("COM8", 115200, Parity.None, 8, StopBits.One);
			serialPort1.Open();
			InitializeComponent();
		}

		private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
		{
			SendMessage();

			if (buttonEnvoyer.Background == Brushes.RoyalBlue)
			{
				buttonEnvoyer.Background = Brushes.Beige;
			}
			else
				buttonEnvoyer.Background = Brushes.RoyalBlue;
		}

		private void buttonEnvoyer_KeyUp(object sender, KeyEventArgs e)
		{
		
			if(e.Key == Key.Enter)
			{

			}

		}
	}
}
