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
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
int const ardflop::ARD_RESOLUTION = 40;
unsigned short const ardflop::microperiods[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    30578, 28861, 27242, 25713, 24270, 22909, 21622, 20409, 19263, 18182, 17161, 16198, //C1 - B1
    15289, 14436, 13621, 12856, 12135, 11454, 10811, 10205, 9632, 9091, 8581, 8099, //C2 - B2
    7645, 7218, 6811, 6428, 6068, 5727, 5406, 5103, 4816, 4546, 4291, 4050, //C3 - B3
    3823, 3609, 3406, 3214, 3034, 2864, 2703, 2552, 2408, 2273, 2146, 2025, //C4 - B4
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

ardflop::ardflop(const std::string PortName) : devname(PortName), ios(), serial(ios, devname), ardmon()
{
    int currentperiod[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (not serial.is_open())
    {
        std::cerr << "Failed to open serial port" << std::endl;
        return;
    }
    boost::asio::serial_port_base::baud_rate rate(500000);
    serial.set_option(rate);
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
        send(pin, 0);
        currentperiod[status -128] = 0;
    }
    else if (status>143 && status<160)//note on
    {
        char pin = (char)(2*(status-143));
        unsigned short period = microperiods[(int)(msg->at(1))]/(2*ARD_RESOLUTION);
        if (msg->at(2)==0)//zero velocity event
        {
            ardmon.note_off_signal(pin);
            send(pin, 0);
            currentperiod[status-144]=0;
        }
        else
        {
            ardmon.note_on_signal(pin, msg->at(1), period);
            send(pin, period);
            currentperiod[status-144]=period;
        }
    }
}
ardflop::~ardflop()
{
    reset();
    serial.close();
    ardmon.print_stats();
}
void ardflop::handler(const boost::system::error_code& error)
{
    if(error)
        std::cerr<<error.message()<<std::endl;
}
void ardflop::send(char pin, unsigned short period)
{
    char p1 = (char)(period & 0x00ff);
    char p2 = (char)(period & 0xff00);
    char msg[]={pin, p1, p2};
    //boost::asio::write(serial, boost::asio::buffer(msg, sizeof(msg)));
    boost::asio::async_write(serial, boost::asio::buffer(msg, sizeof(msg)),boost::bind(&ardflop::handler,this,boost::asio::placeholders::error));
    ardmon.serial_send_signal(msg);
}
void ardflop::reset()
{
    char message[] = {100,0,0};
    boost::asio::write(serial, boost::asio::buffer(message, sizeof(message)));
    ardmon.serial_send_signal(message);
}
