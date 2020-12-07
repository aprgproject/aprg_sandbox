#include "MessageVerifier.hpp"

#include <Common/Messages/Messages.hpp>

using testing::FLAGS_gtest_break_on_failure;

namespace DesignDocumentCreator
{

void MessageVerifier::verifierMESSAGE_1(GenericMessage const& genericMessage)
{
    ASSERT_EQ(MessageName::MESSAGE_1, genericMessage.getMessageName());

    SpecificStaticMessage<MessageName::MESSAGE_1> message(convertGenericToSpecificStatic<MessageName::MESSAGE_1>(genericMessage));
    Message1Structure& payload(message.getPayloadReference());

    EXPECT_EQ(0, payload.temporary);
}

}
