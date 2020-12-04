#include <gtest/gtest.h>

#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/Oam.hpp>
#include <Components/TupcLom.hpp>
#include <ModuleTest.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, Startup)
{
    Oam& oam(*dynamic_cast<Oam*>(activateComponentAsParticipant(ComponentName::Oam)));
    TupcLom& tupcLom(*dynamic_cast<TupcLom*>(activateComponentAsParticipant(ComponentName::TupcLom)));
    sendMessage(ComponentName::Oam, ComponentName::TupcLom, createHwConfigurationMessageForRel3BasedFromLogs());
    tupcLom.handleOneEvent();

    saveUmlLog(R"(C:\APRG\DesignDocumentCreator\DesignDocumentCreatorLogs\CNI21985\Startup.txt)");
}