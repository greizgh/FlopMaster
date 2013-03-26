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
        //Report variables
        unsigned int note_on_received;
        unsigned int note_off_received;
        unsigned int note_on_played;
        //arduino relative members
        static const int microperiods[];
        static const int ARD_RESOLUTION;
        int currentperiod[16];
        void send(char pin, unsigned char period);

    public:
        ardflop(const std::string PortName);
        ~ardflop();
        void reset();
        void processmidi(std::vector<unsigned char> *msg);
};
#endif
