/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/SCI_I_CCS/tags/MB_CCS_COMMON_AASYSCOMGW_4.2.0/overlay/I_Interface/Platform_Env/CCS_ENV/SHARED/MCU_RT/Definitions/IfAaSysComGw_Defs.h $
* @version               $LastChangedRevision: 3182 $
* @date                  $LastChangedDate: 2017-12-14 11:19:27 +0100 (Thu, 14 Dec 2017) $
* @author                $Author: szymala $
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef IF_MCU_RT_AASYSCOM_GW_DEFS_H
#define IF_MCU_RT_AASYSCOM_GW_DEFS_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../../../COMMON/ServiceInterface/IfAaPro.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComGwMcuRt AaSysComGw MCU_RT
 * @ingroup dgAaSysCom
 *
 * Common Computer and Support SW SysCom Gateway.
 *
 * @{
 */

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** CPID for the AaSysComGw */
#ifndef AASYSCOM_GW_CPID
# define AASYSCOM_GW_CPID 0x31e
#endif /* AASYSCOM_GW_CPID */

/** @brief Maximal length of the TAaSysComGwIpAddressStr string (for AaSysCom Gw IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#define AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN 48

/** @name Enums
 * @{
*/


/** @brief Error type and codes used in AaSysCom Gw 
 * @{
*/
typedef enum EAaSysComGwStatus{
  EAaSysComGwStatus_OK                    =  0,  /**< success, no error */
  EAaSysComGwStatus_Unknown               =  1,  /**< unknown/non-classified error */
  EAaSysComGwStatus_NoRouteExists         =  2,  /**< route is not found for message that was trying to be sent */
  EAaSysComGwStatus_TransportFailure      =  3,  /**< transport layer related error */
  EAaSysComGwStatus_InvalidProtocol       =  4,  /**< selected transport is invalid/not supported */
  EAaSysComGwStatus_SocketCreationFailed  =  5,  /**< transport layer socket creation failed */
  EAaSysComGwStatus_InvalidIPAddress      =  6,  /**< IP address is not valid */
  EAaSysComGwStatus_RouteAlreadyExists    =  7,  /**< route has already been registered before */
  EAaSysComGwStatus_InvalidParam          =  8,  /**< invalid parameter */
  EAaSysComGwStatus_OffendingRoute        =  9,  /**< route is offending with previous routes */
  EAaSysComGwStatus_RouteIdsExhausted     =  10, /**< all route IDs are reserved, new route can not be registered */
  EAaSysComGwStatus_TransportReleaseFailed = 11, /**< transport releasing failed */
  EAaSysComGwStatus_PortInUse             =  12, /**< Port is already used and cannot be re-used. */
  EAaSysComGwStatus_InvalidMessageSize    =  13, /**< Received UDP/UDPCP message and SIC message size do not match. */
  EAaSysComGwStatus_InternalError         =  14, /**< Internal error. */
  EAaSysComGwStatus_OutOfMemory           =  15, /**< No memory to execute operation. */
  EAaSysComGwStatus_TcpRoutesExhausted    =  16, /**< Maximum number of TCP routes already reached. */
  EAaSysComGwStatus_InvalidIPVersion      =  17  /**< IP version is not valid */
} EAaSysComGwStatus;

/** @brief Transport protocol type used in AaSysCom Gw */
typedef enum EAaSysComGwProtocol{
  EAaSysComGwProtocol_Unknown               =  0, /**< unknown type */
  EAaSysComGwProtocol_UDP                   =  1, /**< UDP protocol */
  EAaSysComGwProtocol_UDPCP                 =  2, /**< UDPCP protocol */
  EAaSysComGwProtocol_TCP                   =  3, /**< TCP protocol */
  EAaSysComGwProtocol_SCTP                  =  4, /**< SCTP protocol - supported only in MCU */
  EAaSysComGwProtocol_UDS                   =  5  /**< UDS protocol - supported only in LRC LSP AXM */
} EAaSysComGwProtocol;

/** @brief AaSysComGw route reliability information */
typedef enum EAaSysComGwReliability
{
  EAaSysComGwReliability_NonReliable = 0, /**< non reliable route */
  EAaSysComGwReliability_Reliable    = 1  /**< reliable route */
} EAaSysComGwReliability;

/** @brief Msg Header retaining type used in AaSysCom Gw */
typedef enum ERetainMsgHeader
{
  ERetainMsgHeader_No            =  0, /**< Msg header will not be retained */
  ERetainMsgHeader_Yes           =  1  /**< Msg header will be retained */
} ERetainMsgHeader;

/** @brief IPv4 or IPv6 address string, zero terminated (and, if
 *        necessary, zero padded on the right). */
typedef u8 TAaSysComGwIpAddressStr[AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN];

/** @brief Version of IP protocol used in AaSysCom Gw
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
typedef enum EAaSysComGwIpVer{
    EAaSysComGwIpVer_Unknown    =  0, /**< unknown version */
    EAaSysComGwIpVer_4          =  1, /**< IP version 4  */
    EAaSysComGwIpVer_6          =  2, /**< IP version 6  */
    EAaSysComGwIpVer_NotValid   =  3  /**< Not valid version */
} EAaSysComGwIpVer;

/**
 * @brief Defines message format version for SCTP route registration request/response messages: futur eproofing
 */
typedef enum EAaSysComGwSctpReqReplyFormatVer
{
  ESctpRegReplyVer_0 = 0

} EAaSysComGwSctpReqReplyFormatVer;

/**
 * @brief SCTP route protocol specific data
 *
 * Additional parameters needed for SCTP route setup.
 */
typedef struct AaSysComGwRegSctpParameters
{
  EAaSysComGwSctpReqReplyFormatVer msgFormatVer; /** futureproofing */
} AaSysComGwRegSctpParameters;

/** @brief Extended IP address and port information type used in AaSysCom Gw */
typedef struct SAaSysComGwIpAddressExt
{
  TAaSysComGwIpAddressStr   address;    /**< IP address string */
  TAaSysComGwPortNum        port;       /**< port number */
  EAaSysComGwIpVer          ipVersion;  /**< IP Version */
} SAaSysComGwIpAddressExt;

/** @brief TCP route type */
typedef enum EAaSysComGwTcpType
{
  EAaSysComGwTcpType_Unknown         = 0,   /**< Unknown type. */
  EAaSysComGwTcpType_Server          = 1,   /**< TCP server. */
  EAaSysComGwTcpType_Client          = 2,   /**< TCP client. */
  EAaSysComGwTcpType_ConnectedClient = 3    /**< CCS internal. Not to be used by application. */
} EAaSysComGwTcpType;

/** @brief TCP message size format */
typedef enum EMessageSizeFormat
{
  EMessageSizeFormat_BigEndian      = 0,    /**< Big endian format. */
  EMessageSizeFormat_LittleEndian   = 1     /**< Little endian format. */
} EMessageSizeFormat;

/** @brief TCP message size length */
typedef enum EMessageSizeLength
{
  EMessageSizeLength_1Byte  = 1,    /**< Message size length field is 1 byte long. */
  EMessageSizeLength_2Bytes = 2,    /**< Message size length field is 2 bytes long. */
  EMessageSizeLength_4Bytes = 4     /**< Message size length field is 4 bytes long. */
} EMessageSizeLength;

/** @brief Defines how TCP server will validate connecting client IP address and port. */
typedef enum EClientValidation
{
  EClientValidation_IpAndPort = 0,  /**< TCP server checks both IP and port of connecting TCP client.
                                       Both IP and port must match remote IP and port of existing route. */
  EClientValidation_IpOnly    = 1   /**< TCP server checks only IP of connecting TCP client.
                                       Only IP must match remote IP of existing route. Port can be dynamic. */
} EClientValidation;

/**
 * @brief TCP route protocol specific data
 *
 * Additional parameters needed for TCP route setup.
 */
typedef struct AaSysComGwRegTcpParameters
{
  EAaSysComGwTcpType    tcpRouteType;           /**< Either server or client. */
  u32                   messageSizePosition;    /**< Message size position in received stream. Special value
                                                   AASYSCOM_GW_TCP_TRANSPARENT_ROUTE means data is received transparently. */
  EMessageSizeLength    messageSizeLength;      /**< Number of bytes used for message size. */
  EMessageSizeFormat    messageSizeFormat;      /**< Message size format encoding. */
  EClientValidation     clientValidation;       /**< Relevant only for TCP server route type. */
} AaSysComGwRegTcpParameters;

/**
 * @brief TCP route supervision parameters
 *
 * Additional parameters needed for TCP supervision.
 * This structure used only on MCU.
 */
typedef struct AaSysComGwRegTcpSupervisionParameters
{
  u32 keepAliveCnt;        /**< Maximum number of keepalive probes sent to peer before dropping the connection.
                                Value 0 indicates no supervision enabled. */
  u32 keepIdle;            /**< The time in seconds the connection needs to remain idle before sending
                                keepalive probes (only in case supervision is enabled) */
  u32 keepIntvl;           /**< The time in seconds between individual keepalive probes (only in case
                                supervision is enabled) */
} AaSysComGwRegTcpSupervisionParameters;


/**
 * @brief TCP route protocol specific data with supervision parameters
 *
 * Additional parameters needed for TCP route setup.
 * with additional supervision parameters
 * This structure used only on MCU.
 */
typedef struct AaSysComGwRegTcpExtParameters
{
  AaSysComGwRegTcpParameters             tcpRouteParameters;       /** < TCP route parameters */
  AaSysComGwRegTcpSupervisionParameters  tcpSupervisionParameters; /** < TCP supervision parameters */
} AaSysComGwRegTcpExtParameters;

/**
 * @brief Route protocol specific data
 *
 * Additional protocol parameters needed for route setup.
 */
typedef union AaSysComGwRegProtocolParameters
{
  AaSysComGwRegTcpParameters    tcp;    /**< TCP protocol specific data */
  AaSysComGwRegSctpParameters   sctp;   /**< SCTP protocol specific data */
} AaSysComGwRegProtocolParameters;

/** @} */

/** @brief AaSyscom GW route ID type to indentify a route */
typedef u32 TAaSysComGwRouteId;
/** @brief invalid value for route ID */
#define AASYSCOM_GW_INVALID_ROUTE_ID 0

/** @} */

/** @brief Define for TCP route transparent receive mode. Any received data is
    transfered to application as received (no parsing for message size). */
#define AASYSCOM_GW_TCP_TRANSPARENT_ROUTE   0xFFFFFFFF

/** @brief Maximum number of TCP routes in AaSysComGw. */
#define AASYSCOM_GW_MAX_TCP_ROUTES  64

/**
 * @brief   The type of route subscribe request.
 * @par Restrictions: route supervision is supported by CC&S-MCU and RCP CC&S-RT
 * Used in supervision request message.
 */
typedef enum EAaSysComGwRouteSubReqType
{
    EAaSysComGwRouteSubReq_Subscribe     = 0,    /**< Subscribe for receiving transport events. */
    EAaSysComGwRouteSubReq_Unsubscribe   = 1     /**< Unsubscribe for receiving transport events. */
} EAaSysComGwRouteSubReqType;

/**
 * @brief   The status of route (link).
 *
 * Used in supervision indication message.
 */
typedef enum EAaSysComGwRouteStatus
{
    EAaSysComGwRoute_LinkUp             = 0,    /**< Link is up. */
    EAaSysComGwRoute_LinkSetupFailed    = 1,    /**< Link could not be established. */
    EAaSysComGwRoute_LinkGracefullyDown = 2,    /**< Link is gracefully down. */
    EAaSysComGwRoute_LinkLost           = 3     /**< Link is lost. */
} EAaSysComGwRouteStatus;

/**
 * @brief AaSysCom gw message, GW uses this message struct when handling incoming and
 * outgoing messages, payload is transparent data.
 *
 * @note message ID for this message is not fixed and it is the one defined in the
 * corresponding route registration
 */

/** @} end: @addtogroup dgAaSysComGwMcuRt AaSysComGw MCU_RT*/


#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_RT_AASYSCOM_GW_DEFS_H */
