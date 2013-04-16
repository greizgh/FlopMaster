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
#include "flopcom.hpp"
#include "monitor.hpp"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

flopcom::flopcom(const std::string PortName) : devname(PortName), ios(), serial(ios, devname), ardmon()
{
    if (not serial.is_open())
    {
        std::cerr << "Failed to open serial port" << std::endl;
        return;
    }
    boost::asio::serial_port_base::baud_rate rate(500000);
    serial.set_option(rate);
}
flopcom::~flopcom()
{
    reset();
    serial.close();
}
void flopcom::handler(const boost::system::error_code& error)
{
    if(error)
        std::cerr<<error.message()<<std::endl;
}
void flopcom::send(char message[])
{
    boost::asio::async_write(serial, boost::asio::buffer(message, sizeof(message)),boost::bind(&flopcom::handler,this,boost::asio::placeholders::error));
    ardmon.serial_send_signal(message);
}
void flopcom::play(char pin, unsigned short period)
{
    char p1 = (char)(period & 0x00ff);
    char p2 = (char)(period & 0xff00);
    char msg[]={pin, p1, p2};
    send(msg);
}
void flopcom::reset()
{
    char message[] = {100};
    send(message);
}
