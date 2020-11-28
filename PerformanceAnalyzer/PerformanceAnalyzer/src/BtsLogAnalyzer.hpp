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
    using LogTime = alba::AlbaOptional<tcomToolsBackend::BtsLogTime>;
    using LogTimePair = std::pair<LogTime, LogTime>;
    using LogTimePairs = std::map<alba::UserIdentifiers, LogTimePair>;

    BtsLogAnalyzer();
    void clear();
    void processFileWithSortedPrints(std::string const& pathOfBtsLog);

private:
    void saveQueueingTime(std::string const& lineInLogs, std::ofstream& messageQueueingTimeFileStream);
    void saveRlhSetupTime(LogTimePairs& rlSetupLogTimePairs, std::string const& lineInLogs, std::ofstream& rlSetupTimeFileStream);
    void saveRlhDeletionTime(LogTimePairs& rlDeletionLogTimePairs, std::string const& lineInLogs, std::ofstream& rlDeletionTimeFileStream);
    void saveHeadersOfCsvFiles(std::ofstream& messageQueueingTimeFileStream, std::ofstream& rlSetupTimeFileStream, std::ofstream& rlDeletionTimeFileStream);
    void setLogTime(LogTime& logTime, std::string const& lineInLogs);
    double getTotalMicroseconds(tcomToolsBackend::BtsLogTime const& btsLogTime) const;
    DataCollection<unsigned int> m_messageQueueingTime;
    DataCollection<unsigned int> m_rlhRlSetupLatency;
    DataCollection<unsigned int> m_rlhRlDeletionLatency;
};

}
