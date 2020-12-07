#pragma once

#include <Common/Messages/GenericMessage.hpp>

namespace DesignDocumentCreator
{

namespace MessageFactory
{
    GenericMessage createHwConfigurationMessageForRel3BasedFromLogs();
    GenericMessage createOneTransportBearerRegisterForCell();
    GenericMessage createTcomHwConfigurationMsg();
    GenericMessage createTcomHwConfigurationResponseMsg();
}

} // namespace DesignDocumentCreator
