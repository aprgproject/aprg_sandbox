#include <gtest/gtest.h>

#include <Components/Toam.hpp>
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
    Toam& tcom(*dynamic_cast<Toam*>(getComponentAndActivateAsParticipant(ComponentName::Toam)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));

    sendMessage(ComponentName::Toam, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    verifyOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());

    sendMessage(ComponentName::Toam, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    verifyOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());
}
