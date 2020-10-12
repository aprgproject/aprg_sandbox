#pragma once

#include <AlbaOptional.hpp>
#include <BtsLogTime.hpp>
#include <fstream>
#include <map>
#include <string>

using alba::AlbaOptional;
using std::string;
using tcomToolsBackend::BtsLogTime;

namespace alba
{

struct BtsLogDelay
{
    AlbaOptional<BtsLogTime> startTimeOptional;
    AlbaOptional<BtsLogTime> endTimeOptional;
};

struct UniqueId
{
    UniqueId()
        : crnccId(0)
        , nbccId(0)
        , transactionId(0)
    {}
    int crnccId;
    int nbccId;
    int transactionId;
    bool operator <(UniqueId const& uniqueId) const
    {
        if(crnccId!=uniqueId.crnccId)
        {
            return crnccId<uniqueId.crnccId;
        }
        if(nbccId!=uniqueId.nbccId)
        {
            return nbccId<uniqueId.nbccId;
        }
        return transactionId<uniqueId.transactionId;
    }
};

struct WireSharkDelay
{
    AlbaOptional<double> startTimeOptional;    AlbaOptional<double> endTimeOptional;
};

class WireSharkLogReader
{
public:
    WireSharkLogReader();
    WireSharkLogReader(string const pathOfOutputFile);
    void processDirectoryForWireSharkDelay(string const& directoryPath);
    void processFileForWireSharkDelay(string const& filePath);
    void processFileForBtsDelayForRlh(string const& filePath);
    void processFileForBtsDelayForMikhailKnife(string const& filePath);
    void processFileForBtsDelayForGrm(string const& filePath);
    double getWireSharkTime(string const& lineInLogs) const;
    string getNumberAfterThisString(string const& mainString, string const& stringToSearch) const;
    double getComputedAverageDelay() const;private:
    std::ofstream m_outputStream;
    double m_totalDelay;
    int m_count;
    std::map<int, WireSharkDelay> m_wireSharkDelays;
    std::map<UniqueId, BtsLogDelay> m_btsLogDelays;
    std::map<int, BtsLogDelay> m_btsLogDelaysGrm;
};

}//namespace alba