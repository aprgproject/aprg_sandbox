#pragma once

#include <EControlUnitType.h>
#include <EConditional.h>
#include <EResponseCond.h>
#include <STCWamAddressInd.h>
#include <STransportBearerLocationData.h>
#include <STransportBearerSignallingData.h>
#include <SFlexiConnectionInfo.h>
#include <SFspInformation.h>
#include <STupConfigurationInfo.h>
#include <STupcBtsParameters.h>
#include <TAaSysComSicad.h>
#include <TCellId.h>
#include <TCause.h>
#include <TMtuSize.h>
#include <TNbccId.h>
#include <TNumberOfItems.h>
#include <TNumberOfPresence.h>
#include <TTransactionID.h>
#include <EUnregisterType.h>
#include <ETransportBearerCause.h>

#define MAX_NUM_RLH_INSTANCES 8


typedef struct SAtmHwConfigurationMsgFake
{
    MESSAGEHEADER(msgHeader)
    EControlUnitType         typeOfConfiguration;
    EConditional             tupConfigurationPresent;
    STupConfigurationInfo    tupConfigurationInfo;
    STupcBtsParameters       commisioningParameters;
    TMtuSize                 ipMtuSize;
    TNumberOfPresence        numOfWspBoards;
    TNumberOfPresence        numOfFlexiConnections;
    SFspInformation          fspInformation[36]; //fake
    SFlexiConnectionInfo     flexiConnectionInfo[3];//fake
} SAtmHwConfigurationMsgFake;

struct TUP_CmConfigurationCmd
{
    MESSAGEHEADER(msgHeader)
    EControlUnitType       typeOfConfiguration;             ///< Type of configuration
    TNumberOfPresence      numOfFspInfo;
    SFspInformation        fspInformationData[1];
};

struct STCWamAddressIndNew
{
    MESSAGEHEADER(msgHeader)
    EBoolean        isSbts;
    TAaSysComSicad  oamSubscriberSicad;
    TAaSysComSicad  lmsSicad;
    TAaSysComSicad  tupcCmSicad; //changed name
    TAaSysComSicad  cnbapTupcIlmSicad; //changed name
    TAaSysComSicad  dnbapTupcIlmSicad; //changed name
    TNumberOfItems  numOfTcomInstances;
    STcomInstance   tcomInstances[MAX_NUM_OF_CONTROL_UNITS];
};
typedef struct STCWamAddressIndNew STCWamAddressIndNew;

typedef struct STcomDeploymentIndMsg
{
    MESSAGEHEADER(msgHeader)
    STCWamAddressIndNew                    wamAddressInd;
} STcomDeploymentIndMsg;

typedef struct STupcTbmConfigurationMsg
{
    MESSAGEHEADER(msgHeader)
    TAaSysComSicad                    tupcCmSicad;
} STupcTbmConfigurationMsg;

struct SCmBearersSetupReqDynamicPart
{
    EBearerType                 bearerType;
    u32                         transportId;
    SFpLocation                 fpLocation;
    u32                         messageTypeNumber;
    SIpPayloadParameters        ulParameters;
    SIpPayloadParameters        oldUlParameters;
    STransportEndPointVer2      rncEndPoint;
    TDsField                    dsField;
};

typedef struct SCmBearersSetupReqMsg
{
    MESSAGEHEADER(msgHeader)
    TTransactionID                     transactionId;
    TCellId                            cellId;
    TNbccId                            nbccId;
    TNumberOfPresence                  numConnections;
    SCmBearersSetupReqDynamicPart      dynamicPart[1];
} SCmBearersSetupReqMsg;

struct SCmBearersSetupRespDynamicPart
{
    EBearerType                  bearerType;
    u32                          transportId;
    TTransportBearerId           transportBearerId;
    STransportEndPointVer2       btsEndPoint;
    STransportEndPoint           ftmIpta;
    STransportEndPoint           dspIpta;
    TAaSysComSicad               fpSicAddress;
    TTransportIdentifier         localPort;
    STransportEndPoint           remoteAddress;
    TFpId                        fpId;
};

typedef struct SCmBearersSetupRespMsg
{
    MESSAGEHEADER(msgHeader)
    TTransactionID                     transactionId;
    EResponseCond                      response;
    TCause                             cause;
    TCellId                            cellId;
    TNbccId                            nbccId;
    TNumberOfPresence                  numConnections;
    SCmBearersSetupRespDynamicPart     dynamicPart[1];
} SCmBearersSetupRespMsg;

struct SCmBearersReleaseReqDynamicPart
{
    TTransportBearerId               transportBearerId;
};

typedef struct SCmBearersReleaseReqMsg
{
    MESSAGEHEADER(msgHeader)
    TTransactionID                   transactionId;
    EBoolean                         immediateRelease;
    EBoolean                         skipDspConnectionRelease;
    EUnregisterType                  unregisterType;
    TCellId                          cellId;
    TNbccId                          nbccId;
    TNumberOfPresence                numConnections;
    SCmBearersReleaseReqDynamicPart  dynamicPart[1];
} SCmBearersReleaseReqMsg;

struct SCmBearersReleaseRespDynamicPart
{
    TAaSysComSicad            fpSicAddress;
    TTransportIdentifier      localPort;
};

typedef struct SCmBearersReleaseRespMsg
{
    MESSAGEHEADER(msgHeader)
    TNumberOfPresence                 numConnections;
    SCmBearersReleaseRespDynamicPart  dynamicPart[1];
} SCmBearersReleaseRespMsg;

typedef enum ECmBearersModifyTransactionType
{
    ECmBearersModifyTransactionType_Unknown                        = 0,
    ECmBearersModifyTransactionType_ModificationPrepare            = 1,
    ECmBearersModifyTransactionType_ModificationCommit             = 2,
    ECmBearersModifyTransactionType_ModificationCancel             = 3,
    ECmBearersModifyTransactionType_ReallocationPrepare            = 4,
    ECmBearersModifyTransactionType_ReallocationCommit             = 5,
} ECmBearersModifyTransactionType;

struct SCmBearersModifyReqDynamicPart
{
    TTransportBearerId      transportBearerId;
    SIpPayloadParameters    ulParameters;
};

typedef struct SCmBearersModifyReqMsg
{
    MESSAGEHEADER(msgHeader)
    TTransactionID                              transactionId;
    TCellId                                     cellId;
    TNbccId                                     nbccId;
    ECmBearersModifyTransactionType             transactionType;
    TNumberOfPresence                           numConnections;
    SCmBearersModifyReqDynamicPart              dynamicPart[1];
} SCmBearersModifyReqMsg;

typedef struct SCmBearersModifyRespMsg
{
    MESSAGEHEADER(msgHeader)
    TTransactionID           transactionId;
    TCellId                  cellId;
    TNbccId                  nbccId;
    EResponseCond            response;
    ETransportBearerCause    cause;
} SCmBearersModifyRespMsg;

typedef enum ECmBearersUpdateTransactionType
{
    ECmBearersUpdateTransactionType_Unknown                          = 0,
    ECmBearersUpdateTransactionType_ReleasedFromTransport            = 1
} ECmBearersUpdateTransactionType;

struct SCmBearersUpdateIndDynamicPart
{
    TTransportBearerId        transportBearerId;
    TAaSysComSicad            fpSicAddress;
    TTransportIdentifier      localPort;
};

typedef struct SCmBearersUpdateIndMsg
{
    MESSAGEHEADER(msgHeader)
    ECmBearersUpdateTransactionType     transactionType;
    TNumberOfPresence                   numConnections;
    SCmBearersUpdateIndDynamicPart      dynamicPart[1];
} SCmBearersUpdateIndMsg;
