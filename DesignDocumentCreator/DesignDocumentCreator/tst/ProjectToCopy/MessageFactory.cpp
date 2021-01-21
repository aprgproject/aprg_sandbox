#include "MessageFactory.hpp"

#include <Common/Messages/Messages.hpp>

namespace DesignDocumentCreator
{

GenericMessage MessageFactory::createMESSAGE_1()
{
    SpecificStaticMessage<MessageName::MESSAGE_1> message;
    Message1Structure& payload(message.getStaticPayloadReference());
    payload.temporary = 0x0;
    return convertSpecificStaticToGeneric(message);
}

}
