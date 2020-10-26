#include "HeartTee.hpp"

#include <Fourier.hpp>

#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>

using namespace std;

namespace alba
{

HeartTee::HeartTee()
    : m_sfn(0)
    , m_numberOfSamples(0)
    , m_numberOfBytesRead(0)
    , m_numberOfBytesLeftInProcessBuffer(0)
    , m_process_isStarting(false)
    , m_process_isStarted(false)
    , m_process_state(0)
    , m_process_currentEcg(0)
    , m_process_currentPulse(0)
    , m_process_indicatorCount(0)
    , m_process_indicatorCount2(0)
    , m_pulseCount(0)
    , m_pulseTime(0)
{
    m_sqlConnect.deleteTableIfExist();
    m_sqlConnect.createTable();
    m_serialPort.openSerial();
}

HeartTee::~HeartTee()
{
    m_sqlConnect.deleteTableIfExist();
    m_serialPort.closeSerial();
}


void HeartTee::resetTime()
{
    m_timeStamp=time(0);
}

void HeartTee::incrementTime()
{
    m_timeStamp+=1;
    m_pulseTime++;
}

void HeartTee::startRun()
{
    resetTime();
    while(1)
    {
        setDataFromSerial();
        transferDataFromReadToProcess();
        processData();
        printDatabase();
        saveToSql();
    }
}

void HeartTee::setDataManually(unsigned char* buf, unsigned size)
{
    memcpy(m_readBuffer, buf, size);
    m_numberOfBytesRead = size;
}

void HeartTee::setDataFromSerial()
{
    m_serialPort.readSerial(m_readBuffer, sizeof(m_readBuffer));
    m_numberOfBytesRead = m_serialPort.getBytesRead();
}

void HeartTee::transferDataFromReadToProcess()
{
    memcpy(m_processBuffer+m_numberOfBytesLeftInProcessBuffer, m_readBuffer, m_numberOfBytesRead);
    m_numberOfBytesLeftInProcessBuffer = m_numberOfBytesLeftInProcessBuffer+m_numberOfBytesRead;
}

void HeartTee::processData()
{
    m_process_state=0;
    m_process_indicatorCount=0;
    m_process_indicatorCount2=0;

    for(int i=0; i<m_numberOfBytesLeftInProcessBuffer; i++)
    {
        m_process_isStarted = m_process_isStarted || m_process_isStarting;
        //cout<<"m_process_isStarting"<<m_process_isStarting<<"m_process_state"<<m_process_state<<"m_sfn"<<m_sfn<<"m_numberOfSamples"<<std::hex<<m_numberOfSamples<<"m_processBuffer[i]"<<std::hex<<(int)m_processBuffer[i]<<endl;
        if(m_process_isStarting)
        {
            if(m_process_state==0)
            {
                m_sfn = m_processBuffer[i];
            }
            else if(m_process_state==1)
            {
                m_sfn = m_processBuffer[i]<<8 | m_sfn;
            }
            else if(m_process_state==2)
            {
                m_sfn = m_processBuffer[i]<<16 | m_sfn;
            }
            else if(m_process_state==3)
            {
                m_sfn = m_processBuffer[i]<<24 | m_sfn;
            }
            else if(m_process_state==4)
            {
                m_numberOfSamples = m_processBuffer[i];
            }
            else if(m_process_state==5)
            {
                m_numberOfSamples = m_processBuffer[i]<<8 | m_numberOfSamples;
            }
            else if(m_process_state==6)
            {
                m_numberOfSamples = m_processBuffer[i]<<16 | m_numberOfSamples;
            }
            else if(m_process_state==7)
            {
                m_numberOfSamples = m_processBuffer[i]<<24 | m_numberOfSamples;
            }
            m_process_state++;
            if(m_process_state>=8)
            {
                m_process_isStarting=false;
                m_process_state=0;
                int totalSize = m_dataPerSecond.size();
                int count=0;
                for(HeartTeeEcgPulse const& ecgPulse : m_dataPerSecond)
                {
                    int currentMillisecond=(int)round((double)1000*count/totalSize);
                    int ecgTemp = ecgPulse.m_ecg;
                    int pulseTemp = ecgPulse.m_pulse;
                    if(ecgTemp==0x8000)
                    {
                        ecgTemp = 0;
                    }
                    if(pulseTemp==0x8000)
                    {
                        pulseTemp = 0;
                    }

                    m_database.emplace_back(m_timeStamp, currentMillisecond, ecgTemp, pulseTemp);
                    count++;
                }
                incrementTime();
                m_dataPerSecond.clear();
            }
        }
        else
        {
            if((unsigned char)m_processBuffer[i]==0xFF)
            {
                m_process_indicatorCount++;
                if(m_process_indicatorCount==4)
                {
                    m_process_isStarting=true;
                    m_process_state=0;
                    m_process_indicatorCount=0;
                    continue;
                }
            }
            else if((unsigned char)m_processBuffer[i]==0xFE)
            {
                m_process_indicatorCount2++;
                if(m_process_indicatorCount2==4)
                {
                    m_process_state=1;
                    m_process_indicatorCount2=0;
                    continue;
                }
            }
            else
            {
                m_process_indicatorCount=0;
                m_process_indicatorCount2=0;
            }

            if(m_process_state==1)
            {
                m_process_currentEcg = m_processBuffer[i];
                m_process_state++;
            }
            else if(m_process_state==2)
            {
                m_process_currentEcg = m_process_currentEcg | m_processBuffer[i]<<8;
                m_process_state++;
            }
            else if(m_process_state==3)
            {
                m_process_currentPulse = m_processBuffer[i];
                m_process_state++;
            }
            else if(m_process_state==4)
            {
                m_process_currentPulse = m_process_currentPulse | m_processBuffer[i]<<8;
                m_process_state++;
            }
            if(m_process_state>=5)
            {
                m_process_state=0;

                if(m_process_isStarted)
                {
                    if(m_process_currentEcg>0x8000 || m_process_currentPulse>0x8000)
                    {
                        cout<<"m_readBuffer"<<endl;
                        for(int j=0; j<m_numberOfBytesRead; j++)
                        {
                            cout<<"["<<std::hex<<(int)m_readBuffer[j]<<"]";
                        }
                        cout<<"m_processBuffer"<<endl;
                        for(int j=0; j<m_numberOfBytesLeftInProcessBuffer; j++)
                        {
                            cout<<"["<<std::hex<<(int)m_processBuffer[j]<<"]";
                        }
                        cout<<"m_process_currentEcg:"<<m_process_currentEcg<<" m_process_currentPulse:"<<m_process_currentPulse<<" i:"<<i<<endl;
                        exit(0);
                    }
                    m_dataPerSecond.emplace_back(m_process_currentEcg, m_process_currentPulse);
                }
            }
        }
    }
    m_numberOfBytesLeftInProcessBuffer=0;
}

void HeartTee::printDatabase()
{
    for(HeartTeeData const& data: m_database)
    {
        tm *ltm = localtime(&data.m_timeDate);
        cout<<"second:"<<ltm->tm_sec<<" m_milliSecond:"<<std::dec<<data.m_milliSecond<<" ecg:"<<std::hex<<data.m_ecg<<" m_pulse:"<<std::hex<<data.m_pulse<<endl;
    }
    /*for(HeartTeeEcgPulse const& dataPerSecond: m_dataPerSecond)
    {
        cout<<"ecg:"<<std::hex<<dataPerSecond.m_ecg<<" pulse:"<<std::hex<<dataPerSecond.m_pulse<<endl;
    }*/

}

void HeartTee::saveToSql()
{
    const int SQLMAXTABLESIZE=100000;
    const int HIGH_COUNT_ACCEPTABLE=20;
    const int HIGH_VALUE=400;
    if(m_database.size()>0)
    {
        if(m_sqlConnect.getTableSize()<=SQLMAXTABLESIZE )
        {
            int maxValue = m_database[0].m_ecg;
            int minValue = m_database[0].m_ecg;
            int highCount=0;
            int pulseCount=0;
            for(HeartTeeData const& database : m_database)
            {
                if(maxValue<database.m_ecg)
                {
                    maxValue=database.m_ecg;
                }
                if(minValue>database.m_ecg)
                {
                    minValue=database.m_ecg;
                }
                if(HIGH_VALUE>database.m_pulse)
                {
                    highCount++;
                }
                else
                {
                    if(highCount > HIGH_COUNT_ACCEPTABLE)
                    {
                        pulseCount++;
                    }
                    highCount=0;
                }
            }
            m_pulseCount+=pulseCount;
            int pulsePerMin = (int)((double)m_pulseCount*60/m_pulseTime);
            cout<<"pulsePerMin:"<<std::dec<<pulsePerMin<<" ecg amplitude:"<<std::dec<<maxValue-minValue<<endl;
            for(HeartTeeData const& database : m_database)
            {
                m_sqlConnect.write(database.m_timeDate, database.m_milliSecond, database.m_pulse, database.m_ecg, pulsePerMin, 0, maxValue-minValue);
            }
            m_database.clear();

        }
        else
        {
            cout << "SQL is full not saving any data" << endl;
        }
    }
}


}


