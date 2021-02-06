/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Definitions/EControlUnitType.h $
* @version               $LastChangedRevision: 2581 $
* @date                  $LastChangedDate: 2016-05-11 18:45:31 +0800 (Wed, 11 May 2016) $
* @author                $Author: joseplop $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ECONTROLUNITTYPE_H
#define _ECONTROLUNITTYPE_H

typedef enum EControlUnitType
{
    EControlUnitType_Wam             = 0,
    EControlUnitType_Fcm             = 1,
    EControlUnitType_Fcm2            = 2,
    EControlUnitType_Fspc            = 3,
    EControlUnitType_Wsmf            = 4,
    EControlUnitType_Wspf            = 5,
    EControlUnitType_Fct             = 6,
    EControlUnitType_FspRel3         = 7,
    EControlUnitType_Fzp             = 8,
    EControlUnitType_Kepler2ArmCore  = 9
} EControlUnitType;

#endif /* _ECONTROLUNITTYPE_H */

/**
*******************************************************************************
* @enum EControlUnitType
*
* Description :  Enum definitions for unit type of WAM info
*
* Reference   :  BTSOM - TCOM Interface Specification, v 18.0, PI
*
* Parameters :
*
* @param Wam     : if Nora platform is used
* @param Fcm     : FCM type if Flexi rel 1 platform is used
* @param Fcm2    : FCM type if Flexi HCSM (rel 2 HW) is used
* @param Fspc    : if Flexi HCSM FSPC is control unit
* @param Wsmf    : if EUBB WSMF is control unit
* @param Wspf    : if EUBB WSPF is control unit
* @param Fct     : if Flexi Rel3 is used
* @param FspRel3 : if Flexi Rel3 FSP control unit is in use
* @param Fzp : if Flexi Zone Pico control unit is in use
* @param Kepler2ArmCore : if Flexi Rel4 is used
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Bartosz Ciesla
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

