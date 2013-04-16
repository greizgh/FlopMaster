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
#include "ardflop.hpp"
#include "monitor.hpp"
#include "fm_config.h"
#include <string>
#include <iostream>
int const ardflop::ARD_RESOLUTION = 40;
unsigned int const ardflop::microperiods[] = {
    //A4=440Hz
    61156,57724,54484,51426,48540,45815,43244,40817,38526,36364,34323,32396,//C0-B0
    30578,28862,27242,25713,24270,22908,21622,20408,19263,18182,17161,16198,
    15289,14431,13621,12856,12135,11454,10811,10204,9631,9091,8581,8099,
    7645,7215,6810,6428,6067,5727,5405,5102,4816,4545,4290,4050,
    3822,3608,3405,3214,3034,2863,2703,2551,2408,2273,2145,2025,
    1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012,
    956,902,851,804,758,716,676,638,602,568,536,506,
    478,451,426,402,379,358,338,319,301,284,268,253,
    239,225,213,201,190,179,169,159,150,142,134,127
};

ardflop::ardflop(const std::string PortName) : ardmon(), corrector(0), serialcom(PortName)
{
}
void ardflop::processmidi(std::vector<unsigned char> *msg)
{
    unsigned char status = msg->at(0);

    if (status > 127 && status < 144)//note off
    {
        /*Convert midi channel to arduino pin by
         * multiplying by 2*/
        char pin = (char)(2*(status-127));
        ardmon.note_off_signal(pin);
        serialcom.play(pin, 0);
    }
    else if (status>143 && status<160)//note on
    {
        char pin = (char)(2*(status-143));
        unsigned short period = microperiods[(int)(msg->at(1))]/(ARD_RESOLUTION)*corrector;
        if (msg->at(2)==0)//zero velocity event
        {
            ardmon.note_off_signal(pin);
            serialcom.play(pin, 0);
        }
        else
        {
            ardmon.note_on_signal(pin, msg->at(1), period);
            serialcom.play(pin, period);
        }
    }
}
void ardflop::transpose(int octave)
{
    if(octave==0)
        corrector=1;
    if(octave<0 && octave>-4)
        corrector = -2*octave;
    if(octave>0 && octave<4)
        corrector = 1/(2*octave);
}
ardflop::~ardflop()
{
    ardmon.print_stats();
}
