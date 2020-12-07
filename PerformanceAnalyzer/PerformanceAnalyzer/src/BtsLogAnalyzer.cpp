#include "BtsLogAnalyzer.hpp"

#include <Container/AlbaRange.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <BtsLogPrint.hpp>

#include <iostream>

using namespace std;
using tcomToolsBackend::BtsLogPrint;
using tcomToolsBackend::BtsLogTime;using tcomToolsBackend::BtsLogTimeType;

namespace alba
{

BtsLogAnalyzer::BtsLogAnalyzer()
{}

void BtsLogAnalyzer::clear()
{
    m_messageQueueingTime.clear();
    m_rlhRlSetupLatency.clear();
    m_rlhRlDeletionLatency.clear();
}

void BtsLogAnalyzer::processFileWithSortedPrints(std::string const& pathOfBtsSortedLog)
{
    clear();

    AlbaLocalPathHandler btsLogPathHandler(pathOfBtsSortedLog);
    AlbaLocalPathHandler messageQueueingTimeFilePathHandler(btsLogPathHandler.getDirectory()+btsLogPathHandler.getFilenameOnly()+"_MessageQueueingTime.csv");
    AlbaLocalPathHandler rlSetupTimeFilePathHandler(btsLogPathHandler.getDirectory()+btsLogPathHandler.getFilenameOnly()+"_RlSetupTime.csv");
    AlbaLocalPathHandler rlDeletionTimeFilePathHandler(btsLogPathHandler.getDirectory()+btsLogPathHandler.getFilenameOnly()+"_RlDeletionTime.csv");

    ifstream inputLogFileStream(btsLogPathHandler.getFullPath());
    ofstream messageQueueingTimeFileStream(messageQueueingTimeFilePathHandler.getFullPath());
    ofstream rlSetupTimeFileStream(rlSetupTimeFilePathHandler.getFullPath());
    ofstream rlDeletionTimeFileStream(rlDeletionTimeFilePathHandler.getFullPath());
    initializeCsvFileStreams(messageQueueingTimeFileStream, rlSetupTimeFileStream, rlDeletionTimeFileStream);

    AlbaFileReader fileReader(inputLogFileStream);
    LogTimePairs rlSetupLogTimePairs;
    LogTimePairs rlDeletionLogTimePairs;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        saveQueueingTime(lineInLogs, messageQueueingTimeFileStream);
        saveRlhSetupTime(lineInLogs, rlSetupLogTimePairs, rlSetupTimeFileStream);
        saveRlhDeletionTime(lineInLogs, rlDeletionLogTimePairs, rlDeletionTimeFileStream);
    }
}

void BtsLogAnalyzer::saveQueueingTime(string const& lineInLogs, ofstream& messageQueueingTimeFileStream)
{
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "MSG TIME, start queuing time"))
    {
        unsigned int messsageQueueingTime(stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "msgQueuingTime: ")));
        m_messageQueueingTime.addData(messsageQueueingTime);
        saveMessageQueueingTimeToCsvFile(lineInLogs, messsageQueueingTime, messageQueueingTimeFileStream);
    }
}

void BtsLogAnalyzer::saveRlhSetupTime(string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs, ofstream& rlSetupTimeFileStream)
{
    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setFirstLogTimeInPair(lineInLogs, userIdentifiers, rlSetupLogTimePairs);
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setSecondLogTimeInPair(lineInLogs, userIdentifiers, rlSetupLogTimePairs);
        computeLatencyAndUpdateIfLogTimePairIsValid(LogType::RlSetup, userIdentifiers, rlSetupLogTimePairs, rlSetupTimeFileStream);
    }
}
void BtsLogAnalyzer::saveRlhDeletionTime(string const& lineInLogs, LogTimePairs& rlDeletionLogTimePairs, ofstream& rlDeletionTimeFileStream)
{
    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setFirstLogTimeInPair(lineInLogs, userIdentifiers, rlDeletionLogTimePairs);
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setSecondLogTimeInPair(lineInLogs, userIdentifiers, rlDeletionLogTimePairs);
        computeLatencyAndUpdateIfLogTimePairIsValid(LogType::RlDeletion, userIdentifiers, rlDeletionLogTimePairs, rlDeletionTimeFileStream);
    }
}
void BtsLogAnalyzer::setFirstLogTimeInPair(string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const
{
    LogTimePair & logTimePairOfTheUser(logTimePairs[userIdentifiers]);
    setLogTimeIfNeeded(lineInLogs, logTimePairOfTheUser.first);
}

void BtsLogAnalyzer::setSecondLogTimeInPair(string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const
{
    LogTimePair & logTimePairOfTheUser(logTimePairs[userIdentifiers]);
    setLogTimeIfNeeded(lineInLogs, logTimePairOfTheUser.second);
}

void BtsLogAnalyzer::computeLatencyAndUpdateIfLogTimePairIsValid(LogType const logType, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs, ofstream& csvFileStream)
{
    LogTimePair & logTimePairOfTheUser(logTimePairs[userIdentifiers]);
    if(logTimePairOfTheUser.first && logTimePairOfTheUser.second && logTimePairOfTheUser.first.getReference().getTotalSeconds() <= logTimePairOfTheUser.second.getReference().getTotalSeconds())    {
        BtsLogTime latency = logTimePairOfTheUser.second.getReference()-logTimePairOfTheUser.first.getReference();
        double latencyInMicroseconds(getTotalMicroseconds(latency));
        if(logType == LogType::RlSetup)
        {
            m_rlhRlSetupLatency.addData(latencyInMicroseconds);
        }
        else if(logType == LogType::RlDeletion)
        {
            m_rlhRlDeletionLatency.addData(latencyInMicroseconds);
        }
        saveUserIndentifierAndLatencyToCsvFile(userIdentifiers, latencyInMicroseconds, csvFileStream);
    }
    logTimePairs.erase(userIdentifiers);}

void BtsLogAnalyzer::initializeCsvFileStreams(ofstream& messageQueueingTimeFileStream, ofstream& rlSetupTimeFileStream, ofstream& rlDeletionTimeFileStream) const
{
    setPrecisionOfFileStreams(messageQueueingTimeFileStream, rlSetupTimeFileStream, rlDeletionTimeFileStream);
    saveHeadersOnCsvFiles(messageQueueingTimeFileStream, rlSetupTimeFileStream, rlDeletionTimeFileStream);
}

void BtsLogAnalyzer::setPrecisionOfFileStreams(ofstream& messageQueueingTimeFileStream, ofstream& rlSetupTimeFileStream, ofstream& rlDeletionTimeFileStream) const
{
    messageQueueingTimeFileStream.precision(20);
    rlSetupTimeFileStream.precision(20);
    rlDeletionTimeFileStream.precision(20);
}

void BtsLogAnalyzer::saveHeadersOnCsvFiles(ofstream& messageQueueingTimeFileStream, ofstream& rlSetupTimeFileStream, ofstream& rlDeletionTimeFileStream) const
{
    messageQueueingTimeFileStream<<"QueueingTime,LogPrint"<<endl;
    rlSetupTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency(microseconds)"<<endl;
    rlDeletionTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency(microseconds)"<<endl;
}

void BtsLogAnalyzer::saveMessageQueueingTimeToCsvFile(string const& lineInLogs, unsigned int const messageQueueingTime, ofstream& csvFileStream) const
{
    csvFileStream<<messageQueueingTime<<","<<lineInLogs<<endl;
}

void BtsLogAnalyzer::saveUserIndentifierAndLatencyToCsvFile(UserIdentifiers const& userIdentifiers, double const latencyInMicroseconds, ofstream& csvFileStream) const
{
    csvFileStream<<userIdentifiers.getNbccId()<<","<<userIdentifiers.getCrnccId()<<","<<userIdentifiers.getTransactionId()<<","<<latencyInMicroseconds<<endl;
}

void BtsLogAnalyzer::setLogTimeIfNeeded(string const& lineInLogs, LogTime& logTime) const
{
    BtsLogPrint logPrint(lineInLogs);
    //if(!logPrint.getBtsTime().isStartup())
    //{
        logTime.setValue(logPrint.getBtsTime());
    //}
}

double BtsLogAnalyzer::getTotalMicroseconds(BtsLogTime const& btsLogTime) const{
    double result((double)btsLogTime.getMinutes()*1000000*60 + (double)btsLogTime.getSeconds()*1000000 + (double)btsLogTime.getMicroSeconds());
    return result;
}

void BtsLogAnalyzer::printAllCollectedData() const
{
    cout.precision(20);
    cout<<"Message queueing time minimum: "<<m_messageQueueingTime.getMinimum() << " ms" << endl;
    cout<<"Message queueing time maximum: "<<m_messageQueueingTime.getMaximum() << " ms" << endl;
    cout<<"Message queueing time average: "<<m_messageQueueingTime.getAverage() << " ms" << endl;
    cout<<"Message queueing time samples: "<<m_messageQueueingTime.getCount()<<endl;

    cout<<"Rl setup time minimum: "<<m_rlhRlSetupLatency.getMinimum()/1000 << " ms" << endl;
    cout<<"Rl setup time maximum: "<<m_rlhRlSetupLatency.getMaximum()/1000 << " ms" << endl;
    cout<<"Rl setup time average: "<<m_rlhRlSetupLatency.getAverage()/1000 << " ms" << endl;
    cout<<"Rl setup time samples: "<<m_rlhRlSetupLatency.getCount()<<endl;

    cout<<"Rl deletion time minimum: "<<m_rlhRlDeletionLatency.getMinimum()/1000 << " ms" << endl;
    cout<<"Rl deletion time maximum: "<<m_rlhRlDeletionLatency.getMaximum()/1000 << " ms" << endl;
    cout<<"Rl deletion time average: "<<m_rlhRlDeletionLatency.getAverage()/1000 << " ms" << endl;
    cout<<"Rl deletion time samples: "<<m_rlhRlDeletionLatency.getCount()<<endl;
}

}