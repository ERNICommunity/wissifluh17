import { Injectable } from '@angular/core';

@Injectable()
export class DataService {

  constructor() { }

  locations = [
    {id: 1,  lat: 51.5239935252832,    lng:  5.137663903579778,   content: 'Kids Jungalow (5p)'},
    {id: 2,  lat: 51.523853342911906,  lng:  5.1377765563584035,  content: 'Kids Jungalow (5p)'},
    {id: 3,  lat: 51.5237298485607,    lng:  5.137969675407476,   content: 'Kids Jungalow (5p)'},
    {id: 4,  lat: 51.52355628836575,   lng:  5.138066234932012,   content: 'Kids Jungalow (5p)'},
    {id: 5,  lat: 51.52340275379578,   lng:  5.138211074218816,   content: 'Kids Jungalow (5p)'},
    {id: 6,  lat: 51.523199152806626,  lng:  5.138382735595769,   content: 'Kids Jungalow (5p)'},
    {id: 7,  lat: 51.5229955509073,    lng:  5.138511481628484,   content: 'Kids Jungalow (5p)'},
    {id: 8,  lat: 51.52280529912936,   lng:  5.138543668136663,   content: 'Kids Jungalow (5p)'},
    {id: 9,  lat: 51.523596340777075,  lng:  5.138463201866216,   content: 'Kids Jungalow (5p)'},
    {id: 700,lat: 51.523372714362736,  lng:  5.1386992362595265,  content: 'Kids Jungalow (5p)'},
    {id: 101, lat: 51.52329594683302,  lng:  5.138838711128301,   content: 'Kids Jungalow Giraffe'}
  ];

  locations1 = [
    {id: 1,  lat: 46.999857,    lng:  8.481321,   content: 'Kids Jungalow (5p)'},
    {id: 2,  lat: 47.000696,   lng:  8.490698,   content: 'Kids Jungalow (5p)'},
    {id: 3,  lat: 47.002529,   lng:  8.494732,   content: 'Kids Jungalow (5p)'}
  ];
  
  myData() {
    return this.locations1;
  }
}
