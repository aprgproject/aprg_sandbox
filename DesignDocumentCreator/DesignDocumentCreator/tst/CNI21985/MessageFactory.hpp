#pragma once

#include <Common/Messages/GenericMessage.hpp>

namespace DesignDocumentCreator
{

namespace MessageFactory
{
    GenericMessage createHwConfigurationMessageForRel3BasedFromLogs();
    GenericMessage createOneTransportBearerRegisterForCell();
    GenericMessage createOneTransportBearerUnregisterForCell();
    GenericMessage createOneTransportBearerModificationPrepareForUser();
    GenericMessage createOneTransportBearerModificationCommitForUser();
    GenericMessage createOneTransportBearerModificationCancelForUser();
    GenericMessage createTcomHwConfigurationMsg();
    GenericMessage createTcomHwConfigurationResponseMsg();
    GenericMessage createTcomHwConfigurationChangeMsg();
    GenericMessage createLinkStatesMsg();
    GenericMessage createLinkStatesResponseMsg();
}

} // namespace DesignDocumentCreator

