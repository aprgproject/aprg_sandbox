/**
*******************************************************************************
* @file                  $HeadURL:
*https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1806_001_00/I_Interface/Application_Env/Definitions/URxAntennaBusParameters.h
*$
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Sinikka Mikkola
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _U_RX_ANTENNA_BUS_PARAMETERS_H
#define _U_RX_ANTENNA_BUS_PARAMETERS_H

#include <SAntennaBusParametersForRfBus.h>
#include <SAntennaPhysicalAddress.h>

union URxAntennaBusParameters {
    SAntennaBusParametersForRfBus paramsForRfBus;
    SAntennaPhysicalAddress paramsForRp3;
};
typedef union URxAntennaBusParameters URxAntennaBusParameters;

#endif /* _U_RX_ANTENNA_BUS_PARAMETERS_H */

/**
*******************************************************************************
* @union URxAntennaBusParameters
*
* Description         : Union definition for RX antenna bus parameters
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location : PI
*
* @param paramsForRfBus          :Index of R-bus and R-bus Antennas mapped to
*                                 the current LCR id.
* @param paramsForRp3            :RP3 RX Antenna address information mapped to
*                                 current LCR ID.
*
* Additional Information :
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
