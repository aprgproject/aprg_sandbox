#pragma once

#include <BtsLogPrint.hpp>
#include <BtsLogSorterConfiguration.hpp>
#include <BtsPrintReaderWithRollback.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <fstream>
#include <LargeSorter/AlbaLargeSorter.hpp>
#include <set>
#include <string>

namespace tcomToolsBackend
{

class BtsLogSorter
{
public:
    BtsLogSorter(BtsLogSorterConfiguration const& configuration);
    void processDirectory(std::string const& directoryPath);
    void processFile(std::string const& filePath);
    void saveLogsToOutputFile(std::string const& outputPath);

    double getTotalSizeToBeRead();
    double getTotalSizeToBeRead(std::set<std::string> listOfFiles);
private:
    std::string getPathOfLogWithoutPcTime(std::string const& directory, std::string const& name) const;
    void openStartupLogsIfNeeded();    void addStartupLogsOnSorterWithPcTime();
    void writeLogsWithoutPcTimeToOutputFile(std::ofstream & outputLogFileStream);
    void separateLogsWithoutPcTimeIntoDifferentFiles();
    void writeLogsWithPcTimeToOutputFile(std::ofstream & outputLogFileStream);
    void addPrintsFromFileReaderToSorterWithoutPcTime(BtsPrintReaderWithRollback & fileReader);
    void writePrintsFromFileReaderBeforeThisPrint(BtsPrintReaderWithRollback & fileReader, BtsLogPrint const& logPrint, std::ofstream & outputLogFileStream);
    void bufferPrintAndWrite(BtsLogPrint const& logPrint, std::ofstream & outputLogFileStream);
    void writeLastPrint(std::ofstream & outputLogFileStream);
    void deleteFilesInDirectory(std::string const& directoryOfLogs) const;
    alba::AlbaGrepStringEvaluator m_evaluator;
    alba::AlbaLargeSorter<BtsLogPrint> m_sorterWithPcTime;    alba::AlbaLargeSorter<BtsLogPrint> m_sorterWithoutPcTime;
    std::string m_directoryOfLogsWithoutPcTime;
    std::string m_pathOfStartupLog;
    alba::AlbaOptional<std::ofstream> m_startupLogStreamOptional;
    BtsLogPrint m_currentPrintToWrite;
    std::set<std::string> m_foundHardwareAddresses;
};
}