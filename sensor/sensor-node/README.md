# wiring-skeleton
Wiring / Arduino based Skeleton Embedded Application, powered by [PlatformIO](http://platformio.org "Cross-platform build system")

The project has initially been created for and tested on an Arduino Mega 2560 controller module.

## Purpose
This project builds up an Arduino Framework based application skeleton and it comprises of several components helping with debugging and integrating embedded applications on [Arduino](http://arduino.cc) based contoller modules.

This skeleton application can help you to build up your own Arduino Framework based applications with focus on IoT. 

It demonstrates the usage of the following copmonents:

* [Timer](https://github.com/dniklaus/arduino-utils-timer)
* [Debug-Cli](https://github.com/ERNICommunity/debug-cli)
* [Dbg-Trace](https://github.com/ERNICommunity/dbg-trace)

## How to build for Eclipse CDT
  1. Create a directory where your Eclipse Workspace will be stored and where this project shall be cloned into. E.g. `C:\git\pio-prj`
  2. Clone this repository recursively into the folder you created before, `git clone --recursive git@github.com:dniklaus/wiring-skeleton.git`
  3. Open a command shell in the just cloned project folder, i.e in `C:\git\pio-prj\wiring-skeleton`
  4. Run the command `pio init -b megaatmega2560 --ide eclipse`
  5. Run the command `pio run`

## Open project in Eclipse CDT
  6. Open Eclipse CDT, choose the folder you created before as workspace, i.e `C:\git\pio-prj`
  7. Import the project with File->Import->General->Existing Projects into Workspace, choose the `wiring-skeleton` (i.e `C:\git\pio-prj\wiring-skeleton`)

## Connect Terminal Emulation
In order to test and run the CLI commands, a terminal emulation program shall be used. The one giving you the best experience will be the [HTerm](http://www.der-hammer.info/terminal/). 
Load the _hterm-com18.cfg_ file to configure HTerm properly. Alter the COM18 accordingly to the one that has been selected on your computer.

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


### Homebrew Libraries
|Name|URL|Description|
|:------|:---------------------|:-------------------------------|
|Timer|https://github.com/dniklaus/arduino-utils-timer|Universal recurring or non-recurring Timer|
|Debug-Cli|https://github.com/ERNICommunity/debug-cli|Debug CLI for Embedded Applications - Command Line  Interface for debugging and testing based on object oriented tree structure.|
|Dbg-Trace|https://github.com/ERNICommunity/dbg-trace|Debug Trace component for Embedded Applications - Debug and Trace Log message system based on trace ports with adjustable levels.|
|RamUtils|https://github.com/dniklaus/arduino-utils-mem|Arduino Memory Utilities|

