#pragma once

#include <SerialPort.hpp>
#include <SqlConnect.hpp>

#include <ctime>
#include <vector>

namespace alba {

struct HeartTeeEcgPulse {
    HeartTeeEcgPulse(int ecg, int pulse) : m_ecg(ecg), m_pulse(pulse) {}
    int m_ecg;
    int m_pulse;
};

struct HeartTeeData {
    HeartTeeData(time_t timeDate, int milliSecond, int ecg, int pulse) {
        m_timeDate = timeDate;
        m_milliSecond = milliSecond;
        m_ecg = ecg;
        m_pulse = pulse;
    }
    time_t m_timeDate;
    int m_milliSecond;
    int m_ecg;
    int m_pulse;
};

class HeartTee {
public:
    HeartTee();
    ~HeartTee();
    void resetTime();
    void incrementTime();
    void startRun();
    void setDataManually(unsigned char* buf, unsigned size);
    void setDataFromSerial();
    void transferDataFromReadToProcess();
    void processData();
    void printDatabase();
    void saveToSql();

private:
    time_t m_timeStamp;
    int m_sfn;
    int m_numberOfSamples;
    int m_numberOfBytesRead;
    int m_numberOfBytesLeftInProcessBuffer;
    bool m_process_isStarting;
    bool m_process_isStarted;
    int m_process_state;
    int m_process_currentEcg;
    int m_process_currentPulse;
    int m_process_indicatorCount;
    int m_process_indicatorCount2;
    int m_pulseCount;
    int m_pulseTime;
    unsigned char m_readBuffer[1000];
    unsigned char m_processBuffer[2000];
    SerialPort m_serialPort;
    std::vector<HeartTeeData> m_database;
    std::vector<HeartTeeData> m_databaseComplete;
    std::vector<HeartTeeEcgPulse> m_dataPerSecond;
    SqlConnect m_sqlConnect;
};

}  // namespace alba
