/**
*******************************************************************************
* @file                  $HeadURL:
*https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1806_001_00/I_Interface/Application_Env/Definitions/UConfigInfoElement.h
*$
* @version               $LastChangedRevision: 2055 $
* @date                  $LastChangedDate: 2014-07-07 18:59:59 +0800 (Mon, 07 Jul 2014) $
* @author                $Author: jburzyns $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _UCONFIGINFOELEMENT_H
#define _UCONFIGINFOELEMENT_H

#include <SRxTxResource.h>
#include <SWamUnit.h>
#include <SWspUnit.h>

typedef union {
    SWamUnit wamUnit;
    SWspUnit wspUnit;
    SRxTxResource rxTxResource;
} UConfigInfoElement;

#endif /* _UCONFIGINFOELEMENT_H */

/**
*******************************************************************************
* @union UConfigInfoElement
*
* Description :  Union definition for configuration info element
*
* Reference   :  WCDMA BTS SW BTSOM-TCOM IFS, version 8.0. PI
*
* Parameters  :
*
* @param wamUnit              : WAM info
*
* @param wspUnit              : WSP info
*
* @param rxTxResource         : Rx or Tx resource info
*
* Definition Provided by : Codesso / Metsanurm
*
* Additional Information : <type additional information if needed>
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
