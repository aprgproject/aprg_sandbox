#pragma once

#include <Common/Messages/GenericMessage.hpp>

#include <gtest/gtest.h>

namespace DesignDocumentCreator
{

namespace MessageVerifier
{
    void verifyOneTransportBearerRegisterForCell(GenericMessage const& genericMessage);
    void verifySuccessfulHwConfigurationResponseMessage(GenericMessage const& genericMessage);
    void verifyTcomDeploymentIndMessage(GenericMessage const& genericMessage);
    void verifyLinkStateResponseMessage(GenericMessage const& genericMessage);
}

} // namespace DesignDocumentCreator
