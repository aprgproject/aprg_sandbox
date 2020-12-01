#pragma once

#include <Common/Messages/GenericMessage.hpp>

#include <gtest/gtest.h>

namespace DesignDocumentCreator
{

class MessageVerifier : public ::testing::Test
{
public:
    void verifierSample(GenericMessage const& genericMessage) const;

};

} // namespace DesignDocumentCreator

