#include <gtest/gtest.h>

#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/Oam.hpp>
#include <Components/TcomToam.hpp>
#include <Components/TupcCm.hpp>
#include <Components/TupcIlm.hpp>
#include <Components/TupcLom.hpp>#include <Components/TupcTbm.hpp>
#include <ModuleTest.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>
using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, TupcStartup)
{
    UmlLogger& umlLogger(getUmlLogger());
    Oam& oam(*dynamic_cast<Oam*>(getComponentAndActivateAsParticipant(ComponentName::Oam)));
    TupcIlm& tupcIlm(*dynamic_cast<TupcIlm*>(getComponentAndActivateAsParticipant(ComponentName::TupcIlm)));
    TupcLom& tupcLom(*dynamic_cast<TupcLom*>(getComponentAndActivateAsParticipant(ComponentName::TupcLom)));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));

    umlLogger.logNoteOnComponents(ComponentNames{ComponentName::TupcIlm, ComponentName::TupcTbm}, "TUPCexe starts");

    tupcIlm.pushBackEvent(Event(OtherEvent(OtherEventType::MainProcessStartup)));
    tupcIlm.handleOneEvent();

    tupcLom.pushBackEvent(Event(OtherEvent(OtherEventType::MainProcessStartup)));
    tupcLom.handleOneEvent();

    tupcCm.pushBackEvent(Event(OtherEvent(OtherEventType::MainProcessStartup)));
    tupcCm.handleOneEvent();

    tupcTbm.pushBackEvent(Event(OtherEvent(OtherEventType::MainProcessStartup)));
    tupcTbm.handleOneEvent();

    sendMessage(ComponentName::Oam, ComponentName::TupcLom, createHwConfigurationMessageForRel3BasedFromLogs());
    tupcLom.handleOneEvent();

    tupcCm.handleOneEvent();
}

TEST_F(ModuleTest, TupcReceivesTcomDeploymentFromTcomDuringLinkStateUp)
{
    UmlLogger& umlLogger(getUmlLogger());
    Oam& oam(*dynamic_cast<Oam*>(getComponentAndActivateAsParticipant(ComponentName::Oam)));
    TcomToam& tcom(*dynamic_cast<TcomToam*>(getComponentAndActivateAsParticipant(ComponentName::TcomToam)));
    TupcLom& tupcLom(*dynamic_cast<TupcLom*>(getComponentAndActivateAsParticipant(ComponentName::TupcLom)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));

    sendMessage(ComponentName::Oam, ComponentName::TcomToam, createLinkStatesMsg());
    tcom.handleOneEvent();
    verifyLinkStateResponseMessage(oam.peekMessageAtStartOfTheEventQueue());
    verifyTcomDeploymentIndMessage(tupcLom.peekMessageAtStartOfTheEventQueue());
    oam.handleOneEvent();

    tupcLom.handleOneEvent();
    tupcTbm.handleOneEvent();
}
