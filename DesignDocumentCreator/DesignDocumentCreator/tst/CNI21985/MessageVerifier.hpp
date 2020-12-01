#pragma once

#include <Common/Messages/GenericMessage.hpp>

#include <gtest/gtest.h>

namespace DesignDocumentCreator
{

namespace MessageVerifier
{
    void verifierOneTransportBearerRegisterForCell(GenericMessage const& genericMessage);
}

} // namespace DesignDocumentCreator
