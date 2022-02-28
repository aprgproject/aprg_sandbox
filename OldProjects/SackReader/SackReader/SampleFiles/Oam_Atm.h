/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Messages/Oam_Atm.h $
* @version               $LastChangedRevision: 2573 $
* @date                  $LastChangedDate: 2016-04-07 10:34:16 +0800 (Thu, 07 Apr 2016) $
* @author                $Author: psakurai $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _OAM_ATM_H
#define _OAM_ATM_H

#include <glo_def.h>
#include <EResponseCond.h>
#include <TLoopReference.h>
#include <SDspAddressInformation.h>
#include <ECdmaTestDataPattern.h>
#include <ECdmaTestPatternMode.h>
#include <TErrorRate.h>
#include <TPnSeed.h>
#include <TCdmaTestLength.h>
#include <EStatus.h>
#include <TStatsCounter.h>
#include <ELoopPoint.h>
#include <EAtmCause.h>
#include <SMonitorFpFilter.h>
#include <SMonitorMsgIdFilter.h>
#include <EMonitorType.h>
#include <EMonitorMode.h>
#include <TChannelId.h>
#include <SVcc.h>
#include <EAtmStatistics.h>
#include <EAtmStatisticsFlag.h>
#include <TNumberOfPresence.h>
#include <CoreTypes.h>
#include <SAalMgrEthArpTbl.h>
#include <SAalMgrIpoaArpTbl.h>
#include <ESarMode.h>
#include <SMessageHeader.h>
#include <SAtmNatConfigEntry.h>
#include <D_AtmConsts.h>
#include <SConnRec.h>
#include <SMessageAddress.h>
#include <EUnitState.h>
#include <EWspType.h>
#include <EControlUnitType.h>
#include <EConditional.h>
#include <EBoolean.h>
#include <TTransportPathIdentifier.h>
#include <TTransportIdentifier.h>
#include <STupConfigurationInfo.h>
#include <TDynamicData.h>
#include <TMtuSize.h>
#include <STupcBtsParameters.h>
#include <TTransportLayerAddress.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_HW_CONFIGURATION_MSG
 *
*******************************************
*    Static part
*******************************************
*   header      Message header.
*
*   typeOfConfiguration       Type of configuration (NORA or FLEX).
*
*   tupConfigurationPresent     Flexi TUP configuration presence selector.
*
*   flexiTupConfigurationInfo   Check the tupConfigurationPresent field in
*                               the configuration message for presence.
*                               FLEX: Flexi Tup Configuration Information.
*                               (NORA: Not relevant to Nora.)
*
*   commisioningParameters      BTS Commissioning parameters.
*   numOfWspBoards            Number of WSP/FSP boards.
*
*   numOfFlexiConnections     Number of Flexi Connections.
*
*******************************************
*    Dynamic part
*******************************************
*   Content of the dynamic part:
*
*   SFspInformation         Includes parameters related for WSP/FSP board
*                               information. Number of SFspInformation to be
*                               in this message is set to numOfWspBoards in the
*                               static part of this message. NORA: Only WSPA and
*                               WSPC boards are included here (for EUBB boards see
*                               below a separate section).
*
*   SConnection       OPTIONAL.
*                               NORA: Includes parameters related for ATM
*                               Connection array. Number of SConnection
*                               to be in this message is set to numOfNoraConnections
*                               in the Static part of this message. WN6.0: The WAM-WSMF
*                               ATM connections are also included here, which is a static
*                               configuration, see WAM-AXU IFS.
*
*   SFlexiConnectionInfo  OPTIONAL.
*                               FLEX: Includes parameters related for Flexi
*                               connections. The field contains MRS configuration
*                               info and UDP port (FCM) configuration related
*                               information. Number of SFlexiConnectionInfo
*                               to be in this message is set to numOfFlexiConnections
*                               in the Static part of this message.
*
*   SFspInformation   OPTIONAL.
*                               NORA (EUBB): Includes parameters related for WSMF and
*                               WSPF board information. Number of SFspInformation to be
*                               in this message is set to numOfEubbUnits in the static part
*                               of this message. From here you see what EUBB units are
*                               actually installed in the BTS.
*                               Note that the board addresses have been reused from
*                               existing WAM and WSP address numberings, so they are here
*                               in a separate EUBB section, which is allowed to contain
*                               only EUBB boards.
*
*
* dynamicData
*/
typedef struct SAtmHwConfigurationMsg
{
        MESSAGEHEADER(header)

        EControlUnitType         typeOfConfiguration;/* Type of configuration (NORA or FLEX)*/
        EConditional             tupConfigurationPresent;
        STupConfigurationInfo    tupConfigurationInfo;
        STupcBtsParameters       commisioningParameters;
        TMtuSize                 ipMtuSize;            /* Maximal Transport Unit size for IP Stack for SCTP */
        TNumberOfPresence        numOfWspBoards;       /* Number of WSP/FSP boards */
        TNumberOfPresence        numOfFlexiConnections;/* Number of Flexi Connections */

    /*  -- start of dynamic part --*/

    TDynamicData dynamicData[1]; /* dynamic data */
} SAtmHwConfigurationMsg;







/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_HW_CONFIGURATION_RESP_MSG
 *
 *
 */
typedef struct SAtmHwConfigurationResponseMsg
{
        MESSAGEHEADER(header)

        EResponseCond            response;
        EAtmCause                cause;
} SAtmHwConfigurationResponseMsg;








/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_LINK_STATUS_MSG
 *
 *
 */
typedef struct SLinkStatusMsg
{
        MESSAGEHEADER(header)

        ELinkState               cnbap;
        ELinkState               dnbap;
        TTransportLayerAddress   sctpFarEndAddress;
} SLinkStatusMsg;





/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_LINK_STATUS_RESP_MSG
 *
 *
 */
typedef struct SLinkStatusResponseMsg
{
        MESSAGEHEADER(header)
    u32 spare;
} SLinkStatusResponseMsg;








/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_MASTER_INDICATION_MSG
 *
 */
typedef struct SMasterIndicationMsg
{
        MESSAGEHEADER(header)

        TBoard                   oamMaster;
        TBoard                   telecomMaster;
} SMasterIndicationMsg;






/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_MASTER_INDICATION_RESP_MSG
 *
 */
typedef struct SMasterIndicationResponseMsg
{
        MESSAGEHEADER(header)
    u32 spare;
} SMasterIndicationResponseMsg;









/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_CIF_ENABLED_MSG
 *
 */
typedef struct SCifEnabledMsg
{
        MESSAGEHEADER(header)
    u32 spare;
} SCifEnabledMsg;





/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_CIF_ENABLED_RESP_MSG
 *
 *
 */
typedef struct SCifEnabledResponseMsg
{
        MESSAGEHEADER(header)
    u32 spare;
} SCifEnabledResponseMsg;









/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_START_CDMA_LOOP_DATA_GEN_MSG
 *
 */
typedef struct SStartCdmaLoopDataGenMsg
{
        MESSAGEHEADER(header)

        TLoopReference           loopReference;
        SDspAddressInformation   dspAddress;

        ECdmaTestDataPattern     testData;        /* (PN9)*/
        ECdmaTestPatternMode     testPatternMode; /* (continuous)*/

        TErrorRate               inSyncLimit;     /*  BER in percents (all-ones == 100 %)*/
        TErrorRate               outOfSyncLimit;

        TPNSeed                  pnSeed;          /* (1)*/

        TCdmaTestLength          numFramesToSend; /*  0: forever (continue until stop command; 1..n: stop automatically after given number of frames).*/

} SStartCdmaLoopDataGenMsg;




/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_2_START_CDMA_LOOP_DATA_GEN_MSG
 *
 */
typedef struct S2StartCdmaLoopDataGenMsg
{
        MESSAGEHEADER(header)

        TLoopReference           loopReference;

        ECdmaTestDataPattern     testData;        /* (PN9)*/
        ECdmaTestPatternMode     testPatternMode; /* (continuous)*/

        TErrorRate               inSyncLimit;     /*  BER in percents (all-ones == 100 %)*/
        TErrorRate               outOfSyncLimit;

        TPNSeed                  pnSeed;          /* (1)*/

        TCdmaTestLength          numFramesToSend; /*  0: forever (continue until stop command; 1..n: stop automatically after given number of frames).*/

} S2StartCdmaLoopDataGenMsg;






/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_START_CDMA_LOOP_DATA_GEN_RESP_MSG
 *
 */
typedef struct SStartCdmaLoopDataGenResponseMsg
{
        MESSAGEHEADER(header)

        TLoopReference           loopReference;
        EResponseCond            response;
        EAtmCause                cause;
} SStartCdmaLoopDataGenResponseMsg;







/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_STOP_CDMA_LOOP_DATA_GEN_MSG
 *
 */
typedef struct SStopCdmaLoopDataGenMsg
{
        MESSAGEHEADER(header)

        TLoopReference           loopReference;
} SStopCdmaLoopDataGenMsg;






/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_STOP_CDMA_LOOP_DATA_GEN_RESP_MSG
 *
 */
typedef struct SStopCdmaLoopDataGenResponseMsg
{
        MESSAGEHEADER(header)

        TLoopReference           loopReference;
        EResponseCond            response;
        EAtmCause                cause;
} SStopCdmaLoopDataGenResponseMsg;








/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_REQUEST_CDMA_LOOP_RESULTS_MSG
 *
 */
typedef struct SRequestCdmaLoopResultsMsg
{
        MESSAGEHEADER(header)

        TLoopReference           loopReference;
} SRequestCdmaLoopResultsMsg;






/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_REQUEST_CDMA_LOOP_RESULTS_RESP_MSG
 *
 *
 */
typedef struct SRequestCdmaLoopResultsResponseMsg
{
        MESSAGEHEADER(header)

        TLoopReference           loopReference;
        EResponseCond            response;           /*  (Nack returned, if reference not found!)*/
        EAtmCause                cause;

        TErrorRate               bler;
        TErrorRate               ber;                /*  (largest number (all-ones) means 1.0 (100%))*/
        u32                      numberOfReceivedBitsHigh;
        u32                      numberOfReceivedBitsLow;

        u32                      numberOfDefectedBitsHigh;
        u32                      numberOfDefectedBitsLow;
        u32                      crcErrorCountHigh;
        u32                      crcErrorCountLow;

        EStatus                  syncState;
        u32                      unsynchronizedFramesHigh;
        u32                      unsynchronizedFramesLow;
        u32                      frameCountHigh;
        u32                      frameCountLow;

} SRequestCdmaLoopResultsResponseMsg;







/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_SET_MONITORING_MSG
 *
 */
typedef struct SAtmSetMonitoringMsg
{
        MESSAGEHEADER(header)

        EMonitorType             type;
        EMonitorMode             mode;       /*  new monitoring mode*/
        SMessageAddress          target;     /*  where to send*/
        SVcc                     vcc;
        TTransportPathIdentifier transportPath;
        TTransportIdentifier     transportIdentifier;
        SMonitorFpFilter         fpFilter;
        SMonitorMsgIdFilter      msgIdFilter;
        SMessageAddress          monitoringAddress;
} SAtmSetMonitoringMsg;





/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_SET_MONITORING_RESP_MSG
 *
 */
typedef struct SAtmSetMonitoringResponseMsg
{
        MESSAGEHEADER(header)

        EMonitorType             type;
        EMonitorMode             mode;
        EResponseCond            response;
        EAtmCause                cause;
        TChannelId               channelId;
} SAtmSetMonitoringResponseMsg;






/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_GET_STATISTICS_MSG
 *
 *
 */
typedef struct SAtmGetStatisticsMsg
{
        MESSAGEHEADER(header)

        EAtmStatistics         item;
        EAtmStatisticsFlag     flag;
        SVcc                   vcc;
        TTransportIdentifier   transportIdentifier;
        SMessageAddress        locationAddress;
} SAtmGetStatisticsMsg;





/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_GET_STATISTICS_RESP_MSG
 *
 */
typedef struct SAtmGetStatisticsResponseMsg
{
        MESSAGEHEADER(header)

        EAtmStatistics         item;
        EAtmStatisticsFlag     flag;
        EResponseCond          response;   /* NACK == no data returned!*/
        EAtmCause              cause;

        TChannelId             channelId;
        TNumberOfPresence      numOctets;
        u8                     data[1];    /* (item (EAtmStatistics) defines structure to apply)*/
} SAtmGetStatisticsResponseMsg;







/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_AAL2_TEST_RESULT_REQUEST_MSG
 *
 */
typedef struct SAal2TestResultRequestMsg
{
        MESSAGEHEADER(header)
    u32 spare;
} SAal2TestResultRequestMsg;





/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_AAL2_TEST_RESULT_RESP_MSG
 *
 */
typedef struct SAal2TestResultResponseMsg
{
        MESSAGEHEADER(header)

        TNumberOfPresence        numResults;         /*  (N1)*/
        struct
        {
                SMessageAddress      atmMcuId;
                u32                  ber;                /*  (largest number (all-ones) means 1.0 (100%))*/
        } result[3];

} SAal2TestResultResponseMsg;










/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_TEST_DEDICATED_STATE_REQUEST_MSG
 *
 *
 */
typedef struct SAtmTestDedicatedStateRequestMsg
{
        MESSAGEHEADER(header)
    u32 spare;
} SAtmTestDedicatedStateRequestMsg;





/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_TEST_DEDICATED_STATE_RESP_MSG
 *
 *
 */
typedef struct SAtmTestDedicatedStateResponseMsg
{
        MESSAGEHEADER(header)

        EResponseCond            response;
        EAtmCause                cause;
} SAtmTestDedicatedStateResponseMsg;












/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_STATUS_REQ_MSG
 *
 */
typedef struct SAtmStatusRequestMsg
{
        MESSAGEHEADER(header)

        TCpu                     atmProcessor;       /*  (ATMHOST_MCU, ATM1_MCU, ATM2_MCU, (3))*/
} SAtmStatusRequestMsg;




/********************************************************************
 *
 *
 *  SIGNAL NAME:    OAM_ATM_STATUS_RESP_MSG
 *
 */
typedef struct SAtmStatusResponseMsg
{
        MESSAGEHEADER(header)

        TCpu                     atmProcessor;       /*  (ATMHOST_MCU, ATM1_MCU, ATM2_MCU, (3))*/
        EResponseCond            response;
        EAtmCause                cause;
} SAtmStatusResponseMsg;




/*
 *
 *   SIGNAL NAME:  ATM_EthArpAdd_Msg
 *
 */
typedef struct SATM_EthArpAdd
{
        MESSAGEHEADER(header)
        u32                             req;            /*  1 : request, 0 : reply*/
        u32                             ipa;            /*  IP - address*/
        u8                              mac[6];         /*  MAC address*/
        u8                              subrack;        /*  0 : None, 1,2,3 : subrack*/
        u8                              pad;            /*  Padding*/
    u32             status;     /*  1 : ok, 0: failed*/
} SATM_EthArpAdd;

/*
 *
 *   SIGNAL NAME:  ATM_EthArpRemove_Msg
 *
 *
 */
typedef struct SATM_EthArpRemove
{
        MESSAGEHEADER(header)
        u32                             req;            /*  1 : request, 0 : reply*/
        u32                             ipa;            /*  IP - address*/
        u32             status;     /*  1 : ok, 0: failed*/

} SATM_EthArpRemove;

/*
 *
 *   SIGNAL NAME:  ATM_EthArpDump_Msg
 *
 *
 */
typedef struct SATM_EthArpDump
{
        MESSAGEHEADER(header)
        u32                                     req;            /*  1 : request, 0 : reply*/
        u32                                 status;     /*  1 : ok, 0: failed*/
        SAalMgrEthArpTbl        tbl[AALM_ETH_ARPTBL_SIZE];      /*  Entries...*/

} SATM_EthArpDump;




/*
 *
 *   SIGNAL NAME:  ATM_AtmArpAdd_Msg
 *
 *
 */
typedef struct SATM_AtmArpAdd
{
        MESSAGEHEADER(header)
        u32                             req;            /*  1 : request, 0 : reply*/
        u32                             ip_address;     /*  IP - address*/
        u8                              pad;            /*  Not used*/
        u8                              vpi;            /*  VPI*/
        u16                             vci;            /*  VCI*/
        u32                             sar_chid;       /*  Not used*/
        u32             status;     /*  1 : ok, 0: failed*/

} SATM_AtmArpAdd;

/*
 *
 *   SIGNAL NAME:  ATM_AtmArpRemove_Msg
 *
 *
 */
typedef struct SATM_AtmArpRemove
{
        MESSAGEHEADER(header)
        u32                             req;            /*  1 : request, 0 : reply*/
        u32                             ipa;            /*  IP - address*/
        u32             status;     /*  1 : ok, 0: failed*/
} SATM_AtmArpRemove;

/*
 *
 *   SIGNAL NAME:  ATM_AtmArpDump_Msg
 *
 */
typedef struct SATM_AtmArpDump
{
        MESSAGEHEADER(header)
        u32                                     req;            /*  1 : request, 0 : reply*/
        u32                                 status;     /*  1 : ok, 0: failed*/
        SAalMgrIpoaArpTbl       tbl[AALM_ATM_ARPTBL_SIZE];      /*  Entries...*/
} SATM_AtmArpDump;



/*
 *
 *   SIGNAL NAME:  ATM_IpAddrSet_Msg
 *
 */
typedef struct SATM_IpAddrSet
{
        MESSAGEHEADER(header)
        u32                                     req;            /*  1 : request, 0 : reply*/
        u32                                     ipa;            /*  IP - address to set*/
        u32                                     subnetmask; /*  Subnet mask to set*/
        u32                                 status;     /*  Return only : 1 : ok, 0: failed*/
        u32                                     inetstat;       /*  Return only : Err code returned by OSE INET : 0 :ok*/
} SATM_IpAddrSet;




/*
 *
 *   SIGNAL NAME:  ATM_ChangeInitialSarMode_Msg
 *
 */
typedef struct SATM_ChangeInitialSarMode
{
        MESSAGEHEADER(header)
        ESarMode                newInitialSarMode;
} SATM_ChangeInitialSarMode;


/*
 *
 *   SIGNAL NAME:  ATM_ChangeInitialSarModeAck_Msg
 *
 */
typedef struct SATM_ChangeInitialSarModeAck
{
        MESSAGEHEADER(header)
        ESarMode                newInitialSarMode;
        EResponseCond           response;
        EAtmCause               cause;
} SATM_ChangeInitialSarModeAck;



/*
 *
 *   SIGNAL NAME:  ATM_IpUseCif_Msg
 *
 *
 */
typedef struct SATM_IpUseCif
{
        MESSAGEHEADER(header)
        u32     UseCif; /*  Nonzero : yes, 0 : no*/

        /*  Is there currently HUB connection between these subracks ?*/
        u8      HubConnSR_01_02; /*  1 : yes, 0 : no*/
        u8      HubConnSR_01_03; /*  1 : yes, 0 : no*/
        u8      HubConnSR_02_03; /*  1 : yes, 0 : no*/

        /*  Operational WAM:s, those capable to copy IP traffic between*/
        /*  Ethernet and ATM*/
        u8 WAM10_up; /*  1 : yes, 0 : no*/
        u8 WAM11_up; /*  1 : yes, 0 : no*/
        u8 WAM20_up; /*  1 : yes, 0 : no*/
        u8 WAM21_up; /*  1 : yes, 0 : no*/
        u8 WAM30_up; /*  1 : yes, 0 : no*/
        u8 WAM31_up; /*  1 : yes, 0 : no*/

        /*  Normally WAM10 and WAM11 are in subrack 1, WAM20 and WAM21*/
        /*  in subrack 2 etc.*/
        /*  There are exceptions to this, however. If boards are in*/
        /*  non default subracks, the values are given here*/
        /*  Values : 1,2 or 3 : subrack number, 0 : not known*/

        u8 WAM10_sr; /*  Subrack number*/
        u8 WAM11_sr; /*  Subrack number*/
        u8 WAM20_sr; /*  Subrack number*/
        u8 WAM21_sr; /*  Subrack number*/
        u8 WAM30_sr; /*  Subrack number*/
        u8 WAM31_sr; /*  Subrack number*/

} SATM_IpUseCif;

/*
 *
 *   SIGNAL NAME:  ATM_IpUseCifAck_Msg
 *
 */
typedef struct SATM_IpUseCifAck
{
        MESSAGEHEADER(header)
        u32     UseCif;         /*  Returned as a copy of corresponding request message field*/
                                        /*  Status always OK.*/

} SATM_IpUseCifAck;


/********************************************************************
 *
 *
 *  SIGNAL NAME:    ATM_NAT_TABLE_MSG
 *
 */
typedef struct SAtmNatTableMsg
{
        MESSAGEHEADER(header)
        u32                      entryCount;
        SAtmNatConfigEntry       natConfigEntry[1];
} SAtmNatTableMsg;



/********************************************************************
 *
 *
 *  SIGNAL NAME:    ATM_NAT_TABLE_RESP_MSG
 *
 */
typedef struct SAtmNatTableRespMsg
{
        MESSAGEHEADER(header)
        EAtmCause                cause;

} SAtmNatTableRespMsg;


/********************************************************************
 *
 *
 *  SIGNAL NAME:    ATM_CONF_DUMP_MSG
 *
 */
struct SATM_AtmConfDumpCmd
{
        MESSAGEHEADER(header)
    u32 spare;
};


/********************************************************************
 *
 *
 *  SIGNAL NAME:    ATM_CONF_DUMP_ACK_MSG
 *
 */
struct SATM_AtmConfDumpAck
{
        MESSAGEHEADER(header)
        EControlUnitType    typeOfConfiguration;
        TNumberOfPresence   noOfConnections;
        /*  -- start of dynamic part (different for Nora and Flex) --*/
        SConnRec            connection[1];/* Nora: Dump of ATM configuration (SConnRec[]).*/
                                          /* Flex: FlexiBTS connection configuration information.*/
};

/********************************************************************
 *
 *
 *   SIGNAL NAME:  ATM_AtmOamCpuStateChange_Msg
 *
 */
typedef struct SAtmOamCpuStateChangeMsg
{
     MESSAGEHEADER(header)
     SMessageAddress    cpuAddress;
     EUnitState                 newState;
}SAtmOamCpuStateChangeMsg;



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OAM_ATM_H */

/**
*******************************************************************************
* Description : Message definitions for BTSOM - TUP IF
*
* Reference   : ATM CTRL MCUS IF SPEC, 15.0, PI,
*               BTSOM CPLANE IFS, version 2.0, ShareNet-IMS
*
* Parameters  :
*       typeOne         <explanation>
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUP / Kari Vakeva
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


