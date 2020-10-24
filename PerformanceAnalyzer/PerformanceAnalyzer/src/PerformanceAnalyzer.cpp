#include "PerformanceAnalyzer.hpp"

#include <iomanip>
#include <iostream>
#include <map>

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <AprgFileExtractor.hpp>
#include <BtsLogSorter.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

using namespace std;
using tcomToolsBackend::BtsLogTime;
using tcomToolsBackend::BtsLogPrint;

namespace alba
{

namespace ProgressCounters
{
    int numberOfFilesToBeAnalyzedForExtraction;
    int numberOfFilesAnalyzedForExtraction;
    double totalSizeToBeReadForCombine;
    double totalSizeReadForCombine;
    int writeProgressForCombine;
}

PerformanceAnalyzer::UniqueUserId::UniqueUserId()
    : nbccId(0)
    , crnccId(0)
    , transactionId(0)
{}

PerformanceAnalyzer::UniqueUserId::UniqueUserId(std::string const& lineInLogs)
    : nbccId(stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "nbccId: ")))
    , crnccId(getCrnccId(lineInLogs))
    , transactionId(stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "transactionId: ")))
{}

int  PerformanceAnalyzer::UniqueUserId::getCrnccId(std::string const& lineInLogs) const
{
    int properCrnccId;
    int logCrnccId = stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "crnccId: "));
    int logCrncId = stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "crncId: "));
    if(logCrncId>0)
    {
        properCrnccId = logCrncId;
    }
    if(logCrnccId>0)
    {
        properCrnccId = logCrnccId;
    }
    return properCrnccId;
}

bool PerformanceAnalyzer::UniqueUserId::operator <(UniqueUserId const& uniqueUserId) const
{
    if(nbccId != uniqueUserId.nbccId)
    {
        return nbccId < uniqueUserId.nbccId;
    }
    if(crnccId != uniqueUserId.crnccId)
    {
        return crnccId < uniqueUserId.crnccId;
    }
    return transactionId < uniqueUserId.transactionId;
}

PerformanceAnalyzer::PerformanceAnalyzer()
{
    //defautlvalues
    m_extractGrepCondition = R"([LRM] || [alarm] || [UDP] || [CPU] || [syslog] || [ccns] || [tcom] || [startup] || [runtime] || [system] || [radparam] || ([bts]&&([.log]||[.zip]||[.tar])) || [snapshot] || ([tech]&&[report]) || [BTSLogFiles])";
    AlbaWindowsPathHandler pathHandler(R"(C:\temp\BtsSorter\)");
    pathHandler.createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_condition = R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )";
    m_sorterConfiguration.m_pathOfLogsWithoutPcTime = pathHandler.getFullPath() + R"(LogsWithoutPcTime\)";
    AlbaWindowsPathHandler(m_sorterConfiguration.m_pathOfLogsWithoutPcTime).createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_pathOfStartupLog = pathHandler.getFullPath() + R"(Startup.log)";
    m_sorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks = pathHandler.getFullPath() + R"(WithPcTimeBlocks\)";
    AlbaWindowsPathHandler(m_sorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks).createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams = 50;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks = pathHandler.getFullPath() + R"(WithoutPcTimeBlocks\)";
    AlbaWindowsPathHandler(m_sorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks).createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 1000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams = 70;

}

string PerformanceAnalyzer::extract(string const& inputPath) const
{
    cout<<" (Extract) start | Input path: "<<inputPath<<endl;
    AprgFileExtractor fileExtractor(m_extractGrepCondition);
    AlbaWindowsPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if(pathHandler.isDirectory())
    {
        fileExtractor.extractAllRelevantFiles(pathHandler.getFullPath());
    }
    else if(fileExtractor.isRecognizedCompressedFile(pathHandler.getExtension()))
    {
        fileExtractor.extractAllRelevantFiles(pathHandler.getFullPath());
        pathHandler.input(pathHandler.getDirectory() + R"(\)" + pathHandler.getFilenameOnly());
        outputPath = pathHandler.getFullPath();
    }
    else
    {
        cout<<"Extraction step did not proceed. Current path: "<<pathHandler.getFullPath()<<endl;
    }
    cout<<" (Extract) done | Output path: "<<outputPath<<endl;
    return outputPath;
}

string PerformanceAnalyzer::combineAndSort(string const& inputPath) const
{
    cout<<" (CombineAndSort) start | Input path: "<<inputPath<<endl;
    AlbaWindowsPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if(pathHandler.isDirectory())
    {
        tcomToolsBackend::BtsLogSorter btsLogSorter(m_sorterConfiguration);
        btsLogSorter.processDirectory(pathHandler.getDirectory());
        pathHandler.goUp();
        pathHandler.input(pathHandler.getDirectory() + R"(\sorted.log)");
        outputPath = pathHandler.getFullPath();
        btsLogSorter.saveLogsToOutputFile(outputPath);
    }
    else
    {
        cout<<"Combine and sort step did not proceed. Current path: "<<pathHandler.getFullPath()<<endl;
    }
    cout<<" (CombineAndSort) done | Output path: "<<inputPath<<endl;
    return outputPath;
}

void PerformanceAnalyzer::setFileForRawDataDump(string const& rawDataPath)
{
    if(m_RawDataFileOptional)
    {
        m_RawDataFileOptional.clear();
    }
    m_RawDataFileOptional.createObjectUsingDefaultConstructor();
    m_RawDataFileOptional.getReference().open(rawDataPath.c_str());
    if(!m_RawDataFileOptional.getReference().is_open())
    {
        m_RawDataFileOptional.clear();
    }
}

void PerformanceAnalyzer::logInRawDataFile(string const& line)
{
    if(m_RawDataFileOptional)
    {
        m_RawDataFileOptional.getReference()<<line<<endl;
    }
}

void PerformanceAnalyzer::processFileForMsgQueuingTime(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    int totalMsgQueuingTime = 0;
    int highestMsgQueuingTime = 0;
    int numberOfInstances=0;

    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "MSG TIME, start queuing time"))
        {
            int msgQueuingTime = stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "msgQueuingTime: "));
            totalMsgQueuingTime += msgQueuingTime;
            highestMsgQueuingTime = std::max(msgQueuingTime, highestMsgQueuingTime);
            logInRawDataFile(lineInLogs);
            numberOfInstances++;
        }
    }
    cout<<"TotalMsgQueuingTime: "<<totalMsgQueuingTime<<" highestMsgQueuingTime: "<<highestMsgQueuingTime<<" AverageMsgQueuingTime: "<<((double)totalMsgQueuingTime)/numberOfInstances<<" numberOfPrints: "<<numberOfInstances<<endl;
}


void PerformanceAnalyzer::processFileForRlSetupDelayInRlh(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;
    logInRawDataFile("crnccId,nbccId,transactionId,delay");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    std::map<UniqueUserId, bool> isTupcLogSeenMap;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & delayForCrnccId = btsLogDelays[uniqueUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.startTimeOptional.setValue(logPrint.getBtsTime());
                UniqueUserId tupcSeenUserId = uniqueUserId;
                tupcSeenUserId.transactionId=0;
                isTupcLogSeenMap[tupcSeenUserId] = false;
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & delayForCrnccId = btsLogDelays[uniqueUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.endTimeOptional.setValue(logPrint.getBtsTime());
            }

            UniqueUserId tupcSeenUserId = uniqueUserId;
            tupcSeenUserId.transactionId=0;

            if(isTupcLogSeenMap[tupcSeenUserId] && delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional && delayForCrnccId.startTimeOptional.getReference().getTotalSeconds() <= delayForCrnccId.endTimeOptional.getReference().getTotalSeconds())
            {
                BtsLogTime delayTime = delayForCrnccId.endTimeOptional.getReference() - delayForCrnccId.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                if(maxDelay<delay)
                {
                    maxDelay = delay;
                    userIdForMaxDelay = uniqueUserId;
                }
                totalDelay += delay;
                count++;
                stringstream ss;
                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<","<<setw(10)<<delay;
                logInRawDataFile(ss.str());
                btsLogDelays.erase(uniqueUserId);


                isTupcLogSeenMap.erase(tupcSeenUserId);
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TC_TRANSPORT_BEARER_REGISTER_MSG)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            UniqueUserId tupcSeenUserId = uniqueUserId;
            tupcSeenUserId.transactionId=0;
            isTupcLogSeenMap[tupcSeenUserId] = true;
        }
    }
    cout<<"Average Delay:"<<(double)totalDelay/count<<" Max Delay:"<<maxDelay<<endl;
    cout<<"User with max delay -> nbccId:"<<userIdForMaxDelay.nbccId<<" crnccId"<<userIdForMaxDelay.crnccId<<" transactionId"<<userIdForMaxDelay.transactionId<<endl;
}

void PerformanceAnalyzer::processFileForRlDeletionDelayInRlh(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    logInRawDataFile("crnccId,nbccId,transactionId,delay");

    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & delayForCrnccId(btsLogDelays[uniqueUserId]);
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & delayForCrnccId(btsLogDelays[uniqueUserId]);
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.endTimeOptional.setValue(logPrint.getBtsTime());
            }
            if(delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional && delayForCrnccId.startTimeOptional.getReference().getTotalSeconds() <= delayForCrnccId.endTimeOptional.getReference().getTotalSeconds())
            {
                BtsLogTime delayTime = delayForCrnccId.endTimeOptional.getReference() - delayForCrnccId.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                maxDelay = std::max(maxDelay, (double)delay);
                totalDelay += delay;
                count++;
                stringstream ss;
                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<","<<setw(10)<<delay;
                logInRawDataFile(ss.str());
                btsLogDelays.erase(uniqueUserId);
            }
        }
    }
    cout<<"Average Delay:"<<(double)totalDelay/count<<" Max Delay:"<<maxDelay<<endl;
}

}