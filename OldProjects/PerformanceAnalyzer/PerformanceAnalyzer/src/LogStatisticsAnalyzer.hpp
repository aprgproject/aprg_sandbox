#pragma once

#include <Common/Container/AlbaOptional.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WcdmaToolsBackend/BtsLogPrint.hpp>
#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace alba
{

struct LogDetails
{
     stringHelper::strings logStrings;
     unsigned int count;
     bool operator<(LogDetails const& logDetails) const;
     bool operator>(LogDetails const& logDetails) const;
     bool operator==(LogDetails const& logDetails) const;
};

class LogStatisticsAnalyzer
{

public:

    LogStatisticsAnalyzer();
    void saveDataToCsv(std::string const& csvPath);
    void saveLogDetailsToCsv(std::ofstream & outputCsvFileStream);
    void processFileWithSortedPrints(std::string const& pathOfBtsLog);

private:
    void analyzeLog(std::string const& lineInLogs);
    void addLogDetailsToCheckInInitialization(stringHelper::strings const& logStrings);
    void addLogDetailsToCheckInInitialization(std::string const& firstLogString, std::string const& secondLogString);
    void initializeLogDetailsToCheck();
    AlbaLocalPathHandler m_btsLogPathHandler;
    std::vector<LogDetails> m_logDetailsToCheck;
    unsigned int m_totalLinesFound;
    unsigned int m_totalLines;
};

}
