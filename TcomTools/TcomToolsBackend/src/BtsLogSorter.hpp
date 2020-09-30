#pragma once

#include <BtsLogPrint.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <fstream>
#include <LargeSorter/AlbaLargeSorter.hpp>
#include <set>
#include <string>

using std::ifstream;
using std::ofstream;
using std::set;
using std::string;

namespace tcomToolsBackend
{

class BtsLogFileReaderWithRollback
{
public:
    bool isGood() const;
    BtsLogPrint getPrint();
    void rollBackGetPrint();
    void openIfNeeded(string const& filePath);
private:
    bool m_isGood;
    bool m_isPreviousPrintValid;
    BtsLogPrint m_previousPrint;
    ifstream m_inputStream;
};

class BtsLogSorter
{
public:
    BtsLogSorter(
            string const& condition,
            alba::AlbaLargeSorterConfiguration const& mainConfiguration,
            alba::AlbaLargeSorterConfiguration const& configurationWithoutPcTime,
            string const& pathOfLogsWithoutPcTime);
    void processDirectory(string const& directoryPath);
    void processFile(string const& filePath);
    void saveAllToOutputFile(string const& outputPath);

private:
    void saveSortedLogsWithoutPcTime(ofstream & outputLogFileStream);
    void saveSortedLogsWithoutPcTimeIntoDifferentFiles();
    void mergePrintsAndSaveToOutputFile(string const& outputPath);
    void addPrintsFromFileReaderToSorterWithoutPcTime(BtsLogFileReaderWithRollback & fileReader);
    void writePrintsFromFileReaderBeforeThisPrint(BtsLogFileReaderWithRollback & fileReader, BtsLogPrint const& logPrint, ofstream & outputLogFileStream);
    void bufferAndWritePrint(BtsLogPrint const& logPrint, ofstream & outputLogFileStream);
    void writeLastPrintIfNeeded(ofstream & outputLogFileStream);
    string getPathOfLogWithoutPcTime(string const& directory, string const& name) const;
    void deleteFilesInDirectoryOfLogsWithoutPcTime() const;
    alba::AlbaGrepStringEvaluator m_evaluator;
    alba::AlbaLargeSorter<BtsLogPrint> m_sorterWithPcTime;
    alba::AlbaLargeSorter<BtsLogPrint> m_sorterWithoutPcTime;
    BtsLogPrint m_notYetPrintedPrint;
    string m_directoryOfLogsWithoutPcTime;
    set<string> m_foundHardwareAddresses;
};

}
