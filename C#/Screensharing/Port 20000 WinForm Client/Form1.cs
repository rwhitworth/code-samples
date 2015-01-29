using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Drawing.Imaging;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using Utility;

namespace Port_20000_WinForm_Client
{
   public partial class Form1 : Form
   {
      public Form1()
      {
         InitializeComponent();
      }

      // private IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 20000);
      private IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("192.168.1.5"), 20000);
      private Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
      NetworkStream ns;
      StreamReader sr;
      StreamWriter sw;
      BinaryFormatter bf = new BinaryFormatter();
      Bitmap ss = new Bitmap(1, 1);

      private void timer1_Tick(object sender, EventArgs e)
      {
         timer1.Enabled = false;


         //while (true)
         //{
         try
         {
            String b64str = sr.ReadLine();
            Ascii85 a85 = new Ascii85();
            byte[] aq = a85.Decode(b64str);
            System.IO.File.WriteAllBytes("ss.jpg", aq);
            Stream ii = System.IO.File.OpenRead("ss.jpg");
            ss = (Bitmap)Image.FromStream(ii);
            ii.Close();

            Application.DoEvents();
         }
         catch (Exception)
         {
            //break;
            //throw;
         }

         pictureBox1.Image = ss;

         //}

         //server.Close();
         timer1.Enabled = true;
      }

      private void Form1_Load(object sender, EventArgs e)
      {
         //ipep = new IPEndPoint(IPAddress.Parse("192.168.1.5"), 20000);
         //server.Connect(ipep);
         //ns = new NetworkStream(server);
         //sr = new StreamReader(ns);
         //sw = new StreamWriter(ns);
      }

      private void Form1_Resize(object sender, EventArgs e)
      {
         pictureBox1.Width = this.Width - 32;
         pictureBox1.Height = this.Height - 69;
      }

      private void button1_Click(object sender, EventArgs e)
      {
         #region try catch - setup stuff
         try
         {
            server.Disconnect(true);
         }
         catch (Exception)
         {
         }
         try
         {
            ns.Close();
         }
         catch (Exception)
         {
         }
         try
         {
            sr.Close();
         }
         catch (Exception)
         {
         }
         try
         {
            sw.Close();
         }
         catch (Exception)
         {
         }
         #endregion

         try
         {
            ipep = new IPEndPoint(IPAddress.Parse(textBox1.Text), 20000);
         }
         catch (Exception)
         {
            MessageBox.Show("Please check the IP address you typed in, there was an error parsing it");
         }

         try
         {
            server.Connect(ipep);
            ns = new NetworkStream(server);
            sr = new StreamReader(ns);
            sw = new StreamWriter(ns);
         }
         catch (Exception)
         {
            MessageBox.Show("Error connecting to the specified server.");
         }

      }
   }
}
