using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rtsp_client
{

    public partial class Form1 : Form
    {

        private string _ip = "127.0.0.1";
        private int _port = 8554;
        private TcpClient _tcpClient = new TcpClient();
        //
        private byte[] _recvBuf = new byte[4096];
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                //_tcpClient.Close();
                IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(_ip), _port);
                //connect
                _tcpClient.Connect(endPoint);
                int seq = 1;
                //OPTIONS
                string url = string.Format("rtsp://{0}:{1}/live", _ip, _port);
                SendReq(CmdOptions(url, seq));
                string response = RecvRes("OPTIONS");
                //DESCRIBE
                seq++;
                SendReq(CmdDescribe(url, seq));
                response = RecvRes("DESCRIBE");
                string channel = GetChannel(response);
                //SETUP video
                int port = 32421;
                seq++;
                SendReq(CmdSetup(url, channel, seq, port));
                response = RecvRes("SETUP");
                //包含音频和视频时，下一个setup需加入session 
                string session = GetSession(response);
                //SETUP  audio
                //
                //PLAY
                seq++;
                SendReq(CmdPlay(url, seq, session));
                response = RecvRes("PLAY");
            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.Message);
            }

        }
        private void SendReq(string req)
        {
            textBox1.Text += req;
            byte[] cmd_buf = Encoding.UTF8.GetBytes(req);
            NetworkStream netStream = _tcpClient.GetStream();
            netStream.Write(cmd_buf, 0, cmd_buf.Length);
            netStream.Flush();
        }
        private string RecvRes(string flag)
        {
            NetworkStream netStream = _tcpClient.GetStream();
            int count = netStream.Read(_recvBuf, 0, _recvBuf.Length);
            if (count > 0)
            {
                if (flag == "DESCRIBE")
                {
                    if (_recvBuf[count - 4] == '\r' && _recvBuf[count - 3] == '\n' && _recvBuf[count - 2] == '\r' && _recvBuf[count - 1] == '\n')
                        count += netStream.Read(_recvBuf, count, _recvBuf.Length - count);
                }

                string result = Encoding.UTF8.GetString(_recvBuf, 0, count);
                textBox1.Text += result;
                return result;
            }
            else
            {
                return string.Empty;
            }
}

private string CmdOptions(string url, int cseq)
{
    string result = string.Format(
        "OPTIONS {0} RTSP/1.0\r\n"
        + "CSeq: {1}\r\n"
        + "\r\n",
        url, cseq);
    return result;
}
private string CmdDescribe(string url, int cseq)
{
    string result = string.Format(
        "DESCRIBE {0} RTSP/1.0\r\n"
        + "CSeq: {1}\r\n"
        + "Accept:application/sdp\r\n"
        + "\r\n",
        url, cseq);
    return result;
}

private string CmdSetup(string url, string channel, int cseq, int av_port)
{
    string result = string.Format(
        "SETUP {0}/{1} RTSP/1.0\r\n"
        + "CSeq: {2}\r\n"
        + "Transport: RTP/AVP;unicast;client_port={3}-{4}\r\n"
        + "\r\n",
        url, channel, cseq, av_port, av_port + 1);
    return result;
}
private string CmdPlay(string url, int cseq, string session)
{
    string result = string.Format(
        "PLAY {0} RTSP/1.0\r\n"
        + "CSeq: {1}\r\n"
        + "Session:{2}\r\n"
        + "Range: npt=0.000-\r\n"
        + "\r\n",
        url, cseq, session);
    return result;
}

private string GetChannel(string describe)
{
    string result = string.Empty;
    if (describe.StartsWith("RTSP/1.0 200 OK"))
    {
        int pos = describe.IndexOf("m=");
        string media = describe.Substring(pos);
        string pattern = @"a=control:.*/(\S+)\r\n";
        Match match = Regex.Match(media, pattern);
        if (match.Success)
        {
            result = match.Groups[1].Value;
        }
    }
    return result;
}
private string GetSession(string setup)
{
    string pattern = @"Session:(\S)[;\r\n]";
    //string setup = "RTSP/1.0 200 OK\r\nCSeq: 4\r\nTransport: RTP / AVP; unicast; client_port = 54492 - 54493; server_port = 56400 - 56401\r\nSession:66334873\r\n\r\n";
    Match match = Regex.Match(setup, pattern);
    if (match.Success)
    {
        return match.Groups[1].Value;
    }
    return string.Empty;
}

        //private void SendCommand(string command)
        //{
        //    byte[] cmd_buf = Encoding.UTF8.GetBytes(command);
        //    try
        //    {
        //        _tcpClient = new TcpClient();
        //        IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(_ip), _port1);
        //       _ tcpClient.Connect(endPoint);
        //        using (NetworkStream netStream = tcpClient.GetStream())
        //        {
        //            netStream.Write(cmd_buf, 0, cmd_buf.Length);
        //            netStream.Flush();
        //        }
        //    }

        //    catch
        //    {
        //        //    int tmpPort = _port1;
        //        //    _port1 = _port2;
        //        //    _port2 = tmpPort;

        //        //    TcpClient tcpClient = new TcpClient();
        //        //    IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(_ip), _port1);
        //        //    tcpClient.Connect(endPoint);
        //        //    using (NetworkStream netStream = tcpClient.GetStream())
        //        //    {
        //        //        netStream.Write(cmd_buf, 0, cmd_buf.Length);
        //        //        netStream.Flush();
        //        //    }
        //        //    tcpClient.Close();

        //    }
        //}
    }
}
