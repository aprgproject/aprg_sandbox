#include <gtest/gtest.h>

#include <ModuleTest.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>
#include <Common/Utils/StringHelpers.hpp>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, OneTransportBearerRegisterForCell)
{
    Component& tcom(activateComponentAsParticipant(ComponentName::Tcom));
    Component& tupcTbm(activateComponentAsParticipant(ComponentName::TupcTbm));
    sendMessage(ComponentName::Tcom, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    verifierOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());

    saveUmlLog(R"(C:\APRG\DesignDocumentCreator\DesignDocumentCreatorLogs\CNI21985\OneTransportBearerRegisterForCell.txt)");
}