#include <BtsLogAnalyzer.hpp>

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>#include <BtsLogPrint.hpp>
#include <iomanip>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <set>

using namespace std;
using namespace tcomToolsBackend;

namespace alba
{

BtsLogAnalyzer::BtsLogAnalyzer()
    : m_totalDelay(0)
    , m_count(0)
{}

BtsLogAnalyzer::BtsLogAnalyzer(string const pathOfOutputFile)
    : m_outputStream(pathOfOutputFile)
    , m_totalDelay(0)
    , m_count(0){
    if(m_outputStream.is_open())
    {
        cout<<"OutputStream is opened. Saving to output files"<<endl;
    }
}

void BtsLogAnalyzer::processFileForToCountUsersWithTracing(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    set<int> usersWithTracing;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "RLH sends BB_UE_TRACING_REPORT_IND_MSG (0x515D)"))
        {
            int msgType = stringHelper::convertHexStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgType: 0x"));
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            if(msgType == 0x1200)
            {
                usersWithTracing.emplace(nbccId);
                cout<<"msgType: "<<msgType<<" nbccId: "<<nbccId<<" number of usersWithTracing: "<<usersWithTracing.size()<<endl;
            }
            else if(msgType == 0x1300)
            {
                if(usersWithTracing.find(nbccId)!=usersWithTracing.end())
                {
                    usersWithTracing.erase(nbccId);
                }
                cout<<"msgType: "<<msgType<<" nbccId: "<<nbccId<<" number of usersWithTracing: "<<usersWithTracing.size()<<endl;
            }
        }
    }
}

void BtsLogAnalyzer::processDirectoryForWireSharkDelay(string const& directoryPath)
{
    set<string> listOfFiles;
    set<string> listOfDirectories;    AlbaWindowsPathHandler(directoryPath).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        processFileForWireSharkDelay(AlbaWindowsPathHandler(filePath).getFullPath());
    }
}

void BtsLogAnalyzer::processFileForWireSharkDelay(string const& filePath)
{
    m_wireSharkDelays.clear();
    cout<<"processFile: "<<AlbaWindowsPathHandler(filePath).getFile()<<endl;
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    AlbaOptional<double> startTimeFetchedOptional;
    AlbaOptional<double> endTimeFetchedOptional;

    if(!inputLogFileStream.is_open())
    {
        cout<<"Cannot open file: "<<filePath<<endl;
    }
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
            int crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "CRNC-CommunicationContextID: "));
            WireSharkDelay & delayForCrnccId = m_wireSharkDelays[crnccId];
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
                m_wireSharkDelays.erase(crnccId);
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(No.     Time)"))
        {
            startTimeFetchedOptional.clear();
            endTimeFetchedOptional.clear();
        }
    }
}

void BtsLogAnalyzer::processFileForMsgQueuingTime(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    int totalMsgQueuingTime = 0;
    int highestMsgQueuingTime = 0;
    int numberOfPrints=0;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "MSG TIME, start queuing time"))
        {
            int msgQueuingTime = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgQueuingTime: "));
            totalMsgQueuingTime += msgQueuingTime;
            if(msgQueuingTime > highestMsgQueuingTime)
            {
                highestMsgQueuingTime = msgQueuingTime;
            }
            m_outputStream<<msgQueuingTime<<","<<lineInLogs<<endl;
            numberOfPrints++;
        }
    }
    cout<<"TotalMsgQueuingTime: "<<totalMsgQueuingTime<<" highestMsgQueuingTime: "<<highestMsgQueuingTime<<" AverageMsgQueuingTime: "<<((double)totalMsgQueuingTime)/numberOfPrints<<" numberOfPrints: "<<numberOfPrints<<endl;
}


void BtsLogAnalyzer::processFileForBtsDelayForRlh(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);    AlbaFileReader fileReader(inputLogFileStream);
    cout<<"processFile: "<<filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open() << " fileReader: " << fileReader.isNotFinished() <<endl;

    m_outputStream<<"crnccId,nbccId,transactionId,delay"<<endl;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
        {
            UniqueId uniqueKey;
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
        {
            UniqueId uniqueKey;
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.endTimeOptional.setValue(logPrint.getBtsTime());
            }
            if(delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional && delayForCrnccId.startTimeOptional.getReference().getTotalSeconds() <= delayForCrnccId.endTimeOptional.getReference().getTotalSeconds())
            {
                BtsLogTime delayTime = delayForCrnccId.endTimeOptional.getReference() - delayForCrnccId.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                //if(uniqueKey.crnccId == 15167){cout<<"crnccId "<<uniqueKey.crnccId<<"nbccId "<<uniqueKey.nbccId<<"delay "<<delay<<"startTimeOptional "<<delayForCrnccId.startTimeOptional.getReference()<<"endTimeOptional "<<delayForCrnccId.endTimeOptional.getReference()<<endl;}
                m_totalDelay += delay;
                m_count++;
                m_outputStream<<uniqueKey.crnccId<<","<<uniqueKey.nbccId<<","<<uniqueKey.transactionId<<","<<setw(10)<<delay<<endl;
                m_btsLogDelays.erase(uniqueKey);
            }
        }
    }
}

void BtsLogAnalyzer::processFileForBtsDelayForRlDeletion(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    m_outputStream<<"crnccId,nbccId,transactionId,delay"<<endl;
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)"))
        {
            UniqueId uniqueKey;
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)"))
        {
            UniqueId uniqueKey;
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crncId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.endTimeOptional.setValue(logPrint.getBtsTime());
            }
            if(delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional && delayForCrnccId.startTimeOptional.getReference().getTotalSeconds() <= delayForCrnccId.endTimeOptional.getReference().getTotalSeconds())
            {
                BtsLogTime delayTime = delayForCrnccId.endTimeOptional.getReference() - delayForCrnccId.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                //if(uniqueKey.crnccId == 15167){cout<<"crnccId "<<uniqueKey.crnccId<<"nbccId "<<uniqueKey.nbccId<<"delay "<<delay<<"startTimeOptional "<<delayForCrnccId.startTimeOptional.getReference()<<"endTimeOptional "<<delayForCrnccId.endTimeOptional.getReference()<<endl;}
                m_totalDelay += delay;
                m_count++;
                m_outputStream<<uniqueKey.crnccId<<","<<uniqueKey.nbccId<<","<<uniqueKey.transactionId<<","<<setw(10)<<delay<<endl;
                m_btsLogDelays.erase(uniqueKey);
            }
        }
    }
}

void BtsLogAnalyzer::processFileForBtsDelayForMikhailKnife(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    ofstream grmFetchFileStream(filePathHandler.getDirectory()+R"(grmFetchFileStream.csv)");
    ofstream grmProcessFileStream(filePathHandler.getDirectory()+R"(grmProcessFileStream.csv)");
    ofstream messageDeliveryFileStream(filePathHandler.getDirectory()+R"(messageDeliveryFileStream.csv)");
    ofstream rlSetupFileStream(filePathHandler.getDirectory()+R"(rlSetupFileStream.csv)");
    grmFetchFileStream<<"crnccId,"<<"nbccId,"<<"transactionId,"<<"difference"<<endl;
    grmProcessFileStream<<"crnccId,"<<"nbccId,"<<"transactionId,"<<"delay"<<endl;
    messageDeliveryFileStream<<"crnccId,"<<"nbccId,"<<"transactionId,"<<"delay"<<endl;
    rlSetupFileStream<<"crnccId,"<<"nbccId,"<<"transactionId,"<<"delay"<<endl;

    std::map<UniqueId, BtsLogDelay> grmProcessMap;
    std::map<UniqueId, BtsLogDelay> messageDeliveryMap;
    std::map<UniqueId, BtsLogDelay> rlSetupMap;

    double grmFetchTotal=0;
    int grmFetchCount=0;
    double grmProcessTotal=0;
    int grmProcessCount=0;
    double messageDeliveryTotal=0;
    int messageDeliveryCount=0;
    double rlSetupTotal=0;
    int rlSetupCount=0;

    while(fileReader.isNotFinished())
    {
        UniqueId uniqueKey;
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(INF/TCOM/G, decodeRadioLinkRequest API_TCOM_RNC_MSG)"))
        {
            int crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            int transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            unsigned int difference = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "diff in ms: "));
            if(difference!=0x80000000)
            {
                grmFetchTotal += difference*1000;
                grmFetchCount++;
                grmFetchFileStream<<crnccId<<","<<nbccId<<","<<transactionId<<","<<setw(10)<<difference<<endl;
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(INF/TCOM/G, Received API_TCOM_RNC_MSG)"))
        {
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & processMapInstance = grmProcessMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                processMapInstance.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(INF/TCOM/G, Sending API_TCOM_RNC_MSG)"))
        {
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & processMapInstance = grmProcessMap[uniqueKey];
            BtsLogDelay & messageDeliveryInstance = messageDeliveryMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                processMapInstance.endTimeOptional.setValue(logPrint.getBtsTime());
                messageDeliveryInstance.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
        {
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & messageDeliveryInstance = messageDeliveryMap[uniqueKey];
            BtsLogDelay & rlSetupMapInstance = rlSetupMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                messageDeliveryInstance.endTimeOptional.setValue(logPrint.getBtsTime());
                rlSetupMapInstance.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)"))
        {
            uniqueKey.crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & rlSetupMapInstance = rlSetupMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                rlSetupMapInstance.endTimeOptional.setValue(logPrint.getBtsTime());
            }
        }

        BtsLogDelay & processMapInstance = grmProcessMap[uniqueKey];
        if(processMapInstance.startTimeOptional && processMapInstance.endTimeOptional)
        {
            if(processMapInstance.startTimeOptional.getReference() < processMapInstance.endTimeOptional.getReference())
            {
                BtsLogTime delayTime = processMapInstance.endTimeOptional.getReference() - processMapInstance.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                grmProcessTotal += delay;
                grmProcessCount++;
                grmProcessFileStream<<uniqueKey.crnccId<<","<<uniqueKey.nbccId<<","<<uniqueKey.transactionId<<","<<setw(10)<<delay<<endl;
            }
            grmProcessMap.erase(uniqueKey);
        }

        BtsLogDelay & messageDeliveryInstance = messageDeliveryMap[uniqueKey];
        if(messageDeliveryInstance.startTimeOptional && messageDeliveryInstance.endTimeOptional)
        {
            if(messageDeliveryInstance.startTimeOptional.getReference() < messageDeliveryInstance.endTimeOptional.getReference())
            {

                BtsLogTime delayTime = messageDeliveryInstance.endTimeOptional.getReference() - messageDeliveryInstance.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                messageDeliveryTotal += delay;
                messageDeliveryCount++;
                messageDeliveryFileStream<<uniqueKey.crnccId<<","<<uniqueKey.nbccId<<","<<uniqueKey.transactionId<<","<<setw(10)<<delay<<endl;
            }
            messageDeliveryMap.erase(uniqueKey);
        }

        BtsLogDelay & rlSetupMapInstance = rlSetupMap[uniqueKey];
        if(rlSetupMapInstance.startTimeOptional && rlSetupMapInstance.endTimeOptional)
        {
            if(rlSetupMapInstance.startTimeOptional.getReference() < rlSetupMapInstance.endTimeOptional.getReference())
            {
                BtsLogTime delayTime = rlSetupMapInstance.endTimeOptional.getReference() - rlSetupMapInstance.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                rlSetupTotal += delay;
                rlSetupCount++;
                rlSetupFileStream<<uniqueKey.crnccId<<","<<uniqueKey.nbccId<<","<<uniqueKey.transactionId<<","<<setw(10)<<delay<<endl;
            }
            rlSetupMap.erase(uniqueKey);
        }
    }
    cout<<"grmFetchTotal: "<<grmFetchTotal<<" count: "<<grmFetchCount<<" average:"<<grmFetchTotal/grmFetchCount<<endl;
    cout<<"grmProcessTotal: "<<grmProcessTotal<<" count: "<<grmProcessCount<<" average:"<<grmProcessTotal/grmProcessCount<<endl;
    cout<<"messageDeliveryTotal: "<<messageDeliveryTotal<<" count: "<<messageDeliveryCount<<" average:"<<messageDeliveryTotal/messageDeliveryCount<<endl;
    cout<<"rlSetupTotal: "<<rlSetupTotal<<" count: "<<rlSetupCount<<" average:"<<rlSetupTotal/rlSetupCount<<endl;
}

void BtsLogAnalyzer::processFileForBtsDelayForGrm(string const& filePath)
{
    AlbaWindowsPathHandler filePathHandler(filePath);
    cout<<"processFile: "<<filePathHandler.getFullPath()<<endl;
    m_outputStream<<"crnccId,nbccId,transactionId,delay"<<endl;
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(INF/TCOM/G, Received API_TCOM_RNC_MSG)"))
        {
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            BtsLogDelay & delayForCrnccId = m_btsLogDelaysGrm[nbccId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.startTimeOptional.setValue(logPrint.getBtsTime());
            }
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)"))
        {
            int crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            int transactionId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay & delayForCrnccId = m_btsLogDelaysGrm[nbccId];
            BtsLogPrint logPrint(lineInLogs);
            if(!logPrint.getBtsTime().isStartup())
            {
                delayForCrnccId.endTimeOptional.setValue(logPrint.getBtsTime());
            }
            if(delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional && delayForCrnccId.startTimeOptional.getReference().getTotalSeconds() <= delayForCrnccId.endTimeOptional.getReference().getTotalSeconds())
            {
                BtsLogTime delayTime = delayForCrnccId.endTimeOptional.getReference() - delayForCrnccId.startTimeOptional.getReference();
                int delay = delayTime.getMicroSeconds()+delayTime.getSeconds()*1000000;
                if(delay<1000000)
                {
                    m_totalDelay += delay;
                    m_count++;
                    m_outputStream<<crnccId<<","<<nbccId<<","<<transactionId<<","<<setw(10)<<delay<<endl;
                }
                m_btsLogDelaysGrm.erase(nbccId);
            }
        }
        /*else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(INF/TCOM/R, CTRL_RLH_)")
                || stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(INF/TCOM/R, RLH_CTRL_)")
                || stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(LRM_RL_)")
                || stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(TC_2_RL_SETUP_IND_MSG)")
                || stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, R"(BB_2_RL_)")
                )
        {
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            m_btsLogDelaysGrm.erase(nbccId);
        }*/
    }
}

double BtsLogAnalyzer::getWireSharkTime(string const& lineInLogs) const
{
    int length(lineInLogs.length());
    int startIndexOfTime=0, endIndexOfTime=0;    int i=0;
    for(; i<length && stringHelper::isWhiteSpace(lineInLogs[i]); i++) {}
    for(; i<length && stringHelper::isNumber(lineInLogs[i]); i++) {}
    startIndexOfTime = i;
    for(; i<length && stringHelper::isWhiteSpace(lineInLogs[i]); i++) {}
    for(; i<length && !stringHelper::isWhiteSpace(lineInLogs[i]); i++) {}
    endIndexOfTime = i;
    return stringHelper::convertStringToNumber<double>(lineInLogs.substr(startIndexOfTime, endIndexOfTime-startIndexOfTime));
}

string BtsLogAnalyzer::getNumberAfterThisString(string const& mainString, string const& stringToSearch) const
{
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch);    if(stringHelper::isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        int lastIndexOfNumber;
        for(lastIndexOfNumber = lastIndexOfFirstString; stringHelper::isNumber(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

double BtsLogAnalyzer::getComputedAverageDelay() const
{
    cout<<"totalDelay: "<<m_totalDelay<<" count: "<<m_count<<endl;
    return (double)m_totalDelay/m_count;}

}//namespace alba
