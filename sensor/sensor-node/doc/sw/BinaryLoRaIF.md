# Binary Data Interface Definition LoRa

## Data

### Temperature

### Relative Humidity

### PM 2.5
Particulate Matter 2.5um

### PM 10
Particulate Matter 10um

## Serial Data Stream


| Item # | Data |Description      | Datatype | Conversion for serialization | Byte # |
|--------|------|-----------------|----------|------------------------------|--------|
|1|temperature|Temperature [C]  |float|100 * temperature|0, 1|
|2|humidity|Relative Humidity|float|100 * humidity|2, 3|
|3|pm10|PM 10 [ug/m^3]   |float|100 * pm10|4, 5|
|4|pm25|PM 10 [ug/m^3]   |float|100 * pm25|6, 7|
