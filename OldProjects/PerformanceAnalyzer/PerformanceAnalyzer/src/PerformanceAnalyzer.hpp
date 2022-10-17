#pragma once

#include <Common/Container/AlbaOptional.hpp>
#include <WcdmaToolsBackend/BtsLogSorterConfiguration.hpp>
#include <WcdmaToolsBackend/BtsLogTime.hpp>
#include <string>

namespace alba{

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
        void saveNbccId(std::string const& lineInLogs);
        void saveCrnccId(std::string const& lineInLogs);
        void saveTransactionId(std::string const& lineInLogs);
        int getNbccId(std::string const& lineInLogs) const;
        int getCrnccId(std::string const& lineInLogs) const;
        int getTransactionId(std::string const& lineInLogs) const;
    };
    struct BtsLogDelay
    {
        AlbaOptional<wcdmaToolsBackend::BtsLogTime> startTimeOptional;
        AlbaOptional<wcdmaToolsBackend::BtsLogTime> endTimeOptional;
    };

public:
    PerformanceAnalyzer();
    void setFileForRawDataDump(std::string const& rawDataPath);
    void logLineInRawDataFile(std::string const& line);
    void logStringInRawDataFile(std::string const& line);
    std::string extract(std::string const& inputPath) const;
    std::string combineAndSort(std::string const& inputPath) const;
    void processFileForMsgQueueingTime(std::string const& filePath);
    void processFileForRlSetupDelayInRlh(std::string const& filePath);
    void processFileForRlDeletionDelayInRlh(std::string const& filePath);
    void processFileForPeriodicCpuLogging(std::string const& filePath);
    void processFileForRlSetupDelayInTupcWithSymonKnife(std::string const& filePath);
    void processFileForRlSetupDelayInTupcWithSymonKnifeForFtm(std::string const& filePath);
    void processFileForFtmFcmWireshark(std::string const& filePath);
    void processFileForTopLogs(std::string const& filePath);
    void processFileForTopLogsMem(std::string const& filePath);
    void processFileForRlSetupPerSecond(std::string const& filePath);
    void processFileForTraceLog(std::string const& traceLogPath);
    void processDirectoryForTraceLog(std::string const& traceLogPath);

    int getDelayTimeInUs(wcdmaToolsBackend::BtsLogTime const& endTime, wcdmaToolsBackend::BtsLogTime const& startTime) const;
    int getDelayTimeInMinutes(wcdmaToolsBackend::BtsLogTime const& endTime, wcdmaToolsBackend::BtsLogTime const& startTime) const;

private:
    std::string m_extractGrepCondition;
    wcdmaToolsBackend::BtsLogSorterConfiguration m_sorterConfiguration;
    alba::AlbaOptional<std::ofstream> m_RawDataFileOptional;
};

}
