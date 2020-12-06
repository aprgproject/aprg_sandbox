#include "MessageVerifier.hpp"

#include <Common/Messages/Messages.hpp>

using testing::FLAGS_gtest_break_on_failure;

namespace DesignDocumentCreator
{

void MessageVerifier::verifierMessage1(GenericMessage const& genericMessage)
{
    //ASSERT_EQ(MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, genericMessage.getMessageName());
    //SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, 1> tbRegisterMessage(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, 1>(genericMessage));
    //STransportBearerRegisterMsg& tbRegisterStaticPayload(tbRegisterMessage.getStaticPayloadReference());
    //EXPECT_EQ(100001, tbRegisterStaticPayload.transactionId);
}

}
