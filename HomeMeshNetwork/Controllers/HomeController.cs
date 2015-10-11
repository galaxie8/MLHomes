using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using HomeMeshNetwork;
using System.IO.Ports;
using HomeMeshNetwork.Models;
using Newtonsoft.Json;

namespace HomeMeshNetwork.Controllers
{
    public class HomeController : BaseController
    {
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult Dashboard()
        {
            ViewBag.Message = "Your Home dashboard!";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }

        public string GetSensors()
        {
            SerialPort oCon = (SerialPort)this.HttpContext.Application["SerialSensor"]; // We put the serial connection in here so that it's a global object

            var sc = new SerialClient();
            SensorModel stats;

            try
            {
                stats = sc.SensorReadLine(oCon);
                string output = JsonConvert.SerializeObject((object)stats);
                return output;
            }
            catch(Exception ex)
            {
                return "error: " + ex.Message;
            }
        }

        public void ToggleLight()
        {
            SerialPort oCon = (SerialPort)this.HttpContext.Application["SerialSensor"];
            var sc = new SerialClient();

            sc.ToggleLight(oCon);
        }
    }
}