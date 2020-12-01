#include <gtest/gtest.h>

#include <ModuleTest.hpp>
#include <MessageFactory.hpp>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;

TEST_F(ModuleTest, OneTransportBearerRegisterForCell)
{
    sendMessage(ComponentName::Tcom, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
}