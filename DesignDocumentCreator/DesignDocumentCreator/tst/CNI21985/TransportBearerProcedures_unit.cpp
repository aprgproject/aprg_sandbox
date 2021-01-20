#include <gtest/gtest.h>

#include <Components/TcomToam.hpp>
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
    TcomToam& tcom(*dynamic_cast<TcomToam*>(getComponentAndActivateAsParticipant(ComponentName::TcomToam)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));

    sendMessage(ComponentName::TcomToam, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    tupcTbm.handleOneEvent();

    sendMessage(ComponentName::TcomToam, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    verifyOneTransportBearerRegisterForCell(tupcTbm.peekMessageAtStartOfTheEventQueue());}