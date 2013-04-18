/*
 * Copyright 2013 Greizgh <greizgh@gmail.com>
 *
 * This file is part of FlopMaster.
 * FlodMaster is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * FlopMaster is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with FlopMaster.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <string>
#include "ardflop.hpp"
#include "ardmidi.hpp"
#include "RtMidi/RtMidi.h"
#include "RtMidi/RtError.h"
#include "fm_config.h"
#include <boost/program_options.hpp>
namespace po=boost::program_options;
using namespace std;
void callback(double deltatime, std::vector< unsigned char > *message, void *userdata)
{
    ardflop *bridge = (ardflop*)(userdata);
    std::vector<unsigned char> midi = *message;
    ardmidi midimsg(midi);
    bridge->processmidi(midimsg);
}

bool chooseMidiPort( RtMidiIn *rtmidi )
{
  std::cout << "\nWould you like to open a virtual input port? [y/N] ";

  std::string keyHit;
  std::getline( std::cin, keyHit );
  if ( keyHit == "y" ) {
    rtmidi->openVirtualPort("FlopMaster");
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No input ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = rtmidi->getPortName(i);
      std::cout << "  Input port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while ( i >= nPorts );
  }

  std::getline( std::cin, keyHit );  // used to clear out stdin
  rtmidi->openPort( i );

  return true;
}

int main(int argc, char* argv[])
{
    string port;
    int octave=0;
    int poolsize=0;
    po::options_description desc("Usage: FlopMaster [OPTIONS] SERIAL_PORT");
    desc.add_options()
        ("port,p",po::value<string>(&port),"specify serial port to use")
        ("transpose,t",po::value<int>(&octave),"transpose notes of specified octave")
        ("dispatch,d",po::value<int>(&poolsize),"dispatch notes between given number of drives")
        ("verbose,V","display some debug info")
        ("help,h","show this message")
        ("version,v","show version information");
    po::positional_options_description p;
    p.add("port", -1);
    po::variables_map vm;
    try
    {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    }
    catch(const std::exception& ex)
    {
        cerr << "Can't parse command line, check your input!" << endl;
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
    po::notify(vm);
    if(vm.count("help"))
    {
        cout << desc << endl;
        return 1;
    }
    if(vm.count("version"))
    {
        cout << "FlopMaster version " << fm_VERSION_MAJOR << "." << fm_VERSION_MINOR << endl;
        return 1;
    }
    if(vm.count("verbose"))
    {
        fm_DEBUG=true;
    }
    if(vm.count("port"))
    {
        RtMidiIn* midiin = 0;
        ardflop* bridge = new ardflop(port, poolsize);
        bridge->transpose(octave);
        try {
            midiin = new RtMidiIn();
            if (chooseMidiPort(midiin)!=false)
            {
                midiin->setCallback(&callback, bridge);
                midiin->ignoreTypes(false, false, false);
                std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
                if(fm_DEBUG) std::cout<<"Will output debug data"<<std::endl;
                char input;
                std::cin.get(input);
            }
        }
        catch (RtError &error) {
            error.printMessage();
        }
        delete bridge;
        delete midiin;
    }
    else {
        cout << "Serial port not set" << endl;
        return 1;
    }
    return 0;
}
