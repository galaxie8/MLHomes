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
        /// <summary>
        /// Read one line off of the serial port, and hopefully populate a sensormodel
        /// </summary>
        /// <returns>SensorModel or Null if malformed</returns>
        public SensorModel SensorReadLine(SerialPort oCon)
        {
            string sInput = string.Empty;
            try
            {
                //--------------------------------------------------------
                // Format of the string that the base station sends us via serial.
                // Temprature(F)/Humidity(%)/Fire(bit)/distance(cm int)
                // T78:H40:F0:W1
                //--------------------------------------------------------
                oCon.NewLine = "\r\n";
                //oCon.ReadTimeout = 1500;

                oCon.WriteLine("GimmieDaSensors!"); // Send request command
                sInput = oCon.ReadLine(); // Catch the reply

                var asSplitInput = sInput.Split(':'); // [T78][H40][F0][W1][D0]

                var oModel = new SensorModel();

                for (int i = 0; i < asSplitInput.Length; i++)
                {
                    asSplitInput[i] = asSplitInput[i].Remove(0, 1); //Removing the data piece identifyer
                }

                oModel.Temperature = int.Parse(asSplitInput[0]); //Load up the model
                oModel.Humidity = int.Parse(asSplitInput[1]);
                if (asSplitInput[2] == "1")
                {
                    oModel.FireAlarm = true;
                } // bool defaults to false
                if (asSplitInput[3] == "1")
                {
                    oModel.WaterAlarm = true;
                }

                return oModel;
            }
            catch (Exception x)
            {
                //Let the controller deal with it
                throw x;
            }
        }
    }
}