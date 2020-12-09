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

#define MAX_NUM_RLH_INSTANCES 8


typedef struct SAtmHwConfigurationMsgFake
{
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
    EControlUnitType       typeOfConfiguration;             ///< Type of configuration
    TNumberOfPresence      numOfFspInfo;
    SFspInformation        fspInformationData[1];
};

typedef struct SCmBearerSetupReqMsg
{
    TTransactionID                     transactionId;
    TCellId                            cellId;
    TNbccId                            nbccId;
    TNumberOfPresence                  numConnections;
    STransportBearerLocationData       tbLocationData[1];
} SCmBearerSetupReqMsg;

typedef struct SCmBearerSetupRespMsg
{
    TTransactionID                     transactionId;
    EResponseCond                      response;
    TCause                             cause;
    TCellId                            cellId;
    TNbccId                            nbccId;
    TNumberOfPresence                  numConnections;
    STransportBearerSignallingData     tbSignallingData[1];
} SCmBearerSetupRespMsg;


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
    STCWamAddressIndNew                    wamAddressInd;
} STcomDeploymentIndMsg;

typedef struct STupcTbmConfigurationMsg
{
    TAaSysComSicad                    tupcCmSicad;
} STupcTbmConfigurationMsg;

