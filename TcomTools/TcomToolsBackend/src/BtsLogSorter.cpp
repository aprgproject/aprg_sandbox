#include "BtsLogSorter.hpp"

#include <AlbaFileReader.hpp>
#include <iostream>
#include <map>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

using namespace alba;
using namespace std;

namespace tcomToolsBackend
{

BtsLogSorter::BtsLogSorter(BtsLogSorterConfiguration const& configuration)
    : m_evaluator(configuration.m_condition)
    , m_sorterWithPcTime(configuration.m_configurationWithPcTime)
    , m_sorterWithoutPcTime(configuration.m_configurationWithoutPcTime)
    , m_directoryOfLogsWithoutPcTime(configuration.m_pathOfLogsWithoutPcTime)
    , m_pathOfStartupLog(configuration.m_pathOfStartupLog)
{}

void BtsLogSorter::processDirectory(string const& directoryPath)
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaWindowsPathHandler(directoryPath).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        AlbaWindowsPathHandler filePathHandler(filePath);
        if(m_evaluator.evaluate(filePathHandler.getFile()))
        {
            processFile(filePathHandler.getFullPath());        }
    }
}

void BtsLogSorter::processFile(string const& filePath)
{
    openStartupLogsIfNeeded();
    AlbaWindowsPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFile()<<endl;

    ifstream inputLogFileStream(filePath);    AlbaFileReader fileReader(inputLogFileStream);
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
    }
}

void BtsLogSorter::saveLogsToOutputFile(string const& outputPath)
{
    addStartupLogsOnSorterWithPcTime();
    if(m_sorterWithPcTime.isEmpty())
    {
        ofstream outputLogFileStream(outputPath);
        saveLogsFromSorterToOutputFile(outputLogFileStream);
    }
    else
    {
        separateLogsWithoutPcTimeIntoDifferentFiles();
        mergeAndSaveAllLogs(outputPath);
        deleteFilesInDirectory(m_directoryOfLogsWithoutPcTime);
    }
    AlbaWindowsPathHandler directoryPathHandler(m_pathOfStartupLog);
    deleteFilesInDirectory(directoryPathHandler.getDirectory());
}
string BtsLogSorter::getPathOfLogWithoutPcTime(string const& directory, string const& name) const
{
    string filename = name.empty() ? "NoHardwareAddress" : name;
    return AlbaWindowsPathHandler(directory + R"(\)" + filename + R"(.log)").getFullPath();
}

void BtsLogSorter::openStartupLogsIfNeeded(){
    if(!m_startupLogStreamOptional)
    {
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
    while(printReader.isGood())
    {
        m_sorterWithPcTime.add(printReader.getPrint());
    }
}

void BtsLogSorter::saveLogsFromSorterToOutputFile(ofstream & outputLogFileStream)
{
    cout << "Save sorted logs without PC time." << endl;
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        bufferPrintAndWrite(logPrint, outputLogFileStream);
    });
    writeLastPrintIfNeeded(outputLogFileStream);
}

void BtsLogSorter::separateLogsWithoutPcTimeIntoDifferentFiles()
{
    cout << "Save sorted logs without PC time into different addresses." << endl;
    map<string, ofstream> filesWithoutPcTime;

    for(string hardwareAddress: m_foundHardwareAddresses)
    {
        filesWithoutPcTime[hardwareAddress].open(getPathOfLogWithoutPcTime(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        filesWithoutPcTime[logPrint.getHardwareAddress()] << logPrint << endl;
    });
}

void BtsLogSorter::mergeAndSaveAllLogs(string const& outputPath)
{
    cout << "Merge logs with and without PC time and save to output file." << endl;
    map<string, BtsPrintReaderWithRollback> filesWithoutPcTime;
    ofstream outputLogFileStream(outputPath);

    for(string hardwareAddress: m_foundHardwareAddresses)
    {
        filesWithoutPcTime[hardwareAddress].openIfNeeded(getPathOfLogWithoutPcTime(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    m_sorterWithPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        writePrintsFromFileReaderBeforeThisPrint(filesWithoutPcTime[logPrint.getHardwareAddress()], logPrint, outputLogFileStream);
        bufferPrintAndWrite(logPrint, outputLogFileStream);
    });
    for(auto & mapFilesPair: filesWithoutPcTime)
    {
        addPrintsFromFileReaderToSorterWithoutPcTime(mapFilesPair.second);
    }
    saveLogsFromSorterToOutputFile(outputLogFileStream);
}

void BtsLogSorter::addPrintsFromFileReaderToSorterWithoutPcTime(BtsPrintReaderWithRollback & printReader)
{
    while(printReader.isGood())
    {
        BtsLogPrint logPrintWithoutPcTime(printReader.getPrint());
        if(printReader.isGood())
        {
            m_sorterWithoutPcTime.add(logPrintWithoutPcTime);
        }
    }
}

void BtsLogSorter::writePrintsFromFileReaderBeforeThisPrint(BtsPrintReaderWithRollback & printReader, BtsLogPrint const& logPrint, ofstream & outputLogFileStream)
{
    while(printReader.isGood())
    {
        BtsLogPrint logPrintWithoutPcTime(printReader.getPrint());
        if(logPrintWithoutPcTime.getBtsTime() < logPrint.getBtsTime() || logPrintWithoutPcTime.getBtsTime() == logPrint.getBtsTime())
        {
            if(printReader.isGood())
            {
                bufferPrintAndWrite(logPrintWithoutPcTime, outputLogFileStream);
            }
        }
        else
        {
            printReader.rollBackGetPrint();
            break;
        }
    }
}

void BtsLogSorter::bufferPrintAndWrite(BtsLogPrint const& logPrint, ofstream & outputLogFileStream)
{
    if(m_notYetPrinted == logPrint)
    {
        m_notYetPrinted.updatePcTimeAndFileNameDetails(logPrint);
    }
    else
    {
        if(!m_notYetPrinted.getPrint().empty())
        {
            outputLogFileStream << m_notYetPrinted.getPrintWithAllDetails() << endl;
        }
        m_notYetPrinted = logPrint;
    }
}

void BtsLogSorter::writeLastPrintIfNeeded(ofstream & outputLogFileStream)
{
    outputLogFileStream << m_notYetPrinted.getPrintWithAllDetails() << endl;
    m_notYetPrinted = BtsLogPrint{};
}

void BtsLogSorter::deleteFilesInDirectory(string const& directoryOfLogs) const
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaWindowsPathHandler(directoryOfLogs).findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file: listOfFiles)
    {
        AlbaWindowsPathHandler(file).deleteFile();
    }
}
}
