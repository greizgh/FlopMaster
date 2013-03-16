#FlopMaster#
This command line utility aims at making music out of floppy drives easily.

##Features##
* Output data to the Arduino with the same structure as [Moppy](https://github.com/SammyIAm/Moppy/tree/moppy-advanced)
* Connect to any midi output (senquencer, midi keyboard...)
* Can open a virtual port (Linux with Alsa driver and MacOSX only)

##Motivation##
I've been primarily using [Moppy](https://github.com/SammyIAm/Moppy/tree/moppy-advanced), but I was unsatisfied with the way it worked.

What bothered me is that moppy relies on the RXTX lib wich is kinda broken (at least on ArchLinux).
With RXTX working, moppy is doing its job quite correctly, but it lacks some flexibility.

So I started a rewrite of moppy, stripped down to its core functionnality:

* Taking midi data in input
* Feed the arduino with data over serial

##Hardware##
Connections are exactly the same as for moppy. This software can be seen as a drop-in replacement for moppy.
If you are looking for Arduino code, [take a look here](https://github.com/SammyIAm/Moppy/blob/moppy-advanced/Arduino/Moppy/Moppy.ino).

##Compilation##
The code as been written to be as cross-platform as possible, it relies on [Boost](http://www.boost.org/) libs and RtMidi (included).

Makefile generation is handled by cmake.
For now, it has only been built and tested on a linux box, feel free to contribute to make FlopMaster cross-platform.

##Usage##
Once compiled, just type:

        ./FlopMaster /dev/yourttydevice

It will then ask you if you want to create a virtual device or to connect to an existing midi output.
Every note-on / note-off event will be sent to the arduino.
