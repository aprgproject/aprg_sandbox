#include "BtsLogAnalyzer.hpp"

#include <Container/AlbaRange.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <iostream>

#include <Debug/AlbaDebug.hpp>

using namespace std;
using tcomToolsBackend::BtsLogPrint;
using tcomToolsBackend::BtsLogTime;
using tcomToolsBackend::BtsLogTimeType;

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
    AlbaLocalPathHandler messageQueueingTimeFilePathHandler(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_MessageQueueingTime.csv");
    AlbaLocalPathHandler rlSetupTimeFilePathHandler(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_RlSetupTime.csv");
    AlbaLocalPathHandler rlDeletionTimeFilePathHandler(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_RlDeletionTime.csv");
    AlbaLocalPathHandler rlSetupPerSecond(m_btsLogPathHandler.getDirectory()+m_btsLogPathHandler.getFilenameOnly()+"_RlSetupPerSecond.csv");

    ifstream inputLogFileStream(m_btsLogPathHandler.getFullPath());
    ofstream messageQueueingTimeFileStream(messageQueueingTimeFilePathHandler.getFullPath());
    ofstream rlSetupTimeFileStream(rlSetupTimeFilePathHandler.getFullPath());
    ofstream rlDeletionTimeFileStream(rlDeletionTimeFilePathHandler.getFullPath());
    ofstream rlSetupPerSecondFileStream(rlSetupPerSecond.getFullPath());
    initializeCsvFileStreams(messageQueueingTimeFileStream, rlSetupTimeFileStream, rlDeletionTimeFileStream);
    rlSetupPerSecondFileStream<<"Time,Number Of RL setup in a second"<<endl;
    //initializeDataDumpOfAllDspsForR3();

    AlbaFileReader fileReader(inputLogFileStream);
    LogTimePairs rlSetupLogTimePairs;
    LogTimePairs rlDeletionLogTimePairs;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        saveQueueingTime(lineInLogs, messageQueueingTimeFileStream);
        saveRlhSetupTime(lineInLogs, rlSetupLogTimePairs, rlSetupTimeFileStream);
        saveRlhDeletionTime(lineInLogs, rlDeletionLogTimePairs, rlDeletionTimeFileStream);
        saveAdditionalPrintsRlSetup(lineInLogs, rlSetupLogTimePairs);
        saveRlSetupPerSecond(lineInLogs, rlSetupPerSecondFileStream);
        //saveDspCapacityInformationForR3(lineInLogs);
    }
}

void BtsLogAnalyzer::saveDspCapacityInformationForR3(string const& lineInLogs)
{
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "printDspCapacityInd(): 0x"))
    {
        BtsLogPrint logPrint(lineInLogs);
        stringHelper::strings dspCapacitiesPerDsp;
        stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(dspCapacitiesPerDsp, lineInLogs, " ");
        unsigned int boardId(stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getStringInBetweenTwoStrings(lineInLogs, "0x", " ")));
        for(string const& dspCapacityOfOneDsp : dspCapacitiesPerDsp)
        {
            saveDspCapacityInformationOfOneDspForR3BeforeCni1738(dspCapacityOfOneDsp, boardId, logPrint);
        }
    }
}

void BtsLogAnalyzer::saveDspCapacityInformationOfOneDspForR3(string const& dspCapacityOfOneDsp, unsigned int const boardId, BtsLogPrint const& logPrint)
{
    unsigned int state=0;
    string temp;
    DspData dspData;
    dspData.boardId=boardId;
    for(char const character: dspCapacityOfOneDsp)
    {
        if(state==0)
        {
            if(character == '{')
            {
                state=1;
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==1)
        {
            if(character == '}')
            {
                state=2;
                dspData.lcgId = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==2)
        {
            if(character == ':')
            {
                state=3;
                dspData.cpuId = stringHelper::convertHexStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else if(character == 'x')
            {
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==3)
        {
            if(character == '/')
            {
                state=4;
                dspData.availableUlCEs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==4)
        {
            if(character == '[')
            {
                state=5;
                dspData.availableDlCEs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==5)
        {
            if(character == ',')
            {
                state=6;
                dspData.rakeState = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==6)
        {
            if(character == ',')
            {
                state=7;
                dspData.rachHand = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==7)
        {
            if(character == ',')
            {
                state=8;
                dspData.rakeLoad = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==8)
        {
            if(character == ',')
            {
                state=9;
                dspData.hsupaCFs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==9)
        {
            if(character == ']')
            {
                state=10;
                dspData.hsRachCFs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==10)
        {
            if(character == ',')
            {
                state=11;
                dspData.hsupaUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else if(character == '[')
            {
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==11)
        {
            if(character == ',')
            {
                state=12;
                dspData.nbrOfEnhHsupaUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==12)
        {
            if(character == ']')
            {
                dspData.dchUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                state=13;
            }
        }
    }
    if(state==13)
    {
        unsigned int dspAddress = (dspData.boardId<<8) | dspData.cpuId;
        stringstream ss;
        ss<<std::hex<<dspAddress;
        //saveDataDumpOfOneDsp(ss.str(), dspData, logPrint);
        saveDspInformation(dspAddress, dspData);
        //saveMaxDspInformation(dspData);
        saveTotalUsersAndCfs(logPrint);
        saveAllUsersAndCfs(logPrint);
        saveDataDumpOfOneDsp("MaxDspInfo", m_maxDspData, logPrint);
    }
}

void BtsLogAnalyzer::saveDspCapacityInformationOfOneDspForR3BeforeCni1738(string const& dspCapacityOfOneDsp, unsigned int const boardId, BtsLogPrint const& logPrint)
{
    unsigned int state=0;
    string temp;
    DspData dspData;
    dspData.boardId=boardId;
    for(char const character: dspCapacityOfOneDsp)
    {
        if(state==0)
        {
            if(character == '{')
            {
                state=1;
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==1)
        {
            if(character == '}')
            {
                state=2;
                dspData.lcgId = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==2)
        {
            if(character == ':')
            {
                state=3;
                dspData.cpuId = stringHelper::convertHexStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else if(character == 'x')
            {
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==3)
        {
            if(character == '/')
            {
                state=4;
                dspData.availableUlCEs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==4)
        {
            if(character == '[')
            {
                state=5;
                dspData.availableDlCEs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==5)
        {
            if(character == ',')
            {
                state=6;
                dspData.rakeState = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==6)
        {
            if(character == ',')
            {
                state=7;
                dspData.rachHand = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==7)
        {
            if(character == ',')
            {
                state=8;
                dspData.rakeLoad = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==8)
        {
            if(character == ']')
            {
                state=9;
                dspData.hsupaCFs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==9)
        {
            if(character == ',')
            {
                state=10;
                dspData.hsupaUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else if(character == '[')
            {
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==10)
        {
            if(character == ',')
            {
                state=11;
                dspData.nbrOfEnhHsupaUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==11)
        {
            if(character == ']')
            {
                dspData.dchUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                state=12;
            }
            else
            {
                temp+=character;
            }
        }
    }
    if(state==12)
    {
        unsigned int dspAddress = (dspData.boardId<<8) | dspData.cpuId;
        stringstream ss;
        ss<<std::hex<<dspAddress;
        //saveDataDumpOfOneDsp(ss.str(), dspData, logPrint);
        saveDspInformation(dspAddress, dspData);
        //saveMaxDspInformation(dspData);
        saveTotalUsersAndCfs(logPrint);
        saveAllUsersAndCfs(logPrint);
        saveDataDumpOfOneDsp("MaxDspInfo", m_maxDspData, logPrint);
    }
}

void BtsLogAnalyzer::saveDspCapacityInformationForR2(string const& lineInLogs)
{
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "INF/TCOM/LRM/Rep, |0x"))
    {
        BtsLogPrint logPrint(lineInLogs);
        stringHelper::strings dspCapacitiesPerDsp;
        string logsAfterLrmPrint(stringHelper::getStringAfterThisString(lineInLogs, "INF/TCOM/LRM/Rep"));
        stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(dspCapacitiesPerDsp, logsAfterLrmPrint, "(");
        unsigned int boardId(stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getStringInBetweenTwoStrings(lineInLogs, ",0x", "-")));
        for(string const& dspCapacityOfOneDsp : dspCapacitiesPerDsp)
        {
            saveDspCapacityInformationOfOneDspForR2(dspCapacityOfOneDsp, boardId, logPrint);
        }
    }
}

void BtsLogAnalyzer::saveDspCapacityInformationOfOneDspForR2(string const& dspCapacityOfOneDsp, unsigned int const boardId, BtsLogPrint const& logPrint)
{
    unsigned int state=0;
    string temp;
    DspData dspData;
    dspData.boardId=boardId;
    for(char const character: dspCapacityOfOneDsp)
    {
        ALBA_PRINT2(character, state);
        if(state==0)
        {
            if(character == ':')
            {
                state=1;
                dspData.cpuId = stringHelper::convertHexStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==1)
        {
            if(character == '/')
            {
                state=2;
                dspData.availableDlCEs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==2)
        {
            if(character == '[')
            {
                state=3;
                dspData.availableUlCEs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==3)
        {
            if(character == ',')
            {
                state=4;
                dspData.rakeState = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==4)
        {
            if(character == ',')
            {
                state=5;
                dspData.rachHand = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==5)
        {
            if(character == ',')
            {
                state=6;
                dspData.rakeLoad = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==6)
        {
            if(character == ',')
            {
                state=7;
                dspData.hsupaCFs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==7)
        {
            if(character == ',')
            {
                state=8;
                dspData.hsupaUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==8)
        {
            if(character == ',')
            {
                state=9;
                dspData.dchUsers = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
        else if(state==9)
        {
            if(character == ']')
            {
                state=10;
                dspData.hsRachCFs = stringHelper::convertStringToNumber<unsigned int>(temp);
                temp.clear();
            }
            else
            {
                temp+=character;
            }
        }
    }
    ALBA_PRINT0("saveDspCapacityInformationOfOneDspForR2 end");
    if(state==10)
    {
        unsigned int dspAddress = (dspData.boardId<<8) | dspData.cpuId;
        stringstream ss;
        ss<<std::hex<<dspAddress;
        //saveDataDumpOfOneDsp(ss.str(), dspData, logPrint);
        saveDspInformation(dspAddress, dspData);
        //saveMaxDspInformation(dspData);
        saveTotalUsersAndCfs(logPrint);
        saveDataDumpOfOneDsp("MaxDspInfo", m_maxDspData, logPrint);
    }
}

void BtsLogAnalyzer::initializeDataDumpOfAllDspsForR3()
{
    /*initializeDataDumpOfOneDsp("1230");
    initializeDataDumpOfOneDsp("1240");
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
}

void BtsLogAnalyzer::saveDataDumpOfOneDsp(string const& fileName, DspData const& dspData, BtsLogPrint const& logPrint)
{
    AlbaLocalPathHandler dspDataPathHandler(m_btsLogPathHandler.getDirectory()+fileName+".csv");
    ofstream dspDataFileStream(dspDataPathHandler.getFullPath(), std::ios::ate|std::ios::app);
    dspDataFileStream<<logPrint.getBtsTime().getEquivalentStringBtsTimeFormat()<<",";
    dspDataFileStream<<dspData.availableUlCEs<<","<<dspData.availableDlCEs<<",";
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
    for(DspDataPair const& dspDataPair : m_maxDspDataMap)
    {
        totalCfs+=dspDataPair.second.hsupaCFs;
        totalR99Users+=dspDataPair.second.dchUsers;
        totalHsupaUsers+=dspDataPair.second.hsupaUsers;
    }
    totalCfsFileStream<<logPrint.getBtsTime().getEquivalentStringBtsTimeFormat()<<",";
    totalCfsFileStream<<totalCfs<<",";
    totalCfsFileStream<<totalR99Users<<",";
    totalCfsFileStream<<totalHsupaUsers<<",";
    totalCfsFileStream<<endl;
}

void BtsLogAnalyzer::saveAllUsersAndCfs(BtsLogPrint const& logPrint)
{
    AlbaLocalPathHandler dspDataPathHandler(m_btsLogPathHandler.getDirectory()+"SaveAllUsersAndCfs.csv");
    ofstream totalCfsFileStream(dspDataPathHandler.getFullPath(), std::ios::ate|std::ios::app);
    totalCfsFileStream<<logPrint.getBtsTime().getEquivalentStringBtsTimeFormat()<<",";
    unsigned int totalCfs(0);
    for(DspDataPair const& dspDataPair : m_maxDspDataMap)
    {
        totalCfs+=dspDataPair.second.hsupaCFs;
        totalCfsFileStream<<hex<<dspDataPair.first<<",";
        totalCfsFileStream<<dec<<dspDataPair.second.hsupaCFs<<",";
        totalCfsFileStream<<totalCfs<<",";
        totalCfsFileStream<<dspDataPair.second.dchUsers<<",";
        totalCfsFileStream<<dspDataPair.second.hsupaUsers<<",";
    }
    totalCfsFileStream<<endl;
}

void BtsLogAnalyzer::saveDspInformation(unsigned int const dspAddress, DspData const& dspData)
{
    m_maxDspDataMap[dspAddress] = dspData;
}

void BtsLogAnalyzer::saveMaxDspInformation(DspData const& dspData)
{
    if(dspData.availableUlCEs < m_maxDspData.availableUlCEs)
    {
        m_maxDspData.availableUlCEs = dspData.availableUlCEs;
    }
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



void BtsLogAnalyzer::saveQueueingTime(string const& lineInLogs, ofstream& messageQueueingTimeFileStream)
{
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "MSG TIME, start queuing time"))
    {
        unsigned int messsageQueueingTime(stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "msgQueuingTime: ")));
        m_messageQueueingTime.addData(messsageQueueingTime);
        saveMessageQueueingTimeToCsvFile(lineInLogs, messsageQueueingTime, messageQueueingTimeFileStream);
    }
}

void BtsLogAnalyzer::saveRlSetupPerSecond(string const& lineInLogs, ofstream& rlSetupPerSecondFileStream)
{
    static BtsLogTime savedSecond;
    static unsigned int numberOfUsersInSecond=0;
    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
    {
        BtsLogTime currentLogTime;
        BtsLogPrint logPrint(lineInLogs);
        currentLogTime = logPrint.getBtsTime();
        currentLogTime.clearMicroSeconds();
        if(savedSecond == currentLogTime)
        {
            numberOfUsersInSecond++;
        }
        else
        {
            rlSetupPerSecondFileStream<<savedSecond.getEquivalentStringBtsTimeFormat()<<","<<numberOfUsersInSecond<<endl;
            savedSecond=currentLogTime;
            numberOfUsersInSecond=0;
        }
    }
}

void BtsLogAnalyzer::saveRlhSetupTime(string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs, ofstream& rlSetupTimeFileStream)
{
    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setFirstLogTimeInPair(lineInLogs, userIdentifiers, rlSetupLogTimePairs);
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
    {
        UserIdentifiers userIdentifiers(lineInLogs);
        setSecondLogTimeInPair(lineInLogs, userIdentifiers, rlSetupLogTimePairs);
        computeLatencyAndUpdateIfLogTimePairIsValid(LogType::RlSetup, userIdentifiers, rlSetupLogTimePairs, rlSetupTimeFileStream);
        m_rlSetupPrintsAvailableMap.erase(userIdentifiers);
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
        rlDeletionTimeFileStream<<endl;
    }
}

void BtsLogAnalyzer::saveAdditionalPrintsRlSetup(string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs)
{
    UserIdentifiers userIdentifiers(lineInLogs);
    LogTimePair & logTimePairOfTheUser(rlSetupLogTimePairs[userIdentifiers]);
    PrintsAvailable & printsAvailableForTheUser(m_rlSetupPrintsAvailableMap[userIdentifiers]);
    if(logTimePairOfTheUser.first)
    {
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(BB_2_RL_SETUP_REQ_MSG)"))
        {
            printsAvailableForTheUser.hasBB_2_RL_SETUP_REQ_MSG=true;
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(BB_2_RL_SETUP_ACK_MSG)"))
        {
            printsAvailableForTheUser.hasBB_2_RL_SETUP_ACK_MSG=true;
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TC_TRANSPORT_BEARER_REGISTER_MSG)"))
        {
            printsAvailableForTheUser.hasTC_TRANSPORT_BEARER_REGISTER_MSG=true;
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TC_TRANSPORT_BEARER_REGISTER_RESP_MSG)"))
        {
            printsAvailableForTheUser.hasTC_TRANSPORT_BEARER_REGISTER_RESP_MSG=true;
        }
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
    if(logTimePairOfTheUser.first && logTimePairOfTheUser.second && logTimePairOfTheUser.first.getReference().getTotalSeconds() <= logTimePairOfTheUser.second.getReference().getTotalSeconds())
    {
        BtsLogTime latency = logTimePairOfTheUser.second.getReference()-logTimePairOfTheUser.first.getReference();
        double latencyInMicroseconds(getTotalMicroseconds(latency));
        if(logType == LogType::RlSetup)
        {
            m_rlhRlSetupLatency.addData(latencyInMicroseconds);
            saveUserIndentifierAndLatencyToCsvFile(userIdentifiers, latencyInMicroseconds, csvFileStream);
            savePrintsAvailableToCsvFile(userIdentifiers, csvFileStream);
            csvFileStream<<endl;
        }
        else if(logType == LogType::RlDeletion)
        {
            m_rlhRlDeletionLatency.addData(latencyInMicroseconds);
            saveUserIndentifierAndLatencyToCsvFile(userIdentifiers, latencyInMicroseconds, csvFileStream);
            csvFileStream<<endl;
        }
    }
    logTimePairs.erase(userIdentifiers);
}

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
    rlSetupTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency(microseconds),BB_2_RL_SETUP_REQ_MSG,BB_2_RL_SETUP_ACK_MSG,TC_TRANSPORT_BEARER_REGISTER_MSG,TC_TRANSPORT_BEARER_REGISTER_RESP_MSG"<<endl;
    rlDeletionTimeFileStream<<"CrnccId,NbccId,TransactionId,Latency(microseconds),BB_2_RL_SETUP_REQ_MSG,BB_2_RL_SETUP_ACK_MSG,TC_TRANSPORT_BEARER_REGISTER_MSG,TC_TRANSPORT_BEARER_REGISTER_RESP_MSG"<<endl;
}

void BtsLogAnalyzer::saveMessageQueueingTimeToCsvFile(string const& lineInLogs, unsigned int const messageQueueingTime, ofstream& csvFileStream) const
{
    csvFileStream<<messageQueueingTime<<","<<lineInLogs<<endl;
}

void BtsLogAnalyzer::saveUserIndentifierAndLatencyToCsvFile(UserIdentifiers const& userIdentifiers, double const latencyInMicroseconds, ofstream& csvFileStream) const
{
    csvFileStream<<userIdentifiers.getCrnccId()<<","<<userIdentifiers.getNbccId()<<","<<userIdentifiers.getTransactionId()<<","<<latencyInMicroseconds<<",";
}

void BtsLogAnalyzer::savePrintsAvailableToCsvFile(UserIdentifiers const& userIdentifiers, ofstream& csvFileStream)
{
    PrintsAvailable & printsAvailable(m_rlSetupPrintsAvailableMap[userIdentifiers]);
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

double BtsLogAnalyzer::getTotalMicroseconds(BtsLogTime const& btsLogTime) const
{
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
