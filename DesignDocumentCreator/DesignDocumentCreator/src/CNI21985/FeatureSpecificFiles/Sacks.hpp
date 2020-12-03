#pragma once

#include <EControlUnitType.h>
#include <EConditional.h>
#include <STupConfigurationInfo.h>
#include <STupcBtsParameters.h>
#include <TMtuSize.h>
#include <TNumberOfPresence.h>
#include <SFspInformation.h>
#include <SFlexiConnectionInfo.h>

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
        SFlexiConnectionInfo     flexiConnectionInfo[3];
} SAtmHwConfigurationMsg;

struct TUP_CmConfigurationCmd
{
    EControlUnitType       typeOfConfiguration;             ///< Type of configuration
    TNumberOfPresence      numOfFspInfo;
    SFspInformation        fspInformationData[1];
};
