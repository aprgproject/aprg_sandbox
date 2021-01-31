/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Messages/MessageId_OamAtm.sig $
* @version               $LastChangedRevision: 2146 $
* @date                  $LastChangedDate: 2014-09-15 15:56:31 +0800 (Mon, 15 Sep 2014) $
* @author                $Author: grzebiel $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _MESSAGEID_OAMATM_SIG
#define _MESSAGEID_OAMATM_SIG

/*************************************************************************
*   O&M - Atm Protocol signal number space:
*
*   OAM_ATMHOST_BASE      0x8400     O&M <-> Atm Protocol message base number
*   OAM_ATMHOST_MAX       0x87FF     O&M <-> Atm Protocol message maximum number
*
*************************************************************************/

#include <glo_msg.h>

/* OAM-Atm message Ids:*/

#define OAM_ATM_HW_CONFIGURATION_MSG               (OAM_ATMHOST_BASE + 0x0000) /* !- SIGNO(struct SAtmHwConfigurationMsg) -! */
#define OAM_ATM_HW_CONFIGURATION_RESP_MSG          (OAM_ATMHOST_BASE + 0x0001) /* !- SIGNO(struct SAtmHwConfigurationResponseMsg) -! */
#define OAM_LINK_STATUS_MSG                        (OAM_ATMHOST_BASE + 0x0002) /* !- SIGNO(struct SLinkStatusMsg) -! */
#define OAM_LINK_STATUS_RESP_MSG                   (OAM_ATMHOST_BASE + 0x0003) /* !- SIGNO(struct SLinkStatusResponseMsg) -! */
#define OAM_MASTER_INDICATION_MSG                  (OAM_ATMHOST_BASE + 0x0004) /* !- SIGNO(struct SMasterIndicationMsg) -! */
#define OAM_MASTER_INDICATION_RESP_MSG             (OAM_ATMHOST_BASE + 0x0005) /* !- SIGNO(struct SMasterIndicationResponseMsg) -! */
#define OAM_CIF_ENABLED_MSG                        (OAM_ATMHOST_BASE + 0x0006) /* !- SIGNO(struct SCifEnabledMsg) -! */
#define OAM_CIF_ENABLED_RESP_MSG                   (OAM_ATMHOST_BASE + 0x0007) /* !- SIGNO(struct SCifEnabledResponseMsg) -! */
#define OAM_START_CDMA_LOOP_DATA_GEN_MSG           (OAM_ATMHOST_BASE + 0x0008) /* !- SIGNO(struct SStartCdmaLoopDataGenMsg) -! */
#define OAM_2_START_CDMA_LOOP_DATA_GEN_MSG               (0x8032)              /* !- SIGNO(struct S2StartCdmaLoopDataGenMsg) -! */
#define OAM_START_CDMA_LOOP_DATA_GEN_RESP_MSG      (OAM_ATMHOST_BASE + 0x0009) /* !- SIGNO(struct SStartCdmaLoopDataGenResponseMsg) -! */
#define OAM_STOP_CDMA_LOOP_DATA_GEN_MSG            (OAM_ATMHOST_BASE + 0x000A) /* !- SIGNO(struct SStopCdmaLoopDataGenMsg) -! */
#define OAM_STOP_CDMA_LOOP_DATA_GEN_RESP_MSG       (OAM_ATMHOST_BASE + 0x000B) /* !- SIGNO(struct SStopCdmaLoopDataGenResponseMsg) -! */
#define OAM_REQUEST_CDMA_LOOP_RESULTS_MSG          (OAM_ATMHOST_BASE + 0x000C) /* !- SIGNO(struct SRequestCdmaLoopResultsMsg) -! */
#define OAM_REQUEST_CDMA_LOOP_RESULTS_RESP_MSG     (OAM_ATMHOST_BASE + 0x000D) /* !- SIGNO(struct SRequestCdmaLoopResultsResponseMsg) -! */
#define OAM_ATM_SET_MONITORING_MSG                 (OAM_ATMHOST_BASE + 0x0010) /* !- SIGNO(struct SAtmSetMonitoringMsg) -! */
#define OAM_ATM_SET_MONITORING_RESP_MSG            (OAM_ATMHOST_BASE + 0x0011) /* !- SIGNO(struct SAtmSetMonitoringResponseMsg) -! */
#define OAM_ATM_GET_STATISTICS_MSG                 (OAM_ATMHOST_BASE + 0x0012) /* !- SIGNO(struct SAtmGetStatisticsMsg) -! */
#define OAM_ATM_GET_STATISTICS_RESP_MSG            (OAM_ATMHOST_BASE + 0x0013) /* !- SIGNO(struct SAtmGetStatisticsResponseMsg) -! */
#define OAM_AAL2_TEST_RESULT_REQUEST_MSG           (OAM_ATMHOST_BASE + 0x0014) /* !- SIGNO(struct SAal2TestResultRequestMsg) -! */
#define OAM_AAL2_TEST_RESULT_RESP_MSG              (OAM_ATMHOST_BASE + 0x0015) /* !- SIGNO(struct SAal2TestResultResponseMsg) -! */
#define OAM_ATM_STATUS_REQ_MSG                     (OAM_ATMHOST_BASE + 0x0016) /* !- SIGNO(struct SAtmStatusRequestMsg) -! */
#define OAM_ATM_STATUS_RESP_MSG                    (OAM_ATMHOST_BASE + 0x0017) /* !- SIGNO(struct SAtmStatusResponseMsg) -! */
#define ATM_EthArpAdd_Msg                          (OAM_ATMHOST_BASE + 0x0018) /* !- SIGNO(struct SATM_EthArpAdd) -! */
#define ATM_EthArpRemove_Msg                       (OAM_ATMHOST_BASE + 0x0019) /* !- SIGNO(struct SATM_EthArpRemove) -! */
#define ATM_EthArpDump_Msg                         (OAM_ATMHOST_BASE + 0x001A) /* !- SIGNO(struct SATM_EthArpDump) -! */
#define ATM_AtmArpAdd_Msg                          (OAM_ATMHOST_BASE + 0x001B) /* !- SIGNO(struct SATM_AtmArpAdd) -! */
#define ATM_AtmArpRemove_Msg                       (OAM_ATMHOST_BASE + 0x001C) /* !- SIGNO(struct SATM_AtmArpRemove) -! */
#define ATM_AtmArpDump_Msg                         (OAM_ATMHOST_BASE + 0x001D) /* !- SIGNO(struct SATM_AtmArpDump) -! */
#define ATM_IpAddrSet_Msg                          (OAM_ATMHOST_BASE + 0x001E) /* !- SIGNO(struct SATM_IpAddrSet) -! */
#define OAM_ATM_TEST_DEDICATED_STATE_REQUEST_MSG   (OAM_ATMHOST_BASE + 0x001F) /* !- SIGNO(struct SAtmTestDedicatedStateRequestMsg) -! */
#define OAM_ATM_TEST_DEDICATED_STATE_RESP_MSG      (OAM_ATMHOST_BASE + 0x0020) /* !- SIGNO(struct SAtmTestDedicatedStateResponseMsg) -! */
#define ATM_ChangeInitialSarMode_Msg               (OAM_ATMHOST_BASE + 0x0021) /* !- SIGNO(struct SATM_ChangeInitialSarMode) -! */
#define ATM_ChangeInitialSarModeAck_Msg            (OAM_ATMHOST_BASE + 0x0022) /* !- SIGNO(struct SATM_ChangeInitialSarModeAck) -! */
#define ATM_IpUseCif_Msg                           (OAM_ATMHOST_BASE + 0x0023) /* !- SIGNO(struct SATM_IpUseCif) -! */
#define ATM_IpUseCifAck_Msg                        (OAM_ATMHOST_BASE + 0x0024) /* !- SIGNO(struct SATM_IpUseCifAck) -! */
#define ATM_NAT_TABLE_MSG                          (OAM_ATMHOST_BASE + 0x0025) /* !- SIGNO(struct SAtmNatTableMsg) -! */
#define ATM_NAT_TABLE_RESP_MSG                     (OAM_ATMHOST_BASE + 0x0026) /* !- SIGNO(struct SAtmNatTableRespMsg) -! */
#define ATM_CONF_DUMP_MSG                          (OAM_ATMHOST_BASE + 0x0027) /* !- SIGNO(struct SATM_AtmConfDumpCmd) -! */
#define ATM_CONF_DUMP_ACK_MSG                      (OAM_ATMHOST_BASE + 0x0028) /* !- SIGNO(struct SATM_AtmConfDumpAck) -! */
#define ATM_AtmOamCpuStateChange_Msg               (OAM_ATMHOST_BASE + 0x0029) /* !- SIGNO(struct SAtmOamCpuStateChangeMsg) -! */
#define TECH_LOG_FILE_REQ_MSG                      (OAM_ATMHOST_BASE + 0x002A)  /* !- SIGNO(struct TechLogFileReq) -! */
#define TECH_LOG_FILE_ACK_MSG                      (OAM_ATMHOST_BASE + 0x002B)  /* !- SIGNO(struct TechLogFileAck) -! */
#define AAL2_PATH_BLOCK_IND_MSG                    (OAM_ATMHOST_BASE + 0x002C)  /* !- SIGNO(struct Aal2PathBlockInd) -! */
#define AAL2_PATH_BLOCK_ACK_MSG                    (OAM_ATMHOST_BASE + 0x002D)  /* !- SIGNO(struct Aal2PathBlockAck) -! */
#define TUP_START_ETHERNET_UDP_LOOP_REQ_MSG              (0x842E)  /* !- SIGNO(struct TupStartEthernetUdpLoopReq) -! */
#define TUP_START_ETHERNET_UDP_LOOP_RESP_MSG             (0x842F)  /* !- SIGNO(struct TupStartEthernetUdpLoopResp) -! */
#define TUP_STOP_ETHERNET_UDP_LOOP_REQ_MSG               (0x8430)  /* !- SIGNO(struct TupStopEthernetUdpLoopReq) -! */
#define TUP_STOP_ETHERNET_UDP_LOOP_RESP_MSG              (0x8431)  /* !- SIGNO(struct TupStopEthernetUdpLoopResp) -! */
#define TUP_ETHERNET_UDP_LOOP_REPORT_REQ_MSG             (0x8432)  /* !- SIGNO(struct TupEthernetUdpLoopReportReq) -! */
#define TUP_ETHERNET_UDP_LOOP_REPORT_RESP_MSG            (0x8433)  /* !- SIGNO(struct TupEthernetUdpLoopReportResp) -! */
#define OAM_ATM_TUPC_CONMAN_CONFIGURATION_REQ_MSG           (OAM_ATMHOST_BASE + 0x0034) /* !- SIGNO(struct STupcConmanConfigurationReq) -! */
#define OAM_ATM_TUPC_CONMAN_CONFIGURATION_RESP_MSG          (OAM_ATMHOST_BASE + 0x0035) /* !- SIGNO(struct STupcConmanConfigurationResp) -! */
#define OAM_ATM_TUPC_AALMAN_CONFIGURATION_REQ_MSG           (OAM_ATMHOST_BASE + 0x0036) /* !- SIGNO(struct STupcAalmanConfigurationReq) -! */
#define OAM_ATM_TUPC_AALMAN_CONFIGURATION_RESP_MSG          (OAM_ATMHOST_BASE + 0x0038) /* !- SIGNO(struct STupcAalmanConfigurationResp) -! */
#define OAM_ATM_TUPC_AALMAN_INTERNAL_CONFIGURATION_REQ_MSG  (OAM_ATMHOST_BASE + 0x0037) /* !- SIGNO(struct STupcAalmanInternalConfigurationReq) -! */
#define OAM_ATM_TUPC_AALMAN_INTERNAL_CONFIGURATION_RESP_MSG (OAM_ATMHOST_BASE + 0x0039) /* !- SIGNO(struct STupcAalmanInternalConfigurationResp) -! */



#endif /* _MESSAGEID_OAMATM_SIG */

/**
*******************************************************************************
* Description : Signal number definitions for O&M - ATM IF
*
* Reference   : ATM - CTRL MCUs IF spec v13.0
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUP / Kari Vakeva
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

