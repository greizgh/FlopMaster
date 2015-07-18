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
#include "monitor.hpp"
#include "fm_config.h"
#include <iostream>
#include <iomanip>
#include <vector>
ardmonitor::ardmonitor(std::ostream &output) : note_on_played(0), note_on_received(0), note_off_received(0), outpt(output)
{
}
void ardmonitor::note_off_signal(int pin)
{
    note_off_received++;
    if(fm_DEBUG){
        outpt<<"[Note-Off] pin: "<<pin<<std::endl;
    }
}
void ardmonitor::note_on_signal(int pin, int note, int period)
{
    note_on_received++;
    if(fm_DEBUG){
        outpt<<"[Note-On] pin: "<<pin<<", note: "<<note<<", period: "<<period<<std::endl;
    }
    if (period!=0) note_on_played++;
}
void ardmonitor::print_stats()
{
    outpt<<"Received "<<note_on_received<<" note-on signals."<<std::endl;
    outpt<<"Received "<<note_off_received<<" note-off signals."<<std::endl;
    if(note_dropped>0)
        outpt<<"Dropped "<<note_dropped<<" notes due to pool overflow."<<std::endl;
    /*
     * No more used, since we have periods from C0 to B4
     *outpt<<"Really played "<<note_on_played<<" notes."<<std::endl;
     *if(note_on_received>0)
     *{
     *    double ratio=(float)note_on_played/(float)note_on_received;
     *    ratio= (int)(ratio*100);
     *    outpt<<"Played "<<ratio<<"% of total notes."<<std::endl;
     *}
     */
}
void ardmonitor::serial_send_signal(std::vector<char> message)
{
    if(message.size()>=3 && fm_DEBUG)
    {
        outpt<<"Sent: "<<std::showbase<<std::hex<<(unsigned int)(unsigned char)(message[0])<<", "<<(unsigned int)(unsigned char)(message[1])<<", "<<(unsigned int)(unsigned char)(message[2])<<std::dec<<std::endl;
    }
    if(message[0]==100)
        outpt<<"Sent reset signal"<<std::endl;
}
void ardmonitor::pool_note_drop(int note)
{
    note_dropped++;
    if(fm_DEBUG)
        outpt<<"[Pool] overflow, note dropped: "<<note<<std::endl;
}
