#pragma once

#include <Common/Optional/AlbaOptional.hpp>
#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <fstream>
#include <map>
#include <string>

using alba::AlbaOptional;
using wcdmaToolsBackend::BtsLogTime;

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
    AlbaOptional<double> startTimeOptional;
    AlbaOptional<double> endTimeOptional;
};

class BtsLogAnalyzer
{
public:
    BtsLogAnalyzer();
    BtsLogAnalyzer(std::string const& pathOfOutputFile);
    void processFileForToCountUsersWithTracing(std::string const& filePath);
    void processDirectoryForWireSharkDelay(std::string const& directoryPath);
    void processFileForWireSharkDelay(std::string const& filePath);
    void processFileForMsgQueuingTime(std::string const& filePath);
    void processFileForBtsDelayForRlh(std::string const& filePath);
    void processFileForBtsDelayForRlDeletion(std::string const& filePath);
    void processFileForBtsDelayForMikhailKnife(std::string const& filePath);
    void processFileForBtsDelayForGrm(std::string const& filePath);
    double getWireSharkTime(std::string const& lineInLogs) const;
    std::string getNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch) const;
    double getComputedAverageDelay() const;
private:
    std::ofstream m_outputStream;
    double m_totalDelay;
    int m_count;
    std::map<int, WireSharkDelay> m_wireSharkDelays;
    std::map<UniqueId, BtsLogDelay> m_btsLogDelays;
    std::map<int, BtsLogDelay> m_btsLogDelaysGrm;
};

}//namespace alba
