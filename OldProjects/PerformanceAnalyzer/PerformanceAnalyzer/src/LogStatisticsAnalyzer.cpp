#include "LogStatisticsAnalyzer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>
#include <map>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

bool LogDetails::operator<(LogDetails const& logDetails) const
{
    string string1(stringHelper::combineStrings(logStrings, ""));
    string string2(stringHelper::combineStrings(logDetails.logStrings, ""));
    return string1 < string2;
}

bool LogDetails::operator>(LogDetails const& logDetails) const
{
    string string1(stringHelper::combineStrings(logStrings, ""));
    string string2(stringHelper::combineStrings(logDetails.logStrings, ""));
    return string1 > string2;
}

bool LogDetails::operator==(LogDetails const& logDetails) const
{
    string string1(stringHelper::combineStrings(logStrings, ""));
    string string2(stringHelper::combineStrings(logDetails.logStrings, ""));
    return string1 == string2;
}

LogStatisticsAnalyzer::LogStatisticsAnalyzer()
    : m_btsLogPathHandler("")
    , m_totalLinesFound(0)
    , m_totalLines(0)
{
    initializeLogDetailsToCheck();
}

void LogStatisticsAnalyzer::saveDataToCsv(string const& csvPath)
{
    AlbaLocalPathHandler outputFileHandler(csvPath);
    ofstream outputFileStream(outputFileHandler.getFullPath());
    saveLogDetailsToCsv(outputFileStream);
}

void LogStatisticsAnalyzer::saveLogDetailsToCsv(ofstream & outputCsvFileStream)
{
    outputCsvFileStream << "Log,Count,Percentage" <<"\n";
    map<string, unsigned int> dataToDisplay;
    for (LogDetails const& logDetails : m_logDetailsToCheck)
    {        string stringInCsv;
        stringHelper::strings const& logStrings(logDetails.logStrings);
        if(!logStrings.empty())
        {            string firstLogStringInCsv(string("[") + logStrings.front() + "]");
            stringInCsv += firstLogStringInCsv;
            for(auto it=logStrings.cbegin()+1; it!=logStrings.cend(); it++)
            {
                string logStringInCsv(string("[") + *it + "]");
                stringInCsv += " && ";
                stringInCsv += logStringInCsv;
            }
        }
        dataToDisplay.emplace(stringInCsv, logDetails.count);
    }
    for (pair<string, unsigned int> const& data : dataToDisplay)
    {
        outputCsvFileStream << data.first << "," << data.second << "," << ((double)data.second)/m_totalLines*100 <<"\n";
    }
    outputCsvFileStream << "Total Lines found," << m_totalLinesFound << "," << ((double)m_totalLinesFound)/m_totalLines*100 <<"\n";
    outputCsvFileStream << "Total Lines," << m_totalLines << "," << ((double)m_totalLines)/m_totalLines*100 <<"\n";
}

void LogStatisticsAnalyzer::processFileWithSortedPrints(std::string const& pathOfBtsSortedLog){
    m_btsLogPathHandler.input(pathOfBtsSortedLog);
    ifstream inputLogFileStream(m_btsLogPathHandler.getFullPath());
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        analyzeLog(lineInLogs);
    }
}

void LogStatisticsAnalyzer::analyzeLog(std::string const& lineInLogs)
{
    if(m_totalLines%10000==0)
    {
        cout << "m_totalLines: [" << m_totalLines << "]" <<"\n";
    }
    m_totalLines++;
    bool areLogStringFoundInTheLine=false;    for (LogDetails & logDetails : m_logDetailsToCheck)
    {
        bool areLogStringFound=false;
        bool areLogStringFoundInAllLogDetails=true;        for(string const& logString : logDetails.logStrings)
        {
            if(!stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, logString))
            {
                areLogStringFoundInAllLogDetails=false;
                break;
            }
        }
        areLogStringFound = areLogStringFoundInAllLogDetails;
        if(areLogStringFound)
        {
            areLogStringFoundInTheLine=true;
            logDetails.count++;
            //break;
        }
    }
    if(!areLogStringFoundInTheLine)
    {
        cout << "line not processed: [" << lineInLogs << "]" <<"\n";
    }
    else
    {        m_totalLinesFound++;
    }
}
void LogStatisticsAnalyzer::addLogDetailsToCheckInInitialization(strings const& logStrings)
{
    LogDetails logDetails;
    for(string const& logString : logStrings)
    {
        logDetails.logStrings.emplace_back(logString);
    }
    logDetails.count=0;
    m_logDetailsToCheck.emplace_back(logDetails);
}

void LogStatisticsAnalyzer::addLogDetailsToCheckInInitialization(string const& firstLogString, string const& secondLogString)
{
    LogDetails logDetails;
    logDetails.logStrings.emplace_back(firstLogString);
    logDetails.logStrings.emplace_back(secondLogString);
    logDetails.count=0;
    m_logDetailsToCheck.emplace_back(logDetails);
}

void LogStatisticsAnalyzer::initializeLogDetailsToCheck()
{
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_RL_RECONFIG_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_RL_RECONFIG_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_RL_SETUP_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_RL_SETUP_ACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_RL_RECONFIG_COMMIT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_TRANSPORT_SETUP_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_RL_RELEASE_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_DSP_CHANGE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_DSP_CHANGE_NACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_DSP_CHANGE_ACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_DSP_CHANGE_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_2_HSUPA_RESOURCE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_2_HSUPA_RESOURCE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_ANY_CF_HSUPA_RESOURCE_REMOVAL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_HSUPA_RESOURCE_REMOVAL_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_2_HSUPA_RESOURCE_REMOVAL_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_RL_RELEASE_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_HSDPA_RL_RECONFIG_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_HSDPA_RL_RECONFIG_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "printRabAndResourceUsage");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_CF_CF_SOFT_REQUEST_TIMER_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "processHsupaResourceReqWithResourceTypeHspaPool");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_RL_ADDITION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_RL_ADDITION_ACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_CONFIGURE_RAKE_RESOURCE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_CONFIGURE_RAKE_RESOURCE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "handleRlSetupReq(): Some parts of user already exist");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "createNewTransactionErrorHandler(): Error when creating new transaction");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "handleMsg(): NULL transaction has been tried to be used");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_EDCH_RES_RECONFIG_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_EDCH_RES_RECONFIG_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_HSDPA_RL_RECONFIG_COMMIT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_EDCH_RES_RECONFIG_DONE_IND_MSG");

    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_HSUPA_USER_REALLOCATION_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_ANY_CF_BB_COMMON_EDCH_HW_RESOURCE_INFO_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "handleHsRachCfAdditionRequest(): Failed adding HsRach CFs in Dsp.");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "handleUserTransferResp(): Failure of defragmentation user transfer");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_ANY_CF_BB_COMMON_EDCH_HW_RESOURCE_INFO_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_HSUPA_USER_REALLOCATION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_HSUPA_USER_REALLOCATION_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_LICENSED_CHANNEL_CAPACITY_STATE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_LRM_LICENSED_CHANNEL_CAPACITY_STATE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "setupHsRachCf(): HsRach Resource Allocation is blocked");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "printCpuDataCollection");

    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_RL_SETUP_NACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "gatherData(): nbccId:");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_EDCH_RES_RECONFIG_CANCEL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_EDCH_RES_RECONFIG_CANCEL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_CF_CF_REMOVE_CFS_TIMER_MSG");

    addLogDetailsToCheckInInitialization("TCOM/LRM", "TC_2_LRM_HSDPA_RL_RECONFIG_CANCEL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_COMMON_EDCH_HW_RESOURCE_REMOVAL_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_COMMON_EDCH_HW_RESOURCE_REMOVAL_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "BB_COMMON_EDCH_HW_RESOURCE_REMOVAL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/LRM", "handleRlReleaseDoneInd(): Unknown nbccId");





    addLogDetailsToCheckInInitialization("/TUP/", "[Rcvd: M_IP_ECF]");
    addLogDetailsToCheckInInitialization("/TUP/", "Connection data:");

    addLogDetailsToCheckInInitialization("TCOM/R", "CTRL_RLH_RlSetupReq3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "CTRL_RLH_RlDeletionReq3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "CTRL_RLH_RlReconfigPrepare3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "CTRL_RLH_RlDeletionReq3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RlSetupResp3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RlDeletionResp3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "CTRL_RLH_RlReconfigCommit3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RlReconfigReady3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RestoreInd3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_RL_PREP_RECONF_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_RL_RECONF_COMMIT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TNR_NBCC_REL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TNR_NBCC_DMEAS_BOARD_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_TRANSPORT_SETUP_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_RL_SETUP_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_RL_DELETION_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TNR_NBCC_DMEAS_BOARD_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_SETUP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_RL_SETUP_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_RL_SETUP_ACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_RL_RECONFIG_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_EDCH_RES_RECONFIG_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_HSDPA_RL_RECONFIG_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_RL_RECONFIG_COMMIT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_RL_RECONFIG_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_RL_CHANGE_DSP_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_DSP_CHANGE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_DSP_CHANGE_ACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_DSP_CHANGE_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_DSP_CHANGE_NACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_HSDPA_RL_RECONFIG_COMMIT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_EDCH_RES_RECONFIG_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_RECONFIG_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_RL_RECONFIG_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_SETUP_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_SETUP_ACK_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_DELETION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_DELETION_ACK_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_RECONFIG_COMMIT_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_ACTIVATE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_ACTIVATE_ACK_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_RL_RECONFIG_COMMIT_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_SYNC_INDICATION_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REGISTER_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REGISTER_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_UNREGISTER_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_SETUP_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_SETUP_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_DELETION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_DELETION_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_RL_CHANGE_DSP_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_RL_RELEASE_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "MSG TIME");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH internal flag during setup");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH internal flag during reconfig");
    addLogDetailsToCheckInInitialization(strings{"TCOM/R", "nbccId:", "currentSfn:", "commitSfn:", "cfn:"});

    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_RECONFIG_COMMIT_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_RECONFIG_COMMIT_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_HSDPA_RL_RECONFIG_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_EDCH_RES_RECONFIG_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_RECONFIG_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_RECONFIG_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_RECONFIG_COMMIT_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_ACTIVATE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_ACTIVATE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_RL_DELETION_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_RL_DELETION_PREPARE_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_HSUPA_USER_REALLOCATION_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_RL_PARAMETER_UPDATE_IND");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_DSP_REALLOCATION_DONE_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "Periodic CPU Usage Report");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_RLH_COUNTER_SAMPLE_REPORT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RlFailureInd3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_DSP_REALLOCATION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_HSUPA_USER_REALLOCATION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_HSUPA_USER_REALLOCATION_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_DSP_REALLOCATION_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_DSP_REALLOCATION_COMMIT_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_DSP_REALLOCATION_COMMIT_RESP_MSG");


    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RlSetupFail3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RlReconfigFail3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_RL_SETUP_NACK_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_RECONFIG_CANCEL_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_RL_RECONF_CANCEL_START_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_RECONFIG_CANCEL_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_EDCH_RES_RECONFIG_CANCEL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_2_RL_ADDITION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_RL_ADDITION_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_RL_ADDITION_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "CTRL_RLH_RlAdditionReq3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "RLH_CTRL_RlAdditionResp3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_LRM_RL_ADDITION_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_RL_ADDITION_ACK_RESP_MSG");

    addLogDetailsToCheckInInitialization("TCOM/R", "CTRL_RLH_RlReconfigCancel3G");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_CANCEL_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_REALLOCATION_CANCEL_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_DSP_REALLOCATION_CANCEL_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TUP_HSDPA_CANCEL_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_2_LRM_HSDPA_RL_RECONFIG_CANCEL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_RL_RECONF_CANCEL_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_DSP_REALLOCATION_CANCEL_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "BB_RL_RECONFIG_CANCEL_RESP_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/R", "TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_RESP_MSG");


    addLogDetailsToCheckInInitialization("TCOM/WRC", "getAverageRxPowerMonitoringLevel");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "handlePowerEvent");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "handleRxMonitoringTimeout");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "onCarrierStatusChange");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "sendCellMeasurementReport");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "OAM_FAULT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "TC_RADIO_STATE_CHANGE_REQ_MSG");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "TC_TCOM_POWER_LEVEL_REPORT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "sending TC_COUNTERS_MSG");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "received TC_COUNTERS_MSG");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "Periodic CPU Usage Report");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "handleRadioConfiguration");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "addRadioResource");
    addLogDetailsToCheckInInitialization("TCOM/WRC", "sendLtxMessage");


    addLogDetailsToCheckInInitialization("TCOM/CH", "BB_2_BCH_INFORMATION_REQ_MSG");

    addLogDetailsToCheckInInitialization("TCOM/G", "BB_SAMPLE_REPORT_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/G", "TC_2_LRM_DSP_CAPACITY_IND_MSG");
    addLogDetailsToCheckInInitialization("TCOM/G", "API_TCOM_RNC_MSG");
    addLogDetailsToCheckInInitialization("TCOM/G", "INF/TCOM/G, FCT:");
    addLogDetailsToCheckInInitialization("TCOM/G", "INF/TCOM/G, 0x13,");
    addLogDetailsToCheckInInitialization("TCOM/G", "INF/TCOM/G, 0x14,");
    addLogDetailsToCheckInInitialization("TCOM/G", "TNR_NBCC_STORE_IND_MSG");

    addLogDetailsToCheckInInitialization(strings{"TCOM/NC"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/CM"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/DM"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/TNR"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/TLH"});
    addLogDetailsToCheckInInitialization(strings{"/TUP/"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/G"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/TOAM"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/HSCH"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/CCHH"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/CH"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/R"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/LRM"});
    addLogDetailsToCheckInInitialization(strings{"TCOM/WRC"});


}

}
