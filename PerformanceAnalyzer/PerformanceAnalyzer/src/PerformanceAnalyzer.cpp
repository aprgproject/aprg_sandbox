#include "PerformanceAnalyzer.hpp"

#include <AprgFileExtractor.hpp>
#include <BtsLogSorter.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace alba::stringHelper;
using namespace std;
using tcomToolsBackend::BtsLogPrint;
using tcomToolsBackend::BtsLogTime;
using tcomToolsBackend::BtsLogTimeType;

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
    int logCrnccId = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
    int logCrncId = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crncId: "));
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
    int nbccid = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccid: "));
    int nbccId = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
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
    return convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
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
    AlbaLocalPathHandler pathHandler(R"(C:\temp\BtsSorter\)");
    pathHandler.createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_condition = R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )";
    m_sorterConfiguration.m_pathOfTempFiles = pathHandler.getFullPath();
    pathHandler.createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks = pathHandler.getFullPath() + R"(WithPcTimeBlocks\)";
    AlbaLocalPathHandler(m_sorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks).createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams = 50;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks = pathHandler.getFullPath() + R"(WithoutPcTimeBlocks\)";
    AlbaLocalPathHandler(m_sorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks).createDirectoriesForNonExisitingDirectories();
    m_sorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 1000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams = 70;
}

string PerformanceAnalyzer::extract(string const& inputPath) const
{
    cout<<" (Extract) start | Input path: "<<inputPath<<endl;
    AprgFileExtractor fileExtractor(m_extractGrepCondition);
    AlbaLocalPathHandler pathHandler(inputPath);
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
    AlbaLocalPathHandler pathHandler(inputPath);
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

void PerformanceAnalyzer::processFileForMsgQueueingTime(string const& filePath)
{
    AlbaLocalPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    int totalMsgQueueingTime = 0;
    int highestMsgQueueingTime = 0;
    int numberOfInstances=0;

    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "MSG TIME, start queuing time"))
        {
            int msgQueueingTime = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgQueuingTime: "));
            totalMsgQueueingTime += msgQueueingTime;
            highestMsgQueueingTime = std::max(msgQueueingTime, highestMsgQueueingTime);
            logLineInRawDataFile(lineInLogs);
            numberOfInstances++;
        }
    }
    cout<<"TotalMsgQueueingTime: "<<totalMsgQueueingTime<<endl;
    cout<<"highestMsgQueueingTime: "<<highestMsgQueueingTime<<endl;
    cout<<"AverageMsgQueueingTime: "<<((double)totalMsgQueueingTime)/numberOfInstances<<endl;
    cout<<"numberOfPrints: "<<numberOfInstances<<endl;
}


void PerformanceAnalyzer::processFileForRlSetupDelayInRlh(string const& filePath)
{
    AlbaLocalPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;
    logLineInRawDataFile("crnccId,nbccId,transactionId,isSuccessful,delay");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    int countFail = 0;
    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    BtsLogTime startTest, endTest;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
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
                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<",successful"<<","<<setw(10)<<delay;
                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupFail3G)"))
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
                countFail++;
                stringstream ss;
                ss<<uniqueUserId.crnccId<<","<<uniqueUserId.nbccId<<","<<uniqueUserId.transactionId<<",fail"<<","<<setw(10)<<delay;
                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
        }
    }
    cout.precision(10);
    cout<<"Average Delay(ms): "<<(double)totalDelay/count/1000<<endl;
    cout<<"Max Delay(ms): "<<maxDelay/1000<<endl;
    cout<<"User with max delay -> nbccId: "<<userIdForMaxDelay.nbccId<<" crnccId: "<<userIdForMaxDelay.crnccId<<" transactionId: "<<userIdForMaxDelay.transactionId<<endl;
    cout<<"RL setup success count: "<<count<<endl;
    cout<<"RL setup failures count: "<<countFail<<endl;
    BtsLogTime delayTime = endTest-startTest;
    cout<<"Test Duration: "<<delayTime.getEquivalentStringBtsTimeFormat()<<endl;
}

void PerformanceAnalyzer::processFileForRlDeletionDelayInRlh(string const& filePath)
{
    AlbaLocalPathHandler filePathHandler(filePath);
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
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)"))
        {
            UniqueUserId uniqueUserId(lineInLogs);
            BtsLogDelay & btsLogDelay(btsLogDelays[uniqueUserId]);
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                btsLogDelay.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)"))
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
    cout.precision(10);
    cout<<"Average Delay(ms): "<<(double)totalDelay/count/1000<<endl;
    cout<<"Max Delay(ms): "<<maxDelay/1000<<endl;
}

void PerformanceAnalyzer::processFileForPeriodicCpuLogging(string const& filePath)
{
    AlbaLocalPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    logLineInRawDataFile("subsystem,inProcess,inSystem,threadCpuTimeSpent");

    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Periodic CPU Usage Report)")
                || isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(printCpuDataCollection)"))
        {
            string subsystem("Unknown");
            if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TCOM/CM)"))
            {
                subsystem = "CMEAS";
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TCOM/DM)"))
            {
                subsystem = "DMEAS";
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TCOM/G)"))
            {
                subsystem = "GRM";
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TCOM/LRM)"))
            {
                subsystem = "LRM";
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TCOM/R)"))
            {
                subsystem = "RLH";
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TCOM/WRC)"))
            {
                subsystem = "WRC";
            }
            double inProcess = convertStringToNumber<double>(getStringInBetweenTwoStrings(lineInLogs, "inProcess:" , "%"));
            double inSystem = convertStringToNumber<double>(getStringInBetweenTwoStrings(lineInLogs, "inSystem:" , "%"));
            string threadCpuTimeSpent(getStringInBetweenTwoStrings(lineInLogs, "threadCpuTimeSpent:" , " ("));
            stringstream ss;
            ss<<subsystem<<","<<inProcess<<","<<inSystem<<","<<threadCpuTimeSpent;
            logLineInRawDataFile(ss.str());
        }
    }
}

void PerformanceAnalyzer::processFileForRlSetupDelayInTupcWithSymonKnife(string const& filePath)
{
    AlbaLocalPathHandler filePathHandler(filePath);
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
            bool isCorrect = (rlhRlSetupRequestOptional.getConstReference()<rlhTbRegisterTimeOptional.getConstReference()) &&
                    (rlhTbRegisterTimeOptional.getConstReference()<tupcTbRegisterTimeOptional.getConstReference()) &&
                    //(tupcTbRegisterTimeOptional.getConstReference()<tupcFirstTransportConnectionSetupOptional.getConstReference()) &&
                    (tupcTbRegisterTimeOptional.getConstReference()<tupcFirstErqSentOptional.getConstReference()) &&
                    (tupcFirstErqSentOptional.getConstReference()<tupcLastEcfReceivedOptional.getConstReference()) &&
                    (tupcLastEcfReceivedOptional.getConstReference()<tupcFirstTransportConnectionSetupOptional.getConstReference()) &&
                    (tupcFirstTransportConnectionSetupOptional.getConstReference()<tupcLastTransportConnectionSetupResponseOptional.getConstReference()) &&
                    (tupcLastTransportConnectionSetupResponseOptional.getConstReference()<tupcTbRegisterResponseTimeOptional.getConstReference()) &&
                    (tupcTbRegisterResponseTimeOptional.getConstReference()<rlhTbRegisterResponseTimeOptional.getConstReference()) &&
                    (rlhTbRegisterResponseTimeOptional.getConstReference()<rlhRlSetupResponseOptional.getConstReference());

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
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH send TC_TRANSPORT_BEARER_REGISTER_MSG)"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Rcvd:TC_TRANSPORT_BEARER_REGISTER_MSG])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:M_IP_ERQ])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Rcvd[M_IP_ECF])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            ecfLogPrint = logPrint;
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([TUP_TRANSPORT_CONNECTION_SETUP_RESP])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:TC_TRANSPORT_BEARER_REGISTER_RESP_MSG])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH receive TC_TRANSPORT_BEARER_REGISTER_RESP_MSG)"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
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
    AlbaLocalPathHandler filePathHandler(filePath);
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
            bool isCorrect = (rlhRlSetupRequestOptional.getConstReference()<tupcTbRegisterTimeOptional.getConstReference()) &&
                    (tupcTbRegisterTimeOptional.getConstReference()<tupcFirstErqSentOptional.getConstReference()) &&
                    (tupcFirstErqSentOptional.getConstReference()<tupcLastEcfReceivedOptional.getConstReference()) &&
                    (tupcLastEcfReceivedOptional.getConstReference()<tupcFirstTransportConnectionSetupOptional.getConstReference()) &&
                    (tupcFirstTransportConnectionSetupOptional.getConstReference()<rlhRlSetupResponseOptional.getConstReference());

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
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Rcvd:TC_TRANSPORT_BEARER_REGISTER_MSG])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:M_IP_ERQ])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Rcvd[M_IP_ECF])"))
        {
            BtsLogPrint logPrint(lineInLogs);
            ecfLogPrint = logPrint;
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"([Sent:TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG])"))
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
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
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
    AlbaLocalPathHandler filePathHandler(filePath);
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
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(No.     Time        Source                Destination)"))
        {
            string nextLine(fileReader.getLineAndIgnoreWhiteSpaces());
            string timeString(getStringInBetweenTwoStrings(nextLine, " ", " "));
            double wiresharkTime = convertStringToNumber<double>(timeString);\
            endWiresharkTime = wiresharkTime;
            unsigned int numberInWireshark = convertStringToNumber<unsigned int>(getStringBeforeThisString(nextLine, " "));
            WiresharkLogKey key;
            while(fileReader.isNotFinished())
            {
                string followingLine(fileReader.getLineAndIgnoreWhiteSpaces());
                if(isStringFoundInsideTheOtherStringNotCaseSensitive(followingLine, R"(0000)"))
                {
                    unsigned int msgId = convertHexStringToNumber<unsigned int>(followingLine.substr(18,2));
                    unsigned int upperSaidKey = convertHexStringToNumber<unsigned int>(followingLine.substr(48,5));
                    if(msgId==0x75 || msgId==0x77 || msgId==0x7E)
                    {
                        string followingLine2(fileReader.getLineAndIgnoreWhiteSpaces());
                        if(isStringFoundInsideTheOtherStringNotCaseSensitive(followingLine2, R"(0010)"))
                        {
                            key.said = 0;//convertHexStringToNumber<unsigned int>(followingLine2.substr(6,11));
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
                        if(isStringFoundInsideTheOtherStringNotCaseSensitive(followingLine2, R"(0010)"))
                        {
                            unsigned int lowerSaidKey = convertHexStringToNumber<unsigned int>(followingLine2.substr(6,5));
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
    AlbaLocalPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;

    double maxCpuTcomLrm = 0;
    double maxCpuTcomGrm = 0;
    double maxCpuTcomRlh = 0;
    double maxCpuTupcConman = 0;
    double maxCpuTcomAalman = 0;
    double maxTotalCpu = 0;
    double maxTotalCpuFromTop;
    vector<string> processNames;
    vector<double> cpuConsumptions;
    unsigned int state=0;
    int cpuIndexInLine=0;
    int commmandIndexInLine=0;
    stringstream masterStringStream;
    double totalCpuFromTop(0);
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());

        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "=~=~=~=~=~=~=~=~=~=~=~=") || isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "top - "))
        {
            state=1;
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "PID") &&
                isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "%CPU") &&
                isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "COMMAND"))
        {
            state=2;
            cpuIndexInLine = lineInLogs.find("%CPU");
            commmandIndexInLine = lineInLogs.find("COMMAND");

            double totalCpu(0);
            stringstream ss;
            for(int i=0; i<cpuConsumptions.size(); i++)
            {
                totalCpu+=cpuConsumptions[i];
                //ss<<processNames[i]<<":";
                ss<<cpuConsumptions[i]<<", ";
                cpuConsumptions[i] = 0;
            }
            masterStringStream<<totalCpuFromTop<<", "<<totalCpu<<", "<<ss.str()<<endl;
            maxTotalCpu = std::max(maxTotalCpu, totalCpu);
            totalCpuFromTop=0;
        }
        else if(state==1 && isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "%Cpu0  :"))
        {
            unsigned int bracketCpuIndexInLine(lineInLogs.find("["));
            totalCpuFromTop = convertStringToNumber<double>(lineInLogs.substr(bracketCpuIndexInLine-3, 3));
            maxTotalCpuFromTop = std::max(maxTotalCpuFromTop, totalCpuFromTop);
        }
        if(state==2 && isNotNpos(commmandIndexInLine) && isNotNpos(cpuIndexInLine)
                && commmandIndexInLine<lineInLogs.length() && cpuIndexInLine+5<lineInLogs.length())
        {
            string processName(getStringWithoutStartingAndTrailingWhiteSpace(lineInLogs.substr(commmandIndexInLine)));
            double cpuLoad = convertStringToNumber<double>(lineInLogs.substr(cpuIndexInLine,5));
            if(cpuLoad>0 && processName!="`- top")
            {
                int i=0;
                bool isFound(false);
                for(; i<processNames.size(); i++)
                {
                    if(processNames[i] == processName)
                    {
                        isFound = true;
                        break;
                    }
                }
                if(isFound)
                {
                    cpuConsumptions[i]=cpuLoad;
                }
                else
                {
                    processNames.emplace_back(processName);
                    cpuConsumptions.emplace_back(cpuLoad);
                }
            }

            if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(_LRM_)"))
            {
                maxCpuTcomLrm = std::max(maxCpuTcomLrm, cpuLoad);
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(_GRM_)"))
            {
                maxCpuTcomGrm = std::max(maxCpuTcomGrm, cpuLoad);
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(_RLH_)"))
            {
                maxCpuTcomRlh = std::max(maxCpuTcomRlh, cpuLoad);
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Conman_EU)"))
            {
                maxCpuTupcConman = std::max(maxCpuTupcConman, cpuLoad);
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Aalman_EU)"))
            {
                maxCpuTcomAalman = std::max(maxCpuTcomAalman, cpuLoad);
            }
        }
    }
    cout<<"Max Total CPU from TOP:"<<maxTotalCpuFromTop<<endl;
    cout<<"Max Total CPU:"<<maxTotalCpu<<endl;
    cout<<"Max CPU GRM TCOM:"<<maxCpuTcomGrm<<endl;
    cout<<"Max CPU LRM TCOM:"<<maxCpuTcomLrm<<endl;
    cout<<"Max CPU RLH TCOM:"<<maxCpuTcomRlh<<endl;
    cout<<"Max CPU TUP Conman:"<<maxCpuTupcConman<<endl;
    cout<<"Max CPU TUP Aalman:"<<maxCpuTcomAalman<<endl;

    stringstream ss;
    ss<<"totalCpuFromTop, totalCpu, ";
    for(int i=0; i<processNames.size(); i++)
    {
        ss<<processNames[i]<<", ";
    }
    logLineInRawDataFile(ss.str());
    logLineInRawDataFile(masterStringStream.str());
}

void PerformanceAnalyzer::processFileForTopLogsMem(string const& filePath)
{
    AlbaLocalPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;

    double maxMemTcomLrm = 0;
    double maxMemTcomGrm = 0;
    double maxMemTupcConman = 0;
    double maxMemTcomAalman = 0;
    vector<string> processNames;
    vector<double> memConsumptions;
    unsigned int state=0;
    int memIndexInLine=0;
    int commmandIndexInLine=0;
    stringstream masterStringStream;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());

        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "=~=~=~=~=~=~=~=~=~=~=~=") || isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "top - "))
        {
            state=1;
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "PID") &&
                isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "MEM") &&
                isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, "COMMAND"))
        {
            state=2;
            memIndexInLine = lineInLogs.find("MEM");
            commmandIndexInLine = lineInLogs.find("COMMAND");

            double totalMem(0);
            stringstream ss;
            for(int i=0; i<memConsumptions.size(); i++)
            {
                totalMem+=memConsumptions[i];
                //ss<<processNames[i]<<":";
                ss<<memConsumptions[i]<<", ";
                memConsumptions[i] = 0;
            }
            masterStringStream<<totalMem<<", "<<ss.str()<<endl;
        }
        if(state==2 && isNotNpos(commmandIndexInLine) && isNotNpos(memIndexInLine)
                && commmandIndexInLine<lineInLogs.length() && memIndexInLine+5<lineInLogs.length())
        {
            string processName(getStringWithoutStartingAndTrailingWhiteSpace(lineInLogs.substr(commmandIndexInLine)));
            double memLoad = convertStringToNumber<double>(lineInLogs.substr(memIndexInLine-1,4));
            if(memLoad>0 && processName!="`- top")
            {
                int i=0;
                bool isFound(false);
                for(; i<processNames.size(); i++)
                {
                    if(processNames[i] == processName)
                    {
                        isFound = true;
                        break;
                    }
                }
                if(isFound)
                {
                    memConsumptions[i]=memLoad;
                }
                else
                {
                    processNames.emplace_back(processName);
                    memConsumptions.emplace_back(memLoad);
                }
            }

            if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(_LRM_)"))
            {
                maxMemTcomLrm = std::max(maxMemTcomLrm, memLoad);
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TCOM_GRM_TASK)"))
            {
                maxMemTcomGrm = std::max(maxMemTcomGrm, memLoad);
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Conman_EU)"))
            {
                maxMemTupcConman = std::max(maxMemTupcConman, memLoad);
            }
            else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(Aalman_EU)"))
            {
                maxMemTcomAalman = std::max(maxMemTcomAalman, memLoad);
            }
        }
    }
    cout<<"Max MEM GRM TCOM:"<<maxMemTcomGrm<<endl;
    cout<<"Max MEM LRM TCOM:"<<maxMemTcomLrm<<endl;
    cout<<"Max MEM TUP Conman:"<<maxMemTupcConman<<endl;
    cout<<"Max MEM TUP Aalman:"<<maxMemTcomAalman<<endl;

    stringstream ss;
    ss<<"totalMEM, ";
    for(int i=0; i<processNames.size(); i++)
    {
        ss<<processNames[i]<<", ";
    }
    logLineInRawDataFile(ss.str());
    logLineInRawDataFile(masterStringStream.str());
}

void PerformanceAnalyzer::processFileForRlSetupPerSecond(string const& filePath)
{
    AlbaLocalPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;
    logLineInRawDataFile("BtsTime,instances");

    int hour = 0, min = 0, sec = 0, instances=0;
    BtsLogTime firstLogTime;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        BtsLogPrint logPrint(lineInLogs);
            BtsLogTime logTime (logPrint.getBtsTime());

            int hourOffsetForDay=0;
            //cout<<"hourOffsetForDay"<<hourOffsetForDay<<"D1:"<<firstLogTime.getDays()<<"D1:"<<logTime.getDays()<<endl;
            if(!logTime.isStartup())
            {
                if((hour == logTime.getHours()) && (min == logTime.getMinutes()) && (sec == logTime.getSeconds()))
                {
                    instances++;
                }
                else
                {
                    stringstream ss;
                    ss<<hour<<":"<<min<<":"<<sec<<","<<instances;
                    logLineInRawDataFile(ss.str());
                    hour = logTime.getHours(); min = logTime.getMinutes(); sec = logTime.getSeconds();
                    instances=1;
                }
        }
    }
    stringstream ss;
    ss<<hour<<":"<<min<<":"<<sec<<","<<instances;
    logLineInRawDataFile(ss.str());

}

void PerformanceAnalyzer::processFileForTraceLog(string const& traceLogPath)
{
    AlbaLocalPathHandler filePathHandler(traceLogPath);
    ifstream inputLogFileStream(traceLogPath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;

    int hour = 0, min = 0, sec = 0, rlSetups=0;

    stringstream ss;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(START time=)"))
        {
            hour = convertStringToNumber<int>(lineInLogs.substr(22,2));
            min = convertStringToNumber<int>(lineInLogs.substr(25,2));
            sec = convertStringToNumber<int>(lineInLogs.substr(28,2));
            ss<<hour<<":"<<min<<":"<<sec<<",";
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(STOP  time=)"))
        {
            hour = convertStringToNumber<int>(lineInLogs.substr(22,2));
            min = convertStringToNumber<int>(lineInLogs.substr(25,2));
            sec = convertStringToNumber<int>(lineInLogs.substr(28,2));
            ss<<hour<<":"<<min<<":"<<sec;
        }
    }
    logLineInRawDataFile(ss.str());
}

void PerformanceAnalyzer::processDirectoryForTraceLog(string const& traceLogPath)
{
    logLineInRawDataFile("StartTime,EndTime");
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaLocalPathHandler(traceLogPath).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(filePath, "trace"))
        {
            processFileForTraceLog(AlbaLocalPathHandler(filePath).getFullPath());
        }
    }
}


}
