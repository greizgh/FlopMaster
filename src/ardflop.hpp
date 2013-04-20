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
#include <vector>
#include "monitor.hpp"
#include "ardmidi.hpp"
#include "flopcom.hpp"
//! Convert midi to floppy-drives friendly messages
class ardflop
{
    private:
        //Midi play
        float corrector;/*!< Correction factor used to transpose notes*/
        bool dispatchnotes;/*!< Do we pool drives ?*/
        std::vector<unsigned short> pool;/*!< vector that keep track of notes beeing pooled*/
        /*!
         * Dispatch notes in the pool
         * \param messages midi event
         */
        void dispatch(ardmidi message);
        //Monitor
        ardmonitor ardmon;/*!< Debug monitor*/
        //Serial com
        flopcom serialcom;/*!< Serial device handler*/
        //arduino relative members
        static const unsigned int microperiods[];/*!< Array of periods corresponding to midi notes*/
        static const int ARD_RESOLUTION;/*!< Time in µs between two interruptions on the microcontroller*/

    public:
        /*!
         * \param PortName name of the serial device
         * \param poolsize number of drives in the pool
         */
        ardflop(const std::string PortName, int poolsize);
        ~ardflop();
        /*!
         * Transpose notes played by the drives
         */
        void transpose(int octave);
        /*!
         * Midi message handler, called by RtMidi callback
         */
        void processmidi(ardmidi message);
};
#endif
