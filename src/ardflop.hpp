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
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <vector>
class ardflop
{
    private:
        //Serial relative members
        const std::string devname;
        boost::asio::io_service ios;
        boost::asio::serial_port serial;
        void handler(const boost::system::error_code& error);
        //Report variables
        unsigned int note_on_received;
        unsigned int note_off_received;
        unsigned int note_on_played;
        //arduino relative members
        static const unsigned short microperiods[];
        static const int ARD_RESOLUTION;
        int currentperiod[16];
        void send(char pin, unsigned short period);

    public:
        ardflop(const std::string PortName);
        ~ardflop();
        void reset();
        void processmidi(std::vector<unsigned char> *msg);
};
#endif
