using Android.App;
using Android.OS;
using Xamarin.Forms.Platform.Android;

namespace PMS.MobileClient.Android
{
    [Activity(Label = "PMS.MobileClient.Android", Theme = "@style/MainTheme", MainLauncher = true)]
    public class MainActivity : FormsAppCompatActivity//, Android.Support.V4.AppActivityCompat.IOnRequestPermissionsResultCallback
    {
        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            Xamarin.Forms.Forms.Init(this, bundle);
            Xamarin.FormsMaps.Init(this, bundle);
            LoadApplication(new MobileClientApp());

        }

        //public override void OnRequestPermissionsResult(int requestCode, string[] permissions, Permission[] grantResults)
        //{
        //    PermissionsImplementation.Current.OnRequestPermissionsResult(requestCode, permissions, grantResults);
        //}
    }
}

