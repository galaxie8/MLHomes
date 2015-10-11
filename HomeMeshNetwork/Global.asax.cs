using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Optimization;
using System.Web.Routing;

namespace HomeMeshNetwork
{
    public class MvcApplication : System.Web.HttpApplication
    {
        protected void Application_Start()
        {
            AreaRegistration.RegisterAllAreas();
            FilterConfig.RegisterGlobalFilters(GlobalFilters.Filters);
            RouteConfig.RegisterRoutes(RouteTable.Routes);
            BundleConfig.RegisterBundles(BundleTable.Bundles);
            SerialPort oCon = new SerialPort("COM4", 115200); 
            oCon.Open();
            this.Application.Add("SerialSensor", oCon);
            //------------------------------------------------------------
            // This is so that we have one and only one copy of this object. 
            // We were having issues putting this object in the Action code
            // because they were stepping on each other. Now its basically 
            // global. Who needs memory management?
            //------------------------------------------------------------
        }
    }
}
