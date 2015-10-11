using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace HomeMeshNetwork.Controllers
{
    public class BaseController : Controller
    {
        // GET: Base
        [Route("Home/Error/")]
        public ActionResult HandleError(Exception ex)
        {
            return View("Error", new HandleErrorInfo(ex, "",""));
        }
    }
}