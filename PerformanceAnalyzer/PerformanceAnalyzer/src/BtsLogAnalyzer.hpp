#pragma once

#include <DataCollection.hpp>
#include <Optional/AlbaOptional.hpp>
#include <UserIdentifiers.hpp>
#include <BtsLogTime.hpp>

#include <fstream>
#include <map>
#include <string>

namespace alba
{

class BtsLogAnalyzer
{

public:
    enum class LogType
    {
        RlSetup,
        RlDeletion
    };
    using LogTime = alba::AlbaOptional<tcomToolsBackend::BtsLogTime>;
    using LogTimePair = std::pair<LogTime, LogTime>;
    using LogTimePairs = std::map<alba::UserIdentifiers, LogTimePair>;
    BtsLogAnalyzer();
    void clear();
    void processFileWithSortedPrints(std::string const& pathOfBtsLog);
    void printAllCollectedData() const;

private:
    void saveQueueingTime(std::string const& lineInLogs, std::ofstream& messageQueueingTimeFileStream);    void saveRlhSetupTime(std::string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs, std::ofstream& rlSetupTimeFileStream);
    void saveRlhDeletionTime(std::string const& lineInLogs, LogTimePairs& rlDeletionLogTimePairs, std::ofstream& rlDeletionTimeFileStream);
    void setFirstLogTimeInPair(std::string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const;
    void setSecondLogTimeInPair(std::string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const;
    void computeLatencyAndUpdateIfLogTimePairIsValid(LogType const logType, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs, std::ofstream& csvFileStream);
    void initializeCsvFileStreams(std::ofstream& messageQueueingTimeFileStream, std::ofstream& rlSetupTimeFileStream, std::ofstream& rlDeletionTimeFileStream) const;
    void setPrecisionOfFileStreams(std::ofstream& messageQueueingTimeFileStream, std::ofstream& rlSetupTimeFileStream, std::ofstream& rlDeletionTimeFileStream) const;
    void saveHeadersOnCsvFiles(std::ofstream& messageQueueingTimeFileStream, std::ofstream& rlSetupTimeFileStream, std::ofstream& rlDeletionTimeFileStream) const;    void saveMessageQueueingTimeToCsvFile(std::string const& lineInLogs, unsigned int const messageQueueingTime, std::ofstream& csvFileStream) const;
    void saveUserIndentifierAndLatencyToCsvFile(UserIdentifiers const& userIdentifiers, double const latencyInMicroseconds, std::ofstream& csvFileStream) const;
    void setLogTimeIfNeeded(std::string const& lineInLogs, LogTime& logTime) const;
    double getTotalMicroseconds(tcomToolsBackend::BtsLogTime const& btsLogTime) const;
    DataCollection<double> m_messageQueueingTime;
    DataCollection<double> m_rlhRlSetupLatency;
    DataCollection<double> m_rlhRlDeletionLatency;
};

}