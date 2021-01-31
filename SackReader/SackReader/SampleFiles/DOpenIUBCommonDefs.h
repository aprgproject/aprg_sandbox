/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Definitions/DOpenIUBCommonDefs.h $
* @version               $LastChangedRevision: 2708 $
* @date                  $LastChangedDate: 2017-07-25 17:23:56 +0800 (Tue, 25 Jul 2017) $
* @author                $Author: malba $
*
* Original author        Wang Xiaojiang
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _D_OPEN_IUB_COMMON_DEFS_H
#define _D_OPEN_IUB_COMMON_DEFS_H

/* 3GPP TS 25.433 (Chap 9.3.6) Constant Definitions */

#define MAX_NR_OF_CODES 2                /* 3GPP 10 Nokia 2*/
#define MAX_NR_OF_DLTSS 1                /* Not supported (TDD) 15 */
#define MAX_NR_OF_DLTSLCRS 1             /* Not supported (TDD) 6 */
#define MAX_NR_OF_ERRORS 1               /* 3GPP 256*/
#define MAX_TF_COUNT 12                  /*= MaxNrOfTFs*/ /* 3GPP */
#define MAX_NR_OF_TFCS 324               /* Nokia supported value */
#define MAX_NR_OF_RLS 3                  /* Nokia supported value 3/6, 3GPP 16 */
#define MAX_NR_OF_RLS_1 2                /* Nokia supported value 2, 3GPP 15 */
#define MAX_NR_OF_RLS_2 1                /* Nokia supported value 1, 3GPP 14 */
#define MAX_NR_OF_RLSETS 3               /* Nokia supported value 3, 3GPP 16 */
#define MAX_NR_OF_DPCHS 240              /* 3GPP (Not used) */
#define MAX_NR_OF_DPCHLCRS 1             /* Not supported (TDD) 240 */
#define MAX_NR_OF_SCCPCHS 3              /* Nokia supported value 3, 3GPP 8 */
#define MAX_NR_OF_CPCHS 1                /* Not supported (CPCH) 16 */
#define MAX_NR_OF_PCPCHS 1               /* Not supported (CPCH) 64 */
#define MAX_NR_OF_DCHS 8                 /* 3GPP  128 Nokia 8 */
#define MAX_NR_OF_DSCHS 32               /* 3GPP */
#define MAX_NR_OF_FACHS 4                /* Nokia supported value 4, 3GPP 8 */
#define MAX_NR_OF_CCTRCHS 16             /* 3GPP */
#define MAX_NR_OF_PDSCHS 256             /* 3GPP (Not used) */
#define MAX_NR_OF_PUSCHS 1               /* Not supported (TDD) 256 */
#define MAX_NR_OF_PDSCHSETS 256          /* 3GPP (Not Used)*/
#define MAX_NR_OF_PRACHLCRS 1            /* Not supported (TDD) 8 */
#define MAX_NR_OF_PUSCHSETS 1            /* Not supported (TDD) 256 */
#define MAX_NR_OF_SCCPCHLCRS 1           /* Not supported (TDD) 8 */
#define MAX_NR_OF_ULTSS 1                /* Not supported (TDD) 15 */
#define MAX_NR_OF_ULTSLCRS 1             /* Not supported (TDD) 6 */
#define MAX_NR_OF_USCHS 1                /* Not supported (TDD) 32 */
#define MAX_AP_SIG_NUM 1                 /* Not supported 16 */
#define MAX_NR_OF_SLOT_FORMATS_PRACH 8   /* 3GPP */
#define MAX_CCP_IN_NODEB 6               /* Nokia supported value 6, 3GPP 256 */
#define MAX_CPCH_CELL 1                  /*MAX_NR_OF_CPCHS*/ /* Not supported (CPCH) 4 */
#define MAX_CTFC 16777215                /* Nokia supported value 65535, Calculated CTFC -1 according to TS 25.331, 3GPP 16777215 */
#define MAX_NR_OF_LEN 1                  /* Not supported 7 */
#define MAX_FPACH_CELL 1                 /* Not supported (FPACH) 8 */
#define MAX_RACH_CELL 4                  /*MAX_PRACH_CELL*/ /* Nokia supported value 4, 3GPP 16 */
#define MAX_PRACH_CELL 4                 /* Nokia supported value 4, 3GPP 16 */
#define MAX_PCPCH_CELL 1                 /* Not supported (CPCH) 64 */
#define MAX_SCCPCH_CELL 3                /* Nokia supported value 3, 3GPP 32 */
#define MAX_SCPICH_CELL 1                /* Not supported (S-CPICH)  32 */
#define MAX_TTI_COUNT 1                  /* 3GPP (Used in TDD) 4 */
#define MAX_IBSEG 16                     /* 3GPP */
#define MAX_IB 64                        /* 3GPP */
#define MAX_RATE_MATCHING 256            /* 3GPP */
#define MAX_CODE_NR_COMP_1 256           /* 3GPP (Not Used) */
#define MAX_NR_OF_CELL_SYNC_BURSTS 10    /* 3GPP (Not Used) */
#define MAX_NR_OF_CODE_GROUPS 256        /* 3GPP */
#define MAX_NR_OF_RECEPTS_PER_SYNC_FRAME 16     /* 3GPP */
#define MAX_NR_OF_MEAS_NCELL 96          /* 3GPP */
#define MAX_NR_OF_MEAS_NCELL_1 95        /*MAX_NR_OF_MEAS_NCELL - 1*/ /* 3GPP */
#define MAX_NR_OF_TFCI_GROUPS 256          /* 3GPP 256*/
#define MAX_NR_OF_TFCI1_COMBS 512          /* 3GPP 512*/
#define MAX_NR_OF_TFCI2_COMBS 1024          /* 3GPP 1024*/
#define MAX_NR_OF_TFCI2_COMBS_1 1023     /* 3GPP (Not Used)*/
#define MAX_NR_OF_SF 8                   /* 3GPP */
#define MAX_TGPS 4                       /* 3GPP */
#define MAX_COMMUNICATION_CONTEXT 5      /* Nokia supported value 1200 (?), 3GPP 1048575 (!), 5 after PR 29134ES09P */
#define MAX_NR_OF_LEVELS 1               /* 3GPP 256 */
#define MAX_NO_SAT 16                    /* 3GPP */
#define MAX_NO_GPS_ITEMS 8               /* 3GPP */
#define MAX_NR_OF_NIS 256                /* 3GPP */

#define MIN_CELL_ID 0            /* 3GPP TS 25.433 v5.9.0 (Chap 9.2.1.9)(Open Iub)*/
#define MAX_CELL_ID 65535        /* 3GPP TS 25.433 v5.9.0 (Chap 9.2.1.9)(Open Iub)*/



/* For HSDPA related messages, from 3GPP TS 25.433.
*  Some values restricted to smaller by NSN implementation.
*/
#define MAX_NR_OF_PRIORITY_QUEUES           (5)
#define MAX_NR_OF_PRIORITY_QUEUES_VER2      (6)
#define MAX_NR_OF_HARQ_PROCESSES            (8)
#define MAX_HS_PDSCH_CODE_NR_COMP           (15)
#define MAX_NR_OF_HSSCCHS                   (3)
#define MAX_NR_OF_HSSCCHS_VER2              (4)
#define MAX_HS_SCCH_CODE_NR_COMP            (127)
#define MAX_NR_OF_MACD_PDU_INDEXES          (8)
#define MAX_NUM_NO_HSSCCH_CODES             (3)
#define MAX_SEQUENCE_LENGTH                 (14)   /* Test Model N9 sequence length */
#define MAX_NR_OF_HSSCCH_CODES              (4)    /* Maximum number of HS-SCCH Codes */
#define MAX_NR_OF_COMMON_MAC_FLOWS          (8)    /* Maximum number of Common MAC Flows */
#define MAX_NR_OF_COMMON_MAC_QUEUES         (8)    /* Maximum number of Priority Queues for Common MAC Flow */


/* For HSUPA related messages, from 3GPP TS 25.433.
*  Some values restricted to smaller by NSN implementation.
*/
#define MAX_NR_OF_EAGCHS                    (1)
#define MAX_NR_OF_EAGCHS_VER2               (2)
#define MAX_NR_OF_ERGCHEHICHS               (1)
#define MAX_NR_OF_ERGCHEHICHS_VER2          (7)
#define MAX_EAGCH_CODE_NR_COMP              (255)
#define MAX_ERGCHEHICH_CODE_NR_COMP         (127)
#define MAX_NR_OF_REF_ETFCIS                (8)
#define MAX_NR_OF_EDCH_MACD_FLOWS           (4)
#define MAX_NR_OF_EDCH_MACD_FLOWS_VER2      (6)
#define MAX_NR_OF_LOGICAL_CHANNELS          (1)
#define MAX_NR_OF_LOGICAL_CHANNELS_VER2     (4)
#define MAX_NR_OF_DDIS                      (1)
#define MAX_NR_OF_DDIS_VER2                 (6)
#define MAX_NR_OF_MACD_FLOWS                (5)
#define MAX_NR_OF_MACD_FLOWS_VER2           (6)
#define MAX_NR_OF_HS_DSCH_TBS_HS_SCCH_LESS  (4)
#define MAX_NR_OF_COMMON_EDCHS              (32)   /* Maximum number of Common E-DCH Resource Combination for a cell RAN2518 */
#define MAX_NR_OF_ERNTI_TO_RELEASE          (256)  /* Maximum number of E-RNTI to release per cell */
#define MAX_NR_OF_DEDICATED_CHANNEL_DEVICES (35)   /* Maximum number of dedicated channel devices */
#define MAX_NR_OF_EDCH                      (2)   /* Maximum number of uplink frequencies for E-DCH for one UE */
#define MAX_NR_OF_EDCH_RLS                  (4)    /* Maximum number of E-DCH RLs for one UE */
#define MAX_NR_OF_ERNTI                     (256)  /* Maximum number of ERNTIs that can be allocated by the CRNC */


/* AUDITREPLY COST VALUES */
#define CC_SF4_DLCOST    128
#define CC_SF4_ULCOST    96
#define CC_SF8_DLCOST    96
#define CC_SF8_ULCOST    32
#define CC_SF16_DLCOST   32
#define CC_SF16_ULCOST   32
#define CC_SF32_DLCOST   32
#define CC_SF32_ULCOST   16
#define CC_SF64_DLCOST   16
#define CC_SF64_ULCOST   8
#define CC_SF128_DLCOST  8
#define CC_SF128_ULCOST  2
#define CC_SF256_DLCOST  2
#define CC_SF256_ULCOST  1
#define CC_SF512_DLCOST  1
#define CC_SF512_ULCOST  0
#define CC_SF4_DLCOST_80CE_FSPA    208
#define CC_SF4_ULCOST_80CE_FSPA    156
#define CC_SF8_DLCOST_80CE_FSPA    156
#define CC_SF8_ULCOST_80CE_FSPA    52
#define CC_SF16_DLCOST_80CE_FSPA   52
#define CC_SF16_ULCOST_80CE_FSPA   52
#define CC_SF32_DLCOST_80CE_FSPA   52
#define CC_SF32_ULCOST_80CE_FSPA   26
#define CC_SF64_DLCOST_80CE_FSPA   26
#define CC_SF64_ULCOST_80CE_FSPA   13
#define CC_SF128_DLCOST_80CE_FSPA  13
#define CC_SF128_ULCOST_80CE_FSPA  4
#define CC_SF256_DLCOST_80CE_FSPA  4
#define CC_SF256_ULCOST_80CE_FSPA  2
#define CC_SF512_DLCOST_80CE_FSPA  2
#define CC_SF512_ULCOST_80CE_FSPA  0

#define DC_SF4_DLCOST    0
#define DC_SF4_DLCOST2   128
#define DC_SF4_ULCOST    0
#define DC_SF4_ULCOST2   96
#define DC_SF8_DLCOST    0
#define DC_SF8_DLCOST2   96
#define DC_SF8_ULCOST    0
#define DC_SF8_ULCOST2   32
#define DC_SF16_DLCOST   0
#define DC_SF16_DLCOST2  32
#define DC_SF16_ULCOST   0
#define DC_SF16_ULCOST2  32
#define DC_SF32_DLCOST   0
#define DC_SF32_DLCOST2  0
#define DC_SF32_ULCOST   0
#define DC_SF32_ULCOST2  16
#define DC_SF64_DLCOST   0
#define DC_SF64_DLCOST2  16
#define DC_SF64_ULCOST   0
#define DC_SF64_ULCOST2  8
#define DC_SF128_DLCOST  0
#define DC_SF128_DLCOST2 8
#define DC_SF128_ULCOST  0
#define DC_SF128_ULCOST2 8
#define DC_SF256_DLCOST  0
#define DC_SF256_DLCOST2 8
#define DC_SF256_ULCOST  0
#define DC_SF256_ULCOST2 8
#define DC_SF512_DLCOST  0
#define DC_SF512_DLCOST2 8
#define DC_SF512_ULCOST  0
#define DC_SF512_ULCOST2 0

#define EDCH_2SF2andSF4_ULCOST2  0
#define EDCH_2SF2_ULCOST2        0
#define EDCH_2SF4_ULCOST2        85
#define EDCH_SF4_ULCOST2         43
#define EDCH_SF8_ULCOST2         43
#define EDCH_SF16_ULCOST2        43
#define EDCH_SF32_ULCOST2        43
#define EDCH_SF64_ULCOST2        43
#define EDCH_2SF2andSF4_ULCOST2_FSPA  0
#define EDCH_2SF2_ULCOST2_FSPA        0
#define EDCH_2SF4_ULCOST2_FSPA        107
#define EDCH_SF4_ULCOST2_FSPA         53
#define EDCH_SF8_ULCOST2_FSPA         53
#define EDCH_SF16_ULCOST2_FSPA        53
#define EDCH_SF32_ULCOST2_FSPA        53
#define EDCH_SF64_ULCOST2_FSPA        53

/* OWN DEFINITIONS */
#define IB_SG_DATA_BYTE_LEN 29 /* 3GPP TS 25.331 v4.2.0:
                                * SIB data fixed:    Bit String (222)
                                * SIB data variable: Bit String (1..214) */
#define MAX_CELL_IN_BB_CARD 4  /* WSPA = 4, WSPC = 3 */
#define MAX_CELL_IN_WAM 6
#define MAX_RACH_HANDLERS 9
#define MAX_LOCAL_CELL_GROUP_IN_NODEB 4
#define MAX_LOCAL_CELL_IN_LOCAL_CELL_GROUP 12
#define MAX_NR_OF_LOCAL_CELLS_IN_TM6 3
#define MAX_BB_CARDS_PER_WAM 7
#define MAX_NUM_OF_TEST_RL 64
#define MAX_NUM_OF_HSDPA_CELLS_PER_MAC_HS 6
#define MAX_NR_OF_RACH_WSP_ADDRESSES 9
#define MAX_NUM_OF_CODECS_FOR_ONE_CELL 8
#define MAX_NUM_OF_NBCC_IN_WAM 240
#define MAX_NUM_OF_NBCC_IN_BB_CARD 80
#define MAX_PRIORITY_QUEUES 1
#define MAX_FRAME_HANDLING_PRIORITYLST       16   /*For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0*/
#define MAX_LOAD_DCHLIST                     8    /*For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0*/
#define NUM_OF_SPREADING_FACTOR_INDEX        7    /*For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0*/
#define MAX_SET_OF_EDPDCH_INDEX              10   /*For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0*/
#define MAX_NO_OF_EDCH_SCHEDULING_PRIORITIES 16
#define MAX_NUM_OF_DSPS_PER_CONFIG           7
#define MAX_USERS_IN_NODEB                   2500
#define MAX_NUM_OF_RAKE_IN_RTT               3
#define MAX_NUM_OF_MEASUREMENT_VALUE_INFO    16
#define MAX_NUM_OF_UPH_MEASUREMENT_REPORT    78
#define MAX_NR_OF_COMMON_CHANNELS            10   /* Maximum number of common channels */
#define MAX_NR_OF_HS_ENCODERS                6    /* Maximum number of HS-Encoders */
#define MAX_NR_OF_USERS                      800  /* Maximum number of users */
#define MAX_NR_OF_DUMMY_USERS                80   /* Maximum number of dummy users RAN 2518 */
#define MAX_NUM_OF_PIC_CELLS                 6    /* Maximum number of PIC cells */
#define MAX_NR_OF_SM                         3    /* Maximum number of system modules in one BTS */
#define MAX_NR_OF_OPERATOR                   6    /* Maximum number of Operator */
#define MAX_NR_OF_COMMON_EDCH_DCD            2    /* Maximum number of DCD for Common EDCH */
#define MAX_NR_OF_CF_PER_DCD_FSMR3           8    /* Maximum number of CF per DCD for FSMR3 */
#define MAX_NR_OF_CF_PER_DCD_FSMR2           4    /* Maximum number of CF per DCD for FSMR2 */

/* Defines for O&M - Tcom if Ref BTSOM - TCOM Interface Specification v. 19.0 */
/* Max number of control units per BTS */
#define MAX_NUM_OF_CONTROL_UNITS 12

/* Max number of DSP resources per BTS */
#define MAX_NUM_OF_DSP_RESOURCES 42

/* Max number of DSP resources per control unit (WAM/FCM/FSPB) */
#define MAX_DSP_RESOURCES_PER_CONTROL_UNIT 7

/* Max number of Hspa scheduler info structs */
#define MAX_NUM_OF_HSPA_SCHEDULER_INFO 48

/* Maximum number of Secondary Serving HS-DSCH cells for one UE */
#define MAX_NR_OF_HSDSCH 3

/* Maximum number of Possible Secondary Serving HS-DSCH cells of a Primary Serving HS-DSCH cell */
/* Note: This constant is used only in NBAP Audit Response and RSI message. */
/* Nokia-supported value (from RAN3067 onwards) = 23, 3GPP TS 25.433 = 33 */
#define MAX_NR_OF_POSS_SEC_SERV_HSDSCH 23

/* Max number of associated WPAs to TRX and associated TRXes to WPAs (57833ESPE04) */
#define MAX_NUM_OF_WPAS_ASSOCIATED_TO_TRX 2
#define MAX_NUM_OF_TRXES_ASSOCIATED_TO_WPA 2

/* PIC Pool information RAN1308 HSUPA Parallel Interference Cancellation and CN4155 CR1713 PIC configuration changes */
#define MAX_NUM_OF_PIC_POOLS 4
#define MAX_NUM_OF_PIC_POOL_LCR_INFO 6

/* Max number of RX and TX antennas per local cell*/
/* Only used by uRec and LTE */
#define LN_MAX_NUM_OF_TX_ANTENNAS_PER_LOCAL_CELL 16
#define LN_MAX_NUM_OF_RX_ANTENNAS_PER_LOCAL_CELL 16


/* Max number of HSDPA QOS SPI class (77437ESPE04, RAN2390) */
#define MAX_NUM_OF_HSDPA_QOS_SPI_CLASS 16

/* Max number of Common H-RNTI per cell, defined in 3GPP TS 25.331*/
#define MAX_NR_OF_COMMON_HRNTI 4

#define ALL_NBCC 1048575

#define MAX_NUM_OF_DELAYED_LINKS_INFO 2

#endif /* _D_OPEN_IUB_COMMON_DEFS_H */

/**
*******************************************************************************
* Description         : 3GPP TS 25.433(Chap 9.3.6) Constant Definitions
*
* Reference           : 3GPP TS 25.433
*                       DSP SW MCU SW Interface Specification, Sharenet
*                       O&M - Tcom if Ref BTSOM - TCOM Interface Specification, Sharenet
*
* Parameters :
*
* @def MAX_NR_OF_CODES :                  3GPP 10 Nokia 2.
* @def MAX_NR_OF_DLTSS :                  Not supported (TDD) 15.
* @def MAX_NR_OF_DLTSLCRS :               Not supported (TDD) 6.
* @def MAX_NR_OF_ERRORS :                 3GPP 256.
* @def MAX_TF_COUNT :                     Equals MaxNrOfTFs, 3GPP.
* @def MAX_NR_OF_TFCS :                   Nokia supported value.
* @def MAX_NR_OF_RLS :                    Nokia supported value 3/6, 3GPP 16.
* @def MAX_NR_OF_RLS_1 :                  Nokia supported value 2, 3GPP 15.
* @def MAX_NR_OF_RLS_2 :                  Nokia supported value 1, 3GPP 14.
* @def MAX_NR_OF_RLSETS :                 Nokia supported value 3, 3GPP 16.
* @def MAX_NR_OF_DPCHS :                  3GPP (Not used).
* @def MAX_NR_OF_DPCHLCRS :               Not supported (TDD) 240.
* @def MAX_NR_OF_SCCPCHS :                Nokia supported value 3, 3GPP 8.
* @def MAX_NR_OF_CPCHS :                  Not supported (CPCH) 16.
* @def MAX_NR_OF_PCPCHS :                 Not supported (CPCH) 64.
* @def MAX_NR_OF_DCHS :                   3GPP  128 Nokia 8.
* @def MAX_NR_OF_DSCHS :                  3GPP.
* @def MAX_NR_OF_FACHS :                  Nokia supported value 4, 3GPP 8.
* @def MAX_NR_OF_CCTRCHS :                3GPP.
* @def MAX_NR_OF_PDSCHS :                 3GPP (Not used).
* @def MAX_NR_OF_PUSCHS :                 Not supported (TDD) 256.
* @def MAX_NR_OF_PDSCHSETS :              3GPP (Not Used).
* @def MAX_NR_OF_PRACHLCRS :              Not supported (TDD) 8.
* @def MAX_NR_OF_PUSCHSETS :              Not supported (TDD) 256.
* @def MAX_NR_OF_SCCPCHLCRS :             Not supported (TDD) 8.
* @def MAX_NR_OF_ULTSS :                  Not supported (TDD) 15.
* @def MAX_NR_OF_ULTSLCRS :               Not supported (TDD) 6.
* @def MAX_NR_OF_USCHS :                  Not supported (TDD) 32.
* @def MAX_AP_SIG_NUM :                   Not supported 16.
* @def MAX_NR_OF_SLOT_FORMATS_PRACH :     3GPP.
* @def MAX_CCP_IN_NODEB :                 Nokia supported value 6, 3GPP 256.
* @def MAX_CPCH_CELL :                    MAX_NR_OF_CPCHS, Not supported (CPCH) 4.
* @def MAX_CTFC :                         Nokia supported value 65535, Calculated CTFC -1 according to TS 25.331, 3GPP 16777215.
* @def MAX_NR_OF_LEN :                    Not supported 7.
* @def MAX_FPACH_CELL :                   Not supported (FPACH) 8.
* @def MAX_RACH_CELL :                    MAX_PRACH_CELL, Nokia supported value 4, 3GPP 16.
* @def MAX_PRACH_CELL :                   Nokia supported value 4, 3GPP 16.
* @def MAX_PCPCH_CELL :                   Not supported (CPCH) 64.
* @def MAX_SCCPCH_CELL :                  Nokia supported value 3, 3GPP 32.
* @def MAX_SCPICH_CELL :                  Not supported (S-CPICH)  32.
* @def MAX_TTI_COUNT :                    3GPP (Used in TDD) 4.
* @def MAX_IBSEG :                        3GPP.
* @def MAX_IB :                           3GPP.
* @def MAX_RATE_MATCHING :                3GPP.
* @def MAX_CODE_NR_COMP_1 :               3GPP (Not Used).
* @def MAX_NR_OF_CELL_SYNC_BURSTS :       3GPP (Not Used).
* @def MAX_NR_OF_CODE_GROUPS :            3GPP.
* @def MAX_NR_OF_RECEPTS_PER_SYNC_FRAME : 3GPP.
* @def MAX_NR_OF_MEAS_NCELL :             3GPP.
* @def MAX_NR_OF_MEAS_NCELL_1 :           MAX_NR_OF_MEAS_NCELL - 1, 3GPP.
* @def MAX_NR_OF_TFCI_GROUPS :            3GPP 256.
* @def MAX_NR_OF_TFCI1_COMBS :            3GPP 512.
* @def MAX_NR_OF_TFCI2_COMBS :            3GPP 1024.
* @def MAX_NR_OF_TFCI2_COMBS_1 :          3GPP (Not Used).
* @def MAX_NR_OF_SF :                     3GPP.
* @def MAX_TGPS :                         3GPP.
* @def MAX_COMMUNICATION_CONTEXT:         Nokia supported value 1200 (?), 3GPP 1048575 (!), 5 after PR 29134ES09P.
* @def MAX_NR_OF_LEVELS :                 3GPP 256.
* @def MAX_NO_SAT :                       3GPP.
* @def MAX_NO_GPS_ITEMS :                 3GPP.
* @def MAX_NR_OF_NIS :                    3GPP.
* @def MIN_CELL_ID :                      3GPP TS 25.433 v5.9.0 (Chap 9.2.1.9)(Open Iub).
* @def MAX_CELL_ID :                      3GPP TS 25.433 v5.9.0 (Chap 9.2.1.9)(Open Iub).
* @def MAX_NR_OF_PRIORITY_QUEUES :
* @def MAX_NR_OF_PRIORITY_QUEUES_VER2 :
* @def MAX_NR_OF_HARQ_PROCESSES :
* @def MAX_HS_PDSCH_CODE_NR_COMP :
* @def MAX_NR_OF_HSSCCHS :
* @def MAX_NR_OF_HSSCCHS_VER2 :
* @def MAX_HS_SCCH_CODE_NR_COMP :
* @def MAX_NR_OF_MACD_PDU_INDEXES :
* @def MAX_NUM_NO_HSSCCH_CODES :
* @def MAX_SEQUENCE_LENGTH :              Test Model N9 sequence length.
* @def MAX_NR_OF_HSSCCH_CODES :           Maximum number of HS-SCCH Codes.
* @def MAX_NR_OF_COMMON_MAC_FLOWS :       Maximum number of Common MAC Flows.
* @def MAX_NR_OF_COMMON_MAC_QUEUES :      Maximum number of Priority Queues for Common MAC Flow.
* @def MAX_NR_OF_EAGCHS :
* @def MAX_NR_OF_EAGCHS_VER2 :
* @def MAX_NR_OF_ERGCHEHICHS :
* @def MAX_NR_OF_ERGCHEHICHS_VER2 :
* @def MAX_EAGCH_CODE_NR_COMP :
* @def MAX_ERGCHEHICH_CODE_NR_COMP :
* @def MAX_NR_OF_REF_ETFCIS :
* @def MAX_NR_OF_EDCH_MACD_FLOWS :
* @def MAX_NR_OF_EDCH_MACD_FLOWS_VER2 :
* @def MAX_NR_OF_LOGICAL_CHANNELS :
* @def MAX_NR_OF_LOGICAL_CHANNELS_VER2 :
* @def MAX_NR_OF_DDIS :
* @def MAX_NR_OF_DDIS_VER2 :
* @def MAX_NR_OF_MACD_FLOWS :
* @def MAX_NR_OF_MACD_FLOWS_VER2 :
* @def MAX_NR_OF_HS_DSCH_TBS_HS_SCCH_LESS :
* @def MAX_NR_OF_COMMON_EDCHS :              Maximum number of Common E-DCH Resource Combination for a cell RAN2518.
* @def MAX_NR_OF_ERNTI_TO_RELEASE :          Maximum number of E-RNTI to release per cell.
* @def MAX_NR_OF_DEDICATED_CHANNEL_DEVICES : Maximum number of dedicated channel devices.
* @def MAX_NR_OF_EDCH :                      Maximum number of uplink frequencies for E-DCH for one UE.
* @def MAX_NR_OF_EDCH_RLS :                  Maximum number of E-DCH RLs for one UE.
* @def MAX_NR_OF_ERNTI :                     Maximum number of ERNTIs that can be allocated by the CRNC.
* @def CC_SF4_DLCOST :
* @def CC_SF4_ULCOST :
* @def CC_SF8_DLCOST :
* @def CC_SF8_ULCOST :
* @def CC_SF16_DLCOST :
* @def CC_SF16_ULCOST :
* @def CC_SF32_DLCOST :
* @def CC_SF32_ULCOST :
* @def CC_SF64_DLCOST :
* @def CC_SF64_ULCOST :
* @def CC_SF128_DLCOST :
* @def CC_SF128_ULCOST :
* @def CC_SF256_DLCOST :
* @def CC_SF256_ULCOST :
* @def CC_SF512_DLCOST :
* @def CC_SF512_ULCOST :
* @def CC_SF4_DLCOST_80CE_FSPA :
* @def CC_SF4_ULCOST_80CE_FSPA :
* @def CC_SF8_DLCOST_80CE_FSPA :
* @def CC_SF8_ULCOST_80CE_FSPA :
* @def CC_SF16_DLCOST_80CE_FSPA :
* @def CC_SF16_ULCOST_80CE_FSPA :
* @def CC_SF32_DLCOST_80CE_FSPA :
* @def CC_SF32_ULCOST_80CE_FSPA :
* @def CC_SF64_DLCOST_80CE_FSPA :
* @def CC_SF64_ULCOST_80CE_FSPA :
* @def CC_SF128_DLCOST_80CE_FSPA :
* @def CC_SF128_ULCOST_80CE_FSPA :
* @def CC_SF256_DLCOST_80CE_FSPA :
* @def CC_SF256_ULCOST_80CE_FSPA :
* @def CC_SF512_DLCOST_80CE_FSPA :
* @def CC_SF512_ULCOST_80CE_FSPA :
* @def DC_SF4_DLCOST :
* @def DC_SF4_DLCOST2 :
* @def DC_SF4_ULCOST :
* @def DC_SF4_ULCOST2 :
* @def DC_SF8_DLCOST :
* @def DC_SF8_DLCOST2 :
* @def DC_SF8_ULCOST :
* @def DC_SF8_ULCOST2 :
* @def DC_SF16_DLCOST :
* @def DC_SF16_DLCOST2 :
* @def DC_SF16_ULCOST :
* @def DC_SF16_ULCOST2 :
* @def DC_SF32_DLCOST :
* @def DC_SF32_DLCOST2 :
* @def DC_SF32_ULCOST :
* @def DC_SF32_ULCOST2 :
* @def DC_SF64_DLCOST :
* @def DC_SF64_DLCOST2 :
* @def DC_SF64_ULCOST :
* @def DC_SF64_ULCOST2 :
* @def DC_SF128_DLCOST :
* @def DC_SF128_DLCOST2 :
* @def DC_SF128_ULCOST :
* @def DC_SF128_ULCOST2 :
* @def DC_SF256_DLCOST :
* @def DC_SF256_DLCOST2 :
* @def DC_SF256_ULCOST :
* @def DC_SF256_ULCOST2 :
* @def DC_SF512_DLCOST :
* @def DC_SF512_DLCOST2 :
* @def DC_SF512_ULCOST :
* @def DC_SF512_ULCOST2 :
* @def EDCH_2SF2andSF4_ULCOST2 :
* @def EDCH_2SF2_ULCOST2 :
* @def EDCH_2SF4_ULCOST2 :
* @def EDCH_SF4_ULCOST2 :
* @def EDCH_SF8_ULCOST2 :
* @def EDCH_SF16_ULCOST2 :
* @def EDCH_SF32_ULCOST2 :
* @def EDCH_SF64_ULCOST2 :
* @def EDCH_2SF2andSF4_ULCOST2_FSPA :
* @def EDCH_2SF2_ULCOST2_FSPA :
* @def EDCH_2SF4_ULCOST2_FSPA :
* @def EDCH_SF4_ULCOST2_FSPA :
* @def EDCH_SF8_ULCOST2_FSPA :
* @def EDCH_SF16_ULCOST2_FSPA :
* @def EDCH_SF32_ULCOST2_FSPA :
* @def EDCH_SF64_ULCOST2_FSPA :
* @def IB_SG_DATA_BYTE_LEN :                 3GPP TS 25.331 v4.2.0:
*                                            SIB data fixed:    Bit String (222)
*                                            SIB data variable: Bit String (1..214).
* @def MAX_CELL_IN_BB_CARD :                 WSPA = 4, WSPC = 3.
* @def MAX_CELL_IN_WAM :
* @def MAX_RACH_HANDLERS :
* @def MAX_LOCAL_CELL_GROUP_IN_NODEB :
* @def MAX_LOCAL_CELL_IN_LOCAL_CELL_GROUP :
* @def MAX_NR_OF_LOCAL_CELLS_IN_TM6 :
* @def MAX_BB_CARDS_PER_WAM :
* @def MAX_NUM_OF_TEST_RL :
* @def MAX_NUM_OF_HSDPA_CELLS_PER_MAC_HS :
* @def MAX_NR_OF_RACH_WSP_ADDRESSES :
* @def MAX_NUM_OF_CODECS_FOR_ONE_CELL :
* @def MAX_NUM_OF_NBCC_IN_WAM :
* @def MAX_NUM_OF_NBCC_IN_BB_CARD :
* @def MAX_PRIORITY_QUEUES :
* @def MAX_FRAME_HANDLING_PRIORITYLST :      For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0.
* @def MAX_LOAD_DCHLIST :                    For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0.
* @def NUM_OF_SPREADING_FACTOR_INDEX :       For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0.
* @def MAX_SET_OF_EDPDCH_INDEX :             For HSUPA, Ref:Annex Z Rel6 1.0.0 for 3GPP TS 25.433 v6.9.0.
* @def MAX_NO_OF_EDCH_SCHEDULING_PRIORITIES :
* @def MAX_NUM_OF_DSPS_PER_CONFIG :
* @def MAX_USERS_IN_NODEB :
* @def MAX_NUM_OF_RAKE_IN_RTT :
* @def MAX_NUM_OF_MEASUREMENT_VALUE_INFO :
* @def MAX_NUM_OF_UPH_MEASUREMENT_REPORT :   Maximum number of UPH measurement reports.
* @def MAX_NR_OF_COMMON_CHANNELS :           Maximum number of common channels.
* @def MAX_NR_OF_HS_ENCODERS :               Maximum number of HS-Encoders.
* @def MAX_NR_OF_USERS :                     Maximum number of users.
* @def MAX_NR_OF_DUMMY_USERS :               Maximum number of dummy users RAN 2518.
* @def MAX_NUM_OF_PIC_CELLS :                Maximum number of PIC cells.
* @def MAX_NR_OF_SM :                        Maximum number of system modules in one BTS.
* @def MAX_NR_OF_OPERATOR :                  Maximum number of Operator.
* @def MAX_NR_OF_COMMON_EDCH_DCD :           Maximum number of DCD for Common EDCH.
* @def MAX_NR_OF_CF_PER_DCD_FSMR3 :          Maximum number of CF per DCD for FSMR3.
* @def MAX_NR_OF_CF_PER_DCD_FSMR2 :          Maximum number of CF per DCD for FSMR2.
* @def MAX_NUM_OF_CONTROL_UNITS :            Max number of control units per BTS.
* @def MAX_NUM_OF_DSP_RESOURCES :            Max number of DSP resources per BTS.
* @def MAX_DSP_RESOURCES_PER_CONTROL_UNIT :  Max number of DSP resources per control unit (WAM/FCM/FSPB).
* @def MAX_NUM_OF_HSPA_SCHEDULER_INFO :      Max number of Hspa scheduler info structs.
* @def MAX_NR_OF_HSDSCH :                    Maximum number of Secondary Serving HS-DSCH cells for one UE.
* @def MAX_NR_OF_POSS_SEC_SERV_HSDSCH :      Maximum number of Possible Secondary Serving HS-DSCH cells of a Primary Serving HS-DSCH cell.
*                                            Note: This constant is used only in NBAP Audit Response and RSI message.
*                                            Nokia-supported value (from RAN3067 onwards) = 23, 3GPP TS 25.433 = 33.
* @def MAX_NUM_OF_WPAS_ASSOCIATED_TO_TRX :   Max number of associated WPAs to TRX and associated TRXes to WPAs (57833ESPE04).
* @def MAX_NUM_OF_TRXES_ASSOCIATED_TO_WPA :
* @def MAX_NUM_OF_PIC_POOLS :                PIC Pool information RAN1308 HSUPA Parallel Interference Cancellation and CN4155 CR1713 PIC configuration changes.
* @def MAX_NUM_OF_PIC_POOL_LCR_INFO :        PIC Pool information RAN1308 HSUPA Parallel Interference Cancellation and CN4155 CR1713 PIC configuration changes.
* @def LN_MAX_NUM_OF_TX_ANTENNAS_PER_LOCAL_CELL : Max number of RX and TX antennas per local cell, Only used by uRec and LTE.
* @def LN_MAX_NUM_OF_RX_ANTENNAS_PER_LOCAL_CELL : Max number of RX and TX antennas per local cell, Only used by uRec and LTE.
* @def MAX_NUM_OF_HSDPA_QOS_SPI_CLASS :           Max number of HSDPA QOS SPI class (77437ESPE04, RAN2390).
* @def MAX_NR_OF_COMMON_HRNTI :              Max number of Common H-RNTI per cell, defined in 3GPP TS 25.331.
* @def ALL_NBCC :                            Reference: 3GPP TS 25.433 v11.8.0 (2014-06), (2^20)-1 => 1048575.
* @def MAX_NUM_OF_DELAYED_LINKS_INFO:        Max number of Delayed Links Information
* Additional Information :
*
* Definition Provided by : TCOM, DSP,BTSOM
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

