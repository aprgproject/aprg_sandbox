/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1805_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/Oam_Tcom_TestModelService.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Bartosz Ciesla
* @brief                 Set of messages related to BTSOM TCOM IFS Test Loop service
* @module                WCDMA Control Plane
* @owner                 WCDMA Control Plane
*
* Copyright 2012 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _OAM_TCOM_TEST_MODEL_SERVICE_H
#define _OAM_TCOM_TEST_MODEL_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <SMessageHeader.h>
#include <SMessageAddress.h>
#include <EStatus.h>
#include <DTtmTassuDefinitions.h>
#include <TNumberOfItems.h>
#include <SCellConfigData_Ver2.h>
#include <SCellConfigData.h>
#include <SCchhToWamMap.h>
#include <TTelecomTestId.h>
#include <ECdmaTestDataPattern.h>
#include <ECdmaTestPatternMode.h>
#include <TTfi.h>
#include <TCarrierNumber.h>
#include <TPrimaryScramblingCode.h>
#include <TTxPowerOfPrimaryCcpch.h>
#include <TErrorRate.h>
#include <TReportInterval.h>
#include <TTestModel.h>
#include <SCTCSRPRACHC.h>
#include <ETtmMeasType.h>
#include <TMimoPhase.h>
#include <EMimoStream.h>
#include <Glo_bs.h>


/* Service name for Service Discovery functionality
 */
#define TCOM_TEST_MODEL_SERVICE_NAME          "TCOM_TEST_MODEL_SERVICE"

/* Service version major number for Service Discovery
 */
#define TCOM_TEST_MODEL_SERVICE_VERSION_MAJOR 1

/* Service version minor number for Service Discovery
 */
#define TCOM_TEST_MODEL_SERVICE_VERSION_MINOR 0



struct STestDedicatedStateReadyMsg
{
    MESSAGEHEADER(msgHeader)
    EStatus                  status;
    ETestStateCause          cause;
};
typedef struct STestDedicatedStateReadyMsg STestDedicatedStateReadyMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader API message header
*
* status    ack/nack
*
* cause     appropriate cause value if status is nack
*
************************************************************************/




struct STestConfigurationMsg
{
  MESSAGEHEADER(msgHeader)
  TNumberOfItems           numOfValidCellConfig;
  SCellConfigData          cellConfigData[MAX_NUM_OF_LOCAL_CELLS];
  SCchhToWamMap            cellToWamMap[MAX_NUM_OF_LOCAL_CELLS];
};
typedef struct STestConfigurationMsg STestConfigurationMsg;

struct STestConfigurationMsg_Ver2
{
  MESSAGEHEADER(msgHeader)
  TNumberOfItems           numOfValidCellConfig;
  SCellConfigData_Ver2     cellConfigData[MAX_NUM_OF_LOCAL_CELLS];
  SCchhToWamMap            cellToWamMap[MAX_NUM_OF_LOCAL_CELLS];
};
typedef struct STestConfigurationMsg_Ver2 STestConfigurationMsg_Ver2;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                API message header
*
*  numOfValidCellConfig     indicates how many of the following array
*                           elements are valid
*
*  cellConfigData[..]       array of cell configuration parameters (Version 2)
*
*  cellToWamMap[..]         information about how cells are mapped to
*                           different wam's
*
************************************************************************/




struct STestModelSetupReqMsg
{
  MESSAGEHEADER(msgHeader)
  TTestModel                   testModel;
  TTelecomTestId               testId;
  TNumberOfItems               numberOfDpch; /* number of DPCH in test model 0/3/16/32/64*/
  TNumberOfItems               numberOfHsPdsch; /* number of HS-PDSCH in TM5 2/4/8*/
  ECdmaTestDataPattern         testPattern;
  ECdmaTestPatternMode         patternMode;
  TTfi                         dlTfi;
  TCarrierNumber               uarfcn;
  TPrimaryScramblingCode       primaryScramblingCode;
  TTxPowerOfPrimaryCcpch       txPowerOfPrimaryCcpch;
  SDlTestRl                    testRl;
  TMimoPhase                   mimoPhase;
  EMimoStream                  mimoStream;
  TBoolean                     vamDedicatedTestModel;
};
typedef struct STestModelSetupReqMsg STestModelSetupReqMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader             API message header
*
* testModel             indicates that which test model is setup
*
* testId                testId is used to identify message
*
* numberOfDpch          indicates how many DPCH is setup for test model
*
* numberOfHsPdsch       indicates how many HS-PDSCH is setup for TM5
*
* testPattern           indicates what kind of testdata is generated
*                       to test channels
*
* dlTfi                 index to transportformatset array. Defines
*                       max bitrate for test channel
*
* uarfcn                used frequency for testmodel
*
* primaryScramblingCode used primary scramblingcode for testModel
*
* txPowerOfPrimaryCcpch used for testmodel 4 to tell used PCCPCH power
*
*
* testRl                radiolink parameters for testmodel.
*                       cId value is needed to inform used cell
*
* mimoPhase             Phase information between two TXs.
*                       Value "0xFF"  for No-MIMO.
*
* mimmoStream           With single mode both TXs use same seed value
*                       (23 x channelization code) of PN9 data generation.
*                       With dual mode,seed value is different,
*                       23 x channelization code for TX1 and
*                       24 x channelization code for TX2.
*
* vamDedicatedTestModel true/false, default false, determine whether non
*                       standard 3gpp power for DPCH is allowed.
*
************************************************************************/




struct STestModelSetupRespMsg
{
  MESSAGEHEADER(msgHeader)
  TTelecomTestId               testId;
  EStatus                      status;
  ETestStateCause              cause;
};
typedef struct STestModelSetupRespMsg STestModelSetupRespMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader API message header
*
* testId    testId is used to identify message
*
* status    ack/nack
*
* cause     appropriate cause value if status is nack
*
************************************************************************/




struct STestModelReleaseReqMsg
{
  MESSAGEHEADER(msgHeader)
  TTelecomTestId               testId;
};
typedef struct STestModelReleaseReqMsg STestModelReleaseReqMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader API message header
*
* testId    testId is used to identify message
*
************************************************************************/




struct STestModelReleaseRespMsg
{
  MESSAGEHEADER(msgHeader)
  TTelecomTestId               testId;
  EStatus                      status;
  ETestStateCause              cause;
};
typedef struct STestModelReleaseRespMsg STestModelReleaseRespMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader API message header
*
* testId    testId is used to identify message
*
* status    ack/nack
*
* cause     appropriate cause value if status is nack
*
************************************************************************/




struct STtmBerMeasStartMsg
{
  MESSAGEHEADER(msgHeader)
  TTelecomTestId               testId;
  ECdmaTestDataPattern         testDataPattern;
  ECdmaTestPatternMode         patternMode;
  TTfi                         ulTfi;
  ETtmMeasType                 testMeasType;
  TErrorRate                   inSyncLimit;
  TErrorRate                   outOfSyncLimit;
  TCarrierNumber               uarfcn;
  TPrimaryScramblingCode       primaryScramblingCode;
  TReportInterval              measurementPeriod;
  SMessageAddress              berReportReceiver;
  STestRl                      testRl;
  SCTCSRPRACHC                 testRach;

};
typedef struct STtmBerMeasStartMsg STtmBerMeasStartMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader             API message header
*
* testModel             indicates that which test model is setup
*
* testId                testId is used to identify message
*
* testPattern           indicates what kind of testdata is generated
*                       to test channels
*
* patternMode           indicates how UL testdata is generated
*
* ulTfi                 index to transportformatset array. Defines
*                       max bitrate for test channel
*
* testMeasType          Test Measurement type
*
* inSyncLimit           BER in percents (all-ones == 100 %)
*
* outOfSyncLimit        BER in percents (all-ones == 100 %)
*
* uarfcn                used frequency for testmodel
*
* measurementPeriod     BER reporting period in milliseconds
*
* primaryScramblingCode used primary scramblingcode for testModel
*
* berReportReceiver     Receiver information for BER Report message generated by ATM SW.
*
* testRl                radiolink parameters for testmodel.
*                       cId value is needed to inform used cell
*
* testRach              Test Rach
*
************************************************************************/




struct STtmBerMeasStartRespMsg
{
  MESSAGEHEADER(msgHeader)
  TTelecomTestId               testId;
  EStatus                      status;
  ETestStateCause              cause;
};
typedef struct STtmBerMeasStartRespMsg STtmBerMeasStartRespMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                API message header
*
*  testId               testId is used to identify message
*
*  status               ack/nack
*
*  cause             appropriate cause value if status is nack
************************************************************************/




struct STtmBerMeasStopMsg
{
  MESSAGEHEADER(msgHeader)
  TTelecomTestId               testId;
};
typedef struct STtmBerMeasStopMsg STtmBerMeasStopMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader API message header
*
* testId    testId is used to identify message
*
************************************************************************/




struct STtmBerMeasStopRespMsg
{
  MESSAGEHEADER(msgHeader)
  TTelecomTestId               testId;
  EStatus                      status;
  ETestStateCause              cause;
};
typedef struct STtmBerMeasStopRespMsg STtmBerMeasStopRespMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
* msgHeader API message header
*
* testId    testId is used to identify message
*
* status    ack/nack
*
* cause     appropriate cause value if status is nack
*
************************************************************************/




#ifdef __cplusplus
}
#endif

#endif /* _OAM_TCOM_TEST_MODEL_SERVICE_H */

/**
*******************************************************************************
*
* Reference           : BTSOM TCOM IFS, version 53.0
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/


