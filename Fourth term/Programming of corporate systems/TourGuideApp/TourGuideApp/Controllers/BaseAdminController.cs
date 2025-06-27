using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;

namespace TourGuideApp.Controllers
{
    public class BaseAdminController : Controller
    {
        public override void OnActionExecuting(ActionExecutingContext context)
        {
            var actionName = context.ActionDescriptor.RouteValues["action"];

            if (actionName == "Login")
            {
                base.OnActionExecuting(context);
                return;
            }

            if (context.HttpContext.Session.GetString("User") != "Admin")
            {
                context.Result = new RedirectToActionResult("Login", "Admin", null);
            }

            base.OnActionExecuting(context);
        }
    }
}
