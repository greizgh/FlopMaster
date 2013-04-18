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
class ardmonitor
{
    private:
        std::ostream &outpt;
        //Report variables
        unsigned int note_on_received;
        unsigned int note_off_received;
        unsigned int note_on_played;
    public:
        ardmonitor();
        ardmonitor(std::ostream &output);
        void note_on_signal(int pin, int note, int period);
        void note_off_signal(int pin);
        void serial_send_signal(std::vector<char> message);
        void pool_note_drop(int note);
        void print_stats();
};
#endif
