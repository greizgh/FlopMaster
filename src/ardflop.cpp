#include "ardflop.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
int const ardflop::ARD_RESOLUTION = 40;
int const ardflop::microperiods[] = {
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

ardflop::ardflop(const std::string PortName) : devname(PortName), ios(), serial(ios, devname)
{
    int currentperiod[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (not serial.is_open())
    {
        std::cerr << "Failed to open serial port" << std::endl;
        return;
    }
    boost::asio::serial_port_base::baud_rate rate(9600);
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
        send(pin, 0);
        currentperiod[status -128] = 0;
    }
    else if (status>143 && status<160)//note on
    {
        char pin = (char)(2*(status-143));
        int period = microperiods[(int)(msg->at(1))]/(2*ARD_RESOLUTION);
        if (msg->at(2)==0)//zero velocity event
        {
            send(pin, 0);
            currentperiod[status-144]=0;
        }
        else
        {
            send(pin, period);
            currentperiod[status-144]=period;
        }
    }
    /*else if (status>223 && status<240)//pitch bending
    {
        if(currentperiod[status-224]!=0)
        {
            char pin = (char)(2*(status-223));
            double pitchbend = (msg->at(2)<<8)+(msg->at(1));
            int period = currentperiod[status-224]/pow((pitchbend-8192)/8192,2);
            send(pin, period);
        }
    }*/
}
ardflop::~ardflop()
{
    reset();
    serial.close();
}
//const void ardflop::handler(const boost::system::error_code& error, std::size_t bytes_transfered)
//{
//}
void ardflop::send(char pin, unsigned char period)
{
    char p1 = (char)((period >> 8) & 0xff);
    char p2 = (char)(period & 0xff);
    char message[] = {pin, p1, p2};
    boost::asio::write(serial, boost::asio::buffer(message, sizeof(message)));
    //boost::asio::async_write(serial, boost::asio::buffer(message, sizeof(message)), handler);
}
void ardflop::reset()
{
    std::cout << "Resetting drives..." << std::endl;
    unsigned char message[] = {100,0,0};
    boost::asio::write(serial, boost::asio::buffer(message));
}
