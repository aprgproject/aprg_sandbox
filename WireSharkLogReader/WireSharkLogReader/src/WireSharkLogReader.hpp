#pragma once

#include <AlbaOptional.hpp>
#include <fstream>
#include <map>
#include <string>

using alba::AlbaOptional;
using std::string;

namespace alba
{

struct WireSharkDelay
{
    AlbaOptional<double> startTimeOptional;
    AlbaOptional<double> endTimeOptional;
};

class WireSharkLogReader
{
public:
    WireSharkLogReader();
    WireSharkLogReader(string const pathOfOutputFile);
    void processDirectory(string const& directoryPath);
    void processFile(string const& filePath);
    double getWireSharkTime(string const& lineInLogs) const;
    string getNumberAfterThisString(string const& mainString, string const& stringToSearch) const;
    double getComputedAverageDelay() const;
private:
    std::ofstream m_outputStream;
    double m_totalDelay;
    int m_count;
    std::map<int, WireSharkDelay> m_delays;
};

}//namespace alba
