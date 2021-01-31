/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Definitions/SWspUnit.h $
* @version               $LastChangedRevision: 2057 $
* @date                  $LastChangedDate: 2014-07-07 19:42:04 +0800 (Mon, 07 Jul 2014) $
* @author                $Author: jburzyns $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_WSP_UNIT_H
#define _S_WSP_UNIT_H


#include <EWspType.h>
#include <EAvailability.h>
#include <TLocalCellGroupId.h>
#include <DOpenIUBCommonDefs.h>
#include <TChipId.h>
#include <TMsgHeaderTypes.h>
#include <glo_def.h>

struct SWspUnit
{
    TBoard              logUnitAddr;
    TChipId             chipId;
    u8                  pad1;
    u8                  pad2;
    EWspType            typeOfWsp;
    EAvailability       isUnitAvailable;
    TLocalCellGroupId   localCellGroupId;
};
typedef struct SWspUnit SWspUnit;

#endif /* _S_WSP_UNIT_H */


/**
*******************************************************************************
* @struct SWspUnit
*
* Description :
*
* Reference   : WCDMA BTS SW BTSOM - TCOM IFS, v16.0, PI
*
* Parameters  :
* @param logUnitAddr : logical unit address
* @param chipId : DSP chip address
* @param pad1 :
* @param pad2 :
* @param typeOfWsp : type of unit: WSPA, WSPC or Faraday
* @param isUnitAvailable : status of unit (available / not available)
* @param localCellGroupId : fixed pooling for specified LCG type: 1, 2, 3 or 4 / flexible pooling for all candidates type: INVALID_VALUE
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom Toam SW 2.0/ Aldina Codesso
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

