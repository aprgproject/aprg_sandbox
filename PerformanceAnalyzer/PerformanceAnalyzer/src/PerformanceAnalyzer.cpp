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
using tcomToolsBackend::BtsLogPrint;
using tcomToolsBackend::BtsLogTime;

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
    : nbccId(getNbccId(lineInLogs))
    , crnccId(getCrnccId(lineInLogs))
    , transactionId(getTransactionId(lineInLogs))
{}

void PerformanceAnalyzer::UniqueUserId::saveNbccId(std::string const& lineInLogs)
{
    nbccId = getNbccId(lineInLogs);
}

void PerformanceAnalyzer::UniqueUserId::saveCrnccId(std::string const& lineInLogs)
{
    crnccId = getCrnccId(lineInLogs);
}

void PerformanceAnalyzer::UniqueUserId::saveTransactionId(std::string const& lineInLogs)
{
    transactionId = getTransactionId(lineInLogs);
}

int  PerformanceAnalyzer::UniqueUserId::getCrnccId(std::string const& lineInLogs) const
{
    int properCrnccId=0;
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

int PerformanceAnalyzer::UniqueUserId::getNbccId(std::string const& lineInLogs) const
{
    int properNbccId=0;
    int nbccid = stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "nbccid: "));
    int nbccId = stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "nbccId: "));
    if(nbccid>0)
    {
        properNbccId = nbccid;
    }
    if(nbccId>0)
    {
        properNbccId = nbccId;
    }
    return properNbccId;
}

int PerformanceAnalyzer::UniqueUserId::getTransactionId(std::string const& lineInLogs) const
{
    return stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "transactionId: "));
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

void PerformanceAnalyzer::logLineInRawDataFile(string const& line)
{
    if(m_RawDataFileOptional)
    {
        m_RawDataFileOptional.getReference()<<line<<endl;
    }
}

void PerformanceAnalyzer::logStringInRawDataFile(string const& line)
{
    if(m_RawDataFileOptional)
    {
        m_RawDataFileOptional.getReference()<<line;
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
            logLineInRawDataFile(lineInLogs);
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
    logLineInRawDataFile("crnccId,nbccId,transactionId,delay");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    BtsLogTime startTest, endTest;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.startTimeOptional.setValue(logPrint.getBtsTime());
                if(!logPrint.getPcTime().isEmpty())
                {
                    endTest = logPrint.getBtsTime();
                    if(startTest.isEmpty())
                    {
                        startTest=logPrint.getBtsTime();
                    }
                }
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.endTimeOptional.setValue(logPrint.getBtsTime());
            }
            if(btsLogDelay.startTimeOptional && btsLogDelay.endTimeOptional && btsLogDelay.startTimeOptional.getReference().getTotalSeconds() <= btsLogDelay.endTimeOptional.getReference().getTotalSeconds())
            {
                int delay = getDelayTimeInUs(btsLogDelay.endTimeOptional.getReference(), btsLogDelay.startTimeOptional.getReference());
                if(maxDelay<delay)
                {
                    maxDelay = delay;
                    userIdForMaxDelay = uniqueUserId;
                }
                totalDelay += delay;
                count++;
                stringstream ss;
                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<","<<setw(10)<<delay;
                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
        }
    }
    cout<<"Average Delay:"<<(double)totalDelay/count<<" Max Delay:"<<maxDelay<<endl;
    cout<<"User with max delay -> nbccId: "<<userIdForMaxDelay.nbccId<<" crnccId: "<<userIdForMaxDelay.crnccId<<" transactionId: "<<userIdForMaxDelay.transactionId<<endl;
    BtsLogTime delayTime = endTest-startTest;
    cout<<"Test Duration: "<<delayTime.getEquivalentStringBtsTimeFormat()<<endl;
}

void PerformanceAnalyzer::processFileForRlDeletionDelayInRlh(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    logLineInRawDataFile("crnccId,nbccId,transactionId,delay");

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
            BtsLogDelay & btsLogDelay(btsLogDelays[uniqueUserId]);
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & btsLogDelay(btsLogDelays[uniqueUserId]);
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.endTimeOptional.setValue(logPrint.getBtsTime());
            }
            if(btsLogDelay.startTimeOptional && btsLogDelay.endTimeOptional && btsLogDelay.startTimeOptional.getReference().getTotalSeconds() <= btsLogDelay.endTimeOptional.getReference().getTotalSeconds())
            {
                int delay = getDelayTimeInUs(btsLogDelay.endTimeOptional.getReference(), btsLogDelay.startTimeOptional.getReference());
                maxDelay = std::max(maxDelay, (double)delay);
                totalDelay += delay;
                count++;
                stringstream ss;
                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<","<<setw(10)<<delay;
                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
        }
    }
    cout<<"Average Delay:"<<(double)totalDelay/count<<" Max Delay:"<<maxDelay<<endl;
}

void PerformanceAnalyzer::processFileForRlSetupDelayInTupcWithSymonKnife(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;
    logStringInRawDataFile("crnccId,nbccId,transactionId,totalDelayInRlh,");

    logStringInRawDataFile("rlhRlSetupRequest,");
    logStringInRawDataFile("rlhTbRegisterTime,");
    logStringInRawDataFile("tupcTbRegisterTime,");
    logStringInRawDataFile("tupcFirstErqSent,");
    logStringInRawDataFile("tupcLastEcfReceived,");
    logStringInRawDataFile("tupcFirstTransportConnectionSetup,");
    logStringInRawDataFile("tupcLastTransportConnectionSetupResponse,");
    logStringInRawDataFile("tupcTbRegisterResponseTime,");
    logStringInRawDataFile("rlhTbRegisterResponseTime,");
    logStringInRawDataFile("rlhRlSetupResponse,");

    logStringInRawDataFile("delayInRlSetupToTbRegisterInRlh,");
    logStringInRawDataFile("delayInTbRegisterFromRlhToTupc,");
    //logStringInRawDataFile("delayInCommunicationWithFtm,");
    logStringInRawDataFile("delayInTbRegisterToErqInTupc,");
    logStringInRawDataFile("delayInErqToEcfInFtm,");
    logStringInRawDataFile("delayInEcfToTransportConnectionInTupc,");
    logStringInRawDataFile("delayInTransportConnectionRequestResponseInDsp,");
    logStringInRawDataFile("delayInTransportConnectionResponseToTbRegisterResponseInTupc,");
    logStringInRawDataFile("delayInTbRegisterResponseFromTupcToRlh"
                           ",");
    logLineInRawDataFile("delayInTbRegisterResponseToRlSetupResponseInRlh");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;

    struct TupcDelaysData
    {
        AlbaOptional<BtsLogTime> rlhRlSetupRequestOptional;
        AlbaOptional<BtsLogTime> rlhTbRegisterTimeOptional;
        AlbaOptional<BtsLogTime> tupcTbRegisterTimeOptional;
        AlbaOptional<BtsLogTime> tupcFirstErqSentOptional;
        AlbaOptional<BtsLogTime> tupcLastEcfReceivedOptional;
        AlbaOptional<BtsLogTime> tupcFirstTransportConnectionSetupOptional;
        AlbaOptional<BtsLogTime> tupcLastTransportConnectionSetupResponseOptional;
        AlbaOptional<BtsLogTime> tupcTbRegisterResponseTimeOptional;
        AlbaOptional<BtsLogTime> rlhTbRegisterResponseTimeOptional;
        AlbaOptional<BtsLogTime> rlhRlSetupResponseOptional;
        bool isComplete(int nbccId) const
        {
            return rlhRlSetupRequestOptional&&rlhTbRegisterTimeOptional&&tupcTbRegisterTimeOptional&&
                    tupcFirstErqSentOptional&&tupcLastEcfReceivedOptional&&
                    tupcFirstTransportConnectionSetupOptional&&tupcLastTransportConnectionSetupResponseOptional&&
                    tupcTbRegisterResponseTimeOptional&&rlhTbRegisterResponseTimeOptional&&rlhRlSetupResponseOptional;
        }
        bool isCorrect(int nbccId) const
        {
            if(!isComplete(nbccId))
            {
                return false;
            }
            bool isCorrect = (rlhRlSetupRequestOptional.getReference()<rlhTbRegisterTimeOptional.getReference()) &&
                    (rlhTbRegisterTimeOptional.getReference()<tupcTbRegisterTimeOptional.getReference()) &&
                    //(tupcTbRegisterTimeOptional.getReference()<tupcFirstTransportConnectionSetupOptional.getReference()) &&
                    (tupcTbRegisterTimeOptional.getReference()<tupcFirstErqSentOptional.getReference()) &&
                    (tupcFirstErqSentOptional.getReference()<tupcLastEcfReceivedOptional.getReference()) &&
                    (tupcLastEcfReceivedOptional.getReference()<tupcFirstTransportConnectionSetupOptional.getReference()) &&
                    (tupcFirstTransportConnectionSetupOptional.getReference()<tupcLastTransportConnectionSetupResponseOptional.getReference()) &&
                    (tupcLastTransportConnectionSetupResponseOptional.getReference()<tupcTbRegisterResponseTimeOptional.getReference()) &&
                    (tupcTbRegisterResponseTimeOptional.getReference()<rlhTbRegisterResponseTimeOptional.getReference()) &&
                    (rlhTbRegisterResponseTimeOptional.getReference()<rlhRlSetupResponseOptional.getReference());

            return isCorrect;
        }
    };

    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    std::map<UniqueUserId, TupcDelaysData> tupcLogDelays;
    UniqueUserId tupcRegisterRequestTupcUserId;
    BtsLogPrint ecfLogPrint;

    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay & btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.startTimeOptional.setValue(logPrint.getBtsTime());
                UniqueUserId tupcUserId;
                tupcUserId.saveNbccId(lineInLogs);
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.rlhRlSetupRequestOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH send TC_TRANSPORT_BEARER_REGISTER_MSG)"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.rlhTbRegisterTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Rcvd:TC_TRANSPORT_BEARER_REGISTER_MSG])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcTbRegisterTimeOptional.setValue(logPrint.getBtsTime());
                tupcRegisterRequestTupcUserId = tupcUserId;
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:M_IP_ERQ])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            if(tupcLogDelays.count(tupcRegisterRequestTupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcRegisterRequestTupcUserId];
                if(!tupcLogDelay.tupcFirstErqSentOptional)
                {
                    tupcLogDelay.tupcFirstErqSentOptional.setValue(logPrint.getBtsTime());
                }
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Rcvd[M_IP_ECF])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            ecfLogPrint = logPrint;
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                if(!tupcLogDelay.tupcFirstTransportConnectionSetupOptional)
                {
                    tupcLogDelay.tupcLastEcfReceivedOptional.setValue(ecfLogPrint.getBtsTime());
                    tupcLogDelay.tupcFirstTransportConnectionSetupOptional.setValue(logPrint.getBtsTime());
                }
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([TUP_TRANSPORT_CONNECTION_SETUP_RESP])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:TC_TRANSPORT_BEARER_REGISTER_RESP_MSG])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcTbRegisterResponseTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH receive TC_TRANSPORT_BEARER_REGISTER_RESP_MSG)"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.rlhTbRegisterResponseTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay & btsLogDelay = btsLogDelays[uniqueUserId];
            TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.endTimeOptional.setValue(logPrint.getBtsTime());
                tupcLogDelay.rlhRlSetupResponseOptional.setValue(logPrint.getBtsTime());
            }
            if(tupcLogDelay.isCorrect(tupcUserId.nbccId) && btsLogDelay.startTimeOptional && btsLogDelay.endTimeOptional && btsLogDelay.startTimeOptional.getReference().getTotalSeconds() <= btsLogDelay.endTimeOptional.getReference().getTotalSeconds())
            {
                int delay = getDelayTimeInUs(btsLogDelay.endTimeOptional.getReference(), btsLogDelay.startTimeOptional.getReference());
                if(maxDelay<delay)
                {
                    maxDelay = delay;
                    userIdForMaxDelay = uniqueUserId;
                }
                totalDelay += delay;
                count++;
                stringstream ss;

                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<","<<setw(10)<<delay;

                ss<<","<<setw(10)<<tupcLogDelay.rlhRlSetupRequestOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.rlhTbRegisterTimeOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcTbRegisterTimeOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcFirstErqSentOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcLastEcfReceivedOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcFirstTransportConnectionSetupOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcTbRegisterResponseTimeOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.rlhTbRegisterResponseTimeOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.rlhRlSetupResponseOptional.getReference().getEquivalentStringBtsTimeFormat();

                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.rlhTbRegisterTimeOptional.getReference(), tupcLogDelay.rlhRlSetupRequestOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcTbRegisterTimeOptional.getReference(), tupcLogDelay.rlhTbRegisterTimeOptional.getReference());
                //ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcFirstTransportConnectionSetupOptional.getReference(), tupcLogDelay.tupcTbRegisterTimeOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcFirstErqSentOptional.getReference(), tupcLogDelay.tupcTbRegisterTimeOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcLastEcfReceivedOptional.getReference(), tupcLogDelay.tupcFirstErqSentOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcFirstTransportConnectionSetupOptional.getReference(), tupcLogDelay.tupcLastEcfReceivedOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional.getReference(), tupcLogDelay.tupcFirstTransportConnectionSetupOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcTbRegisterResponseTimeOptional.getReference(), tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.rlhTbRegisterResponseTimeOptional.getReference(), tupcLogDelay.tupcTbRegisterResponseTimeOptional.getReference());
                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.rlhRlSetupResponseOptional.getReference(), tupcLogDelay.rlhTbRegisterResponseTimeOptional.getReference());

                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
            tupcLogDelays.erase(tupcUserId);
        }
    }
    cout<<"Average Delay:"<<(double)totalDelay/count<<" Max Delay:"<<maxDelay<<endl;
    cout<<"User with max delay -> nbccId: "<<userIdForMaxDelay.nbccId<<" crnccId: "<<userIdForMaxDelay.crnccId<<" transactionId: "<<userIdForMaxDelay.transactionId<<endl;
}

void PerformanceAnalyzer::processFileForRlSetupDelayInTupcWithSymonKnifeForFtm(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;
    logStringInRawDataFile("crnccId,nbccId,transactionId,totalDelayInRlh,");

    logStringInRawDataFile("rlhRlSetupRequest,");
    logStringInRawDataFile("tupcTbRegisterTime,");
    logStringInRawDataFile("tupcFirstErqSent,");
    logStringInRawDataFile("tupcLastEcfReceived,");
    logStringInRawDataFile("tupcFirstTransportConnectionSetup,");
    logStringInRawDataFile("rlhRlSetupResponse,");

    logLineInRawDataFile("delayInErqToEcfInFtm,");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;

    struct TupcDelaysData
    {
        AlbaOptional<BtsLogTime> rlhRlSetupRequestOptional;
        AlbaOptional<BtsLogTime> tupcTbRegisterTimeOptional;
        AlbaOptional<BtsLogTime> tupcFirstErqSentOptional;
        AlbaOptional<BtsLogTime> tupcLastEcfReceivedOptional;
        AlbaOptional<BtsLogTime> tupcFirstTransportConnectionSetupOptional;
        AlbaOptional<BtsLogTime> rlhRlSetupResponseOptional;
        bool isComplete(int nbccId) const
        {
            return rlhRlSetupRequestOptional&&tupcTbRegisterTimeOptional&&
                    tupcFirstErqSentOptional&&tupcLastEcfReceivedOptional&&
                    tupcFirstTransportConnectionSetupOptional&&
                    rlhRlSetupResponseOptional;
        }
        bool isCorrect(int nbccId) const
        {
            if(!isComplete(nbccId))
            {
                return false;
            }
            bool isCorrect = (rlhRlSetupRequestOptional.getReference()<tupcTbRegisterTimeOptional.getReference()) &&
                    (tupcTbRegisterTimeOptional.getReference()<tupcFirstErqSentOptional.getReference()) &&
                    (tupcFirstErqSentOptional.getReference()<tupcLastEcfReceivedOptional.getReference()) &&
                    (tupcLastEcfReceivedOptional.getReference()<tupcFirstTransportConnectionSetupOptional.getReference()) &&
                    (tupcFirstTransportConnectionSetupOptional.getReference()<rlhRlSetupResponseOptional.getReference());

            return isCorrect;
        }
    };

    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    std::map<UniqueUserId, TupcDelaysData> tupcLogDelays;
    UniqueUserId tupcRegisterRequestTupcUserId;
    BtsLogPrint ecfLogPrint;

    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay & btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.startTimeOptional.setValue(logPrint.getBtsTime());
                UniqueUserId tupcUserId;
                tupcUserId.saveNbccId(lineInLogs);
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.rlhRlSetupRequestOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Rcvd:TC_TRANSPORT_BEARER_REGISTER_MSG])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcTbRegisterTimeOptional.setValue(logPrint.getBtsTime());
                tupcRegisterRequestTupcUserId = tupcUserId;
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:M_IP_ERQ])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            if(tupcLogDelays.count(tupcRegisterRequestTupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcRegisterRequestTupcUserId];
                if(!tupcLogDelay.tupcFirstErqSentOptional)
                {
                    tupcLogDelay.tupcFirstErqSentOptional.setValue(logPrint.getBtsTime());
                }
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Rcvd[M_IP_ECF])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            ecfLogPrint = logPrint;
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if(tupcLogDelays.count(tupcUserId)>0)
            {
                TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
                if(!tupcLogDelay.tupcFirstTransportConnectionSetupOptional)
                {
                    tupcLogDelay.tupcLastEcfReceivedOptional.setValue(ecfLogPrint.getBtsTime());
                    tupcLogDelay.tupcFirstTransportConnectionSetupOptional.setValue(logPrint.getBtsTime());
                }
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay & btsLogDelay = btsLogDelays[uniqueUserId];
            TupcDelaysData & tupcLogDelay = tupcLogDelays[tupcUserId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.endTimeOptional.setValue(logPrint.getBtsTime());
                tupcLogDelay.rlhRlSetupResponseOptional.setValue(logPrint.getBtsTime());
            }
            if(tupcLogDelay.isCorrect(tupcUserId.nbccId) && btsLogDelay.startTimeOptional && btsLogDelay.endTimeOptional && btsLogDelay.startTimeOptional.getReference().getTotalSeconds() <= btsLogDelay.endTimeOptional.getReference().getTotalSeconds())
            {
                int delay = getDelayTimeInUs(btsLogDelay.endTimeOptional.getReference(), btsLogDelay.startTimeOptional.getReference());
                if(maxDelay<delay)
                {
                    maxDelay = delay;
                    userIdForMaxDelay = uniqueUserId;
                }
                totalDelay += delay;
                count++;
                stringstream ss;

                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<","<<setw(10)<<delay;

                ss<<","<<setw(10)<<tupcLogDelay.rlhRlSetupRequestOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcTbRegisterTimeOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcFirstErqSentOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcLastEcfReceivedOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.tupcFirstTransportConnectionSetupOptional.getReference().getEquivalentStringBtsTimeFormat();
                ss<<","<<setw(10)<<tupcLogDelay.rlhRlSetupResponseOptional.getReference().getEquivalentStringBtsTimeFormat();

                ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcLastEcfReceivedOptional.getReference(), tupcLogDelay.tupcFirstErqSentOptional.getReference());

                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
            tupcLogDelays.erase(tupcUserId);
        }
    }
    cout<<"Average Delay:"<<(double)totalDelay/count<<" Max Delay:"<<maxDelay<<endl;
    cout<<"User with max delay -> nbccId: "<<userIdForMaxDelay.nbccId<<" crnccId: "<<userIdForMaxDelay.crnccId<<" transactionId: "<<userIdForMaxDelay.transactionId<<endl;
}


int PerformanceAnalyzer::getDelayTimeInUs(BtsLogTime const& endTime, BtsLogTime const& startTime) const
{
    BtsLogTime delayTime = endTime-startTime;
    return delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
}

int PerformanceAnalyzer::getDelayTimeInMinutes(BtsLogTime const& endTime, BtsLogTime const& startTime) const
{
    BtsLogTime delayTime = endTime-startTime;
    return delayTime.getMinutes();
}

void PerformanceAnalyzer::processFileForFtmFcmWireshark(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;
    logLineInRawDataFile("saidKey(hex),erqTime,ecfTime,numberInWiresharkOfStart,numberInWiresharkOfEnd,delay");

    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    double endWiresharkTime;
    struct WiresharkLogKey
    {
        unsigned int operation;
        unsigned int said;
        bool operator <(WiresharkLogKey const& key) const
        {
            if(said == key.said)
            {
                return operation < key.operation;
            }
            return said < key.said;
        }

    };
    struct WiresharkLogDelay
    {
        AlbaOptional<double> startTimeOptional;
        AlbaOptional<double> endTimeOptional;
        unsigned int numberInWiresharkOfStart;
        unsigned int numberInWiresharkOfEnd;
    };
    std::map<WiresharkLogKey, WiresharkLogDelay> wiresharkLogDelays;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(No.     Time        Source                Destination)"))
        {
            string nextLine(fileReader.getLineAndIgnoreWhiteSpaces());
            string timeString(stringHelper::getStringInBetweenTwoStrings(nextLine, " ", " "));
            double wiresharkTime = stringHelper::convertStringToNumber<double>(timeString);\
            endWiresharkTime = wiresharkTime;
            unsigned int numberInWireshark = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getStringBeforeThisString(nextLine, " "));
            WiresharkLogKey key;
            while(fileReader.isNotFinished())
            {
                string followingLine(fileReader.getLineAndIgnoreWhiteSpaces());
                if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(followingLine, R"(0000)"))
                {
                    unsigned int msgId = stringHelper::convertHexStringToNumber<unsigned int>(followingLine.substr(18,2));
                    unsigned int upperSaidKey = stringHelper::convertHexStringToNumber<unsigned int>(followingLine.substr(48,5));
                    if(msgId==0x75 || msgId==0x77 || msgId==0x7E)
                    {
                        string followingLine2(fileReader.getLineAndIgnoreWhiteSpaces());
                        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(followingLine2, R"(0010)"))
                        {
                            key.said = 0;//stringHelper::convertHexStringToNumber<unsigned int>(followingLine2.substr(6,11));
                            if(msgId==0x75)
                            {
                                key.operation=1;
                            }
                            else if(msgId==0x77)
                            {
                                key.operation=2;
                            }
                            else if(msgId==0x7E)
                            {
                                key.operation=3;
                            }
                            else
                            {
                                key.operation=4;
                            }
                            WiresharkLogDelay&  wiresharkLogDelay = wiresharkLogDelays[key];

                            wiresharkLogDelay.startTimeOptional.setValue(wiresharkTime);
                            wiresharkLogDelay.numberInWiresharkOfStart = numberInWireshark;

                        }
                    }
                    else if(msgId==0x74 || msgId==0x76 || msgId==0x7C)
                    {
                        string followingLine2(fileReader.getLineAndIgnoreWhiteSpaces());
                        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(followingLine2, R"(0010)"))
                        {
                            unsigned int lowerSaidKey = stringHelper::convertHexStringToNumber<unsigned int>(followingLine2.substr(6,5));
                            key.said = 0;//((upperSaidKey&0xFFFF)<<16) | (lowerSaidKey&0xFFFF);
                            if(msgId==0x74)
                            {
                                key.operation=1;
                            }
                            else if(msgId==0x76)
                            {
                                key.operation=2;
                            }
                            else if(msgId==0x7C)
                            {
                                key.operation=3;
                            }
                            else
                            {
                                key.operation=4;
                            }
                            WiresharkLogDelay&  wiresharkLogDelay = wiresharkLogDelays[key];
                            wiresharkLogDelay.endTimeOptional.setValue(wiresharkTime);
                            wiresharkLogDelay.numberInWiresharkOfEnd = numberInWireshark;
                        }
                    }
                    break;
                }
            }
            WiresharkLogDelay& checkWiresharkLogDelay = wiresharkLogDelays[key];
            if(checkWiresharkLogDelay.startTimeOptional && checkWiresharkLogDelay.endTimeOptional && checkWiresharkLogDelay.startTimeOptional.getReference() <= checkWiresharkLogDelay.endTimeOptional.getReference())
            {
                double delay = checkWiresharkLogDelay.endTimeOptional.getReference() - checkWiresharkLogDelay.startTimeOptional.getReference();
                maxDelay = std::max(maxDelay, delay);
                totalDelay += delay;
                count++;
                stringstream ss;
                ss<<"0x"<<std::hex<<key.said<<",";
                ss.precision(17);
                ss<<std::dec
                 <<checkWiresharkLogDelay.startTimeOptional.getReference()<<","
                <<checkWiresharkLogDelay.endTimeOptional.getReference()<<","
                <<checkWiresharkLogDelay.numberInWiresharkOfStart<<","
                <<checkWiresharkLogDelay.numberInWiresharkOfEnd<<","
                <<setw(17)<<delay;
                logLineInRawDataFile(ss.str());
                wiresharkLogDelays.erase(key);
            }
        }
    }
    cout<<"Average Delay:"<<(double)totalDelay/count<<" Max Delay:"<<maxDelay<<endl;
    cout<<"endWiresharkTime:"<<endWiresharkTime<<endl;
}

void PerformanceAnalyzer::processFileForTopLogs(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;

    double maxCpuTcom = 0;
    double maxCpuTupcConman = 0;
    double maxCpuTcomAalman = 0;
    double startTime=0, endTime=0;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(lineInLogs.length()>80)
        {
            double cpuLoad = stringHelper::convertStringToNumber<double>(lineInLogs.substr(62,5));

            if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(`- TC+)"))
            {
                maxCpuTcom = std::max(maxCpuTcom, cpuLoad);
            }
            else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(`- CO+)"))
            {
                maxCpuTupcConman = std::max(maxCpuTupcConman, cpuLoad);
            }
            else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(`- Aa+)"))
            {
                maxCpuTcomAalman = std::max(maxCpuTcomAalman, cpuLoad);
            }
            else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(top - )"))
            {
                string time = stringHelper::getStringInBetweenTwoStrings(lineInLogs, "top - ", " ");
                unsigned int hours = stringHelper::convertStringToNumber<unsigned int>(time.substr(0,2));
                unsigned int mins = stringHelper::convertStringToNumber<unsigned int>(time.substr(3,2));
                unsigned int secs = stringHelper::convertStringToNumber<unsigned int>(time.substr(5,2));
                double totalTime = ((((double)hours*60)+mins)*60)+secs;
                if(startTime==0)
                {
                    startTime = totalTime;
                }
                endTime = totalTime;
            }
        }
    }
    cout<<"Max CPU TCOM:"<<maxCpuTcom<<endl;
    cout<<"Max CPU TUP Conman:"<<maxCpuTupcConman<<endl;
    cout<<"Max CPU TUP Aalman:"<<maxCpuTcomAalman<<endl;
    double duration = endTime - startTime;
    //cout<<"duration min:"<<duration/60<<" sec:"<<((int)duration)%60<<endl; // di reliable
}

}
