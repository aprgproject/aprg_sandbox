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

bool BtsLogFileReaderWithRollback::isGood() const
{
    return m_inputStream.good();
}

BtsLogPrint BtsLogFileReaderWithRollback::getPrint()
{
    m_isPreviousPrintValid = false;
    if(isGood())
    {
        m_inputStream >> m_previousPrint;
        if(!isGood())
        {
            return BtsLogPrint{};
        }
        return m_previousPrint;
    }
    return BtsLogPrint{};
}

void BtsLogFileReaderWithRollback::rollBackGetPrint()
{
    if(isGood())
    {
        m_isPreviousPrintValid = true;
    }
}

void BtsLogFileReaderWithRollback::openIfNeeded(string const& filePath)
{
    if(!m_inputStream.is_open())
    {
        m_inputStream.open(filePath);
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
    AlbaWindowsPathHandler pathHandlerOfLogsWithoutPcTime;    pathHandlerOfLogsWithoutPcTime.inputPath(pathOfLogsWithoutPcTime);
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
    cout<<"Processing File: "<<filePathHandler.getFile()<<endl;

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

void BtsLogSorter::saveAllToOutputFile(string const& outputPath)
{
    cout<<"Saving output file: "<<outputPath<<endl;
    if(m_sorterWithPcTime.isEmpty())
    {
        ofstream outputLogFileStream(outputPath);
        saveSortedLogsWithoutPcTime(outputLogFileStream);
    }
    else
    {
        saveSortedLogsWithoutPcTimeIntoDifferentFiles();
        mergePrintsAndSaveToOutputFile(outputPath);
        deleteFilesInDirectoryOfLogsWithoutPcTime();
    }
}

void BtsLogSorter::saveSortedLogsWithoutPcTime(ofstream & outputLogFileStream)
{
    cout << "saveSortedLogsWithoutPcTime" << endl;
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        bufferAndWritePrint(logPrint, outputLogFileStream);
    });
    writeLastPrintIfNeeded(outputLogFileStream);
}

void BtsLogSorter::saveSortedLogsWithoutPcTimeIntoDifferentFiles()
{
    cout << "saveSortedLogsWithoutPcTimeIntoDifferentFiles" << endl;
    map<string, ofstream> filesWithoutPcTime;

    for(string hardwareAddress: m_foundHardwareAddresses)
    {
        filesWithoutPcTime[hardwareAddress].open(
                    getPathOfLogWithoutPcTime(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        filesWithoutPcTime[logPrint.getHardwareAddress()] << logPrint << endl;
    });
}

void BtsLogSorter::mergePrintsAndSaveToOutputFile(string const& outputPath)
{
    cout << "mergeWithPcTimeAndSaveToOutputFile" << endl;
    map<string, BtsLogFileReaderWithRollback> filesWithoutPcTime;
    ofstream outputLogFileStream(outputPath);

    for(string hardwareAddress: m_foundHardwareAddresses)
    {
        filesWithoutPcTime[hardwareAddress].openIfNeeded(
                    getPathOfLogWithoutPcTime(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    m_sorterWithPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint)
    {
        writePrintsFromFileReaderBeforeThisPrint(filesWithoutPcTime[logPrint.getHardwareAddress()], logPrint, outputLogFileStream);
        bufferAndWritePrint(logPrint, outputLogFileStream);
    });
    for(auto & mapFilesPair: filesWithoutPcTime)
    {
        addPrintsFromFileReaderToSorterWithoutPcTime(mapFilesPair.second);
    }
    saveSortedLogsWithoutPcTime(outputLogFileStream);
}

void BtsLogSorter::addPrintsFromFileReaderToSorterWithoutPcTime(BtsLogFileReaderWithRollback & fileReader)
{
    while(fileReader.isGood())
    {
        BtsLogPrint logPrintWithoutPcTime(fileReader.getPrint());
        if(fileReader.isGood())
        {
            m_sorterWithoutPcTime.add(logPrintWithoutPcTime);
        }
    }
}

void BtsLogSorter::writePrintsFromFileReaderBeforeThisPrint(BtsLogFileReaderWithRollback & fileReader, BtsLogPrint const& logPrint, ofstream & outputLogFileStream)
{
    while(fileReader.isGood())
    {
        BtsLogPrint logPrintWithoutPcTime(fileReader.getPrint());
        if(logPrintWithoutPcTime.getBtsTime() < logPrint.getBtsTime() || logPrintWithoutPcTime.getBtsTime() == logPrint.getBtsTime())
        {
            if(fileReader.isGood())
            {
                bufferAndWritePrint(logPrintWithoutPcTime, outputLogFileStream);
            }
        }
        else
        {
            fileReader.rollBackGetPrint();
            break;
        }
    }
}
void BtsLogSorter::bufferAndWritePrint(BtsLogPrint const& logPrint, ofstream & outputLogFileStream)
{
    if(m_notYetPrintedPrint == logPrint)
    {
        m_notYetPrintedPrint.updatePcTimeAndFileNameDetails(logPrint);
    }
    else
    {
        if(!m_notYetPrintedPrint.getPrint().empty())
        {
            outputLogFileStream << m_notYetPrintedPrint.getPrintWithAllDetails() << endl;
        }
        m_notYetPrintedPrint = logPrint;
    }
}

void BtsLogSorter::writeLastPrintIfNeeded(ofstream & outputLogFileStream)
{
    outputLogFileStream << m_notYetPrintedPrint.getPrintWithAllDetails() << endl;
    m_notYetPrintedPrint = BtsLogPrint{};
}

string BtsLogSorter::getPathOfLogWithoutPcTime(string const& directory, string const& name) const
{
    string filename = name.empty() ? "NoHardwareAddress" : name;
    AlbaWindowsPathHandler newFilePath;
    newFilePath.inputPath(directory + R"(\)" + filename + R"(.log)");
    return newFilePath.getFullPath();
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
        logWithoutPcTime.deleteFile();
    }
}

}
