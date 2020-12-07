#include "MessageFactory.hpp"

#include <Common/Messages/Messages.hpp>

namespace DesignDocumentCreator
{

GenericMessage MessageFactory::createLrmConfigurationDataForMoreThan2K2sWithNbic()
{
    SpecificStaticMessage<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG> message;
    SLrmConfigurationDataInd& payload(message.getPayloadReference());
    payload.numOfDsps = 4;
    payload.dspInfo[0].dspAddress = 0x1230;
    payload.dspInfo[0].isUnitAvailable = EAvailability_Available;
    payload.dspInfo[0].dspType = EWspType_Kepler2;
    payload.dspInfo[0].localCellGroupId = 1;
    payload.dspInfo[0].powerGroupId = 1;
    payload.dspInfo[1].dspAddress = 0x1240;
    payload.dspInfo[1].isUnitAvailable = EAvailability_Available;
    payload.dspInfo[1].dspType = EWspType_Kepler2;
    payload.dspInfo[1].localCellGroupId = 1;
    payload.dspInfo[1].powerGroupId = 1;
    payload.dspInfo[2].dspAddress = 0x1250;
    payload.dspInfo[2].isUnitAvailable = EAvailability_Available;
    payload.dspInfo[2].dspType = EWspType_Kepler2;
    payload.dspInfo[2].localCellGroupId = 2;
    payload.dspInfo[2].powerGroupId = 1;
    payload.dspInfo[3].dspAddress = 0x1260;
    payload.dspInfo[3].isUnitAvailable = EAvailability_Available;
    payload.dspInfo[3].dspType = EWspType_Kepler2;
    payload.dspInfo[3].localCellGroupId = 2;
    payload.dspInfo[3].powerGroupId = 1;
    payload.numOfLcgInfo = 1;
    payload.lcgInfo[0].lcgId = 1;
    payload.lcgInfo[0].nbrOfWsps = 0;
    payload.lcgInfo[0].numOfLcr = 6;
    payload.lcgInfo[0].minNumOfHsRachResourceStepsRes = 1;
    payload.lcgInfo[0].minNumOfHsRachResourceStepsRes = 1;
    payload.lcgInfo[0].hspaConfigurationType = EHspaConfigurationType_BasicRel4;
    payload.lcgInfo[0].isNbicEnabled = EBoolean_True;
    payload.numOfLcrInfo = 1;
    payload.lcrInfo[0].lcrId = 1;
    payload.lcrInfo[0].lcgId = 1;
    payload.lcrInfo[0].isMIMOCapable = 0;
    payload.lcrInfo[0].isVAMEnabled = 0;
    payload.lcrInfo[0].defaultCarrierDlUarfcn = 10663;
    payload.lcrInfo[0].numOfRx = 2;
    payload.lcrInfo[1].lcrId = 2;
    payload.lcrInfo[1].lcgId = 1;
    payload.lcrInfo[1].isMIMOCapable = 0;
    payload.lcrInfo[1].isVAMEnabled = 0;
    payload.lcrInfo[1].defaultCarrierDlUarfcn = 10663;
    payload.lcrInfo[1].numOfRx = 2;
    payload.lcrInfo[2].lcrId = 3;
    payload.lcrInfo[2].lcgId = 1;
    payload.lcrInfo[2].isMIMOCapable = 0;
    payload.lcrInfo[2].isVAMEnabled = 0;
    payload.lcrInfo[2].defaultCarrierDlUarfcn = 10663;
    payload.lcrInfo[2].numOfRx = 2;
    payload.lcrInfo[3].lcrId = 4;
    payload.lcrInfo[3].lcgId = 1;
    payload.lcrInfo[3].isMIMOCapable = 0;
    payload.lcrInfo[3].isVAMEnabled = 0;
    payload.lcrInfo[3].defaultCarrierDlUarfcn = 10688;
    payload.lcrInfo[3].numOfRx = 2;
    payload.lcrInfo[4].lcrId = 5;
    payload.lcrInfo[4].lcgId = 1;
    payload.lcrInfo[4].isMIMOCapable = 0;
    payload.lcrInfo[4].isVAMEnabled = 0;
    payload.lcrInfo[4].defaultCarrierDlUarfcn = 10688;
    payload.lcrInfo[4].numOfRx = 2;
    payload.lcrInfo[5].lcrId = 6;
    payload.lcrInfo[5].lcgId = 1;
    payload.lcrInfo[5].isMIMOCapable = 0;
    payload.lcrInfo[5].isVAMEnabled = 0;
    payload.lcrInfo[5].defaultCarrierDlUarfcn = 10688;
    payload.lcrInfo[5].numOfRx = 2;
    payload.configChangeType = EConfigChangeType_Standard;
    payload.isCellDeletionIndicationNeeded = EBoolean_True;
    //payload.transportLayerAddress = 0; // why does LRM need this?
    return convertSpecificStaticToGeneric(message);
}

}
