# STM32F4 Template


This is a simple "stm32f4-template" example using the Standard Peripheral Library for [STM32F4 Discovery board](http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/PF252419).

### Files

Here is an overview of the files found in this project:

* .gdbinit: contains startup commands for gdb, the debugger. This file is a copy of the [original by Ross Wolin](https://github.com/rowol/stm32_discovery_arm_gcc/blob/master/blinky/.gdbinit).
* Makefile: commented makefile used to compile this project. You can use this file to see how the whole compilation process works and how to use the tools.
* main.c: this is the actual program (with comments).
* stm32\_flash.ld: linker script provided by ST. Contains a description of the memory layout used by the Cortex-M4.
* stm32f4xx\_conf.h: this file is used to include the header files of the standard peripheral library. It is a configuration file. You could include those headers directly in main.c, but the peripheral library includes this configuration header (stm32f4xx.h includes it conditionally), so we must provide it - or else we cannot compile our code against the library. This file is provided by ST and is supposed to be adapted to every project.
* system\_stm32f4xx.c: implements intialization code called from the startup file startup\_stm32f4xx.s (present in the library). This file is provided by ST.

#### Missing files

This project does not include the peripheral library used to build the program. You can however download the library from ST (see link below). In my setup I have extracted the library in a folder one level above the "stm32f4-template" folder.

### Tools and software requirements

* [GCC ARM Embedded toolchain](https://launchpad.net/gcc-arm-embedded) for ARM Cortex-M. You need this in order to compile and debug your code. You can download pre-built binaries for all major operating systems. After downloading, just extract the archive somewhere (a good place: /opt/gcc-arm-embedded/), no installation is required. The exact location of the extracted folder will be used in the makefile.

* [stlink](https://github.com/texane/stlink) utility written by texane. You need this for flashing the compiled code to the board. It also contains a gdb server used to debug your code on the chip. Install this from the source code or if you are on OS X, you can do it from brew: ```brew install stlink```

* The [STM32F4DISCOVERY board firmware package](http://www.st.com/web/en/catalog/tools/PF257904). You need this library in order to access and use the board's peripherals. It contains headers and source files which you compile and link together with your own files.

* make. You need this in order to... make this project. make should be pre-installed on all Linux and OS X machines.

### Usage

1. Download and install the requirements mentioned above.
2. Download or clone this repository.
3. Edit the Makefile if needed.
4. Open a terminal window and change to the stm32f4-template directory.
5. Type `make`.
6. Connect the stm32f4 discovery board to your computer.
7. If you just want to flash the stm32f4-template program, type `make flash`.
8. If you want to debug the program:
   1. Start the gdb server included in the stlink package by typing `st-util`. You should start st-util in a separated terminal window so that it does not polute the gdb session.
   2. Type `make debug`. This will start gdb which will read the .gdbinit file and thus connect to localhost port 4242, where st-util is listening. From this point on, st-util will take commands from gdb and control the discovery board.
   3. In the gdb window, type `break main` to set up a break point to the main
   function.
   4. Type `continue`.
   5. Have fun.

### Thanks

* Many thanks to [texane](https://github.com/texane) for writting the
  [stlink](https://github.com/texane/stlink) utility!
