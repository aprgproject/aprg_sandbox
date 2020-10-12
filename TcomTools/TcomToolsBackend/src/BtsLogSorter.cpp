#include "BtsLogSorter.hpp"

#include <AlbaFileReader.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace alba;
using namespace std;

namespace tcomToolsBackend
{

bool BtsPrintReaderWithRollback::isGood() const
{
    return m_inputStream.good();
}

BtsLogPrint BtsPrintReaderWithRollback::getPrint()
{
    if(isGood())
    {
        if(m_isPreviousPrintValid)
        {
            m_isPreviousPrintValid = false;
            return m_previousPrint;
        }
        else
        {
            m_inputStream >> m_previousPrint;
            /*if(!isGood())
            {
                currentPrint = BtsLogPrint{};//clear
            }*/
            return m_previousPrint;
        }
    }
    return BtsLogPrint{};
}

void BtsPrintReaderWithRollback::rollBackGetPrint()
{
    if(m_isPreviousPrintValid)
    {
        cout<<"Double rollback of prints detected, possible print drop, please implement line put back in stream to avoid this."<<endl;
    }
    m_isPreviousPrintValid = true;
}

void BtsPrintReaderWithRollback::openIfNeeded(string const& filePath)
{
    if(!m_inputStream.is_open())
    {        m_inputStream.open(filePath);
    }
}
BtsLogSorter::BtsLogSorter(
        string const& condition,
        alba::AlbaLargeSorterConfiguration const& configurationWithPcTime,
        alba::AlbaLargeSorterConfiguration const& configurationWithoutPcTime,
        string const& pathOfLogsWithoutPcTime)
    : m_evaluator(condition)
    , m_sorterWithPcTime(configurationWithPcTime)
    , m_sorterWithoutPcTime(configurationWithoutPcTime)
{
    AlbaWindowsPathHandler pathHandlerOfLogsWithoutPcTime;
    pathHandlerOfLogsWithoutPcTime.inputPath(pathOfLogsWithoutPcTime);
    m_directoryOfLogsWithoutPcTime = pathHandlerOfLogsWithoutPcTime.getDirectory();
}

void BtsLogSorter::processDirectory(string const& directoryPath)
{
    AlbaWindowsPathHandler directoryPathHandler;
    directoryPathHandler.inputPath(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        AlbaWindowsPathHandler filePathHandler;
        filePathHandler.inputPath(filePath);
        if(m_evaluator.evaluate(filePathHandler.getFile()))
        {
            processFile(filePathHandler.getFullPath());
        }
    }
}

void BtsLogSorter::processFile(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler;
    filePathHandler.inputPath(filePath);
    cout<<"processFile: "<<filePathHandler.getFile()<<endl;

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
        else
        {
            m_sorterWithPcTime.add(logPrint);
        }
    }
}

void BtsLogSorter::saveLogsToOutputFile(string const& outputPath)
{
    if(m_sorterWithPcTime.isEmpty())
    {
        ofstream outputLogFileStream(outputPath);
        saveLogsFromSorterToOutputFile(outputLogFileStream);
    }
    else
    {
        separateLogsWithoutPcTimeIntoDifferentFiles();
        mergeAndSaveAllLogs(outputPath);
        deleteFilesInDirectoryOfLogsWithoutPcTime();
    }
}

void BtsLogSorter::saveLogsFromSorterToOutputFile(ofstream & outputLogFileStream)
{
    cout << "Save sorted logs without PC time." << endl;
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)    {
        bufferAndWritePrint(logPrint, outputLogFileStream);
    });
    writeLastPrintIfNeeded(outputLogFileStream);
}

void BtsLogSorter::separateLogsWithoutPcTimeIntoDifferentFiles()
{
    cout << "Save sorted logs without PC time into different addresses." << endl;
    map<string, ofstream> filesWithoutPcTime;
    for(string hardwareAddress: m_foundHardwareAddresses)
    {
        filesWithoutPcTime[hardwareAddress].open(                    getPathOfLogWithoutPcTime(m_directoryOfLogsWithoutPcTime, hardwareAddress));
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

    for(string hardwareAddress: m_foundHardwareAddresses)    {
        filesWithoutPcTime[hardwareAddress].openIfNeeded(
                    getPathOfLogWithoutPcTime(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }    m_sorterWithPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        writePrintsFromFileReaderBeforeThisPrint(filesWithoutPcTime[logPrint.getHardwareAddress()], logPrint, outputLogFileStream);
        bufferAndWritePrint(logPrint, outputLogFileStream);
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
        }    }
}

void BtsLogSorter::writePrintsFromFileReaderBeforeThisPrint(BtsPrintReaderWithRollback & printReader, BtsLogPrint const& logPrint, ofstream & outputLogFileStream)
{
    while(printReader.isGood())
    {
        BtsLogPrint logPrintWithoutPcTime(printReader.getPrint());
        if(logPrintWithoutPcTime.getBtsTime().getMicroSeconds() == 979764)
        {
            cout<<"found without:"<<logPrintWithoutPcTime.getPrint()<<endl;
            cout<<"found with:"<<logPrint.getPrint()<<endl;
        }

        if(logPrintWithoutPcTime.getBtsTime() < logPrint.getBtsTime() || logPrintWithoutPcTime.getBtsTime() == logPrint.getBtsTime())
        {
            if(logPrintWithoutPcTime.getBtsTime().getMicroSeconds() == 979764)
            {
                cout<<"found1";
            }
            if(printReader.isGood())
            {
                if(logPrintWithoutPcTime.getBtsTime().getMicroSeconds() == 979764)
                {
                    cout<<"found2";
                }
                bufferAndWritePrint(logPrintWithoutPcTime, outputLogFileStream);
            }
        }
        else
        {
            if(logPrintWithoutPcTime.getBtsTime().getMicroSeconds() == 979764)
            {
                cout<<"found3";
            }
            printReader.rollBackGetPrint();
            break;
        }
    }
}

void BtsLogSorter::bufferAndWritePrint(BtsLogPrint const& logPrint, ofstream & outputLogFileStream)
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

string BtsLogSorter::getPathOfLogWithoutPcTime(string const& directory, string const& name) const{
    string filename = name.empty() ? "NoHardwareAddress" : name;
    AlbaWindowsPathHandler newFilePath;
    newFilePath.inputPath(directory + R"(\)" + filename + R"(.log)");    return newFilePath.getFullPath();
}

void BtsLogSorter::deleteFilesInDirectoryOfLogsWithoutPcTime() const
{
    AlbaWindowsPathHandler directoryOfLogsWithoutPcTime;
    directoryOfLogsWithoutPcTime.inputPath(m_directoryOfLogsWithoutPcTime);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryOfLogsWithoutPcTime.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file: listOfFiles)
    {
        AlbaWindowsPathHandler logWithoutPcTime;
        logWithoutPcTime.inputPath(file);
        //logWithoutPcTime.deleteFile();
    }
}
}