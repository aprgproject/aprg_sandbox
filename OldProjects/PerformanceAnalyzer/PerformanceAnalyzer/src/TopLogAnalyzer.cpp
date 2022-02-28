#include "TopLogAnalyzer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

void TopLogAnalyzer::DataEntry::clear()
{
    timeInTop.clear();
    totalCpuFromTop = 0;
    processToCpuMemMap.clear();
}

bool TopLogAnalyzer::DataEntry::isEmpty() const
{
    return timeInTop.isEmpty() && totalCpuFromTop ==0  && processToCpuMemMap.empty();
}

void TopLogAnalyzer::ColumnHeaders::clear()
{
    size = 0;
    cpuIndex = 0;
    memIndex = 0;
}

void TopLogAnalyzer::ColumnHeaders::set(unsigned int const sizeFromTop, double const cpuIndexFromTop, double const memIndexFromTop)
{
    size = sizeFromTop;
    cpuIndex = cpuIndexFromTop;
    memIndex = memIndexFromTop;
}


TopLogAnalyzer::TopLogAnalyzer()
{}

void TopLogAnalyzer::clear()
{
    m_state = TopLogAnalyzerState::BeforeColumnHeaders;
    m_dataEntries.clear();
}

void TopLogAnalyzer::processTopLog(std::string const& pathOfTopLog)
{
    clear();
    readTopLogsAndSaveToDatabase(pathOfTopLog);
    generateCpuReport(pathOfTopLog);
    generateMemReport(pathOfTopLog);
}

void TopLogAnalyzer::readTopLogsAndSaveToDatabase(std::string const& pathOfTopLog)
{
    AlbaLocalPathHandler topLogPathHandler(pathOfTopLog);
    ifstream inputLogFileStream(topLogPathHandler.getFullPath());

    AlbaFileReader fileReader(inputLogFileStream);
    DataEntry currentEntry;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());

        if(isTopCommandFirstLine(lineInLogs))
        {
            m_state=TopLogAnalyzerState::BeforeColumnHeaders;
            saveAndClearCurrentEntry(currentEntry);
            saveTimeFromTop(lineInLogs, currentEntry);
        }
        else if(isTopCommandHeaderLine(lineInLogs))
        {
            m_state = TopLogAnalyzerState::AfterColumnHeaders;
            saveDataFromHeaders(lineInLogs);
        }
        else if(m_state==TopLogAnalyzerState::BeforeColumnHeaders && stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "%Cpu0  :"))
        {
            saveOverallCpuData(lineInLogs, currentEntry);
        }
        if(m_state==TopLogAnalyzerState::AfterColumnHeaders)
        {
            saveCpuAndMem(lineInLogs, currentEntry);
        }
    }
}

void TopLogAnalyzer::generateCpuReport(std::string const& pathOfTopLog)
{
    AlbaLocalPathHandler topLogPathHandler(pathOfTopLog);
    AlbaLocalPathHandler cpuReportFilePathHandler(topLogPathHandler.getDirectory()+topLogPathHandler.getFilenameOnly()+"_CpuReport.csv");
    ofstream cpuReportFileStream(cpuReportFilePathHandler.getFullPath());

    stringHelper::strings processNamesInReport(getProcessNamesForCpuReport());
    putHeadersInCpuReport(processNamesInReport, cpuReportFileStream);
    putEntriesInCpuReport(processNamesInReport, cpuReportFileStream);
}

stringHelper::strings TopLogAnalyzer::getProcessNamesForCpuReport()
{
    stringHelper::strings processNamesInReport;
    for(std::pair<std::string, CpuMemCollection> const& processToCpuMemCollectionPair : m_processToCpuMemCollectionMap)
    {
        if(processToCpuMemCollectionPair.second.cpu.getMaximum() != 0)
        {
            processNamesInReport.emplace_back(processToCpuMemCollectionPair.first);
        }
    }

    sort(processNamesInReport.begin(), processNamesInReport.end(), [&](string const& firstProcessName, string const& secondProcessName)
    {
        bool result(false);
        bool isTcomTupcOnFirstProcess(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(firstProcessName, "TCOM") ||
                                      stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(firstProcessName, "Conman") ||
                                      stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(firstProcessName, "Aalman"));
        bool isTcomTupcOnSecondProcess(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(secondProcessName, "TCOM") ||
                                       stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(secondProcessName, "Conman") ||
                                       stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(secondProcessName, "Aalman"));
        double firstProcessCpuBasis(0);
        double secondProcessCpuBasis(0);
        if(m_processToCpuMemCollectionMap.find(firstProcessName) != m_processToCpuMemCollectionMap.end())
        {
            firstProcessCpuBasis = m_processToCpuMemCollectionMap.at(firstProcessName).cpu.getAverage();
        }
        if(m_processToCpuMemCollectionMap.find(secondProcessName) != m_processToCpuMemCollectionMap.end())
        {
            secondProcessCpuBasis = m_processToCpuMemCollectionMap.at(secondProcessName).cpu.getAverage();
        }

        result = (isTcomTupcOnFirstProcess && !isTcomTupcOnSecondProcess) ? true :
                 (!isTcomTupcOnFirstProcess && isTcomTupcOnSecondProcess) ? false :
                 firstProcessCpuBasis > secondProcessCpuBasis;
        return result;
    });
    return processNamesInReport;
}

void TopLogAnalyzer::putHeadersInCpuReport(stringHelper::strings const& processNamesInReport, ofstream& cpuReportFileStream) const
{
    cpuReportFileStream<<"Time,TotalCpuFromTop,TotalCpuCalculated,";
    for(string const& processName : processNamesInReport)
    {
        cpuReportFileStream << processName << ",";
    }
    cpuReportFileStream<<endl;
}

void TopLogAnalyzer::putEntriesInCpuReport(stringHelper::strings const& processNamesInReport, ofstream& cpuReportFileStream) const
{
    cpuReportFileStream.precision(3);
    for(DataEntry const& entry : m_dataEntries)
    {
        double totalCalculatedCpu = accumulate(entry.processToCpuMemMap.begin(), entry.processToCpuMemMap.end(), double(0), [](double const partialSum, DataEntry::ProcessToCpuMemPair const& processToCpuMemPair)
        {
            return partialSum + processToCpuMemPair.second.cpuLoad;
        });
        cpuReportFileStream << entry.timeInTop.getPrintableStringFormat2() << ",";
        cpuReportFileStream << entry.totalCpuFromTop << ",";
        cpuReportFileStream << totalCalculatedCpu << ",";
        DataEntry::ProcessToCpuMemMap const& currentProcessToCpuMemMap(entry.processToCpuMemMap);
        for(string const& processName : processNamesInReport)
        {
            DataEntry::ProcessToCpuMemMap::const_iterator processToCpuMemIterator = currentProcessToCpuMemMap.find(processName);
            if(processToCpuMemIterator != currentProcessToCpuMemMap.cend())
            {
                cpuReportFileStream << currentProcessToCpuMemMap.at(processName).cpuLoad << ",";
            }
            else
            {
                cpuReportFileStream << "0,";
            }
        }
        cpuReportFileStream<<endl;
    }
}

void TopLogAnalyzer::generateMemReport(std::string const& pathOfTopLog)
{
    AlbaLocalPathHandler topLogPathHandler(pathOfTopLog);
    AlbaLocalPathHandler cpuReportFilePathHandler(topLogPathHandler.getDirectory()+topLogPathHandler.getFilenameOnly()+"_MemReport.csv");
    ofstream cpuReportFileStream(cpuReportFilePathHandler.getFullPath());

    stringHelper::strings processNamesInReport(getProcessNamesForMemReport());
    putHeadersInMemReport(processNamesInReport, cpuReportFileStream);
    putEntriesInMemReport(processNamesInReport, cpuReportFileStream);
}

stringHelper::strings TopLogAnalyzer::getProcessNamesForMemReport()
{
    stringHelper::strings processNamesInReport;
    for(std::pair<std::string, CpuMemCollection> const& processToCpuMemCollectionPair : m_processToCpuMemCollectionMap)
    {
        if(processToCpuMemCollectionPair.second.cpu.getMaximum() != 0)
        {
            processNamesInReport.emplace_back(processToCpuMemCollectionPair.first);
        }
    }

    sort(processNamesInReport.begin(), processNamesInReport.end(), [&](string const& firstProcessName, string const& secondProcessName)
    {
        bool result(false);
        bool isTcomTupcOnFirstProcess(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(firstProcessName, "TCOM") ||
                                      stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(firstProcessName, "Conman") ||
                                      stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(firstProcessName, "Aalman"));
        bool isTcomTupcOnSecondProcess(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(secondProcessName, "TCOM") ||
                                       stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(secondProcessName, "Conman") ||
                                       stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(secondProcessName, "Aalman"));
        double firstProcessMemBasis(0);
        double secondProcessMemBasis(0);
        if(m_processToCpuMemCollectionMap.find(firstProcessName) != m_processToCpuMemCollectionMap.end())
        {
            firstProcessMemBasis = m_processToCpuMemCollectionMap.at(firstProcessName).mem.getAverage();
        }
        if(m_processToCpuMemCollectionMap.find(secondProcessName) != m_processToCpuMemCollectionMap.end())
        {
            secondProcessMemBasis = m_processToCpuMemCollectionMap.at(secondProcessName).mem.getAverage();
        }

        result = (isTcomTupcOnFirstProcess && !isTcomTupcOnSecondProcess) ? true :
                 (!isTcomTupcOnFirstProcess && isTcomTupcOnSecondProcess) ? false :
                 firstProcessMemBasis > secondProcessMemBasis;
        return result;
    });
    return processNamesInReport;
}

void TopLogAnalyzer::putHeadersInMemReport(stringHelper::strings const& processNamesInReport, ofstream& memReportFileStream) const
{
    memReportFileStream<<"Time,";
    for(string const& processName : processNamesInReport)
    {
        memReportFileStream << processName << ",";
    }
    memReportFileStream<<endl;
}

void TopLogAnalyzer::putEntriesInMemReport(stringHelper::strings const& processNamesInReport, ofstream& memReportFileStream) const
{
    memReportFileStream.precision(3);
    for(DataEntry const& entry : m_dataEntries)
    {
        memReportFileStream << entry.timeInTop.getPrintableStringFormat2() << ",";
        DataEntry::ProcessToCpuMemMap const& currentProcessToCpuMemMap(entry.processToCpuMemMap);
        for(string const& processName : processNamesInReport)
        {
            DataEntry::ProcessToCpuMemMap::const_iterator processToCpuMemIterator = currentProcessToCpuMemMap.find(processName);
            if(processToCpuMemIterator != currentProcessToCpuMemMap.cend())
            {
                memReportFileStream << currentProcessToCpuMemMap.at(processName).memLoad << ",";
            }
            else
            {
                memReportFileStream << "0,";
            }
        }
        memReportFileStream<<endl;
    }
}

bool TopLogAnalyzer::isTopCommandFirstLine(string const& lineInLogs) const
{
    return stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "top - ");
}

bool TopLogAnalyzer::isTopCommandHeaderLine(string const& lineInLogs) const
{
    return stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "PID") &&
            stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "%CPU") &&
            stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "%MEM") &&
            stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "COMMAND");
}

void TopLogAnalyzer::saveAndClearCurrentEntry(DataEntry & currentEntry)
{
    if(!currentEntry.isEmpty())
    {
        m_dataEntries.emplace_back(currentEntry);
        currentEntry.clear();
    }
}

void TopLogAnalyzer::saveTimeFromTop(string const& lineInLogs, DataEntry & currentEntry) const
{
    string timeString(stringHelper::getStringInBetweenTwoStrings(lineInLogs, "top - ", " "));
    stringHelper::strings timeValues;
    stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(timeValues, timeString, ":");
    if(timeValues.size() == 3)
    {
        currentEntry.timeInTop.setTime(0, 0, 0, stringHelper::convertStringToNumber<unsigned int>(timeValues[0]), stringHelper::convertStringToNumber<unsigned int>(timeValues[1]), stringHelper::convertStringToNumber<unsigned int>(timeValues[2]), 0);
    }
}

void TopLogAnalyzer::saveDataFromHeaders(string const& lineInLogs)
{
    stringHelper::strings headers;
    stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(headers, lineInLogs, " ");
    unsigned int headersSize(headers.size());
    unsigned int cpuIndexInHeaders(distance(headers.cbegin(), find(headers.cbegin(), headers.cend(), "%CPU")));
    cpuIndexInHeaders = cpuIndexInHeaders > headersSize ? 0 : cpuIndexInHeaders;
    unsigned int memIndexInHeaders(distance(headers.cbegin(), find(headers.cbegin(), headers.cend(), "%MEM")));
    memIndexInHeaders = memIndexInHeaders > headersSize ? 0 : memIndexInHeaders;
    m_columnHeaders.set(headersSize, cpuIndexInHeaders, memIndexInHeaders);
}

void TopLogAnalyzer::saveOverallCpuData(string const& lineInLogs, DataEntry & currentEntry) const
{
    unsigned int bracketCpuIndexInLine(lineInLogs.find("["));
    if(bracketCpuIndexInLine > 3)
    {
        currentEntry.totalCpuFromTop = stringHelper::convertStringToNumber<double>(lineInLogs.substr(bracketCpuIndexInLine-3, 3));
    }
}

void TopLogAnalyzer::saveCpuAndMem(string const& lineInLogs, DataEntry & currentEntry)
{
    stringHelper::strings contents;
    stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(contents, lineInLogs, " ");
    if(m_columnHeaders.size>0 && contents.size() > m_columnHeaders.size-1)
    {
        stringHelper::strings lastContents(contents.cbegin()+m_columnHeaders.size-1, contents.cend());
        string processName(stringHelper::getStringWithoutStartingAndTrailingCharacters(stringHelper::combineStrings(lastContents, "_"), "`-_"));
        double cpuLoad = stringHelper::convertStringToNumber<double>(contents[m_columnHeaders.cpuIndex]);
        double memLoad = stringHelper::convertStringToNumber<double>(contents[m_columnHeaders.memIndex]);
        if(cpuLoad>0)
        {
            currentEntry.processToCpuMemMap[processName].cpuLoad = cpuLoad;
            m_processToCpuMemCollectionMap[processName].cpu.addData(cpuLoad);
        }
        if(memLoad>0)
        {
            currentEntry.processToCpuMemMap[processName].memLoad = memLoad;
            m_processToCpuMemCollectionMap[processName].mem.addData(memLoad);
        }
    }
}


}
