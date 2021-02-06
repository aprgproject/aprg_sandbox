/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Definitions/SWamUnit.h $
* @version               $LastChangedRevision: 2432 $
* @date                  $LastChangedDate: 2015-06-30 17:25:09 +0800 (Tue, 30 Jun 2015) $
* @author                $Author: zborkows $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_WAM_UNIT_H
#define _S_WAM_UNIT_H

#include <TMsgHeaderTypes.h>
#include <EAvailability.h>
#include <TSubrackNbr.h>
#include <glo_def.h>
#include <TTrafficTpIdentification.h>
#include <SAal2Tp.h>
#include <Glo_bs.h>
#include <EControlUnitType.h>
#include <SMessageAddress.h>
#include <EMcuSwDeployment.h>

struct SWamUnit
{
    TBoard                    logUnitAddr;
    TCpu                      cpuAddr;
    u8                        pad1;
    u8                        numOfFspUnits;
    EControlUnitType          unitType;
    EAvailability             isUnitAvailable;
    EMcuSwDeployment          swDeployment;
};
typedef struct SWamUnit SWamUnit;

#endif /* _S_WAM_UNIT_H */

/**
*******************************************************************************
* @struct SWamUnit
*
* @param logUnitAddr                : logical unit address (e.g. WAM10)
*
* @param cpuAddr                    : cpu address (e.g.CTRL_MCU)
*
* @param pad1                       : padding
*
* @param numOfFspUnits              : Number of FSP units in System Module.
*                                     Valid only for EControlUnitType_Fcm2 from Extension System Module
*                                     in TC_HW_CONFIGURATION_CHANGE_MSG.
* @param unitType                   : unit type (WAM/FCM/FSPB/WSMF/WSPF)
*
* @param isUnitAvailable            : status of whole unit (available/baseband disabled/not available)
*
* @param swDeployment               : defines if TCOM SW is deployed on given MCU
*
* Description : Structure definition for WAM info
*
* Additional Information :
*
* Reference : BTSOM - TCOM Interface Specification (BTSOM CPLANE IFS), v 4.0, ShareNet-IMS
*
* Definition Provided by : Margus Metsanurm, Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/
