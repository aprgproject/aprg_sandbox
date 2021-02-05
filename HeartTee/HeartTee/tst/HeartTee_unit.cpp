#include <HeartTee.hpp>
#include <SerialPort.hpp>
#include <unistd.h>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;
/*
TEST(SampleTest, DISABLED_SampleTest1)
{
    unsigned char buffer[100];
    SerialPort serialPort;
    serialPort.openSerial();
    while(serialPort.getFd() >= 0)
    {
        serialPort.readSerial(buffer, sizeof(buffer));
        cout<<"Bytes read: "<<<std::dec<<serialPort.getBytesRead();
        for(int i=0; i<serialPort.getBytesRead(); i++)
        {
            cout<<"["<<std::hex<<(int)buffer[i]<<"]";
        }
        cout<<endl;
        usleep(1000);
    }
}
*/
TEST(SampleTest, ProcessTest)
{
    HeartTee heartTee;
    unsigned char buffer1[100] = {0x0, 0x80, 0x7b, 0x1, 0x0, 0x80, 0x7a, 0x1, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0xf4, 0x1, 0x0, 0x0};
    heartTee.setDataManually(buffer1, 20);
    heartTee.transferDataFromReadToProcess();
    heartTee.processData();
    heartTee.printDatabase();

    unsigned char buffer2[100] = {0xce, 0x0, 0x7d, 0x1, 0x21, 0x0, 0x7a, 0x1};
    heartTee.setDataManually(buffer2, 8);
    heartTee.transferDataFromReadToProcess();
    heartTee.processData();
    heartTee.printDatabase();

    unsigned char buffer3[100] = {0x3a, 0x0, 0x7a, 0x1, 0x38, 0x0, 0x7a, 0x1};
    heartTee.setDataManually(buffer3, 8);
    heartTee.transferDataFromReadToProcess();
    heartTee.processData();
    heartTee.printDatabase();

    unsigned char buffer4[100] = {0x0, 0x80, 0x7b, 0x1, 0x0, 0x80, 0x7a, 0x1, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0xf4, 0x1, 0x0, 0x0};
    heartTee.setDataManually(buffer4, 20);
    heartTee.transferDataFromReadToProcess();
    heartTee.processData();
    heartTee.printDatabase();
}
