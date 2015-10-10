using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.IO.Ports;
using HomeMeshNetwork.Models;
using System.Threading;

namespace HomeMeshNetwork
{
    public class SerialClient
    {
        SerialPort oCon = new SerialPort("COM3", 115200);
        /// <summary>
        /// Read one line off of the serial port, and if its not garbled, populate a sensormodel
        /// </summary>
        /// <returns>SensorModel or Null if malformed</returns>
        public string SensorReadLine()
        {
            SensorModel oResult;
            string sInput = string.Empty;
            oCon.NewLine = "\r\n";
            oCon.ReadTimeout = 1500;
            try
            {
                //--------------------------------------------------------
                // Format of the string that the base station sends us via serial.
                // Temprature(F)/Humidity(%)/Fire(bit)/distance(cm int)
                // (T:78H:40F:0W:1D:0)
                //--------------------------------------------------------
                oCon.Open();
                oCon.WriteLine("GimmieDaSensors!");
                Thread.Sleep(200); // wait a bit for the base station to respond
                sInput = oCon.ReadLine();
           

                if (!(sInput.StartsWith("(") && sInput.EndsWith(")")) && sInput.Length < 28) // Check for chunk frame and proper size
                {
                    //throw new Exception("Serial input was malformed.");
                }
                sInput = sInput.Replace("(", "");
                sInput = sInput.Replace(")", "");
                oCon.Close();
                return sInput;
                string[] asInput = sInput.Split(':');

            }
            catch (Exception x)
            { // Cleaning up our mess
                oCon.Close();
                oCon.Dispose();
                sInput = x.Message;
                return sInput;
            }
           // return oResult;
        }
    }
}