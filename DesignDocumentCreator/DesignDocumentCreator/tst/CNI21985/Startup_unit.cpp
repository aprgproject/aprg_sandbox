/*#include <gtest/gtest.h>

#include <ModuleTest.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>
#include <Common/Utils/StringHelpers.hpp>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, Startup)
{
    Component& oam(activateComponentAsParticipant(ComponentName::Oam));
    Component& tupcLom(activateComponentAsParticipant(ComponentName::TupcLom));
    sendMessage(ComponentName::Oam, ComponentName::TupcLom, createHwConfigurationMessageForRel3BasedFromLogs());
    verifierOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());

    saveUmlLog(R"(C:\APRG\DesignDocumentCreator\DesignDocumentCreatorLogs\CNI21985\OneTransportBearerRegisterForCell.txt)");
}*/
