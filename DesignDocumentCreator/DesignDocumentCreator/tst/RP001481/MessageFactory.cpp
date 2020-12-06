#include "MessageFactory.hpp"

#include <Common/Messages/Messages.hpp>

namespace DesignDocumentCreator
{

GenericMessage MessageFactory::createTC_LRM_CONFIGURATION_DATA_IND_MSG()
{
    SpecificStaticMessage<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG> message;
    SLrmConfigurationDataInd& payload(message.getPayloadReference());
    payload.numOfDsps = 0x0;
    return convertSpecificStaticToGeneric(message);
}

}
