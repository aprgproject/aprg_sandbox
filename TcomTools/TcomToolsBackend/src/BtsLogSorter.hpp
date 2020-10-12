#pragma once

#include <BtsLogPrint.hpp>
#include <BtsLogSorterConfiguration.hpp>
#include <BtsPrintReaderWithRollback.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <fstream>
#include <LargeSorter/AlbaLargeSorter.hpp>
#include <set>
#include <string>

using std::ofstream;
using std::string;

namespace tcomToolsBackend
{

class BtsLogSorter
{
public:
    BtsLogSorter(BtsLogSorterConfiguration const& configuration);
    void processDirectory(string const& directoryPath);
    void processFile(string const& filePath);
    void saveLogsToOutputFile(string const& outputPath);

private:
    string getPathOfLogWithoutPcTime(string const& directory, string const& name) const;
    void openStartupLogsIfNeeded();
    void addStartupLogsOnSorterWithPcTime();
    void saveLogsFromSorterToOutputFile(ofstream & outputLogFileStream);
    void separateLogsWithoutPcTimeIntoDifferentFiles();
    void mergeAndSaveAllLogs(string const& outputPath);
    void addPrintsFromFileReaderToSorterWithoutPcTime(BtsPrintReaderWithRollback & fileReader);
    void writePrintsFromFileReaderBeforeThisPrint(BtsPrintReaderWithRollback & fileReader, BtsLogPrint const& logPrint, ofstream & outputLogFileStream);
    void bufferPrintAndWrite(BtsLogPrint const& logPrint, ofstream & outputLogFileStream);
    void writeLastPrintIfNeeded(ofstream & outputLogFileStream);
    void deleteFilesInDirectory(string const& directoryOfLogs) const;
    alba::AlbaGrepStringEvaluator m_evaluator;
    alba::AlbaLargeSorter<BtsLogPrint> m_sorterWithPcTime;
    alba::AlbaLargeSorter<BtsLogPrint> m_sorterWithoutPcTime;
    string m_directoryOfLogsWithoutPcTime;
    string m_pathOfStartupLog;
    alba::AlbaOptional<ofstream> m_startupLogStreamOptional;
    BtsLogPrint m_notYetPrinted;
    set<string> m_foundHardwareAddresses;
};

}
