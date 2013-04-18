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
#ifndef ARDMIDI_H
#define ARDMIDI_H
#include <vector>
namespace midistatus
{
    enum signal {
        UNKNOWN,
        NOTE_ON,
        NOTE_OFF
    };
}
class ardmidi
{
    private:
        int note;
        int velocity;
        int channel;
        midistatus::signal msg_status;
    public:
        ardmidi(std::vector<unsigned char> *msg);
        int get_note() const;
        int get_velocity() const;
        int get_channel() const;
        midistatus::signal get_status() const;
};
#endif
