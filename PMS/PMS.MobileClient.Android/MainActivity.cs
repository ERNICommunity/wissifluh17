using Android.App;
using Android.OS;
using Xamarin.Forms.Platform.Android;

namespace PMS.MobileClient.Android
{
    [Activity(Label = "PMS.MobileClient.Android", Theme = "@style/MainTheme", MainLauncher = true)]
    public class MainActivity : FormsAppCompatActivity
    {
        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            Xamarin.Forms.Forms.Init(this, bundle);
            Xamarin.FormsMaps.Init(this, bundle);
            LoadApplication(new MobileClientApp());

        }
    }
}

