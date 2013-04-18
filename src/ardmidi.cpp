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
#include "ardmidi.hpp"
#include <vector>
ardmidi::ardmidi(std::vector<unsigned char> *message) :  msg_status(midistatus::UNKNOWN)
{
    if(message->size()>=3)
    {
        note = message->at(1);
        velocity = message->at(2);
    }
    unsigned char status = message->at(0);
    if (status > 127 && status < 144)//note off
    {
        channel = status - 127;
        msg_status = midistatus::NOTE_OFF;
    }
    else if (status>143 && status<160)//note on
    {
        channel = status - 143;
        if(velocity==0)
            msg_status = midistatus::NOTE_OFF;
        else
            msg_status = midistatus::NOTE_ON;
    }
}
int ardmidi::get_note() const
{
    return note;
}
int ardmidi::get_channel() const
{
    return channel;
}
int ardmidi::get_velocity() const
{
    return velocity;
}
midistatus::signal ardmidi::get_status() const
{
    return msg_status;
}
