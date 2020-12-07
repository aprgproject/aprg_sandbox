#include <gtest/gtest.h>

#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/TOAM.hpp>
#include <Components/LRM.hpp>
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
    LRM& lrm(*dynamic_cast<LRM*>(getComponentAndActivateAsParticipant(ComponentName::LRM)));

    sendMessage(ComponentName::TOAM, ComponentName::LRM, createLrmConfigurationDataForMoreThan2K2sWithNbic());
    lrm.handleOneEvent();
}
