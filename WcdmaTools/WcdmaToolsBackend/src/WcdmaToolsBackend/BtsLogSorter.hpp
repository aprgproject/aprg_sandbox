#pragma once

#include <Algorithm/Sort/LargeSorter/AlbaLargeSorter.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <WcdmaToolsBackend/BtsLogPrint.hpp>
#include <WcdmaToolsBackend/BtsLogSorterConfiguration.hpp>
#include <WcdmaToolsBackend/BtsPrintReaderWithRollback.hpp>

#include <fstream>
#include <set>
#include <string>

namespace wcdmaToolsBackend
{

class BtsLogSorter
{
public:
    BtsLogSorter(BtsLogSorterConfiguration const& configuration);
    void processDirectory(std::string const& directoryPath);
    void processFile(std::string const& filePath);
    void processLineInFile(std::string const& filename, std::string const& lineInFile);
    void saveLogsToOutputFile(std::string const& outputPath);

    double getTotalSizeToBeRead();
    double getTotalSizeToBeRead(std::set<std::string> const& listOfFiles);


private:
    void createTempDirectories() const;
    void deleteTempFilesAndDirectoriesOfOneDayOld() const;
    void deleteStartupLog() const;
    void deleteLogsWithoutPcTime() const;
    void saveLogToOutputFileIfAllHavePcTime(std::string const& outputPath);
    void saveLogToOutputFileIfNotAllHavePcTime(std::string const& outputPath);
    std::string getPathOfLogWithoutPcTimeBasedFromHardwareAddress(std::string const& directory, std::string const& hardwareAddress) const;
    void openStartupLogsIfNeeded();
    void addStartupLogsOnSorterWithPcTime();
    void writeLogsWithoutPcTimeToOutputFile(std::ofstream & outputLogFileStream);
    void separateLogsWithoutPcTimeIntoDifferentAddresses();
    void writeLogsWithPcTimeToOutputFile(std::ofstream & outputLogFileStream);
    void addPrintsFromReaderToSorterWithoutPcTime(BtsPrintReaderWithRollback & printReader);
    void writePrintsFromFileReaderBeforeThisPrint(BtsPrintReaderWithRollback & printReader, BtsLogPrint const& logPrint, std::ofstream & outputLogFileStream);
    void updateOrWriteCurrentPrint(BtsLogPrint const& logPrint, std::ofstream & outputLogFileStream);
    void writeLastPrint(std::ofstream & outputLogFileStream);
    void deleteFilesInDirectory(std::string const& directoryOfLogs) const;
    bool m_isFilterOn;
    alba::AlbaGrepStringEvaluator m_acceptedFilesGrepEvaluator;
    alba::AlbaGrepStringEvaluator m_filterGrepEvaluator;
    std::string m_pathOfAllTempFiles;
    std::string m_pathOfCurrentTempFiles;
    alba::algorithm::AlbaLargeSorter<BtsLogPrint> m_sorterWithPcTime;
    alba::algorithm::AlbaLargeSorter<BtsLogPrint> m_sorterWithoutPcTime;
    std::string m_directoryOfLogsWithoutPcTime;
    std::string m_pathOfStartupLog;
    std::optional<std::ofstream> m_startupLogStreamOptional;
    BtsLogPrint m_currentPrintToWrite;
    std::set<std::string> m_foundHardwareAddresses;
};

}
