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
    Tcom& tcom(*dynamic_cast<Tcom*>(getComponentAndActivateAsParticipant(ComponentName::Tcom)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));

    sendMessage(ComponentName::Tcom, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    verifyOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());

    sendMessage(ComponentName::Tcom, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    verifyOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());
}
