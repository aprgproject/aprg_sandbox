/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Messages/MessageId_OamTcom.sig $
* @version               $LastChangedRevision: 2728 $
* @date                  $LastChangedDate: 2018-02-22 11:38:25 +0800 (Thu, 22 Feb 2018) $
* @author                $Author: rancastr $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _MESSAGEID_OAM_TCOM_SIG
#define _MESSAGEID_OAM_TCOM_SIG

/*************************************************************************
*   Telecom - O&M Protocol signal number space:
*
*   TC_OAM_BASE           0x6400    TCOM <-> O&M Protocol message base number
*   TC_OAM_MAX            0x67FF    TCOM <-> O&M Protocol message maximum number
*
*************************************************************************/
#include <glo_msg.h>

#define TC_HW_CONFIGURATION_MSG                     (TC_OAM_BASE + 0x00) /* !- SIGNO(struct SHwConfigurationMsg) -! */
#define TC_HW_CONFIGURATION_RESP_MSG                (TC_OAM_BASE + 0x01) /* !- SIGNO(struct SHwConfigurationResponseMsg) -! */
#define TC_HW_CONFIGURATION_CHANGE_MSG              (TC_OAM_BASE + 0x02) /* !- SIGNO(struct SHwConfigurationChangeMsg) -! */
#define TC_HW_CONFIGURATION_CHANGE_RESP_MSG         (TC_OAM_BASE + 0x03) /* !- SIGNO(struct SHwConfigurationChangeResponseMsg) -! */
#define TC_LOCAL_CELL_RESOURCE_STATE_IND_MSG        (TC_OAM_BASE + 0x04) /* !- SIGNO(struct SLocalCellResourceStateIndicationMsg) -! */
#define TC_CLOCK_STATE_MSG                          (TC_OAM_BASE + 0x05) /* !- SIGNO(struct SClockStateMsg) -! */
#define TC_LOCAL_CELL_MAPPING_INFO_MSG              (TC_OAM_BASE + 0x06) /* !- SIGNO(struct SLocalCellMappingInfoMsg) -! */
#define TC_CELL_AVAILABILITY_STATE_REQ_MSG          (TC_OAM_BASE + 0x07) /* !- SIGNO(struct SCellAvailabilityStateRequestMsg) -! */
#define TC_CELL_AVAILABILITY_STATE_IND_MSG          (TC_OAM_BASE + 0x08) /* !- SIGNO(struct SCellAvailabilityStateIndicationMsg) -! */
#define TC_START_FORCED_HO_MSG                      (TC_OAM_BASE + 0x09) /* !- SIGNO(struct SStartForcedHoMsg) -! */
#define TC_HO_FINISHED_MSG                          (TC_OAM_BASE + 0x0A) /* !- SIGNO(struct SHoFinishedMsg) -! */
#define TC_LINK_STATES_MSG                          (TC_OAM_BASE + 0x0B) /* !- SIGNO(struct SLinkStatesMsg) -! */
#define TC_LINK_STATES_RESP_MSG                     (TC_OAM_BASE + 0x0C) /* !- SIGNO(struct SLinkStatesResponseMsg) -! */
#define TC_RESERVE_CDMA_LOOP_RESOURCES_MSG          (TC_OAM_BASE + 0x0E) /* !- SIGNO(struct SReserveCdmaLoopResourcesMsg) -! */
#define TC_RESERVE_CDMA_LOOP_RESOURCES_RESPONSE_MSG (TC_OAM_BASE + 0x0F) /* !- SIGNO(struct SReserveCdmaLoopResourcesResponseMsg) -! */
#define TC_RELEASE_CDMA_LOOP_RESOURCES_MSG          (TC_OAM_BASE + 0x10) /* !- SIGNO(struct SReleaseCdmaLoopResourcesMsg) -! */
#define TC_RELEASE_CDMA_LOOP_RESOURCES_RESPONSE_MSG (TC_OAM_BASE + 0x11) /* !- SIGNO(struct SReleaseCdmaLoopResourcesResponseMsg) -! */
#define TC_SIR_REQUEST_MSG                          (TC_OAM_BASE + 0x12) /* !- SIGNO(struct SSirRequestMsg) -! */
#define TC_SIR_RESPONSE_MSG                         (TC_OAM_BASE + 0x13) /* !- SIGNO(struct SSirResponseMsg) -! */
#define TC_FREE_RESOURCE_REQ_MSG                    (TC_OAM_BASE + 0x14) /* !- SIGNO(struct SFreeResourceReqMsg) -! */
#define TC_FREE_RESOURCE_RESP_MSG                   (TC_OAM_BASE + 0x15) /* !- SIGNO(struct SFreeResourceRespMsg) -! */
#define TC_BTS_MANAGER_USED_IND_MSG                 (TC_OAM_BASE + 0x16) /* !- SIGNO(struct SBtsManagerUsedIndMsg) -! */
#define TC_TCOM_STARTUP_READY_IND_MSG               (TC_OAM_BASE + 0x17) /* !- SIGNO(struct STcomStartupReadyIndMsg) -! */
#define TC_LOOP_DELAY_REQ_MSG                       (TC_OAM_BASE + 0x18) /* !- SIGNO(struct SLoopDelayReqMsg) -! */
#define TC_LOOP_DELAY_REPORT_MSG                    (TC_OAM_BASE + 0x19) /* !- SIGNO(struct SLoopDelayReportMsg) -! */
#define TC_CELL_BLOCK_REQ_MSG                       (TC_OAM_BASE + 0x1A) /* !- SIGNO(struct SCellBlockingReq) -! */
#define TC_CELL_BLOCK_RESP_MSG                      (TC_OAM_BASE + 0x1B) /* !- SIGNO(struct SCellBlockingResp) -! */
#define TC_TOAM_CELL_BLOCK_CANCEL_MSG               (TC_OAM_BASE + 0x1C) /* !- SIGNO(struct SCancelBlockingInd) -! */
#define TC_LOCAL_CELL_PARAMETERS_IND_MSG            (TC_OAM_BASE + 0x1D) /* !- SIGNO(struct SLocalCellParametersIndMsg) -! */
#define TC_SET_CELL_PARAM_REQ_MSG                         (0x6422)       /* !- SIGNO(struct SetCellParamReq) -! */
#define TC_SET_CELL_PARAM_RESP_MSG                        (0x6423)       /* !- SIGNO(struct SetCellParamResp) -! */

/* new INC2 */
#define TC_USER_PLANE_PROCESSING_OVERLOAD_REQ_MSG         (0x6420)      /* !- SIGNO(struct SUserPlaneProcessingOverloadReq) -! */
#define TC_USER_PLANE_PROCESSING_OVERLOAD_RESP_MSG        (0x6421)      /* !- SIGNO(struct SUserPlaneProcessingOverloadResp) -! */

#define TC_USER_PLANE_PROCESSING_OVERLOAD_CANCEL_REQ_MSG  (0x6424)      /* !- SIGNO(struct SUserPlaneProcessingOverloadCancelReq) -! */
#define TC_USER_PLANE_PROCESSING_OVERLOAD_CANCEL_RESP_MSG (0x6425)      /* !- SIGNO(struct SUserPlaneProcessingOverloadCancelResp) -! */

/* INC6 */
#define TC_INITIAL_CALIBRATION_RESULT_IND_MSG             (0x695E)      /* !- SIGNO(struct InitialCalibrationResultInd) -! */
#define TC_INITIAL_CALIBRATION_GAIN_REQ_MSG               (0x6960)      /* !- SIGNO(struct InitialCalibrationGainReq) -! */
#define TC_INITIAL_CALIBRATION_GAIN_RESP_MSG              (0x695F)      /* !- SIGNO(struct InitialCalibrationGainResp) -! */

/* INC11 */
#define TC_TCOM_POWER_LEVEL_REPORT_IND_MSG                (0x6E45)      /* !- SIGNO(struct TcomPowerLevelReportInd) -! */
#define TC_BASEBAND_ALLOCATION_IND_MSG                    (0x6E46)      /* !- SIGNO(struct BasebandAllocationInd) -! */
#define TC_RTT_REQ_MSG                                    (0x6E4B)      /* !- SIGNO(struct RttReq) -! */
#define TC_RTT_RESP_MSG                                   (0x6E4C)      /* !- SIGNO(struct RttResp) -! */

/* INC12 */
#define TC_CELL_READY_FOR_LOOP_IND_MSG                    (0x6E63)      /* !- SIGNO(struct CellReadyForLoopInd) -! */
#define TC_HW_READY_FOR_LOOP_IND_MSG                      (0x6E64)      /* !- SIGNO(struct HwReadyForLoopInd) -! */

/* INC16 */
#define TC_HSPA_SCHEDULER_LOCATIONS_IND_MSG               (0x642A)      /* !- SIGNO(struct HspaSchedulerLocationsInd) -! */

/* INC23 */
#define TC_HSPA_LICENSE_ALLOCATION_IND_MSG                (0x642D)      /* !- SIGNO(struct SHspaLicenseAllocationInd) -! */

/* June 2010 iteration (1006) */
#define TC_TCOM_TLH_STARTUP_READY_IND_MSG                 (0x6E9D)      /* !- SIGNO(struct STcomTlhStartupReadyInd) -! */
#define TC_FEATURE_FLAGS_IND_MSG                          (0x6E9E)      /* !- SIGNO(struct SFeatureFlagsInd) -! */

/* August 2010 iteration (1008) - not used from WN9.0 - 44214ESPE05 */
#define TC_PIC_CONFIGURATION_UPDATE_IND_MSG               (0x5C06)      /* !- SIGNO(struct SPicConfigurationUpdateInd) -! */

/* September 2013 - 44214ESPE05 */
#define TC_PIC_CONFIGURATION_IND_MSG                      (0x6434)      /* !- SIGNO(struct SPicConfigurationInd) -! */

/* November 2010 iteration (1011) */
#define TC_MULTICAST_GROUP_ID_REQ_MSG                     (0x642E)      /* !- SIGNO(struct SMulticastGroupIdReq) -! */
#define TC_MULTICAST_GROUP_ID_RESP_MSG                    (0x642F)      /* !- SIGNO(struct SMulticastGroupIdResp) -! */

/* December 2010 iteration (1012) */
#define TC_COMPONENT_DEPLOYMENT_IND_MSG                   (0x6430)      /* !- SIGNO(struct SComponentDeploymentInd) -! */

/* September 2011 iteration (1109) */
#define TC_HS_CONFIGURATION_UPDATE_IND_MSG                (0x6431)      /* !- SIGNO(struct HsConfigurationUpdateInd) -! */

/* October 2011 iteration (1110) */
#define TC_POWER_SCALING_FACTOR_UPDATE_IND_MSG            (0x6432)      /* !- SIGNO(struct PowerScalingFactorUpdateInd) -! */

/* December 2012 iteration (1212) */
#define TC_HSDPA_SCHEDULER_INFO_UPDATE_IND_MSG            (0x6433)      /* !- SIGNO(struct HsdpaSchedulerInfoUpdateInd) -! */

/* December 2013 - CN5275 */
#define TC_RX_THRESHOLD_MONITORING_IND_MSG                (0x6436)      /* !- SIGNO(struct SRxThresholdMonitoringInd) -! */

/* February 2014 - CN5275 */
#define TC_COMMISSIONING_PARAMETERS_CHANGE_IND_MSG        (0x6437)      /* !- SIGNO(struct SCommissioningParametersChangeInd) -! */

/* May 2014 - 117088ESPE04 */
#define OAM_CANCEL_POWER_LEVEL_REPORT_IND_MSG             (0x6438)      /* !- SIGNO(struct SCancelPowerLevelReportInd) -! */

/* August 2014 - 111808ESPE01 */
#define TC_PIC_POOL_SETUP_READY_IND_MSG                   (0x6439)      /* !- SIGNO(struct SPicPoolSetupReadyInd) -! */
#endif /* _MESSAGEID_OAM_TCOM_SIG */

/* August 2014, PR: 53813ESPE05 */
#define TC_BASEBAND_ALLOCATION_REQ_MSG                    (0x6440)      /* !- SIGNO(struct SBasebandAllocationReq) -! */
#define TC_BASEBAND_ALLOCATION_RESP_MSG                   (0x6441)      /* !- SIGNO(struct SBasebandAllocationResp) -! */

/* RAN3252 */
#define TC_RESET_REQ_MSG                                  (0x6442)      /* !- SIGNO(struct SResetReq) -! */
#define TC_RESET_RESP_MSG                                 (0x6443)      /* !- SIGNO(struct SResetResp) -! */
#define TC_NE_ID_IND_MSG                                  (0x6444)      /* !- SIGNO(struct SNeIdInd) -! */

/* RAN3463 */
#define TC_FEATURE_ACTIVATION_STATE_UPDATE_IND_MSG        (0x6445)      /* !- SIGNO(struct SFeatureActivationStateUpdateInd) -! */
#define TC_CHANGE_FSP_POWER_STATE_REQ_MSG                 (0x6446)      /* !- SIGNO(struct SChangeFspPowerStateReq) -! */
#define TC_CHANGE_FSP_POWER_STATE_RESP_MSG                (0x6447)      /* !- SIGNO(struct SChangeFspPowerStateResp) -! */

/**
*******************************************************************************
* Description  : Defines the used signal identification numbers.
*
* Title        : Signal number definitions for O&M - Telecom IF
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* Additional Information :
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

