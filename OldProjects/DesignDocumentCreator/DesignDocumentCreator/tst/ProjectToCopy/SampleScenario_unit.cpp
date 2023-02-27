#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/Component1.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>
#include <ModuleTest.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, SampleScenario)
{
    UmlLogger& umlLogger(getUmlLogger());
    Component1& component1(*static_cast<Component1*>(getComponentAndActivateAsParticipant(ComponentName::Component1, "COMPONENT1")));

    umlLogger.logNoteOnComponent(ComponentName::Component1, "Component1 note starts");
    umlLogger.logNoteOnComponents(ComponentNames{ComponentName::Component1, ComponentName::Component1}, "Component1 note starts");
    component1.pushBackEvent(Event(OtherEvent(OtherEventType::MainProcessStartup)));
    component1.handleOneEvent();
    sendMessage(ComponentName::Component1, ComponentName::Component1, createMESSAGE_1());
    component1.handleOneEvent();
}
