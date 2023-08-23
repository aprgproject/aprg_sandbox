/**
*******************************************************************************
* @file                  $HeadURL:
*https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1803_001_00/I_Interface/Application_Env/Definitions/EHspaMapping.h
*$
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EHSPA_MAPPING_H
#define _EHSPA_MAPPING_H

typedef enum EHspaMapping {
    EHspaMapping_EmptyValue = 0,
    EHspaMapping_Fsm1 = 1,
    EHspaMapping_Fsm2 = 2,
    EHspaMapping_Subrack1 = 3,
    EHspaMapping_SubrackUltra = 4
} EHspaMapping;

#endif /* _EHSPA_MAPPING_H */

/**
*******************************************************************************
* @enum EHspaMapping
*
* Description         : Enum definitions for mapping HSPA local cells to baseband HW resources
*
* Reference           : BTSOM - TCOM Interface Specification, v 18.0, PI
*
* Parameters :
*
* @param EHspaMapping_EmptyValue   : mapping not used
* @param EHspaMapping_Fsm1         : in case of Flexi
* @param EHspaMapping_Fsm2         : in case of Flexi
* @param EHspaMapping_Subrack1     : in case of EUBB
* @param EHspaMapping_SubrackUltra : in case of UltraSite
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TCOM / Paula Viljamaa
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
