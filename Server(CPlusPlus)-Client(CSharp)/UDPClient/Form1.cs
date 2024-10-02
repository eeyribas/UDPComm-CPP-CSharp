using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UDPClient
{
    public partial class Form1 : Form
    {
        private UdpClient udpClient = new UdpClient();
        private IPEndPoint ipEndPoint;
        private int portNo = 65432;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            udpClient = new UdpClient(portNo);
            ipEndPoint = new IPEndPoint(IPAddress.Parse("192.168.1.10"), portNo);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Send(textBox1.Text);
            textBox1.Clear();
        }

        private void Send(string sendDataString)
        {
            byte[] sendData = Encoding.ASCII.GetBytes(sendDataString);
            udpClient.Send(sendData, sendData.Length, ipEndPoint);
        }
    }
}
