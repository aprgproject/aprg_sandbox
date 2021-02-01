#pragma once

#include <Common/Environment.hpp>
#include <Common/Uml/UmlLogger.hpp>

#include <gtest/gtest.h>

#include <string>

namespace DesignDocumentCreator
{

class CommonModuleTest : public ::testing::Test
{
public:
    CommonModuleTest();
    void SetUp() override;
    void TearDown() override;
    void sendMessage(GenericMessage const& genericMessage);
    void sendMessage(ComponentName const sender, ComponentName const receiver, GenericMessage const& genericMessage);
    Component* getComponentAndActivateAsParticipant(ComponentName const componentName, std::string const& umlAlias);
    void saveUmlLog();
    UmlLogger& getUmlLogger();
private:
    Environment& m_environment;
};


} // namespace DesignDocumentCreator

