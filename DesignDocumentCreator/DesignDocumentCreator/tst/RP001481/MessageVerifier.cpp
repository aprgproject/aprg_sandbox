#include "MessageVerifier.hpp"

#include <Common/Messages/Messages.hpp>

using testing::FLAGS_gtest_break_on_failure;

namespace DesignDocumentCreator
{

void MessageVerifier::verifierTC_LRM_CONFIGURATION_DATA_IND_MSG(GenericMessage const& genericMessage)
{
    ASSERT_EQ(MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG, genericMessage.getMessageName());

    SpecificStaticMessage<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG> message(convertGenericToSpecificStatic<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG>(genericMessage));
    SLrmConfigurationDataInd& payload(message.getStaticPayloadReference());

    EXPECT_EQ(0u, payload.numOfDsps);
}

}
