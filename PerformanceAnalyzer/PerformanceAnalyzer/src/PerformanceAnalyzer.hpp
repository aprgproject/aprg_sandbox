#pragma once

#include <string>

#include <Optional/AlbaOptional.hpp>
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
        void saveNbccId(std::string const& lineInLogs);
        void saveCrnccId(std::string const& lineInLogs);
        void saveTransactionId(std::string const& lineInLogs);
        int getNbccId(std::string const& lineInLogs) const;
        int getCrnccId(std::string const& lineInLogs) const;
        int getTransactionId(std::string const& lineInLogs) const;
    };
    struct BtsLogDelay
    {
        AlbaOptional<tcomToolsBackend::BtsLogTime> startTimeOptional;
        AlbaOptional<tcomToolsBackend::BtsLogTime> endTimeOptional;
    };

public:
    PerformanceAnalyzer();
    void setFileForRawDataDump(std::string const& rawDataPath);
    void logLineInRawDataFile(std::string const& line);
    void logStringInRawDataFile(std::string const& line);
    std::string extract(std::string const& inputPath) const;
    std::string combineAndSort(std::string const& inputPath) const;
    void processFileForMsgQueuingTime(std::string const& filePath);
    void processFileForRlSetupDelayInRlh(std::string const& filePath);
    void processFileForRlDeletionDelayInRlh(std::string const& filePath);
    void processFileForRlSetupDelayInTupcWithSymonKnife(std::string const& filePath);
    void processFileForRlSetupDelayInTupcWithSymonKnifeForFtm(std::string const& filePath);
    void processFileForFtmFcmWireshark(std::string const& filePath);
    void processFileForTopLogs(std::string const& filePath);

    int getDelayTimeInUs(tcomToolsBackend::BtsLogTime const& endTime, tcomToolsBackend::BtsLogTime const& startTime) const;
    int getDelayTimeInMinutes(tcomToolsBackend::BtsLogTime const& endTime, tcomToolsBackend::BtsLogTime const& startTime) const;

private:
    std::string m_extractGrepCondition;
    tcomToolsBackend::BtsLogSorterConfiguration m_sorterConfiguration;
    alba::AlbaOptional<std::ofstream> m_RawDataFileOptional;
};

}
