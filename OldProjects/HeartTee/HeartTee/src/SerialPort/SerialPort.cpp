#include <SerialPort.hpp>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int SerialPort::set_interface_attribs (int speed, int parity)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (m_fd, &tty) != 0)
    {
        printf ("error %d from tcgetattr", errno);
        return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (m_fd, TCSANOW, &tty) != 0)
    {
        printf("error %d from tcsetattr", errno);
        return -1;
    }
    return 0;
}

void SerialPort::set_blocking (int should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (m_fd, &tty) != 0)
    {
        printf("error %d from tggetattr", errno);
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (m_fd, TCSANOW, &tty) != 0)
        printf("error %d setting term attributes", errno);
}

void SerialPort::openSerial()
{
#define PORTNAME "/dev/ttyACM0"
    m_fd  = open (PORTNAME, O_RDWR | O_NOCTTY | O_SYNC);
    if (m_fd < 0)
    {
        printf("error %d opening %s: %s", errno, PORTNAME, strerror (errno));
        return;
    }

    set_interface_attribs (B1000000, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (0);                // set no blocking
#undef PORTNAME
}

void SerialPort::closeSerial()
{
    close(m_fd);
}

void SerialPort::writeSerial(unsigned char* buf, unsigned size)
{
    write(m_fd, buf, size);           // send 7 character greeting
    usleep ((size + 25) * 100);             // sleep enough to transmit the 7 plus
    // receive 25:  approx 100 uS per char transmit
}

void SerialPort::readSerial(unsigned char* buf, unsigned size)
{
    m_bytesRead = read (m_fd, buf, size);  // read up to 100 characters if ready to read
    /*cout<<"Bytes read: "<<std::dec<<getBytesRead();
    for(int i=0; i<getBytesRead(); i++)
    {
        cout<<"["<<std::hex<<(int)buf[i]<<"]";
    }
    cout<<"\n";*/
}

int SerialPort::getFd()
{
    return m_fd;
}

int SerialPort::getBytesRead()
{
    return m_bytesRead;
}
