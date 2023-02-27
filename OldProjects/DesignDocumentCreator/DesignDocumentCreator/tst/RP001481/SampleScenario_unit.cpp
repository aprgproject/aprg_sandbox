#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/LRM.hpp>
#include <Components/TOAM.hpp>
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
    TOAM& toam(*static_cast<TOAM*>(getComponentAndActivateAsParticipant(ComponentName::TOAM, "TOAM")));
    LRM& lrm(*static_cast<LRM*>(getComponentAndActivateAsParticipant(ComponentName::LRM, "LRM")));

    sendMessage(ComponentName::TOAM, ComponentName::LRM, createLrmConfigurationDataForMoreThan2K2sWithNbic());
    lrm.handleOneEvent();}