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

namespace UDPServer
{
    public partial class Form1 : Form
    {
        private UdpClient udpServer = new UdpClient();
        private IPEndPoint ipEndPoint;
        private int portNo = 65432;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            udpServer = new UdpClient(portNo);
            ipEndPoint = new IPEndPoint(IPAddress.Parse("192.168.1.10"), portNo);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Send(textBox1.Text);
            textBox1.Clear();
        }

        private void Send(string sendDataString)
        {
            label1.Text = "";

            byte[] receiveData = udpServer.Receive(ref ipEndPoint);
            for (int i = 0; i < receiveData.Length; i++)
                label1.Text += receiveData[i].ToString();

            byte[] sendData = Encoding.ASCII.GetBytes(sendDataString);
            udpServer.Send(sendData, sendData.Length, ipEndPoint);
        }
    }
}
