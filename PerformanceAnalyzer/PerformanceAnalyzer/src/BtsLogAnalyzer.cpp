#include "BtsLogAnalyzer.hpp"

#include <Container/AlbaRange.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <BtsLogPrint.hpp>


using namespace std;
using tcomToolsBackend::BtsLogPrint;
using tcomToolsBackend::BtsLogTime;
using tcomToolsBackend::BtsLogTimeType;

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

    saveHeadersOfCsvFiles(messageQueueingTimeFileStream, rlSetupTimeFileStream, rlDeletionTimeFileStream);

    AlbaFileReader fileReader(inputLogFileStream);
    LogTimePairs rlSetupLogTimePairs;
    LogTimePairs rlDeletionLogTimePairs;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        saveQueueingTime(lineInLogs);
        saveRlhSetupTime(rlSetupLogTimePairs, lineInLogs);
        saveRlhDeletionTime(rlDeletionLogTimePairs, lineInLogs);
    }
}

void BtsLogAnalyzer::saveQueueingTime(string const& lineInLogs, ofstream& messageQueueingTimeFileStream)
{
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "MSG TIME, start queuing time"))
    {
        unsigned int msgQueueingTime(stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "msgQueuingTime: ")));
        m_messageQueueingTime.addData(msgQueueingTime);
        messageQueueingTimeFileStream<<msgQueueingTime<<","<<lineInLogs<<endl;
    }
}

void BtsLogAnalyzer::saveRlhSetupTime(LogTimePairs& rlSetupLogTimePairs, string const& lineInLogs, ofstream& rlSetupTimeFileStream)
{
    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        LogTimePair & logTimePairOfTheUser(rlSetupLogTimePairs[userIdentifiers]);
        setLogTime(logTimePairOfTheUser.first, lineInLogs);
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        LogTimePair & logTimePairOfTheUser(rlSetupLogTimePairs[userIdentifiers]);
        setLogTime(logTimePairOfTheUser.second, lineInLogs);
        if(logTimePairOfTheUser.first && logTimePairOfTheUser.second && logTimePairOfTheUser.first.getReference().getTotalSeconds() <= logTimePairOfTheUser.second.getReference().getTotalSeconds())
        {
            BtsLogTime latency = logTimePairOfTheUser.second.getReference()-logTimePairOfTheUser.first.getReference();
            double latencyInMicroseconds(getTotalMicroseconds(latency));
            m_rlhRlSetupLatency.addData(latencyInMicroseconds);
            rlSetupTimeFileStream<<userIdentifiers.getNbccId()<<","<<userIdentifiers.getNbccId()<<","<<userIdentifiers.getNbccId()<<","<<lineInLogs<<endl;
        }
        rlSetupLogTimePairs.erase(userIdentifiers);
    }
}

void BtsLogAnalyzer::saveRlhDeletionTime(LogTimePairs& rlDeletionLogTimePairs, string const& lineInLogs)
{
    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        LogTimePair & logTimePairOfTheUser(rlDeletionLogTimePairs[userIdentifiers]);
        setLogTime(logTimePairOfTheUser.first, lineInLogs);
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        LogTimePair & logTimePairOfTheUser(rlDeletionLogTimePairs[userIdentifiers]);
        setLogTime(logTimePairOfTheUser.second, lineInLogs);
        if(logTimePairOfTheUser.first && logTimePairOfTheUser.second && logTimePairOfTheUser.first.getReference().getTotalSeconds() <= logTimePairOfTheUser.second.getReference().getTotalSeconds())
        {
            BtsLogTime latency = logTimePairOfTheUser.second.getReference()-logTimePairOfTheUser.first.getReference();
            double latencyInMicroseconds(getTotalMicroseconds(latency));
            m_rlhRlDeletionLatency.addData(latencyInMicroseconds);
        }
        rlDeletionLogTimePairs.erase(userIdentifiers);
    }
}

void BtsLogAnalyzer::saveHeadersOfCsvFiles(ofstream& messageQueueingTimeFileStream, ofstream& rlSetupTimeFileStream, ofstream& rlDeletionTimeFileStream)
{
    messageQueueingTimeFileStream<<"QueueingTime,LogPrint"<<endl;
    rlSetupTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency"<<endl;
    rlDeletionTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency"<<endl;
}

void BtsLogAnalyzer::setLogTime(LogTime& logTime, string const& lineInLogs)
{
    BtsLogPrint logPrint(lineInLogs);
    if(!logPrint.getBtsTime().isStartup())
    {
        logTime.setValue(logPrint.getBtsTime());
    }
}

double BtsLogAnalyzer::getTotalMicroseconds(BtsLogTime const& btsLogTime) const
{
    double result((double)btsLogTime.getMinutes()*1000000*60 + (double)btsLogTime.getSeconds()*1000000 + (double)btsLogTime.getMicroSeconds());
    return result;
}

}
