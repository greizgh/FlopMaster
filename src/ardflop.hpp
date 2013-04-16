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
#ifndef ARDFLOP_H
#define ARDFLOP_H
#include <string>
#include "monitor.hpp"
#include "flopcom.hpp"
class ardflop
{
    private:
        //Midi
        float corrector;
        //Monitor
        ardmonitor ardmon;
        //Serial com
        flopcom serialcom;
        //arduino relative members
        static const unsigned int microperiods[];
        static const int ARD_RESOLUTION;

    public:
        ardflop(const std::string PortName);
        ~ardflop();
        void transpose(int octave);
        void processmidi(std::vector<unsigned char> *msg);
};
#endif
