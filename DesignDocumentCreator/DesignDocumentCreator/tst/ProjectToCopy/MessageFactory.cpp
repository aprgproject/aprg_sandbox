#include "MessageFactory.hpp"

#include <Common/Messages/Messages.hpp>

namespace DesignDocumentCreator
{

GenericMessage MessageFactory::createMessage1()
{
    //SpecificStaticMessage<MessageName::OAM_ATM_HW_CONFIGURATION_MSG> hwConfigurationMessage;
    //SAtmHwConfigurationMsgFake& payload(hwConfigurationMessage.getPayloadReference());
    //payload.typeOfConfiguration = EControlUnitType_Fcm;
    //return convertSpecificStaticToGeneric(hwConfigurationMessage);
}

}
