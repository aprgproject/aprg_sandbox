#include "BtsLogSorter.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <iostream>
#include <map>

using namespace alba;
using namespace std;

namespace alba
{

namespace ProgressCounters
{
extern double totalSizeToBeReadForCombine;
extern double totalSizeReadForCombine;
extern int writeProgressForCombine;
}

}

namespace tcomToolsBackend
{

BtsLogSorter::BtsLogSorter(BtsLogSorterConfiguration const& configuration)
    : m_evaluator(configuration.m_condition)
    , m_sorterWithPcTime(configuration.m_configurationWithPcTime)
    , m_sorterWithoutPcTime(configuration.m_configurationWithoutPcTime)
    , m_directoryOfLogsWithoutPcTime(configuration.m_pathOfLogsWithoutPcTime)
    , m_pathOfStartupLog(configuration.m_pathOfStartupLog)
{}

double BtsLogSorter::getTotalSizeToBeRead(set<string> listOfFiles)
{
    double totalFileSize(0);
    for(string const& filePath : listOfFiles)
    {
        AlbaLocalPathHandler filePathHandler(filePath);
        if(m_evaluator.evaluate(filePathHandler.getFile()))
        {
            totalFileSize += filePathHandler.getFileSizeEstimate();
        }
    }
    return totalFileSize;
}

void BtsLogSorter::processDirectory(string const& directoryPath)
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaLocalPathHandler(directoryPath).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    ProgressCounters::totalSizeToBeReadForCombine = getTotalSizeToBeRead(listOfFiles);
    for(string const& filePath : listOfFiles)
    {
        AlbaLocalPathHandler filePathHandler(filePath);
        if(m_evaluator.evaluate(filePathHandler.getFile()))
        {
            processFile(filePathHandler.getFullPath());
        }
    }
}

void BtsLogSorter::processFile(string const& filePath)
{
    openStartupLogsIfNeeded();
    AlbaLocalPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFile()<<endl;

    double previousTotalSize(ProgressCounters::totalSizeReadForCombine);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        BtsLogPrint logPrint(filePathHandler.getFile(), fileReader.getLineAndIgnoreWhiteSpaces());
        m_foundHardwareAddresses.emplace(logPrint.getHardwareAddress());
        if(logPrint.getPcTime().isEmpty())
        {
            m_sorterWithoutPcTime.add(logPrint);
        }
        else if(logPrint.getBtsTime().isStartup())
        {
            m_startupLogStreamOptional.getReference() << logPrint <<endl;
        }
        else
        {
            m_sorterWithPcTime.add(logPrint);
        }
        ProgressCounters::totalSizeReadForCombine = previousTotalSize + fileReader.getCurrentLocation();
    }
    ProgressCounters::totalSizeReadForCombine = previousTotalSize + filePathHandler.getFileSizeEstimate();
}

void BtsLogSorter::saveLogsToOutputFile(string const& outputPath)
{
    addStartupLogsOnSorterWithPcTime();
    if(m_sorterWithPcTime.isEmpty())
    {
        saveLogToOutputFileIfAllHavePcTime(outputPath);
    }
    else
    {
        saveLogToOutputFileIfNotAllHavePcTime(outputPath);
    }
    AlbaLocalPathHandler directoryPathHandler(m_pathOfStartupLog);
    deleteFilesInDirectory(directoryPathHandler.getDirectory());
}

void BtsLogSorter::saveLogToOutputFileIfAllHavePcTime(string const& outputPath)
{
    cout << "Save log to output file if all have pc time." << endl;
    ofstream outputLogFileStream(outputPath);
    writeLogsWithoutPcTimeToOutputFile(outputLogFileStream);
}

void BtsLogSorter::saveLogToOutputFileIfNotAllHavePcTime(string const& outputPath)
{
    cout << "Save log to output file if not all have pc time." << endl;
    ofstream outputLogFileStream(outputPath);
    separateLogsWithoutPcTimeIntoDifferentAddresses();
    writeLogsWithPcTimeToOutputFile(outputLogFileStream);
    writeLogsWithoutPcTimeToOutputFile(outputLogFileStream);
    deleteFilesInDirectory(m_directoryOfLogsWithoutPcTime);
}

string BtsLogSorter::getPathOfLogWithoutPcTimeBasedFromHardwareAddress(string const& directory, string const& hardwareAddress) const
{
    string filename = hardwareAddress.empty() ? "NoHardwareAddress" : hardwareAddress;
    return AlbaLocalPathHandler(directory + R"(\)" + filename + R"(.log)").getFullPath();
}
void BtsLogSorter::openStartupLogsIfNeeded()
{
    if(!m_startupLogStreamOptional)    {
        m_startupLogStreamOptional.createObjectUsingDefaultConstructor();
        m_startupLogStreamOptional.getReference().open(m_pathOfStartupLog, std::ios::ate|std::ios::app);
    }
}

void BtsLogSorter::addStartupLogsOnSorterWithPcTime()
{
    cout << "Add startup logs on sorter with PC time." << endl;
    m_startupLogStreamOptional.clear();
    BtsPrintReaderWithRollback printReader;
    printReader.openIfNeeded(m_pathOfStartupLog);
    double fileSize(AlbaLocalPathHandler(m_pathOfStartupLog).getFileSizeEstimate());
    while(printReader.isGood())
    {
        BtsLogPrint startupLogPrint(printReader.getPrint());
        if(!startupLogPrint.isEmpty())
        {
            m_sorterWithPcTime.add(startupLogPrint);
        }
        ProgressCounters::writeProgressForCombine = 25*printReader.getCurrentLocation()/fileSize;
    }}

void BtsLogSorter::writeLogsWithoutPcTimeToOutputFile(ofstream & outputLogFileStream)
{    cout << "Save sorted logs without PC time." << endl;
    unsigned long long printCount(0);
    unsigned long long size(m_sorterWithoutPcTime.getSize());
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        updateOrWriteCurrentPrint(logPrint, outputLogFileStream);
        ProgressCounters::writeProgressForCombine = 75 + (printCount++ * 25/size);
    });
    writeLastPrint(outputLogFileStream);
}

void BtsLogSorter::separateLogsWithoutPcTimeIntoDifferentAddresses()
{
    cout << "Save sorted logs without PC time into different addresses." << endl;
    map<string, ofstream> hardwareAddressToOutputSteamMap;

    for(string hardwareAddress: m_foundHardwareAddresses)
    {
        hardwareAddressToOutputSteamMap[hardwareAddress].open(getPathOfLogWithoutPcTimeBasedFromHardwareAddress(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    unsigned long long printCount(0);
    unsigned long long size(m_sorterWithoutPcTime.getSize());
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        hardwareAddressToOutputSteamMap[logPrint.getHardwareAddress()] << logPrint << endl;
        ProgressCounters::writeProgressForCombine = 25 + (printCount++ * 25/size);
    });
}
void BtsLogSorter::writeLogsWithPcTimeToOutputFile(ofstream & outputLogFileStream)
{
    cout << "Merge logs with and without PC time and save to output file." << endl;
    map<string, BtsPrintReaderWithRollback> hardwareAddressToReaderMap;
    for(string hardwareAddress: m_foundHardwareAddresses)
    {
        hardwareAddressToReaderMap[hardwareAddress].openIfNeeded(getPathOfLogWithoutPcTimeBasedFromHardwareAddress(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    unsigned long long printCount(0);
    unsigned long long size(m_sorterWithPcTime.getSize());
    m_sorterWithPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        writePrintsFromFileReaderBeforeThisPrint(hardwareAddressToReaderMap[logPrint.getHardwareAddress()], logPrint, outputLogFileStream);
        updateOrWriteCurrentPrint(logPrint, outputLogFileStream);
        ProgressCounters::writeProgressForCombine = 50 + (printCount++ * 25/size);
    });
    for(auto & hardwareAddressToReaderPair: hardwareAddressToReaderMap)
    {
        addPrintsFromReaderToSorterWithoutPcTime(hardwareAddressToReaderPair.second);
    }
}

void BtsLogSorter::addPrintsFromReaderToSorterWithoutPcTime(BtsPrintReaderWithRollback & printReader)
{
    while(printReader.isGood())
    {
        BtsLogPrint logPrintWithoutPcTime(printReader.getPrint());
        if(!logPrintWithoutPcTime.isEmpty())
        {
            m_sorterWithoutPcTime.add(logPrintWithoutPcTime);
        }    }
}

void BtsLogSorter::writePrintsFromFileReaderBeforeThisPrint(BtsPrintReaderWithRollback & printReader, BtsLogPrint const& logPrint, ofstream & outputLogFileStream){
    while(printReader.isGood())
    {
        BtsLogPrint logPrintWithoutPcTime(printReader.getPrint());
        if(logPrintWithoutPcTime.getBtsTime() < logPrint.getBtsTime() || logPrintWithoutPcTime.getBtsTime() == logPrint.getBtsTime())
        {
            if(!logPrintWithoutPcTime.isEmpty())
            {
                updateOrWriteCurrentPrint(logPrintWithoutPcTime, outputLogFileStream);
            }
        }
        else
        {
            printReader.rollBackPrint();
            break;
        }
    }
}

void BtsLogSorter::updateOrWriteCurrentPrint(BtsLogPrint const& logPrint, ofstream & outputLogFileStream)
{
    if(m_currentPrintToWrite == logPrint)
    {        m_currentPrintToWrite.updatePcTimeAndFileNameDetails(logPrint);
    }
    else
    {        if(!m_currentPrintToWrite.getPrint().empty())
        {
            outputLogFileStream << m_currentPrintToWrite.getPrintWithAllDetails() << endl;
        }
        m_currentPrintToWrite = logPrint;
    }
}

void BtsLogSorter::writeLastPrint(ofstream & outputLogFileStream)
{
    outputLogFileStream << m_currentPrintToWrite.getPrintWithAllDetails() << endl;
    m_currentPrintToWrite = BtsLogPrint{};
}

void BtsLogSorter::deleteFilesInDirectory(string const& directoryOfLogs) const
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaLocalPathHandler(directoryOfLogs).findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file: listOfFiles)
    {
        AlbaLocalPathHandler(file).deleteFile();
    }
}

}
