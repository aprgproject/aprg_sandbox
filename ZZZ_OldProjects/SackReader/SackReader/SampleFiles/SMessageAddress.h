/**
*******************************************************************************
* @file                  $HeadURL:
*https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_13_54/I_Interface/Global_Env/Definitions/SMessageAddress.h
*$
* @version               $LastChangedRevision: 4238 $
* @date                  $LastChangedDate: 2016-10-11 22:13:29 +0800 (Tue, 11 Oct 2016) $
* @author                $Author: demx1779 $
*
* Original author        Tomi Kahila
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SMESSAGEADDRESS_H
#define _SMESSAGEADDRESS_H

#include <TMsgHeaderTypes.h>

/* For Texas compiler environment - ref glo_def.h
 * SMESSAGEADDRESS_LITTLE_ENDIAN should be defined on little-endian targets
 * that does not use TTC
 * CNI-4982: Also ARM and x86 processors should use little endian version of struct - so add CCS_LITTLE_ENDIAN.
 */
#if defined(__TCC__) || defined(SMESSAGEADDRESS_LITTLE_ENDIAN) || defined(CCS_LITTLE_ENDIAN)

struct SMessageAddress {
    TTask task;
    TCpu cpu;
    TBoard board;
};
typedef struct SMessageAddress SMessageAddress;

#else /* for PPC and PC MSC compilers */

struct SMessageAddress {
    TBoard board;
    TCpu cpu;
    TTask task;
};
typedef struct SMessageAddress SMessageAddress;

#endif /* __TCC__ */

#endif /* _SMESSAGEADDRESS_H */

/**
*******************************************************************************
* @struct SMessageAddress
* Description         : structure definition used in message header
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
* @param board :
* @param cpu :
* @param task :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : BTS-RAN1 SACK / Tomi Kahila
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
************************************************************************/
