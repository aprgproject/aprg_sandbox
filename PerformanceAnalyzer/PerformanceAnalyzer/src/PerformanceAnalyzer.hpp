#pragma once

#include <string>

#include <AlbaOptional.hpp>
#include <BtsLogSorterConfiguration.hpp>
#include <BtsLogTime.hpp>

namespace alba
{

class PerformanceAnalyzer
{
private:
    struct UniqueUserId
    {
        UniqueUserId();
        UniqueUserId(std::string const& lineInLogs);
        int nbccId;
        int crnccId;
        int transactionId;
        bool operator <(UniqueUserId const& uniqueUserId) const;
        int getCrnccId(std::string const& lineInLogs) const;
    };
    struct BtsLogDelay
    {
        AlbaOptional<tcomToolsBackend::BtsLogTime> startTimeOptional;
        AlbaOptional<tcomToolsBackend::BtsLogTime> endTimeOptional;
    };

public:
    PerformanceAnalyzer();
    void setFileForRawDataDump(std::string const& rawDataPath);
    void logInRawDataFile(std::string const& line);
    std::string extract(std::string const& inputPath) const;
    std::string combineAndSort(std::string const& inputPath) const;
    void processFileForMsgQueuingTime(std::string const& filePath);
    void processFileForRlSetupDelayInRlh(std::string const& filePath);
    void processFileForRlDeletionDelayInRlh(std::string const& filePath);

private:
    std::string m_extractGrepCondition;
    tcomToolsBackend::BtsLogSorterConfiguration m_sorterConfiguration;
    alba::AlbaOptional<std::ofstream> m_RawDataFileOptional;
};

}