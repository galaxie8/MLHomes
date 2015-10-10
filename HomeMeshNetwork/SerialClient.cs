using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.IO.Ports;

namespace HomeMeshNetwork
{
    public class SerialClient
    {
        SerialPort oCon = new SerialPort("COM3", 115200);

        public string SensorReadLine()
        {
            string sResult;
            try
            {
                oCon.Open();
                sResult = oCon.ReadLine();
                oCon.Close();
            }
            catch (Exception x)
            {
                sResult = x.Message;
            }
            return sResult;
        }
    }
}