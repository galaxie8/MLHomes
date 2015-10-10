using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(HomeMeshNetwork.Startup))]
namespace HomeMeshNetwork
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
