using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using Utility;

namespace Port_20000_Server
{
    class Program
    {
        static void Main(string[] args)
        {
            TCPServer.Server s = new TCPServer.Server();
        }
    }
}



namespace TCPServer
{
   class Server
   {
      private TcpListener tcpListener;
      private Thread listenThread;
      private Int32 percent_compression = 70;

      public Server()
      {
         Console.Write("Compress JPEGs how much percent [70] ?");
         String pctstr = Console.ReadLine();
         if (pctstr == "")
         {
            percent_compression = 70;
         }
         else
         {
            percent_compression = Int32.Parse(pctstr);
         }
         Console.WriteLine("Screenshot server is now listening for connections on port 20000");

         this.tcpListener = new TcpListener(IPAddress.Any, 20000);
         this.listenThread = new Thread(new ThreadStart(ListenForClients));

         this.listenThread.Start();
      }
      private void ListenForClients()
      {
         this.tcpListener.Start();

         while (true)
         {
            TcpClient client = this.tcpListener.AcceptTcpClient();
            Console.WriteLine("{0} remote client", client.Client.RemoteEndPoint.ToString());
            Thread clientThread = new Thread(new ParameterizedThreadStart(HandleClientComm));
            clientThread.Start(client);
         }
      }
      private void HandleClientComm(object client)
      {
         TcpClient tcpClient = (TcpClient)client;
         NetworkStream clientStream = tcpClient.GetStream();
         ASCIIEncoding enc = new ASCIIEncoding();

         StreamReader sr = new StreamReader(clientStream);
         StreamWriter sw = new StreamWriter(clientStream);
         BinaryFormatter bf = new BinaryFormatter();

         while (true)
         {
            try
            {
               Bitmap ss = get_screenshot();

               Ascii85 a85 = new Ascii85();
               a85.LineLength = 0;
               Bitmap ss1 = (Bitmap)ss.GetThumbnailImage(800, 600, new System.Drawing.Image.GetThumbnailImageAbort(ThumbnailCallback), IntPtr.Zero);
               SaveJPGWithCompressionSetting(ss1, "ss.jpg", percent_compression);
               byte[] aq = System.IO.File.ReadAllBytes("ss.jpg");
               String b64str = a85.Encode(aq);
               Console.WriteLine("Sending data {0} -- {1}", tcpClient.Client.RemoteEndPoint.ToString().Split(":".ToCharArray())[0], b64str.Length);
               sw.WriteLine(b64str);
               sw.Flush();

               Application.DoEvents();
               System.Threading.Thread.Sleep(1);
               Application.DoEvents();
            }
            catch (Exception exc)
            {
               //a socket error has occured
               Console.WriteLine(tcpClient.Client.RemoteEndPoint.ToString() + " disconnected");
               Console.WriteLine("error: " + exc.Message);
               break;
            }
         }

         tcpClient.Close();
      }
      private Bitmap get_screenshot()
      {
         Rectangle totalSize = Rectangle.Empty;
         foreach (Screen s in Screen.AllScreens)
         {
            totalSize = Rectangle.Union(totalSize, s.Bounds);
         }
         //Bitmap screenShotBMP = new Bitmap(totalSize.Width, totalSize.Height, PixelFormat.Format32bppArgb);
         Bitmap screenShotBMP = new Bitmap(totalSize.Width, totalSize.Height, PixelFormat.Format16bppRgb555);
         Graphics screenShotGraphics = Graphics.FromImage(screenShotBMP);
         screenShotGraphics.CopyFromScreen(totalSize.X, totalSize.Y, 0, 0, totalSize.Size, CopyPixelOperation.SourceCopy);
         screenShotGraphics.Dispose();
         return screenShotBMP;
      }
      private static ImageCodecInfo GetEncoderInfo(String mimeType)
      {
         int j;
         ImageCodecInfo[] encoders;
         encoders = ImageCodecInfo.GetImageEncoders();
         for (j = 0; j < encoders.Length; ++j)
         {
            if (encoders[j].MimeType == mimeType)
               return encoders[j];
         }
         return null;
      }
      private void SaveJPGWithCompressionSetting(Image image, string szFileName, long lCompression)
      {
         EncoderParameters eps = new EncoderParameters(1);
         eps.Param[0] = new EncoderParameter(System.Drawing.Imaging.Encoder.Quality, lCompression);
         ImageCodecInfo ici = GetEncoderInfo("image/jpeg");
         image.Save(szFileName, ici, eps);
      }
      private bool ThumbnailCallback()
      {
         return true;
      }
   }
}