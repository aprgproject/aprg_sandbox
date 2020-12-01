#include <Common/Environment.hpp>
#include <Common/Events/Events.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <gtest/gtest.h>

using namespace DesignDocumentCreator;
using namespace std;

TEST(TransportBearerProcedureTest, OneTransportBearerRegisterForCell)
{
    SpecificMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG> specificMessage;
    STransportBearerRegisterMsg& payload = specificMessage.getPayloadReference();
    payload.cellId =

}
