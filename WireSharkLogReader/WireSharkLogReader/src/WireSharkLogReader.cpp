#include "WireSharkLogReader.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <iomanip>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <set>

using namespace std;

namespace alba
{

WireSharkLogReader::WireSharkLogReader()
    : m_totalDelay(0)
    , m_count(0)
{}

WireSharkLogReader::WireSharkLogReader(string const pathOfOutputFile)
    : m_outputStream(pathOfOutputFile)
    , m_totalDelay(0)
    , m_count(0)
{
    if(m_outputStream.is_open())
    {
        cout<<"OutputStream is opened. Saving to output files"<<endl;
    }
    m_outputStream<<"crnccId,delay"<<endl;
}

void WireSharkLogReader::processDirectory(string const& directoryPath)
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
        processFile(filePathHandler.getFullPath());
    }
}

void WireSharkLogReader::processFile(string const& filePath)
{
    m_delays.clear();
    AlbaWindowsPathHandler filePathHandler;
    filePathHandler.inputPath(filePath);
    cout<<"processFile: "<<filePathHandler.getFile()<<endl;

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    AlbaOptional<double> startTimeFetchedOptional;
    AlbaOptional<double> endTimeFetchedOptional;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(id-radioLinkSetup , RadioLinkSetupRequestFDD)"))
        {
            startTimeFetchedOptional.setValue(getWireSharkTime(lineInLogs));
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(id-radioLinkSetup , RadioLinkSetupResponseFDD)"))
        {
            endTimeFetchedOptional.setValue(getWireSharkTime(lineInLogs));
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CRNC-CommunicationContextID: )"))
        {
            int crnccId = stringHelper::stringToNumber<int>(getNumberAfterThisString(lineInLogs, "CRNC-CommunicationContextID: "));
            WireSharkDelay & delayForCrnccId = m_delays[crnccId];
            if(startTimeFetchedOptional)
            {
                delayForCrnccId.startTimeOptional.setValue(startTimeFetchedOptional.getReference());
            }
            if(endTimeFetchedOptional)
            {
                delayForCrnccId.endTimeOptional.setValue(endTimeFetchedOptional.getReference());
            }
            startTimeFetchedOptional.clear();
            endTimeFetchedOptional.clear();

            if(delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional)
            {
                double delay = delayForCrnccId.endTimeOptional.getReference() - delayForCrnccId.startTimeOptional.getReference();
                m_totalDelay += delay;
                m_count++;
                m_outputStream<<crnccId<<","<<setw(10)<<delay<<endl;
                //cout<<"CrnccId: "<<crnccId<<" Delay: "<<delay<<" count: "<<m_count<<" totalDelay: "<<m_totalDelay<<endl;
                m_delays.erase(crnccId);
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(No.     Time)"))
        {
            startTimeFetchedOptional.clear();
            endTimeFetchedOptional.clear();
        }
    }
}

double WireSharkLogReader::getWireSharkTime(string const& lineInLogs) const
{
    int length(lineInLogs.length());
    int startIndexOfTime=0, endIndexOfTime=0;
    int i=0;
    for(; i<length && stringHelper::isWhiteSpace(lineInLogs[i]); i++) {}
    for(; i<length && stringHelper::isNumber(lineInLogs[i]); i++) {}
    startIndexOfTime = i;
    for(; i<length && stringHelper::isWhiteSpace(lineInLogs[i]); i++) {}
    for(; i<length && !stringHelper::isWhiteSpace(lineInLogs[i]); i++) {}
    endIndexOfTime = i;
    return stringHelper::stringToNumber<double>(lineInLogs.substr(startIndexOfTime, endIndexOfTime-startIndexOfTime));
}

string WireSharkLogReader::getNumberAfterThisString(string const& mainString, string const& stringToSearch) const
{
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(stringHelper::isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        int lastIndexOfNumber;
        for(lastIndexOfNumber = lastIndexOfFirstString; stringHelper::isNumber(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

double WireSharkLogReader::getComputedAverageDelay() const
{
    return (double)m_totalDelay/m_count;
}

}//namespace alba
