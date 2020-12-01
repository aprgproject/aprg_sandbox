#include "CommonModuleTest.hpp"

using testing::FLAGS_gtest_break_on_failure;

namespace DesignDocumentCreator
{

void CommonModuleTest::sendMessage(GenericMessage const& genericMessage)
{
    m_environment.send(genericMessage);
}

void CommonModuleTest::sendMessage(ComponentName const sender, ComponentName const receiver, GenericMessage const& genericMessage)
{
    m_environment.send(sender, receiver, genericMessage);
}

void CommonModuleTest::sendMessage(ComponentName const sender, ComponentName const receiver, GenericMessage const& genericMessage)
{
    m_environment.send(sender, receiver, genericMessage);
}

void CommonModuleTest::saveUmlLog(std::string const& filePath)
{
    m_environment.getUmlLogger().saveUmlLogsToFile(filePath);
}
}
