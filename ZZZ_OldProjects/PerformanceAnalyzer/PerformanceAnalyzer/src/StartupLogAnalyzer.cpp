#include "StartupLogAnalyzer.hpp"

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;
using wcdmaToolsBackend::BtsLogPrint;
using wcdmaToolsBackend::BtsLogTime;
using wcdmaToolsBackend::BtsLogTimeType;

namespace alba {

StartupLogAnalyzer::StartupLogAnalyzer()
    : m_btsLogPathHandler(""),
      m_firstLogTime(),
      m_processingAndMessagingTotalDelay(0),
      m_processingAndMessagingTotalDelaysDescriptionString(),
      m_firstDspToBecomeAvailableTimeDescriptionString("First DSP to become available time: "),
      m_allDspsBecomeAvailableTimeDescriptionString("All DSPs become available time: "),
      m_settingSrioRoutesTimeDescriptionString("Setting SRIO routes time: "),
      m_basebandAllocationRequestResponseTimeDescriptionString(
          "Baseband allocation request and response available time: "),
      m_firstDspModeChangeFromFirstDspAvailableDescriptionString(
          "First DSP mode change from first DSP available time: "),
      m_firstModeChangeTimeDescriptionString("First mode change time: "),
      m_startupAllocationTimeAfterModeChangeDescriptionString("Startup allocation time after first mode change: "),
      m_remainingLicenseExchangesTimeDescriptionString("Waiting for license exchanges after startup allocation: "),
      m_resetRequestResponseWithRncTimeDescriptionString("Reset request response with RNC time: "),
      m_auditRequestResponseWithRncTimeDescriptionString("Audit request response with RNC time: "),
      m_auditToFirstCellSetupTimeDescriptionString("Audit to first cell setup with RNC time: "),
      m_cellAllocationInTelecomTimeDescriptionString(
          "Cell allocation in Telecom before cell setup to other components: "),
      m_cellSetupInDspTimeDescriptionString("Cell setup in DSP: "),
      m_antennaCarrierSetupRequestResponseTimeDescriptionString("Antenna carrier setup request and response time: "),
      m_antennaCarrierActivateRequestResponseTimeDescriptionString(
          "Antenna carrier activate request and response time: "),
      m_commonChannelsSetupInDspDescriptionString("Common channels setup in DSP: "),
      m_commonChannelsActivationInDspDescriptionString("Common channels activation in DSP: "),
      m_commonChannelsActivationToCellSetupResponseTimeDescriptionString(
          "Common channels activation to Cell Setup response time: "),
      m_firstCtchSetupAfterFirstCellSetupTimeDescriptionString("First CTCH setup after first cell setup time: "),
      m_firstCtchSetupProcedureTimeDescriptionString("First CTCH setup procedure time: "),
      m_firstCtchSetupToSiuTimeDescriptionString("First CTCH setup to SIU time: "),
      m_siuProcedureTimeDescriptionString("SIU procedure time: "),
      m_siuToCellOnAirTimeDescriptionString("SIU to cell on air time: ")

{}

void StartupLogAnalyzer::clear() { m_processingAndMessagingTotalDelay = 0; }

void StartupLogAnalyzer::saveDataToCsv(string const& csvPath) {
    AlbaLocalPathHandler outputFileHandler(csvPath);
    ofstream outputFileStream(outputFileHandler.getFullPath());
    saveDataTimeToCsv(
        outputFileStream, m_firstDspToBecomeAvailableTimeDescriptionString, m_firstDspToBecomeAvailableTime);
    saveDataTimeToCsv(outputFileStream, m_allDspsBecomeAvailableTimeDescriptionString, m_allDspsBecomeAvailableTime);
    // saveDataTimeToCsv(outputFileStream, m_settingSrioRoutesTimeDescriptionString, m_settingSrioRoutesTime);
    saveDataTimeToCsv(
        outputFileStream, m_basebandAllocationRequestResponseTimeDescriptionString,
        m_basebandAllocationRequestResponseTime);
    saveDataTimeToCsv(
        outputFileStream, m_firstDspModeChangeFromFirstDspAvailableDescriptionString,
        m_firstDspModeChangeFromFirstDspAvailable);
    saveDataTimeToCsv(outputFileStream, m_firstModeChangeTimeDescriptionString, m_firstModeChangeTime);
    saveDataTimeToCsv(
        outputFileStream, m_startupAllocationTimeAfterModeChangeDescriptionString,
        m_startupAllocationTimeAfterModeChange);
    // saveDataTimeToCsv(outputFileStream, m_remainingLicenseExchangesTimeDescriptionString,
    // m_remainingLicenseExchangesTime); saveDataTimeToCsv(outputFileStream,
    // m_resetRequestResponseWithRncTimeDescriptionString, m_resetRequestResponseWithRncTime);
    // saveDataTimeToCsv(outputFileStream, m_auditRequestResponseWithRncTimeDescriptionString,
    // m_auditRequestResponseWithRncTime);
    saveDataTimeToCsv(outputFileStream, m_auditToFirstCellSetupTimeDescriptionString, m_auditToFirstCellSetupTime);
    saveDataTimeToCsv(outputFileStream, m_cellAllocationInTelecomTimeDescriptionString, m_cellAllocationInTelecomTime);
    saveDataTimeToCsv(outputFileStream, m_cellSetupInDspTimeDescriptionString, m_cellSetupInDspTime);
    saveDataTimeToCsv(
        outputFileStream, m_antennaCarrierSetupRequestResponseTimeDescriptionString,
        m_antennaCarrierSetupRequestResponseTime);
    saveDataTimeToCsv(
        outputFileStream, m_antennaCarrierActivateRequestResponseTimeDescriptionString,
        m_antennaCarrierActivateRequestResponseTime);
    saveDataTimeToCsv(outputFileStream, m_commonChannelsSetupInDspDescriptionString, m_commonChannelsSetupInDsp);
    saveDataTimeToCsv(
        outputFileStream, m_commonChannelsActivationInDspDescriptionString, m_commonChannelsActivationInDsp);
    saveDataTimeToCsv(
        outputFileStream, m_commonChannelsActivationToCellSetupResponseTimeDescriptionString,
        m_commonChannelsActivationToCellSetupResponseTime);
    saveDataTimeToCsv(
        outputFileStream, m_firstCtchSetupAfterFirstCellSetupTimeDescriptionString,
        m_firstCtchSetupAfterFirstCellSetupTime);
    saveDataTimeToCsv(outputFileStream, m_firstCtchSetupProcedureTimeDescriptionString, m_firstCtchSetupProcedureTime);
    saveDataTimeToCsv(outputFileStream, m_firstCtchSetupToSiuTimeDescriptionString, m_firstCtchSetupToSiuTime);
    saveDataTimeToCsv(outputFileStream, m_siuProcedureTimeDescriptionString, m_siuProcedureTime);
    saveDataTimeToCsv(outputFileStream, m_siuToCellOnAirTimeDescriptionString, m_siuToCellOnAirTime);
    saveDataTimeToCsv(outputFileStream, "Processing and messaging total delay:", m_processingAndMessagingTotalDelays);
}

void StartupLogAnalyzer::saveDataTimeToCsv(
    ofstream& outputCsvFileStream, string const& description, vector<double> const& data) {
    outputCsvFileStream << description << ",";
    for (double const value : data) {
        outputCsvFileStream << value << ",";
    }
    outputCsvFileStream << "\n";
}

void StartupLogAnalyzer::processFileWithSortedPrints(std::string const& pathOfBtsSortedLog) {
    clear();

    m_btsLogPathHandler.input(pathOfBtsSortedLog);
    ifstream inputLogFileStream(m_btsLogPathHandler.getFullPath());

    cout.precision(20);
    AlbaFileReader fileReader(inputLogFileStream);
    BtsLogTime previousNotableTime;
    while (fileReader.isNotFinished()) {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        analyzeStartupDelays(lineInLogs, previousNotableTime);
    }
}

void StartupLogAnalyzer::analyzeStartupDelays(string const& lineInLogs, BtsLogTime& previousNotableTime) {
    static unsigned int state = 1;

    BtsLogPrint logPrint(lineInLogs);
    BtsLogTime logTimeInLogs(logPrint.getBtsTime());

    BtsLogTime allowedLogs(BtsLogTimeType::BtsTimeStamp, "2019-12-03T00:00:00.000000Z");
    if (logTimeInLogs > allowedLogs) {
        if (state == 1 && isStringFoundNotCaseSensitive(lineInLogs, R"(/WTS/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_HW_CONFIGURATION_MSG)")) {
            cout << "Log: [" << lineInLogs << "]\n\n";
            previousNotableTime = logTimeInLogs;
            m_firstLogTime = logTimeInLogs;
            state++;
        } else if (
            state == 2 &&
            (isStringFoundNotCaseSensitive(lineInLogs, R"(/WTS/)") &&
             //                 isStringFoundNotCaseSensitive(lineInLogs,
             //                 R"(PrintHwConfigurationChangeMsg(), hardware: WspUnit)") &&
             isStringFoundNotCaseSensitive(
                 lineInLogs, R"(TC_HW_CONFIGURATION_CHANGE_MSG for dsp)") &&
             isStringFoundNotCaseSensitive(lineInLogs, R"(isUnitAvailable: Available)"))) {
            double firstDspToBecomeAvailableTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_firstDspToBecomeAvailableTimeDescriptionString << firstDspToBecomeAvailableTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_firstDspToBecomeAvailableTime.emplace_back(firstDspToBecomeAvailableTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 3 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(
                lineInLogs, R"(Entering state: InitialHWConfiguration)")) {
            double allDspsBecomeAvailableTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_allDspsBecomeAvailableTimeDescriptionString << allDspsBecomeAvailableTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_allDspsBecomeAvailableTime.emplace_back(allDspsBecomeAvailableTime);
            previousNotableTime = logTimeInLogs;
            state = 6;
        } /*
         else if(state==4 &&
                 isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
                 isStringFoundNotCaseSensitive(lineInLogs, R"(sending API_SET_SRIO_ROUTE_REQ_MSG)"))
         {
             double processingAndMessagingDelay=getTotalSeconds(previousNotableTime, logTimeInLogs);
             cout<<"Processing and messaging delay time: "<<processingAndMessagingDelay<<"\n";
             cout<<"Log: ["<<lineInLogs<<"]\n\n";
             m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
             previousNotableTime = logTimeInLogs;
             state++;
         }
         else if(state==5 &&
                 isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
                 (isStringFoundNotCaseSensitive(lineInLogs, R"(CHwapiSrioServiceAgent, Error:
         Timeout())")
                  || isStringFoundNotCaseSensitive(lineInLogs, R"(API_SET_SRIO_ROUTE_RESP_MSG)")))
         {
             double settingSrioRoutesTime=getTotalSeconds(previousNotableTime, logTimeInLogs);
             cout<<m_settingSrioRoutesTimeDescriptionString<<settingSrioRoutesTime<<"\n";
             cout<<"Log: ["<<lineInLogs<<"]\n\n";
             m_settingSrioRoutesTime.emplace_back(settingSrioRoutesTime);
             previousNotableTime = logTimeInLogs;
             state++;
         }*/
        else if (
            state == 6 &&
            (isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") ||
             isStringFoundNotCaseSensitive(lineInLogs, R"(/WTS/)")) &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_BASEBAND_ALLOCATION_REQ_MSG)")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << "Processing and messaging delay time: " << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 7 &&
            (isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") ||
             isStringFoundNotCaseSensitive(lineInLogs, R"(/WTS/)")) &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_BASEBAND_ALLOCATION_RESP_MSG)")) {
            double basebandAllocationRequestResponseTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_basebandAllocationRequestResponseTimeDescriptionString << basebandAllocationRequestResponseTime
                 << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_basebandAllocationRequestResponseTime.emplace_back(basebandAllocationRequestResponseTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 8 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(MODE_CHANGE_REQ_MSG)")) {
            double firstDspModeChangeFromFirstDspAvailable = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_firstDspModeChangeFromFirstDspAvailableDescriptionString
                 << firstDspModeChangeFromFirstDspAvailable << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_firstDspModeChangeFromFirstDspAvailable.emplace_back(firstDspModeChangeFromFirstDspAvailable);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 9 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(MODE_CHANGE_RESP_MSG)")) {
            double firstModeChangeTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_firstModeChangeTimeDescriptionString << firstModeChangeTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_firstModeChangeTime.emplace_back(firstModeChangeTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 10 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_STARTUP_ALLOCATION_DONE_IND_MSG)")) {
            double startupAllocationTimeAfterModeChange = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_startupAllocationTimeAfterModeChangeDescriptionString << startupAllocationTimeAfterModeChange
                 << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_startupAllocationTimeAfterModeChange.emplace_back(startupAllocationTimeAfterModeChange);
            previousNotableTime = logTimeInLogs;
            state = 14;
        }
        /*else if(state==11 &&
                isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
                isStringFoundNotCaseSensitive(lineInLogs, R"(TC_GRM_TOAM_LICENCE_READY_IND_MSG)"))
        {
            double remainingLicenseExchangesTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout<<m_remainingLicenseExchangesTimeDescriptionString<<remainingLicenseExchangesTime<<"\n";
            cout<<"Log: ["<<lineInLogs<<"]\n\n";
            m_remainingLicenseExchangesTime.emplace_back(remainingLicenseExchangesTime);
            previousNotableTime = logTimeInLogs;
            state++;
        }
        else if(state==12 &&
                isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
                isStringFoundNotCaseSensitive(lineInLogs, R"(API_TCOM_RNC_CNBAP_MSG 0x1B3A,
        SendResetRequest())"))
        {
            double processingAndMessagingDelay=getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout<<"Processing and messaging delay time: "<<processingAndMessagingDelay<<"\n";
            cout<<"Log: ["<<lineInLogs<<"]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        }
        else if(state==13 &&
                isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
                isStringFoundNotCaseSensitive(lineInLogs, R"(Decoded ResetResponse3G)"))
        {
            double resetRequestResponseWithRncTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout<<m_resetRequestResponseWithRncTimeDescriptionString<<resetRequestResponseWithRncTime<<"\n";
            cout<<"Log: ["<<lineInLogs<<"]\n\n";
            m_resetRequestResponseWithRncTime.emplace_back(resetRequestResponseWithRncTime);
            previousNotableTime = logTimeInLogs;
            state++;
        }*/
        else if (
            state == 14 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(CAuditHandler, HandleAuditRequest())")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << "Processing and messaging delay time: " << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 15 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(
                lineInLogs, R"(API_TCOM_RNC_CNBAP_MSG 0x1B3A, SendAuditResponse())")) {
            double auditRequestResponseWithRncTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_auditRequestResponseWithRncTimeDescriptionString << auditRequestResponseWithRncTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_auditRequestResponseWithRncTime.emplace_back(auditRequestResponseWithRncTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 14 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(
                lineInLogs, R"(API_TCOM_RNC_CNBAP_MSG 0x1B3A, SendResourceStatusIndicationNF)")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << "Processing and messaging delay time: " << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 15 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(
                lineInLogs, R"(API_TCOM_RNC_CNBAP_MSG 0x1B3A, SendCapabilityIndication())")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << "Processing and messaging delay time: " << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        }
        // old stuffs
        else if (
            state == 16 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(NBAP Procedure code 5,)")) {
            double auditToFirstCellSetupTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_auditToFirstCellSetupTimeDescriptionString << auditToFirstCellSetupTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_auditToFirstCellSetupTime.emplace_back(auditToFirstCellSetupTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 17 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_DMGR_CELL_SETUP_REQ_MSG)")) {
            double cellAllocationInTelecomTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_cellAllocationInTelecomTimeDescriptionString << cellAllocationInTelecomTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_cellAllocationInTelecomTime.emplace_back(cellAllocationInTelecomTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 18 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_DMGR_CELL_SETUP_RESP_MSG)")) {
            double cellSetupInDspTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_antennaCarrierSetupRequestResponseTimeDescriptionString << cellSetupInDspTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_cellSetupInDspTime.emplace_back(cellSetupInDspTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 19 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(ANTENNA_CARRIER_SETUP_REQ)")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << "Processing and messaging delay time: " << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 20 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(ANTENNA_CARRIER_SETUP_REPLY)")) {
            double antennaCarrierSetupRequestResponseTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_antennaCarrierActivateRequestResponseTimeDescriptionString
                 << antennaCarrierSetupRequestResponseTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_antennaCarrierSetupRequestResponseTime.emplace_back(antennaCarrierSetupRequestResponseTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 21 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(ANTENNA_CARRIER_ACTIVATE_REQ)")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_commonChannelsSetupInDspDescriptionString << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 22 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(ANTENNA_CARRIER_ACTIVATE_REPLY)")) {
            double antennaCarrierActivateRequestResponseTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_antennaCarrierActivateRequestResponseTimeDescriptionString
                 << antennaCarrierActivateRequestResponseTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_antennaCarrierActivateRequestResponseTime.emplace_back(antennaCarrierActivateRequestResponseTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 23 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_DMGR_COMMON_CHANNEL_SETUP_REQ_MSG)")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << "Processing and messaging delay time: " << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 24 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_DMGR_COMMON_CHANNEL_SETUP_RESP_MSG)")) {
            double commonChannelsSetupInDsp = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_commonChannelsSetupInDspDescriptionString << commonChannelsSetupInDsp << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_commonChannelsSetupInDsp.emplace_back(commonChannelsSetupInDsp);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 25 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(
                lineInLogs, R"(TC_DMGR_COMMON_CHANNEL_ACTIVATION_REQ_MSG)")) {
            double processingAndMessagingDelay = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << "Processing and messaging delay time: " << processingAndMessagingDelay << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_processingAndMessagingTotalDelay += getTotalSeconds(previousNotableTime, logTimeInLogs);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 26 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(
                lineInLogs, R"(TC_DMGR_COMMON_CHANNEL_ACTIVATION_RESP_MSG)")) {
            double commonChannelsActivationInDsp = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_commonChannelsActivationInDspDescriptionString << commonChannelsActivationInDsp << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_commonChannelsActivationInDsp.emplace_back(commonChannelsActivationInDsp);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 27 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(SendCellSetupResponse())")) {
            double commonChannelsActivationToCellSetupResponseTime =
                getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_commonChannelsActivationToCellSetupResponseTimeDescriptionString
                 << commonChannelsActivationToCellSetupResponseTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_commonChannelsActivationToCellSetupResponseTime.emplace_back(
                commonChannelsActivationToCellSetupResponseTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 28 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_CCHH_CTCH_SETUP_REQ_MSG)")) {
            double firstCtchSetupAfterFirstCellSetupTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_firstCtchSetupAfterFirstCellSetupTimeDescriptionString << firstCtchSetupAfterFirstCellSetupTime
                 << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_firstCtchSetupAfterFirstCellSetupTime.emplace_back(firstCtchSetupAfterFirstCellSetupTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 29 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_CCHH_CTCH_SETUP_RESP_MSG)")) {
            double firstCtchSetupProcedureTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_firstCtchSetupProcedureTimeDescriptionString << firstCtchSetupProcedureTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_firstCtchSetupProcedureTime.emplace_back(firstCtchSetupProcedureTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 30 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_CCHH_SYSTEM_INFO_UPDATE_REQ_MSG)")) {
            double firstCtchSetupToSiuTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_firstCtchSetupToSiuTimeDescriptionString << firstCtchSetupToSiuTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_firstCtchSetupToSiuTime.emplace_back(firstCtchSetupToSiuTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 31 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_CCHH_SYSTEM_INFO_UPDATE_RESP_MSG)")) {
            double siuProcedureTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_siuProcedureTimeDescriptionString << siuProcedureTime << "\n";
            cout << "Log: [" << lineInLogs << "]\n\n";
            m_siuProcedureTime.emplace_back(siuProcedureTime);
            previousNotableTime = logTimeInLogs;
            state++;
        } else if (
            state == 32 && isStringFoundNotCaseSensitive(lineInLogs, R"(/TCOM/)") &&
            isStringFoundNotCaseSensitive(lineInLogs, R"(TC_CELL_AVAILABILITY_STATE_CHANGE_MSG)")) {
            double siuToCellOnAirTime = getTotalSeconds(previousNotableTime, logTimeInLogs);
            cout << m_siuToCellOnAirTimeDescriptionString << siuToCellOnAirTime << "\n";
            m_siuToCellOnAirTime.emplace_back(siuToCellOnAirTime);
            cout << "Log: [" << lineInLogs << "]\n\n";

            // print other stuffs:

            cout << "Total processing and messaging delay: " << m_processingAndMessagingTotalDelay << "\n";
            m_processingAndMessagingTotalDelays.emplace_back(m_processingAndMessagingTotalDelay);
            cout << "Total time from hardware configuration to cell on air: "
                 << getTotalSeconds(m_firstLogTime, logTimeInLogs) << "\n\n";

            previousNotableTime = logTimeInLogs;
            state = 1;
        }
    }
}

double StartupLogAnalyzer::getTotalSeconds(BtsLogTime const& beforeTime, BtsLogTime const& afterTime) const {
    BtsLogTime latency = afterTime - beforeTime;
    return getTotalSeconds(latency);
}

double StartupLogAnalyzer::getTotalSeconds(BtsLogTime const& btsLogTime) const {
    double result(
        (double)btsLogTime.getMinutes() * 1000000 * 60 + (double)btsLogTime.getSeconds() * 1000000 +
        (double)btsLogTime.getMicroSeconds());
    return result / 1000000;
}

}  // namespace alba
