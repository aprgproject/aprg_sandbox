/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1806_001_00/I_Interface/Application_Env/Definitions/UIpMacAddress.h $
* @version               $LastChangedRevision: 2150 $
* @date                  $LastChangedDate: 2014-09-15 21:09:01 +0800 (Mon, 15 Sep 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        grzela
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _U_IP_MAC_ADDRESS_H
#define _U_IP_MAC_ADDRESS_H

#include <SIpMacAddressV4.h>
#include <SIpMacAddressV6.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef union UIpMacAddress
{
    SIpMacAddressV4 ipMacv4;
    SIpMacAddressV6 ipMacv6;
} UIpMacAddress;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_IP_MAC_ADDRESS_H */


/**
********************************************************************************
* @union UIpMacAddress
*
* Description : <TODO>
*
* Reference   : <TODO>
*
* @param ipMacv4 : <TODO>
* @param ipMacv6 : <TODO>
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : LTE OAM
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/
