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
#ifndef FLOPCOM_H
#define FLOPCOM_H
#include "monitor.hpp"
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
class flopcom
{
    private:
        ardmonitor ardmon;
        //Serial relative members
        const std::string devname;
        boost::asio::io_service ios;
        boost::asio::serial_port serial;
        void handler(const boost::system::error_code& error);
        void send(char message[]);
    public:
        flopcom(const std::string PortName);
        ~flopcom();
        void reset();
        void play(char pin, unsigned short period);
};
#endif
