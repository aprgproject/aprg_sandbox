#include <gtest/gtest.h>

#include <Components/Dsp.hpp>
#include <Components/TcomCchhRlh.hpp>
#include <Components/Trsw.hpp>
#include <Components/TupcCm.hpp>
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

TEST_F(ModuleTest, OneTransportBearerRegister)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH/CCHH/HSCH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw, "TRSW/Transport")));
    Dsp& dsp(*dynamic_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "DSP")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerUnregister)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH/CCHH/HSCH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw, "TRSW/Transport")));
    Dsp& dsp(*dynamic_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "DSP")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerUnregisterForCell());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationPrepareForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw, "TRSW/Transport")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationPrepareForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationCommitForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw, "TRSW/Transport")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationCommitForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationCancelForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw, "TRSW/Transport")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationCancelForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationPrepareForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    Dsp& dsp(*dynamic_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "New DSP")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationPrepareForUser());
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationCommitForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw, "TRSW/Transport")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationCommitForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationCleanupForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    Dsp& dsp(*dynamic_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "Old DSP")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationCleanupForUser());
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationCancelForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationCancelForUser());
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerUnexpectedRelFromTransport)
{
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh, "TCOM/RLH/CCHH/HSCH")));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw, "TRSW/Transport")));
    Dsp& dsp(*dynamic_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "DSP")));

    umlLogger.logNoteOnComponents(ComponentNames{ComponentName::TupcCm, ComponentName::Trsw}, "TupcCm receives REL from TRSW/Transport");

    sendMessage(ComponentName::TupcCm, ComponentName::TupcTbm, createOneTransportBearerCmUpdateReleaseFromTransport());
    umlLogger.logNoteOnPreviousMessage("TupcCm sends TUPC_CM_BEARERS_UPDATE_IND_MSG with **ECmBearersUpdateTransactionType_ReleasedFromTransport**");
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

/*TEST_F(ModuleTest, TransportChannelReset)
{
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    TcomToam& tcomToam(*dynamic_cast<TcomToam*>(getComponentAndActivateAsParticipant(ComponentName::TcomToam, "TCOM/TOAM")));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));

    umlLogger.logNoteOnComponents(ComponentNames{ComponentName::TupcCm, ComponentName::Trsw}, "TupcCm receives REL from TRSW/Transport");

    sendMessage(ComponentName::TupcCm, ComponentName::TupcTbm, createOneTransportBearerCmUpdateReleaseFromTransport());
    umlLogger.logNoteOnPreviousMessage("TupcCm sends TUPC_CM_BEARERS_UPDATE_IND_MSG with **ECmBearersUpdateTransactionType_ReleasedFromTransport**");
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}*/
