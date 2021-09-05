#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/Oam.hpp>
#include <Components/TcomToam.hpp>
#include <Components/TupcCm.hpp>
#include <Components/TupcIlm.hpp>
#include <Components/TupcLom.hpp>
#include <Components/TupcTbm.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>
#include <ModuleTest.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, TupcStartup)
{
    UmlLogger& umlLogger(getUmlLogger());
    Oam& oam(*dynamic_cast<Oam*>(getComponentAndActivateAsParticipant(ComponentName::Oam, "OAM")));
    TupcIlm& tupcIlm(*dynamic_cast<TupcIlm*>(getComponentAndActivateAsParticipant(ComponentName::TupcIlm, "TUPC/ILM")));
    TupcLom& tupcLom(*dynamic_cast<TupcLom*>(getComponentAndActivateAsParticipant(ComponentName::TupcLom, "TUPC/LOM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));

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
    Oam& oam(*dynamic_cast<Oam*>(getComponentAndActivateAsParticipant(ComponentName::Oam, "OAM")));
    TcomToam& tcomToam(*dynamic_cast<TcomToam*>(getComponentAndActivateAsParticipant(ComponentName::TcomToam, "TCOM/TOAM")));
    TupcLom& tupcLom(*dynamic_cast<TupcLom*>(getComponentAndActivateAsParticipant(ComponentName::TupcLom, "TUPC/LOM")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));

    sendMessage(ComponentName::Oam, ComponentName::TcomToam, createLinkStatesMsg());
    tcomToam.handleOneEvent();
    verifyLinkStateResponseMessage(oam.peekMessageAtStartOfTheEventQueue());
    verifyTcomDeploymentIndMessage(tupcLom.peekMessageAtStartOfTheEventQueue());

    oam.handleOneEvent();

    tupcLom.handleOneEvent();

    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, TupcReceivesTcomDeploymentFromTcomDuringHwAvailableOrAddition)
{
    UmlLogger& umlLogger(getUmlLogger());
    Oam& oam(*dynamic_cast<Oam*>(getComponentAndActivateAsParticipant(ComponentName::Oam, "OAM")));
    TcomToam& tcomToam(*dynamic_cast<TcomToam*>(getComponentAndActivateAsParticipant(ComponentName::TcomToam, "TCOM/TOAM")));
    TupcLom& tupcLom(*dynamic_cast<TupcLom*>(getComponentAndActivateAsParticipant(ComponentName::TupcLom, "TUPC/LOM")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));

    sendMessage(ComponentName::Oam, ComponentName::TcomToam, createTcomHwConfigurationChangeMsg());
    tcomToam.handleOneEvent();
    verifyTcomDeploymentIndMessage(tupcLom.peekMessageAtStartOfTheEventQueue());

    tupcLom.handleOneEvent();

    tupcTbm.handleOneEvent();
}
