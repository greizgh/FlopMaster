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
//! Serial communication class
/*!
 * Flopcom handle serial communication with the microcontroller
 */
class flopcom
{
    private:
        ardmonitor ardmon;
        //Serial relative members
        const std::string devname;/*!< name of the serial port */
        boost::asio::io_service ios;
        boost::asio::serial_port serial;
        void handler(const boost::system::error_code& error);
        /*!
         * Send data over serial.
         * \param message data to be sent
         */
        void send(std::vector<char> message);
    public:
        flopcom(const std::string PortName);
        ~flopcom();
        /*!
         * Send a reset signal to the microcontroller.
         * Code send: 0x64.
         */
        void reset();
        /*!
         * Turn pin and period information into data
         * that can be sent through serial. Call flopcom::send()
         * \param pin the pin which will send pulse
         * \param period the period between two pulses
         */
        void play(char pin, unsigned short period);
};
#endif
