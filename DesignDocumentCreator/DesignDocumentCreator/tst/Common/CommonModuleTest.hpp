#pragma once

#include <Common/Environment.hpp>

#include <gtest/gtest.h>

#include <string>

namespace DesignDocumentCreator
{

class CommonModuleTest : public ::testing::Test
{
public:
    void sendMessage(GenericMessage const& genericMessage);
    void sendMessage(ComponentName const sender, ComponentName const receiver, GenericMessage const& genericMessage);
    void saveUmlLog(std::string const& filePath);
    Component& activateComponentAsParticipant(ComponentName const componentName);
private:
    Environment m_environment;
};
} // namespace DesignDocumentCreator

