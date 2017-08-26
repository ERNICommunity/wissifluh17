using PMS.MobileClient.Services;
using Xamarin.Forms;
using Xamarin.Forms.Maps;
using Plugin.Geolocator;
using System;

namespace PMS.MobileClient.Views
{
    public partial class MainPage : ContentPage
	{
        private SensorNodeService _sensorNodeService;

        public MainPage()
		{
			InitializeComponent();
            _sensorNodeService = new SensorNodeService();
		}

        protected override async void OnAppearing()
        {
            var sensors = _sensorNodeService.GetAll();

            foreach(var sensor in sensors)
            {
                var position = new Position(sensor.Latitude, sensor.Longitude);
                var pin = new Pin
                {
                    Type = PinType.Place,
                    Position = position,
                    Label = sensor.Name
                };

                MapControl.Pins.Add(pin);
            }
            
            // TODO :)
            //var currentPosition = await CrossGeolocator.Current.GetPositionAsync(TimeSpan.FromSeconds(60));
            //MapControl.MoveToRegion(MapSpan.FromCenterAndRadius(new Position(currentPosition.Latitude, currentPosition.Longitude), Distance.FromKilometers(1)));
        }
    }
}
