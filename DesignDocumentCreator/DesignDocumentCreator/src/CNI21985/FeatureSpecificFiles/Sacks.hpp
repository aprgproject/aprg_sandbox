#pragma once

#include <EControlUnitType.h>
#include <EConditional.h>
#include <EResponseCond.h>
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
#include <TNumberOfPresence.h>
#include <TTransactionID.h>


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
{    EControlUnitType       typeOfConfiguration;             ///< Type of configuration
    TNumberOfPresence      numOfFspInfo;
    SFspInformation        fspInformationData[1];
};

typedef struct SCmBearerSetupReqMsg
{
    TAaSysComSicad                     conmanAddress;
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