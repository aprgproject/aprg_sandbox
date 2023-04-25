/**
*******************************************************************************
* @file                  $HeadURL:
*https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_13_54/I_Interface/Global_Env/Definitions/SMessageHeader.h
*$
* @version               $LastChangedRevision: 3080 $
* @date                  $LastChangedDate: 2014-05-23 20:32:51 +0800 (Fri, 23 May 2014) $
* @author                $Author: plaskonk $
*
* Original author        Tomi Kahila
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _SMESSAGEHEADER_H
#define _SMESSAGEHEADER_H

#include <SHeaderFlags.h>
#include <SMessageAddress.h>

#ifdef SYSCOM_NOT_IN_USE
#define MESSAGEHEADER(fieldname) SMessageHeader fieldname;
#else
#define MESSAGEHEADER(fieldname)
#endif

#ifdef __TCC__ /* For texas compiler environment */

#include <TMessageIdDsp.h>
#include <TPad16.h>
#include <glo_def.h>

struct SMessageHeader {
    TMessageIdDsp id;
    TPad16 pad;
    SMessageAddress receiver;
    SMessageAddress sender;
    SHeaderFlags flags;
    u16 length;
};
typedef struct SMessageHeader SMessageHeader;

#else /* for PPC and PC MSC compilers */

#include <TMsgHeaderTypes.h>

struct SMessageHeader {
    TMessageId id;
    SMessageAddress receiver;
    SMessageAddress sender;
    TMsgLength length;
    SHeaderFlags flags;
};
typedef struct SMessageHeader SMessageHeader;

#endif /* __TCC__ */

#endif /* _SMESSAGEHEADER_H */

/**
*******************************************************************************
* @struct SMessageHeader
* Description         : Message header definition
*
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
* @param id :
* @param pad :
* @param receiver :
* @param sender :
* @param flags :
* @param length :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
************************************************************************/
