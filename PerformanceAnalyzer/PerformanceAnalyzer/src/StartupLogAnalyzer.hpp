#pragma once

#include <BtsLogPrint.hpp>
#include <BtsLogTime.hpp>
#include <Optional/AlbaOptional.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace alba
{

class StartupLogAnalyzer
{

public:

    StartupLogAnalyzer();
    void clear();
    void saveDataToCsv(std::string const& csvPath);
    void saveDataTimeToCsv(std::ofstream & outputCsvFileStream, std::string const& description, std::vector<double> const& data);
    void processFileWithSortedPrints(std::string const& pathOfBtsLog);

private:
    void analyzeStartupDelays(std::string const& lineInLogs, tcomToolsBackend::BtsLogTime& previousNotableTime);
    double getTotalSeconds(tcomToolsBackend::BtsLogTime const& beforeTime, tcomToolsBackend::BtsLogTime const& afterTime) const;
    double getTotalSeconds(tcomToolsBackend::BtsLogTime const& btsLogTime) const;
    AlbaLocalPathHandler m_btsLogPathHandler;
    tcomToolsBackend::BtsLogTime m_firstLogTime;
    double m_processingAndMessagingTotalDelay;
    std::string m_processingAndMessagingTotalDelaysDescriptionString;
    std::string m_firstDspToBecomeAvailableTimeDescriptionString;
    std::string m_allDspsBecomeAvailableTimeDescriptionString;
    std::string m_settingSrioRoutesTimeDescriptionString;
    std::string m_basebandAllocationRequestResponseTimeDescriptionString;
    std::string m_firstDspModeChangeFromFirstDspAvailableDescriptionString;
    std::string m_firstModeChangeTimeDescriptionString;
    std::string m_startupAllocationTimeAfterModeChangeDescriptionString;
    std::string m_remainingLicenseExchangesTimeDescriptionString;
    std::string m_resetRequestResponseWithRncTimeDescriptionString;
    std::string m_auditRequestResponseWithRncTimeDescriptionString;
    std::string m_auditToFirstCellSetupTimeDescriptionString;
    std::string m_cellAllocationInTelecomTimeDescriptionString;
    std::string m_cellSetupInDspTimeDescriptionString;
    std::string m_antennaCarrierSetupRequestResponseTimeDescriptionString;
    std::string m_antennaCarrierActivateRequestResponseTimeDescriptionString;
    std::string m_commonChannelsSetupInDspDescriptionString;
    std::string m_commonChannelsActivationInDspDescriptionString;
    std::string m_commonChannelsActivationToCellSetupResponseTimeDescriptionString;
    std::string m_firstCtchSetupAfterFirstCellSetupTimeDescriptionString;
    std::string m_firstCtchSetupProcedureTimeDescriptionString;
    std::string m_firstCtchSetupToSiuTimeDescriptionString;
    std::string m_siuProcedureTimeDescriptionString;
    std::string m_siuToCellOnAirTimeDescriptionString;
    std::vector<double> m_processingAndMessagingTotalDelays;
    std::vector<double> m_firstDspToBecomeAvailableTime;
    std::vector<double> m_allDspsBecomeAvailableTime;
    std::vector<double> m_settingSrioRoutesTime;
    std::vector<double> m_basebandAllocationRequestResponseTime;
    std::vector<double> m_firstDspModeChangeFromFirstDspAvailable;
    std::vector<double> m_firstModeChangeTime;
    std::vector<double> m_startupAllocationTimeAfterModeChange;
    std::vector<double> m_remainingLicenseExchangesTime;
    std::vector<double> m_resetRequestResponseWithRncTime;
    std::vector<double> m_auditRequestResponseWithRncTime;
    std::vector<double> m_auditToFirstCellSetupTime;
    std::vector<double> m_cellAllocationInTelecomTime;
    std::vector<double> m_cellSetupInDspTime;
    std::vector<double> m_antennaCarrierSetupRequestResponseTime;
    std::vector<double> m_antennaCarrierActivateRequestResponseTime;
    std::vector<double> m_commonChannelsSetupInDsp;
    std::vector<double> m_commonChannelsActivationInDsp;
    std::vector<double> m_commonChannelsActivationToCellSetupResponseTime;
    std::vector<double> m_firstCtchSetupAfterFirstCellSetupTime;
    std::vector<double> m_firstCtchSetupProcedureTime;
    std::vector<double> m_firstCtchSetupToSiuTime;
    std::vector<double> m_siuProcedureTime;
    std::vector<double> m_siuToCellOnAirTime;


};

}
