#include "CommonModuleTest.hpp"

#include <Common/Utils/StringHelpers.hpp>
#include <FeatureSpecificFiles/Uml/UmlHelpers.hpp>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;using testing::FLAGS_gtest_break_on_failure;

namespace DesignDocumentCreator
{
CommonModuleTest::CommonModuleTest()
    : m_environment(Environment::getInstance())
{}

void CommonModuleTest::SetUp()
{
    m_environment.clear();
}

void CommonModuleTest::TearDown()
{
    saveUmlLog();
}

void CommonModuleTest::sendMessage(GenericMessage const& genericMessage)
{
    m_environment.send(genericMessage);
}

void CommonModuleTest::sendMessage(ComponentName const sender, ComponentName const receiver, GenericMessage const& genericMessage)
{
    m_environment.send(sender, receiver, genericMessage);
}

Component* CommonModuleTest::getComponentAndActivateAsParticipant(ComponentName const componentName)
{
    getUmlLogger().addParticipant(UmlParticipant(UmlParticipantType::participant, convertToString(componentName), UmlHelpers::getUmlAlias(componentName)));
    return m_environment.getComponentPointer(componentName);
}

void CommonModuleTest::saveUmlLog()
{
    const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
    getUmlLogger().saveUmlLogsToFile(string(LOG_LOCATION)+"/"+test_info->test_case_name()+"_"+test_info->name()+".txt");
}

UmlLogger& CommonModuleTest::getUmlLogger()
{
    return m_environment.getUmlLogger();
}

}
