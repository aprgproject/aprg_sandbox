#include "BtsLogAnalyzer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WcdmaToolsBackend/BtsLogPrint.hpp>

#include <iomanip>
#include <iostream>
#include <set>

using namespace std;
using namespace wcdmaToolsBackend;

namespace alba {

BtsLogAnalyzer::BtsLogAnalyzer() : m_totalDelay(0), m_count(0) {}

BtsLogAnalyzer::BtsLogAnalyzer(string const& pathOfOutputFile)
    : m_outputStream(pathOfOutputFile), m_totalDelay(0), m_count(0) {
    if (m_outputStream.is_open()) {
        cout << "OutputStream is opened. Saving to output files"
             << "\n";
    }
}

void BtsLogAnalyzer::processFileForToCountUsersWithTracing(string const& filePath) {
    AlbaLocalPathHandler filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getFullPath() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    set<int> usersWithTracing;
    while (fileReader.isNotFinished()) {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundCaseSensitive(
                lineInLogs, "RLH sends BB_UE_TRACING_REPORT_IND_MSG (0x515D)")) {
            int msgType =
                stringHelper::convertHexStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgType: 0x"));
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            if (msgType == 0x1200) {
                usersWithTracing.emplace(nbccId);
                cout << "msgType: " << msgType << " nbccId: " << nbccId
                     << " number of usersWithTracing: " << usersWithTracing.size() << "\n";
            } else if (msgType == 0x1300) {
                if (usersWithTracing.find(nbccId) != usersWithTracing.end()) {
                    usersWithTracing.erase(nbccId);
                }
                cout << "msgType: " << msgType << " nbccId: " << nbccId
                     << " number of usersWithTracing: " << usersWithTracing.size() << "\n";
            }
        }
    }
}

void BtsLogAnalyzer::processDirectoryForWireSharkDelay(string const& directoryPath) {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaLocalPathHandler(directoryPath).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        processFileForWireSharkDelay(AlbaLocalPathHandler(filePath).getFullPath());
    }
}

void BtsLogAnalyzer::processFileForWireSharkDelay(string const& filePath) {
    m_wireSharkDelays.clear();
    cout << "processFile: " << AlbaLocalPathHandler(filePath).getFile() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    optional<double> startTimeFetchedOptional;
    optional<double> endTimeFetchedOptional;

    if (!inputLogFileStream.is_open()) {
        cout << "Cannot open file: " << filePath << "\n";
    }
    while (fileReader.isNotFinished()) {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(
                lineInLogs, R"(id-radioLinkSetup , RadioLinkSetupRequestFDD)")) {
            startTimeFetchedOptional = getWireSharkTime(lineInLogs);
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(id-radioLinkSetup , RadioLinkSetupResponseFDD)")) {
            endTimeFetchedOptional = getWireSharkTime(lineInLogs);
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(CRNC-CommunicationContextID: )")) {
            int crnccId = stringHelper::convertStringToNumber<int>(
                getNumberAfterThisString(lineInLogs, "CRNC-CommunicationContextID: "));
            WireSharkDelay& delayForCrnccId = m_wireSharkDelays[crnccId];
            if (startTimeFetchedOptional) {
                delayForCrnccId.startTimeOptional = startTimeFetchedOptional;
            }
            if (endTimeFetchedOptional) {
                delayForCrnccId.endTimeOptional = endTimeFetchedOptional;
            }
            startTimeFetchedOptional.reset();
            endTimeFetchedOptional.reset();

            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional) {
                double delay = delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                m_totalDelay += delay;
                m_count++;
                m_outputStream << crnccId << "," << setw(10) << delay << "\n";
                // cout<<"CrnccId: "<<crnccId<<" Delay: "<<delay<<" count: "<<m_count<<" totalDelay:
                // "<<m_totalDelay<<"\n";
                m_wireSharkDelays.erase(crnccId);
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(No.     Time)")) {
            startTimeFetchedOptional.reset();
            endTimeFetchedOptional.reset();
        }
    }
}

void BtsLogAnalyzer::processFileForMsgQueuingTime(string const& filePath) {
    AlbaLocalPathHandler filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getFullPath() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    int totalMsgQueuingTime = 0;
    int highestMsgQueuingTime = 0;
    int numberOfPrints = 0;
    while (fileReader.isNotFinished()) {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundCaseSensitive(lineInLogs, "MSG TIME, start queuing time")) {
            int msgQueuingTime =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgQueuingTime: "));
            totalMsgQueuingTime += msgQueuingTime;
            if (msgQueuingTime > highestMsgQueuingTime) {
                highestMsgQueuingTime = msgQueuingTime;
            }
            m_outputStream << msgQueuingTime << "," << lineInLogs << "\n";
            numberOfPrints++;
        }
    }
    cout << "TotalMsgQueuingTime: " << totalMsgQueuingTime << " highestMsgQueuingTime: " << highestMsgQueuingTime
         << " AverageMsgQueuingTime: " << ((double)totalMsgQueuingTime) / numberOfPrints
         << " numberOfPrints: " << numberOfPrints << "\n";
}

void BtsLogAnalyzer::processFileForBtsDelayForRlh(string const& filePath) {
    AlbaLocalPathHandler filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    cout << "processFile: " << filePathHandler.getFullPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";

    m_outputStream << "crnccId,nbccId,transactionId,delay"
                   << "\n";
    while (fileReader.isNotFinished()) {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(RLH_CTRL_RlSetupResp3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.endTimeOptional = logPrint.getBtsTime();
            }
            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional &&
                delayForCrnccId.startTimeOptional->getTotalSeconds() <=
                    delayForCrnccId.endTimeOptional->getTotalSeconds()) {
                BtsLogTime delayTime =
                    delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                int delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                // if(uniqueKey.crnccId == 15167){cout<<"crnccId "<<uniqueKey.crnccId<<"nbccId
                // "<<uniqueKey.nbccId<<"delay "<<delay<<"startTimeOptional
                // "<<delayForCrnccId.startTimeOptional.getReference()<<"endTimeOptional
                // "<<delayForCrnccId.endTimeOptional.getReference()<<"\n";}
                m_totalDelay += delay;
                m_count++;
                m_outputStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId << ","
                               << setw(10) << delay << "\n";
                m_btsLogDelays.erase(uniqueKey);
            }
        }
    }
}

void BtsLogAnalyzer::processFileForBtsDelayForRlDeletion(string const& filePath) {
    AlbaLocalPathHandler filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getFullPath() << "\n";

    m_outputStream << "crnccId,nbccId,transactionId,delay"
                   << "\n";
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(
                lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crncId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.endTimeOptional = logPrint.getBtsTime();
            }
            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional &&
                delayForCrnccId.startTimeOptional->getTotalSeconds() <=
                    delayForCrnccId.endTimeOptional->getTotalSeconds()) {
                BtsLogTime delayTime =
                    delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                int delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                // if(uniqueKey.crnccId == 15167){cout<<"crnccId "<<uniqueKey.crnccId<<"nbccId
                // "<<uniqueKey.nbccId<<"delay "<<delay<<"startTimeOptional
                // "<<delayForCrnccId.startTimeOptional.getReference()<<"endTimeOptional
                // "<<delayForCrnccId.endTimeOptional.getReference()<<"\n";}
                m_totalDelay += delay;
                m_count++;
                m_outputStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId << ","
                               << setw(10) << delay << "\n";
                m_btsLogDelays.erase(uniqueKey);
            }
        }
    }
}

void BtsLogAnalyzer::processFileForBtsDelayForMikhailKnife(string const& filePath) {
    AlbaLocalPathHandler filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getFullPath() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    ofstream grmFetchFileStream(filePathHandler.getDirectory() + R"(grmFetchFileStream.csv)");
    ofstream grmProcessFileStream(filePathHandler.getDirectory() + R"(grmProcessFileStream.csv)");
    ofstream messageDeliveryFileStream(filePathHandler.getDirectory() + R"(messageDeliveryFileStream.csv)");
    ofstream rlSetupFileStream(filePathHandler.getDirectory() + R"(rlSetupFileStream.csv)");
    grmFetchFileStream << "crnccId,"
                       << "nbccId,"
                       << "transactionId,"
                       << "difference"
                       << "\n";
    grmProcessFileStream << "crnccId,"
                         << "nbccId,"
                         << "transactionId,"
                         << "delay"
                         << "\n";
    messageDeliveryFileStream << "crnccId,"
                              << "nbccId,"
                              << "transactionId,"
                              << "delay"
                              << "\n";
    rlSetupFileStream << "crnccId,"
                      << "nbccId,"
                      << "transactionId,"
                      << "delay"
                      << "\n";

    std::map<UniqueId, BtsLogDelay> grmProcessMap;
    std::map<UniqueId, BtsLogDelay> messageDeliveryMap;
    std::map<UniqueId, BtsLogDelay> rlSetupMap;

    double grmFetchTotal = 0;
    int grmFetchCount = 0;
    double grmProcessTotal = 0;
    int grmProcessCount = 0;
    double messageDeliveryTotal = 0;
    int messageDeliveryCount = 0;
    double rlSetupTotal = 0;
    int rlSetupCount = 0;

    while (fileReader.isNotFinished()) {
        UniqueId uniqueKey;
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(
                lineInLogs, R"(INF/TCOM/G, decodeRadioLinkRequest API_TCOM_RNC_MSG)")) {
            int crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            int transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            unsigned int difference =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "diff in ms: "));
            if (difference != 0x80000000) {
                grmFetchTotal += difference * 1000;
                grmFetchCount++;
                grmFetchFileStream << crnccId << "," << nbccId << "," << transactionId << "," << setw(10) << difference
                                   << "\n";
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(INF/TCOM/G, Received API_TCOM_RNC_MSG)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& processMapInstance = grmProcessMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                processMapInstance.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(INF/TCOM/G, Sending API_TCOM_RNC_MSG)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& processMapInstance = grmProcessMap[uniqueKey];
            BtsLogDelay& messageDeliveryInstance = messageDeliveryMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                processMapInstance.endTimeOptional = logPrint.getBtsTime();
                messageDeliveryInstance.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& messageDeliveryInstance = messageDeliveryMap[uniqueKey];
            BtsLogDelay& rlSetupMapInstance = rlSetupMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                messageDeliveryInstance.endTimeOptional = logPrint.getBtsTime();
                rlSetupMapInstance.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(RLH_CTRL_RlSetupResp3G)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& rlSetupMapInstance = rlSetupMap[uniqueKey];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                rlSetupMapInstance.endTimeOptional = logPrint.getBtsTime();
            }
        }

        BtsLogDelay& processMapInstance = grmProcessMap[uniqueKey];
        if (processMapInstance.startTimeOptional && processMapInstance.endTimeOptional) {
            if (processMapInstance.startTimeOptional.value() < processMapInstance.endTimeOptional.value()) {
                BtsLogTime delayTime =
                    processMapInstance.endTimeOptional.value() - processMapInstance.startTimeOptional.value();
                int delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                grmProcessTotal += delay;
                grmProcessCount++;
                grmProcessFileStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId
                                     << "," << setw(10) << delay << "\n";
            }
            grmProcessMap.erase(uniqueKey);
        }

        BtsLogDelay& messageDeliveryInstance = messageDeliveryMap[uniqueKey];
        if (messageDeliveryInstance.startTimeOptional && messageDeliveryInstance.endTimeOptional) {
            if (messageDeliveryInstance.startTimeOptional.value() < messageDeliveryInstance.endTimeOptional.value()) {
                BtsLogTime delayTime =
                    messageDeliveryInstance.endTimeOptional.value() - messageDeliveryInstance.startTimeOptional.value();
                int delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                messageDeliveryTotal += delay;
                messageDeliveryCount++;
                messageDeliveryFileStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << ","
                                          << uniqueKey.transactionId << "," << setw(10) << delay << "\n";
            }
            messageDeliveryMap.erase(uniqueKey);
        }

        BtsLogDelay& rlSetupMapInstance = rlSetupMap[uniqueKey];
        if (rlSetupMapInstance.startTimeOptional && rlSetupMapInstance.endTimeOptional) {
            if (rlSetupMapInstance.startTimeOptional.value() < rlSetupMapInstance.endTimeOptional.value()) {
                BtsLogTime delayTime =
                    rlSetupMapInstance.endTimeOptional.value() - rlSetupMapInstance.startTimeOptional.value();
                int delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                rlSetupTotal += delay;
                rlSetupCount++;
                rlSetupFileStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId
                                  << "," << setw(10) << delay << "\n";
            }
            rlSetupMap.erase(uniqueKey);
        }
    }
    cout << "grmFetchTotal: " << grmFetchTotal << " count: " << grmFetchCount
         << " average:" << grmFetchTotal / grmFetchCount << "\n";
    cout << "grmProcessTotal: " << grmProcessTotal << " count: " << grmProcessCount
         << " average:" << grmProcessTotal / grmProcessCount << "\n";
    cout << "messageDeliveryTotal: " << messageDeliveryTotal << " count: " << messageDeliveryCount
         << " average:" << messageDeliveryTotal / messageDeliveryCount << "\n";
    cout << "rlSetupTotal: " << rlSetupTotal << " count: " << rlSetupCount << " average:" << rlSetupTotal / rlSetupCount
         << "\n";
}

void BtsLogAnalyzer::processFileForBtsDelayForGrm(string const& filePath) {
    AlbaLocalPathHandler filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getFullPath() << "\n";

    m_outputStream << "crnccId,nbccId,transactionId,delay"
                   << "\n";
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(
                lineInLogs, R"(INF/TCOM/G, Received API_TCOM_RNC_MSG)")) {
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelaysGrm[nbccId];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            int crnccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            int transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelaysGrm[nbccId];
            BtsLogPrint logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.endTimeOptional = logPrint.getBtsTime();
            }
            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional &&
                delayForCrnccId.startTimeOptional->getTotalSeconds() <=
                    delayForCrnccId.endTimeOptional->getTotalSeconds()) {
                BtsLogTime delayTime =
                    delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                int delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                if (delay < 1000000) {
                    m_totalDelay += delay;
                    m_count++;
                    m_outputStream << crnccId << "," << nbccId << "," << transactionId << "," << setw(10) << delay
                                   << "\n";
                }
                m_btsLogDelaysGrm.erase(nbccId);
            }
        }
        /*else if(stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(INF/TCOM/R,
        CTRL_RLH_)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(INF/TCOM/R,
        RLH_CTRL_)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(LRM_RL_)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs,
        R"(TC_2_RL_SETUP_IND_MSG)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(BB_2_RL_)")
                )
        {
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            m_btsLogDelaysGrm.erase(nbccId);
        }*/
    }
}

double BtsLogAnalyzer::getWireSharkTime(string const& lineInLogs) const {
    int length(lineInLogs.length());
    int startIndexOfTime = 0, endIndexOfTime = 0;
    int i = 0;
    for (; i < length && stringHelper::isWhiteSpace(lineInLogs[i]); i++) {
    }
    for (; i < length && stringHelper::isNumber(lineInLogs[i]); i++) {
    }
    startIndexOfTime = i;
    for (; i < length && stringHelper::isWhiteSpace(lineInLogs[i]); i++) {
    }
    for (; i < length && !stringHelper::isWhiteSpace(lineInLogs[i]); i++) {
    }
    endIndexOfTime = i;
    return stringHelper::convertStringToNumber<double>(
        lineInLogs.substr(startIndexOfTime, endIndexOfTime - startIndexOfTime));
}

string BtsLogAnalyzer::getNumberAfterThisString(string const& mainString, string const& stringToSearch) const {
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch);
    if (stringHelper::isNotNpos(firstIndexOfFirstString)) {
        int lastIndexOfFirstString = static_cast<int>(firstIndexOfFirstString + stringToSearch.length());
        int lastIndexOfNumber;
        for (lastIndexOfNumber = lastIndexOfFirstString; stringHelper::isNumber(mainString[lastIndexOfNumber]);
             ++lastIndexOfNumber)
            ;
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber - lastIndexOfFirstString);
    }
    return result;
}

double BtsLogAnalyzer::getComputedAverageDelay() const {
    cout << "totalDelay: " << m_totalDelay << " count: " << m_count << "\n";
    return (double)m_totalDelay / m_count;
}

}  // namespace alba
