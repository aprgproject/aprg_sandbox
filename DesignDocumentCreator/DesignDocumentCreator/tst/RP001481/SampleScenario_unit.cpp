#include <gtest/gtest.h>

#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/TOAM.hpp>
#include <ModuleTest.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, SampleScenario)
{
    UmlLogger& umlLogger(getUmlLogger());
    TOAM& toam(*dynamic_cast<TOAM*>(getComponentAndActivateAsParticipant(ComponentName::TOAM)));

    umlLogger.logNoteOnComponent(ComponentName::TOAM, "TOAM note starts");
    umlLogger.logNoteOnComponents(ComponentNames{ComponentName::TOAM, ComponentName::TOAM}, "TOAM note starts");

    toam.pushBackEvent(Event(OtherEvent(OtherEventType::MainProcessStartup)));
    toam.handleOneEvent();

    sendMessage(ComponentName::TOAM, ComponentName::TOAM, createLrmConfigurationDataForMoreThan2K2sWithNbic());
    toam.handleOneEvent();
}
