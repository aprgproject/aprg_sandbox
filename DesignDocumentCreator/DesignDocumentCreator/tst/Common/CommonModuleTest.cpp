#include "CommonModuleTest.hpp"
#include <Common/Utils/StringHelpers.hpp>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;
using testing::FLAGS_gtest_break_on_failure;

namespace DesignDocumentCreator{

void CommonModuleTest::sendMessage(GenericMessage const& genericMessage)
{
    m_environment.send(genericMessage);
}

void CommonModuleTest::sendMessage(ComponentName const sender, ComponentName const receiver, GenericMessage const& genericMessage)
{
    m_environment.send(sender, receiver, genericMessage);
}

void CommonModuleTest::saveUmlLog(string const& filePath)
{
    m_environment.getUmlLogger().saveUmlLogsToFile(filePath);
}

Component& CommonModuleTest::activateComponentAsParticipant(ComponentName const componentName)
{
    m_environment.getUmlLogger().addParticipant(UmlParticipant(convertToString(componentName), UmlParticipantType::participant));
    return m_environment.getComponentReference(componentName);
}

}