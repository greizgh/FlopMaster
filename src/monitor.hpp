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
#ifndef ARDMONITOR_H
#define ARDMONITOR_H
#include <iostream>
#include <vector>
//! Debug monitor class
/*!
 * Ardmon counts sote-on/note-off signals and pool overflow.
 * If debug is set, it outputs what is received (midi message)
 * and what is sent through serial.
 */
class ardmonitor
{
    private:
        std::ostream &outpt;
        //Report variables
        unsigned int note_on_received; /*!< number of note-on signals received */
        unsigned int note_off_received; /*!< number of note-off signals received */
        unsigned int note_on_played; /*!< number of notes played: non null period */
        unsigned int note_dropped; /*!< number of notes dropped due to pool overflow */
    public:
        ardmonitor();
        ardmonitor(std::ostream &output);
        /*!
         * Member called when a note-on signal is received.
         * \param pin the output pin on which the pulse will be sent.
         * \param note the midi code for the note.
         * \param period the period between two motor steps.
         */
        void note_on_signal(int pin, int note, int period);
        /*!
         * Member called when a note-off signal is received.
         * \param pin the output pin which will stop sending pulses.
         */
        void note_off_signal(int pin);
        /*!
         * Member called when a message is sent over serial.
         * Will output only in debug mode.
         * \param message the message sent.
         */
        void serial_send_signal(std::vector<char> message);
        /*!
         * Member called when pool is full and note-on signal
         * can't be played.
         * Will output only in debug mode.
         * \param note the midi note concerned.
         */
        void pool_note_drop(int note);
        /*!
         * Output number of played notes, signals received and
         * notes dropped if any.
         */
        void print_stats();
};
#endif
