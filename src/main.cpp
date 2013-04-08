/*
 *   Copyright 2013 Greizgh <greizgh@gmail.com>
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#include <iostream>
#include <string>
#include "ardflop.hpp"
#include "RtMidi/RtMidi.h"
#include "RtMidi/RtError.h"
#include "fm_config.h"
#include <boost/program_options.hpp>
namespace po=boost::program_options;
using namespace std;
void callback(double deltatime, std::vector< unsigned char > *message, void *userdata)
{
    ardflop *bridge = (ardflop*)(userdata);
    bridge->processmidi(message);
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
    po::options_description desc("Usage: FlopMaster [OPTIONS] SERIAL_PORT");
    desc.add_options()
        ("help,h","show this message")
        ("version,v","show version information")
        ("port,p",po::value<string>(&port),"specify serial port to use");
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
    if(vm.count("port"))
    {
        RtMidiIn* midiin = 0;
        ardflop* bridge = new ardflop(port);
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
