#include "BtsLogAnalyzer.hpp"

#include <Container/AlbaRange.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;
using tcomToolsBackend::BtsLogPrint;
using tcomToolsBackend::BtsLogTime;using tcomToolsBackend::BtsLogTimeType;

namespace alba
{
BtsLogAnalyzer::PrintsAvailable::PrintsAvailable()
    : hasBB_2_RL_SETUP_REQ_MSG(false)
    , hasBB_2_RL_SETUP_ACK_MSG(false)
    , hasTC_TRANSPORT_BEARER_REGISTER_MSG(false)
    , hasTC_TRANSPORT_BEARER_REGISTER_RESP_MSG(false)
{}

BtsLogAnalyzer::BtsLogAnalyzer()
    : m_btsLogPathHandler("")
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

    m_btsLogPathHandler.input(pathOfBtsSortedLog);
    ifstream inputLogFileStream(m_btsLogPathHandler.getFullPath());
    initializeMessageQueueingTimeFileStream();
    initializeRlSetupTimeFileStream();
    initializeRlSetupPerSecondFileStream();
    initializeRlDeletionTimeFileStream();
    initializeRlSetupPerSecondFileStream();
    initializeDataDumpOfAllDspsForR3();

    AlbaFileReader fileReader(inputLogFileStream);
    LogTimePairs rlSetupLogTimePairs;    LogTimePairs rlDeletionLogTimePairs;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        saveQueueingTime(lineInLogs);
        saveRlhSetupTime(lineInLogs, rlSetupLogTimePairs);
        saveRlhDeletionTime(lineInLogs, rlDeletionLogTimePairs);
        saveAdditionalPrintsRlSetup(lineInLogs, rlSetupLogTimePairs);
        saveRlSetupPerSecond(lineInLogs);
        saveDspCapacityInformationForR3(lineInLogs);
    }
}

void BtsLogAnalyzer::initializeMessageQueueingTimeFileStream()
{
    AlbaLocalPathHandler messageQueueingTimeFilePathHandler(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_MessageQueueingTime.csv");
    messageQueueingTimeFileStreamOptional.createObjectUsingDefaultConstructor();
    ofstream& messageQueueingTimeFileStream(messageQueueingTimeFileStreamOptional.getReference());
    messageQueueingTimeFileStream.open(messageQueueingTimeFilePathHandler.getFullPath());
    messageQueueingTimeFileStream.precision(20);
    messageQueueingTimeFileStream<<"QueueingTime,LogPrint"<<endl;
}

void BtsLogAnalyzer::initializeRlSetupTimeFileStream()
{
    AlbaLocalPathHandler rlSetupTimeFilePathHandler(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_RlSetupTime.csv");
    rlSetupTimeFileStreamOptional.createObjectUsingDefaultConstructor();
    ofstream& rlSetupTimeFileStream(rlSetupTimeFileStreamOptional.getReference());
    rlSetupTimeFileStream.open(rlSetupTimeFilePathHandler.getFullPath());
    rlSetupTimeFileStream.precision(20);
    rlSetupTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency(microseconds),BB_2_RL_SETUP_REQ_MSG,BB_2_RL_SETUP_ACK_MSG,TC_TRANSPORT_BEARER_REGISTER_MSG,TC_TRANSPORT_BEARER_REGISTER_RESP_MSG"<<endl;
}

void BtsLogAnalyzer::initializeRlDeletionTimeFileStream()
{
    AlbaLocalPathHandler rlDeletionTimeFilePathHandler(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_RlDeletionTime.csv");
    rlDeletionTimeFileStreamOptional.createObjectUsingDefaultConstructor();
    ofstream& rlDeletionTimeFileStream(rlDeletionTimeFileStreamOptional.getReference());
    rlDeletionTimeFileStream.open(rlDeletionTimeFilePathHandler.getFullPath());
    rlDeletionTimeFileStream.precision(20);
    rlDeletionTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency(microseconds),BB_2_RL_SETUP_REQ_MSG,BB_2_RL_SETUP_ACK_MSG,TC_TRANSPORT_BEARER_REGISTER_MSG,TC_TRANSPORT_BEARER_REGISTER_RESP_MSG"<<endl;
}

void BtsLogAnalyzer::initializeRlSetupPerSecondFileStream()
{
    AlbaLocalPathHandler rlSetupPerSecondFilePathHandler(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_RlSetupPerSecond.csv");
    rlSetupPerSecondFileStreamOptional.createObjectUsingDefaultConstructor();
    ofstream& rlSetupPerSecondFileStream(rlSetupPerSecondFileStreamOptional.getReference());
    rlSetupPerSecondFileStream.open(rlSetupPerSecondFilePathHandler.getFullPath());
    rlSetupPerSecondFileStream.precision(20);
    rlSetupPerSecondFileStream<<"Time,Number Of RL setup in a second"<<endl;
}

void BtsLogAnalyzer::saveDspCapacityInformationForR3(string const& lineInLogs)
{
    if(isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "printDspCapacityInd(): 0x"))
    {
        BtsLogPrint logPrint(lineInLogs);
        strings dspCapacitiesPerDsp;
        splitToStrings<SplitStringType::WithoutDelimeters>(dspCapacitiesPerDsp, lineInLogs, " ");
        unsigned int boardId(convertHexStringToNumber<unsigned int>(getStringInBetweenTwoStrings(lineInLogs, "0x", " ")));
        for(string const& dspCapacityOfOneDsp : dspCapacitiesPerDsp)
        {
            saveDspCapacityInformationOfOneDspForR3(dspCapacityOfOneDsp, boardId, logPrint);
        }
    }
}
void BtsLogAnalyzer::saveDspCapacityInformationOfOneDspForR3(string const& dspCapacityOfOneDsp, unsigned int const boardId, BtsLogPrint const& logPrint)
{
    bool isDspDataFilled(false);
    DspData dspData;
    dspData.boardId=boardId;
    strings delimetersBeforeCni1738{"{", "}", ":", "/", "[", ",", ",", ",", "]", "[", ",", ",", "]"};
    strings delimetersAfterCni1738{"{", "}", ":", "/", "[", ",", ",", ",", ",", "]", "[", ",", ",", "]"};
    strings valuesWithBeforeCni1738;
    strings valuesWithAfterCni1738;
    splitToStringsUsingASeriesOfDelimeters(valuesWithBeforeCni1738, dspCapacityOfOneDsp, delimetersBeforeCni1738);
    splitToStringsUsingASeriesOfDelimeters(valuesWithAfterCni1738, dspCapacityOfOneDsp, delimetersAfterCni1738);

    if(valuesWithBeforeCni1738.size()==11)
    {
        strings & values(valuesWithBeforeCni1738);
        dspData.lcgId = convertStringToNumber<unsigned int>(values[0]);
        dspData.cpuId = convertHexStringToNumber<unsigned int>(values[1]);
        dspData.availableUlCEs = convertStringToNumber<unsigned int>(values[2]);
        dspData.availableDlCEs = convertStringToNumber<unsigned int>(values[3]);
        dspData.rakeState = convertStringToNumber<unsigned int>(values[4]);
        dspData.rachHand = convertStringToNumber<unsigned int>(values[5]);
        dspData.rakeLoad = convertStringToNumber<unsigned int>(values[6]);
        dspData.hsupaCFs = convertStringToNumber<unsigned int>(values[7]);
        dspData.hsupaUsers = convertStringToNumber<unsigned int>(values[8]);
        dspData.nbrOfEnhHsupaUsers = convertStringToNumber<unsigned int>(values[9]);
        dspData.dchUsers = convertStringToNumber<unsigned int>(values[10]);
        isDspDataFilled=true;
    }
    if(valuesWithAfterCni1738.size()==12)
    {
        strings & values(valuesWithAfterCni1738);
        dspData.lcgId = convertStringToNumber<unsigned int>(values[0]);
        dspData.cpuId = convertHexStringToNumber<unsigned int>(values[1]);
        dspData.availableUlCEs = convertStringToNumber<unsigned int>(values[2]);
        dspData.availableDlCEs = convertStringToNumber<unsigned int>(values[3]);
        dspData.rakeState = convertStringToNumber<unsigned int>(values[4]);
        dspData.rachHand = convertStringToNumber<unsigned int>(values[5]);
        dspData.rakeLoad = convertStringToNumber<unsigned int>(values[6]);
        dspData.hsupaCFs = convertStringToNumber<unsigned int>(values[7]);
        dspData.hsRachCFs = convertStringToNumber<unsigned int>(values[8]);
        dspData.hsupaUsers = convertStringToNumber<unsigned int>(values[9]);
        dspData.nbrOfEnhHsupaUsers = convertStringToNumber<unsigned int>(values[10]);
        dspData.dchUsers = convertStringToNumber<unsigned int>(values[11]);
        isDspDataFilled=true;
    }
    if(isDspDataFilled)
    {
        unsigned int dspAddress = (dspData.boardId<<8) | dspData.cpuId;
        stringstream ss;
        ss<<std::hex<<dspAddress;
        //saveDataDumpOfOneDsp(ss.str(), dspData, logPrint);
        saveDspInformation(dspAddress, dspData);
        saveTotalUsersAndCfs(logPrint);
        saveAllUsersAndCfs(logPrint);
        //saveMaxDspInformation(dspData);
        //saveDataDumpOfOneDsp("MaxDspInfo", m_maxDspData, logPrint);
    }
}


void BtsLogAnalyzer::saveDspCapacityInformationForR2(string const& lineInLogs)
{
    if(isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "INF/TCOM/LRM/Rep, |0x"))
    {
        BtsLogPrint logPrint(lineInLogs);
        strings dspCapacitiesPerDsp;
        string logsAfterLrmPrint(getStringAfterThisString(lineInLogs, "INF/TCOM/LRM/Rep"));
        splitToStrings<SplitStringType::WithoutDelimeters>(dspCapacitiesPerDsp, logsAfterLrmPrint, "(");
        unsigned int boardId(convertHexStringToNumber<unsigned int>(getStringInBetweenTwoStrings(lineInLogs, ",0x", "-")));
        for(string const& dspCapacityOfOneDsp : dspCapacitiesPerDsp)
        {
            saveDspCapacityInformationOfOneDspForR2(dspCapacityOfOneDsp, boardId, logPrint);        }
    }
}

void BtsLogAnalyzer::saveDspCapacityInformationOfOneDspForR2(string const& dspCapacityOfOneDsp, unsigned int const boardId, BtsLogPrint const& logPrint)
{
    bool isDspDataFilled(false);
    DspData dspData;
    dspData.boardId=boardId;
    strings delimetersBeforeCni1738{":", "/", "[", ",", ",", ",", ",", ",", "]"};
    strings delimetersAfterCni1738{":", "/", "[", ",", ",", ",", ",", ",", ",", "]"};
    strings valuesWithBeforeCni1738;
    strings valuesWithAfterCni1738;
    splitToStringsUsingASeriesOfDelimeters(valuesWithBeforeCni1738, dspCapacityOfOneDsp, delimetersBeforeCni1738);
    splitToStringsUsingASeriesOfDelimeters(valuesWithAfterCni1738, dspCapacityOfOneDsp, delimetersAfterCni1738);

    if(valuesWithBeforeCni1738.size()==9)
    {
        strings & values(valuesWithBeforeCni1738);
        dspData.cpuId = convertHexStringToNumber<unsigned int>(values[0]);
        dspData.availableDlCEs = convertStringToNumber<unsigned int>(values[1]);
        dspData.availableUlCEs = convertStringToNumber<unsigned int>(values[2]);
        dspData.rakeState = convertStringToNumber<unsigned int>(values[3]);
        dspData.rachHand = convertStringToNumber<unsigned int>(values[4]);
        dspData.rakeLoad = convertStringToNumber<unsigned int>(values[5]);
        dspData.hsupaCFs = convertStringToNumber<unsigned int>(values[6]);
        dspData.hsupaUsers = convertStringToNumber<unsigned int>(values[7]);
        dspData.dchUsers = convertStringToNumber<unsigned int>(values[8]);
        isDspDataFilled=true;
    }
    if(valuesWithAfterCni1738.size()==10)
    {
        strings & values(valuesWithAfterCni1738);
        dspData.cpuId = convertHexStringToNumber<unsigned int>(values[0]);
        dspData.availableDlCEs = convertStringToNumber<unsigned int>(values[1]);
        dspData.availableUlCEs = convertStringToNumber<unsigned int>(values[2]);
        dspData.rakeState = convertStringToNumber<unsigned int>(values[3]);
        dspData.rachHand = convertStringToNumber<unsigned int>(values[4]);
        dspData.rakeLoad = convertStringToNumber<unsigned int>(values[5]);
        dspData.hsupaCFs = convertStringToNumber<unsigned int>(values[6]);
        dspData.hsupaUsers = convertStringToNumber<unsigned int>(values[7]);
        dspData.dchUsers = convertStringToNumber<unsigned int>(values[8]);
        dspData.hsRachCFs = convertStringToNumber<unsigned int>(values[9]);
        isDspDataFilled=true;
    }
    if(isDspDataFilled)
    {
        unsigned int dspAddress = (dspData.boardId<<8) | dspData.cpuId;
        stringstream ss;
        ss<<std::hex<<dspAddress;
        //saveDataDumpOfOneDsp(ss.str(), dspData, logPrint);
        saveDspInformation(dspAddress, dspData);
        saveTotalUsersAndCfs(logPrint);
        //saveMaxDspInformation(dspData);
        //saveDataDumpOfOneDsp("MaxDspInfo", m_maxDspData, logPrint);
    }
}
void BtsLogAnalyzer::initializeDataDumpOfAllDspsForR3()
{
    /*initializeDataDumpOfOneDsp("1230");    initializeDataDumpOfOneDsp("1240");
    initializeDataDumpOfOneDsp("1250");
    initializeDataDumpOfOneDsp("1260");
    initializeDataDumpOfOneDsp("1270");
    initializeDataDumpOfOneDsp("1280");
    initializeDataDumpOfOneDsp("MaxDspInfo");*/
    initializeTotalUsersAndCfsDump();
    initializeSaveAllUsersAndCfsDump();
}

void BtsLogAnalyzer::initializeDataDumpOfAllDspsForR2()
{
    /*initializeDataDumpOfOneDsp("1230");
    initializeDataDumpOfOneDsp("1240");
    initializeDataDumpOfOneDsp("1250");
    initializeDataDumpOfOneDsp("1260");
    initializeDataDumpOfOneDsp("1270");
    initializeDataDumpOfOneDsp("1280");
    initializeDataDumpOfOneDsp("1290");
    initializeDataDumpOfOneDsp("1330");
    initializeDataDumpOfOneDsp("1340");
    initializeDataDumpOfOneDsp("1350");
    initializeDataDumpOfOneDsp("1360");
    initializeDataDumpOfOneDsp("1370");
    initializeDataDumpOfOneDsp("1380");
    initializeDataDumpOfOneDsp("1390");
    initializeDataDumpOfOneDsp("1430");
    initializeDataDumpOfOneDsp("1440");
    initializeDataDumpOfOneDsp("1450");
    initializeDataDumpOfOneDsp("1460");
    initializeDataDumpOfOneDsp("1470");
    initializeDataDumpOfOneDsp("1480");
    initializeDataDumpOfOneDsp("1490");
    initializeDataDumpOfOneDsp("MaxDspInfo");*/
    initializeTotalUsersAndCfsDump();
}

void BtsLogAnalyzer::initializeDataDumpOfOneDsp(string const& fileName)
{
    AlbaLocalPathHandler dspDataPathHandler(m_btsLogPathHandler.getDirectory()+fileName+".csv");
    ofstream dspDataFileStream(dspDataPathHandler.getFullPath());
    dspDataFileStream<<"BtsTime"<<",";
    dspDataFileStream<<"availableUlCEs"<<","<<"availableDlCEs"<<",";
    dspDataFileStream<<"rakeState"<<","<<"rachHand"<<","<<"rakeLoad"<<",";
    dspDataFileStream<<"hsupaCFs"<<","<<"hsRachCFs"<<",";
    dspDataFileStream<<"hsupaUsers"<<","<<"nbrOfEnhHsupaUsers"<<","<<"dchUsers"<<",";
    dspDataFileStream<<endl;
}

void BtsLogAnalyzer::initializeTotalUsersAndCfsDump()
{
    AlbaLocalPathHandler totalUsersAndCfsFileHandler(m_btsLogPathHandler.getDirectory()+"TotalUsersAndCfs.csv");
    ofstream totalUsersAndCfsFileStream(totalUsersAndCfsFileHandler.getFullPath());
    totalUsersAndCfsFileStream<<"BtsTime"<<",";
    totalUsersAndCfsFileStream<<"TotalCfs"<<",";
    totalUsersAndCfsFileStream<<"TotalR99Users"<<",";
    totalUsersAndCfsFileStream<<"TotalHsupaUsers"<<",";
    totalUsersAndCfsFileStream<<endl;
}

void BtsLogAnalyzer::initializeSaveAllUsersAndCfsDump()
{
    AlbaLocalPathHandler totalUsersAndCfsFileHandler(m_btsLogPathHandler.getDirectory()+"SaveAllUsersAndCfs.csv");
    ofstream totalUsersAndCfsFileStream(totalUsersAndCfsFileHandler.getFullPath());
    totalUsersAndCfsFileStream<<"Time,Address,hsupaCFs,totalCfs,dchUsers,hsupaUsers"<<endl;
}

void BtsLogAnalyzer::saveDataDumpOfOneDsp(string const& fileName, DspData const& dspData, BtsLogPrint const& logPrint){
    AlbaLocalPathHandler dspDataPathHandler(m_btsLogPathHandler.getDirectory()+fileName+".csv");
    ofstream dspDataFileStream(dspDataPathHandler.getFullPath(), std::ios::ate|std::ios::app);
    dspDataFileStream<<logPrint.getBtsTime().getEquivalentStringBtsTimeFormat()<<",";    dspDataFileStream<<dspData.availableUlCEs<<","<<dspData.availableDlCEs<<",";
    dspDataFileStream<<dspData.rakeState<<","<<dspData.rachHand<<","<<dspData.rakeLoad<<",";
    dspDataFileStream<<dspData.hsupaCFs<<","<<dspData.hsRachCFs<<",";
    dspDataFileStream<<dspData.hsupaUsers<<","<<dspData.nbrOfEnhHsupaUsers<<","<<dspData.dchUsers<<",";
    dspDataFileStream<<endl;
}

void BtsLogAnalyzer::saveTotalUsersAndCfs(BtsLogPrint const& logPrint)
{
    AlbaLocalPathHandler dspDataPathHandler(m_btsLogPathHandler.getDirectory()+"TotalUsersAndCfs.csv");
    ofstream totalCfsFileStream(dspDataPathHandler.getFullPath(), std::ios::ate|std::ios::app);
    unsigned int totalCfs(0);
    unsigned int totalR99Users(0);
    unsigned int totalHsupaUsers(0);
    for(DspDataPair const& dspDataPair : m_dspDataMap)
    {
        totalCfs+=dspDataPair.second.hsupaCFs;
        totalR99Users+=dspDataPair.second.dchUsers;        totalHsupaUsers+=dspDataPair.second.hsupaUsers;
    }
    totalCfsFileStream<<logPrint.getBtsTime().getEquivalentStringBtsTimeFormat()<<",";
    totalCfsFileStream<<totalCfs<<",";    totalCfsFileStream<<totalR99Users<<",";
    totalCfsFileStream<<totalHsupaUsers<<",";
    totalCfsFileStream<<endl;
}

void BtsLogAnalyzer::saveAllUsersAndCfs(BtsLogPrint const& logPrint)
{
    AlbaLocalPathHandler dspDataPathHandler(m_btsLogPathHandler.getDirectory()+"SaveAllUsersAndCfs.csv");
    ofstream totalUsersAndCfsFileStream(dspDataPathHandler.getFullPath(), std::ios::ate|std::ios::app);
    totalUsersAndCfsFileStream<<logPrint.getBtsTime().getEquivalentStringBtsTimeFormat()<<",";
    unsigned int totalCfs(0);
    for(DspDataPair const& dspDataPair : m_dspDataMap)
    {
        totalCfs+=dspDataPair.second.hsupaCFs;
        totalUsersAndCfsFileStream<<hex<<dspDataPair.first<<",";
        totalUsersAndCfsFileStream<<dec<<dspDataPair.second.hsupaCFs<<",";
        totalUsersAndCfsFileStream<<totalCfs<<",";
        totalUsersAndCfsFileStream<<dspDataPair.second.dchUsers<<",";
        totalUsersAndCfsFileStream<<dspDataPair.second.hsupaUsers<<",";
    }
    totalUsersAndCfsFileStream<<endl;
}

void BtsLogAnalyzer::saveDspInformation(unsigned int const dspAddress, DspData const& dspData)
{
    m_dspDataMap[dspAddress] = dspData;
}

void BtsLogAnalyzer::saveMaxDspInformation(DspData const& dspData){
    if(dspData.availableUlCEs < m_maxDspData.availableUlCEs)
    {
        m_maxDspData.availableUlCEs = dspData.availableUlCEs;    }
    if(dspData.availableDlCEs < m_maxDspData.availableDlCEs)
    {
        m_maxDspData.availableDlCEs = dspData.availableDlCEs;
    }
    if(dspData.rachHand > m_maxDspData.rachHand)
    {
        m_maxDspData.rachHand = dspData.rachHand;
    }
    if(dspData.rakeLoad > m_maxDspData.rakeLoad)
    {
        m_maxDspData.rakeLoad = dspData.rakeLoad;
    }
    if(dspData.hsupaCFs > m_maxDspData.hsupaCFs)
    {
        m_maxDspData.hsupaCFs = dspData.hsupaCFs;
    }
    if(dspData.hsRachCFs > m_maxDspData.hsRachCFs)
    {
        m_maxDspData.hsRachCFs = dspData.hsRachCFs;
    }
    if(dspData.hsupaUsers > m_maxDspData.hsupaUsers)
    {
        m_maxDspData.hsupaUsers = dspData.hsupaUsers;
    }
    if(dspData.nbrOfEnhHsupaUsers > m_maxDspData.nbrOfEnhHsupaUsers)
    {
        m_maxDspData.nbrOfEnhHsupaUsers = dspData.nbrOfEnhHsupaUsers;
    }
    if(dspData.dchUsers > m_maxDspData.dchUsers)
    {
        m_maxDspData.dchUsers = dspData.dchUsers;
    }
}

void BtsLogAnalyzer::saveQueueingTime(string const& lineInLogs)
{
    if(isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "MSG TIME, start queuing time"))
    {
        unsigned int messsageQueueingTime(convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgQueuingTime: ")));
        m_messageQueueingTime.addData(messsageQueueingTime);
        saveMessageQueueingTimeToCsvFile(lineInLogs, messsageQueueingTime);
    }
}

void BtsLogAnalyzer::saveRlSetupPerSecond(string const& lineInLogs)
{
    static BtsLogTime savedSecond;
    static unsigned int numberOfUsersInSecond=0;
    if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
    {
        BtsLogTime currentLogTime;
        BtsLogPrint logPrint(lineInLogs);        currentLogTime = logPrint.getBtsTime();
        currentLogTime.clearMicroSeconds();
        if(savedSecond == currentLogTime)
        {            numberOfUsersInSecond++;
        }
        else
        {
            if(rlSetupPerSecondFileStreamOptional.hasContent())
            {
                ofstream& rlSetupPerSecondFileStream(rlSetupPerSecondFileStreamOptional.getReference());
                rlSetupPerSecondFileStream<<savedSecond.getEquivalentStringBtsTimeFormat()<<","<<numberOfUsersInSecond<<endl;
            }
            savedSecond=currentLogTime;
            numberOfUsersInSecond=0;
        }    }
}

void BtsLogAnalyzer::saveRlhSetupTime(string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs)
{
    if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setFirstLogTimeInPair(lineInLogs, userIdentifiers, rlSetupLogTimePairs);
    }
    else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setSecondLogTimeInPair(lineInLogs, userIdentifiers, rlSetupLogTimePairs);
        computeRlSetupLatencyAndUpdateIfLogTimePairIsValid(userIdentifiers, rlSetupLogTimePairs);
        m_rlSetupPrintsAvailableMap.erase(userIdentifiers);
    }
}

void BtsLogAnalyzer::saveRlhDeletionTime(string const& lineInLogs, LogTimePairs& rlDeletionLogTimePairs)
{
    if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setFirstLogTimeInPair(lineInLogs, userIdentifiers, rlDeletionLogTimePairs);
    }
    else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setSecondLogTimeInPair(lineInLogs, userIdentifiers, rlDeletionLogTimePairs);
        computeRLDeletionLatencyAndUpdateIfLogTimePairIsValid(userIdentifiers, rlDeletionLogTimePairs);
    }
}
void BtsLogAnalyzer::saveAdditionalPrintsRlSetup(string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs)
{
    UserIdentifiers userIdentifiers(lineInLogs);    LogTimePair & logTimePairOfTheUser(rlSetupLogTimePairs[userIdentifiers]);
    PrintsAvailable & printsAvailableForTheUser(m_rlSetupPrintsAvailableMap[userIdentifiers]);
    if(logTimePairOfTheUser.first)
    {
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(BB_2_RL_SETUP_REQ_MSG)"))
        {
            printsAvailableForTheUser.hasBB_2_RL_SETUP_REQ_MSG=true;
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(BB_2_RL_SETUP_ACK_MSG)"))
        {
            printsAvailableForTheUser.hasBB_2_RL_SETUP_ACK_MSG=true;
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TC_TRANSPORT_BEARER_REGISTER_MSG)"))
        {
            printsAvailableForTheUser.hasTC_TRANSPORT_BEARER_REGISTER_MSG=true;
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TC_TRANSPORT_BEARER_REGISTER_RESP_MSG)"))
        {
            printsAvailableForTheUser.hasTC_TRANSPORT_BEARER_REGISTER_RESP_MSG=true;
        }    }
}

void BtsLogAnalyzer::setFirstLogTimeInPair(string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const{
    LogTimePair & logTimePairOfTheUser(logTimePairs[userIdentifiers]);
    setLogTimeIfNeeded(lineInLogs, logTimePairOfTheUser.first);
}

void BtsLogAnalyzer::setSecondLogTimeInPair(string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const
{
    LogTimePair & logTimePairOfTheUser(logTimePairs[userIdentifiers]);
    setLogTimeIfNeeded(lineInLogs, logTimePairOfTheUser.second);
}

void BtsLogAnalyzer::computeRlSetupLatencyAndUpdateIfLogTimePairIsValid(UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs)
{
    LogTimePair & logTimePairOfTheUser(logTimePairs[userIdentifiers]);
    if(logTimePairOfTheUser.first && logTimePairOfTheUser.second && logTimePairOfTheUser.first.getReference().getTotalSeconds() <= logTimePairOfTheUser.second.getReference().getTotalSeconds())
    {
        double latencyInMicroseconds(getTotalMicroseconds(logTimePairOfTheUser));
        m_rlhRlSetupLatency.addData(latencyInMicroseconds);
        if(rlSetupTimeFileStreamOptional.hasContent())
        {
            ofstream& rlSetupTimeFileStream(rlSetupTimeFileStreamOptional.getReference());
            saveUserIndentifierAndLatencyToCsvFile(userIdentifiers, latencyInMicroseconds, rlSetupTimeFileStream);
            savePrintsAvailableToCsvFile(userIdentifiers, rlSetupTimeFileStream);
            rlSetupTimeFileStream<<endl;
        }
    }
    logTimePairs.erase(userIdentifiers);
}

void BtsLogAnalyzer::computeRLDeletionLatencyAndUpdateIfLogTimePairIsValid(UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs)
{
    LogTimePair & logTimePairOfTheUser(logTimePairs[userIdentifiers]);
    if(logTimePairOfTheUser.first && logTimePairOfTheUser.second && logTimePairOfTheUser.first.getReference().getTotalSeconds() <= logTimePairOfTheUser.second.getReference().getTotalSeconds())
    {
        double latencyInMicroseconds(getTotalMicroseconds(logTimePairOfTheUser));
        m_rlhRlDeletionLatency.addData(latencyInMicroseconds);
        if(rlDeletionTimeFileStreamOptional.hasContent())
        {
            ofstream& rlDeletionTimeFileStream(rlDeletionTimeFileStreamOptional.getReference());
            saveUserIndentifierAndLatencyToCsvFile(userIdentifiers, latencyInMicroseconds, rlDeletionTimeFileStream);
            rlDeletionTimeFileStream<<endl;
        }
    }
    logTimePairs.erase(userIdentifiers);
}

void BtsLogAnalyzer::saveMessageQueueingTimeToCsvFile(string const& lineInLogs, unsigned int const messageQueueingTime) const
{
    if(messageQueueingTimeFileStreamOptional.hasContent())
    {
        ofstream& messageQueueingTimeFileStream(messageQueueingTimeFileStreamOptional.getReference());
        messageQueueingTimeFileStream<<messageQueueingTime<<","<<lineInLogs<<endl;
    }
}

void BtsLogAnalyzer::saveUserIndentifierAndLatencyToCsvFile(UserIdentifiers const& userIdentifiers, double const latencyInMicroseconds, ofstream& csvFileStream) const
{
    csvFileStream<<userIdentifiers.getCrnccId()<<","<<userIdentifiers.getNbccId()<<","<<userIdentifiers.getTransactionId()<<","<<latencyInMicroseconds<<",";}

void BtsLogAnalyzer::savePrintsAvailableToCsvFile(UserIdentifiers const& userIdentifiers, ofstream& csvFileStream)
{    PrintsAvailable & printsAvailable(m_rlSetupPrintsAvailableMap[userIdentifiers]);
    csvFileStream<<printsAvailable.hasBB_2_RL_SETUP_REQ_MSG<<","<<printsAvailable.hasBB_2_RL_SETUP_ACK_MSG<<","<<printsAvailable.hasTC_TRANSPORT_BEARER_REGISTER_MSG<<","<<printsAvailable.hasTC_TRANSPORT_BEARER_REGISTER_RESP_MSG<<",";
}

void BtsLogAnalyzer::setLogTimeIfNeeded(string const& lineInLogs, LogTime& logTime) const
{
    BtsLogPrint logPrint(lineInLogs);
    //if(!logPrint.getBtsTime().isStartup())
    //{
    logTime.setValue(logPrint.getBtsTime());
    //}
}

double BtsLogAnalyzer::getTotalMicroseconds(LogTimePair const& logTimePairOfTheUser) const
{
    BtsLogTime latency = logTimePairOfTheUser.second.getReference()-logTimePairOfTheUser.first.getReference();
    return getTotalMicroseconds(latency);
}

double BtsLogAnalyzer::getTotalMicroseconds(BtsLogTime const& btsLogTime) const
{
    double result((double)btsLogTime.getMinutes()*1000000*60 + (double)btsLogTime.getSeconds()*1000000 + (double)btsLogTime.getMicroSeconds());    return result;
}

void BtsLogAnalyzer::printAllCollectedData() const{
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
