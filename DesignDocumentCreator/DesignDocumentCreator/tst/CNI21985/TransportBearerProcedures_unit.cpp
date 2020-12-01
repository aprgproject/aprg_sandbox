#include <Common/Environment.hpp>
#include <Common/Events/Events.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <gtest/gtest.h>

using namespace DesignDocumentCreator;
using namespace std;

TEST(TransportBearerProcedureTest, OneTransportBearerRegisterForCell)
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG> specificStaticMessage;
    STransportBearerRegisterMsg& payload = specificStaticMessage.getPayloadReference();
    payload.cellId = 111;
    payload.numConnections = 1;
    payload.transactionId = 222;

}
