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
    //! Midi message type
    enum signal {
        UNKNOWN,/*!< Any message other than note-on/off */
        NOTE_ON,/*!< Note-on message */
        NOTE_OFF/*!< Note-off message */
    };
}
//! Small but convenient class to represent a midi event
class ardmidi
{
    private:
        int note;/*!< midi note code */
        int velocity;/*!< midi event velocity */
        int channel;/*!< midi channel */
        midistatus::signal msg_status;/*!< type of event */
    public:
        /*!
         * Constructor
         * \param msg pointer to a midi message as returned by RtMidi
         */
        ardmidi(std::vector<unsigned char> *msg);
        //! \return event's note if any, 0 otherwise
        int get_note() const;
        //! \return event's velocity if any, 0 otherwise
        int get_velocity() const;
        //! \return event's channel
        int get_channel() const;
        //! \return event's type
        midistatus::signal get_status() const;
};
#endif
