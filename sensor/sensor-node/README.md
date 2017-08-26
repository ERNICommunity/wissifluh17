# sensor-node
Wiring / Arduino framework based Embedded Application for PM data measurement sending data using LoRaWan / TTN, powered by [PlatformIO](http://platformio.org "Cross-platform build system").

The project builds for Adafruit Feather M0 / LoRa by default and could also be compiledfor and run on an Arduino Mega 2560 with Dragino LoRa Shield. 

## Toolchain
[PlatformIO](http://platformio.org "Cross-platform build system") is the ideal foundation when developing IoT devices. It supports cross-platform development for many different controller boards widely used in the maker field and also for industrial applications.

### Installation
#### Python 2.7

**Windows**

* download Python 2.7.x from: https://www.python.org/downloads/
* install for all users
* select destinationdirectory (keep default): C:\Python27\
* add python.exe to path

**Linux**

Install Python 2.7 using your package manager.

#### PlatformIO
Install PlatformIO using the Python Package Manager
(see also http://docs.platformio.org/en/latest/installation.html#python-package-manager):

* in a cmd shell enter: `pip install -U platformio`
* upgrade pip, in the cmd shell enter: `python -m pip install --upgrade pip`
* upgrade PlatformIO, in the cmd shell enter: `pio upgrade`
 

## How to build for Eclipse CDT
  1. Open a command shell in this folder (i.e. `C:\wissifluh17\sensor\sensor-node`)
  2. Run the command `pio init --ide eclipse`
  3. Run the command `pio run`

## Open project in Eclipse CDT
  1. Open Eclipse CDT, choose the folder as workspace one level up where you ran the cmd shell before (i.e. `C:\wissifluh17\sensor`)
  2. Import the project with File->Import->General->Existing Projects into Workspace, choose the `sensor-node` (i.e `C:\wissifluh17\sensor\sensor-node`)

## Connect Terminal Emulation
In order to test and run the CLI commands, a terminal emulation program shall be used. The one giving you the best experience will be the [HTerm](http://www.der-hammer.info/terminal/). 
Load the _hterm-com10.cfg_ file to configure HTerm properly. Alter the COM10 accordingly to the one that has been selected on your computer.

## Debug Features
### Debug CLI Commands
#### Command Tree
     dbg                      Debug CLI root node
       tr                     Debug Trace Port config access
         heap                 Particular Trace Port (heap: see below in chapter Trace Port)
           out                Trace Output config access for the current trace port
             get              Show the assigned Trace Output
             set <outName>    Set a particular Trace Output name
             list             Show all available Trace Output names (and the currently selected)
           lvl                Trace Level config access for the current trace port
             get              Show the current trace level
             set <level>      Set a particular trace level
             list             Show all available trace levels (and the currenntly selected)

#### Example commands
* `dbg tr heap lvl set debug`


### Trace Port
|Trace Port|default level|functionality|
|----------|-------------|:------------|
|heap|info|if set to debug level: automatically print free heap memory [bytes], every 10 seconds|

## Library Usage
This chapter lists all the libraries this project is using.

### PlatformIO Libraries
|ID|Name|URL|Description|
|:--|:-------|:----------------|:-----------------------|
|173|SerialCommand|https://github.com/kroimon/Arduino-SerialCommand|A Wiring/Arduino library to tokenize and parse commands received over a serial port.|
|1699|wiring-timer|https://github.com/dniklaus/wiring-timer|Universal recurring or non-recurring Timer|



### Homebrew Libraries
|Name|URL|Description|
|:------|:---------------------|:-------------------------------|
|Debug-Cli|https://github.com/ERNICommunity/debug-cli|Debug CLI for Embedded Applications - Command Line  Interface for debugging and testing based on object oriented tree structure.|
|Dbg-Trace|https://github.com/ERNICommunity/dbg-trace|Debug Trace component for Embedded Applications - Debug and Trace Log message system based on trace ports with adjustable levels.|
|RamUtils|https://github.com/dniklaus/arduino-utils-mem|Arduino Memory Utilities|

