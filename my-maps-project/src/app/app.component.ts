import { Component,OnInit } from '@angular/core';
import { DataService } from './data.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  locations: any;
  latLng = {};

  constructor(private dataService: DataService) {
    this.locations = this.dataService.myData();
  }
  title: string = 'Current Sensor locations';
  lat: number = 47.002775;
  lng: number = 8.493895;
  latitudeA:number;
  longitudeA:number;

  zoom = 16;

  ngOnInit() {
    console.log('ngOnInit fired');
    function showPosition(position) {
      this.latLng = {
        'lat': position.coords.latitude,
        'lng': position.coords.longitude
      };
      console.log("new value:"+position.coords.latitude);
    }

    if (navigator.geolocation) {
      console.log('navigator found');
      navigator.geolocation.getCurrentPosition(position => {
        this.latLng = position.coords;
        console.log(position.coords);
        this.latitudeA = position.coords.latitude;
        this.longitudeA= position.coords.longitude;
        console.log(position.coords.latitude);
        console.log(position.coords.longitude);
      });
    } else {
      console.log("Geolocation is not supported by this browser.");
    }
  }
}
