# FlopMaster
FlopMaster is a software made to revive old floppy drives. Ever wanted to make them sing? Then FlopMaster is for you!

This software is split in two parts: FlopMaster on your computer and the controller firmware. You need both in order to play with your drives.

## Features
* Connect to any midi output (sequencer, midi keyboard...)
* Transpose notes being played
* Pool drives, so that you can play live
* Can open a virtual port (Linux with Alsa driver and MacOSX only)

## Hardware
Keep in mind that odd pins are ground on the connector. Your microcontroller and the drives should be on the same ground.

Make sure you enable your drives by grounding pin 14. Connect pin 18 of the drive to odd pins on the arduino, those are direction pins. Connect pin 20 of the drive to even pins on the arduino, those are 'step' pins.

## Compilation

### Computer side
The code as been written to be as cross-platform as possible, it relies on [Boost](http://www.boost.org/) libs and RtMidi (included).

Makefile generation is handled by cmake.
For now, it has only been built and tested on a linux box, feel free to contribute to make FlopMaster cross-platform.

Once you cloned the repository, follow these steps:

    cd <repo path>
    mkdir build
    cd build
    cmake ..
    make

### Microcontroller side
The code originally targeted atmega328p on arduino board, but you surely can adapt it to other similar microcontrollers.

Change the variables in 'arduino/Makefile' to your config, type 'make' and it should be done. 'make upload' to flash your microcontroller.

## Usage
Just type:

        ./FlopMaster /dev/yourttydevice

It will then ask you if you want to create a virtual device or to connect to an existing midi output.
Every note-on / note-off event will be sent to the arduino.

## License
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the [GNU General Public License](http://www.gnu.org/licenses/gpl-3.0.html) for more details.
