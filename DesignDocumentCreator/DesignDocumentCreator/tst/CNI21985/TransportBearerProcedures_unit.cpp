#include <gtest/gtest.h>

#include <Components/Tcom.hpp>
#include <Components/TupcTbm.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <ModuleTest.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, OneTransportBearerRegisterForCell)
{
    Tcom& tcom(*dynamic_cast<Tcom*>(activateComponentAsParticipant(ComponentName::Tcom)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(activateComponentAsParticipant(ComponentName::TupcTbm)));
    sendMessage(ComponentName::Tcom, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    verifierOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());

    saveUmlLog(R"(C:\APRG\DesignDocumentCreator\DesignDocumentCreatorLogs\CNI21985\OneTransportBearerRegisterForCell.txt)");
}