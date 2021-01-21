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

TEST_F(ModuleTest, OneTransportBearerRegisterForCell)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm)));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw)));
    Dsp& dsp(*dynamic_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp)));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerUnregisterForCell)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm)));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw)));
    Dsp& dsp(*dynamic_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp)));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerUnregisterForCell());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationPrepareForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm)));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw)));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationPrepareForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationCommitForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm)));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw)));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationCommitForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationCancelForUser)
{
    TcomCchhRlh& tcomCchhRlh(*dynamic_cast<TcomCchhRlh*>(getComponentAndActivateAsParticipant(ComponentName::TcomCchhRlh)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm)));
    Trsw& trsw(*dynamic_cast<Trsw*>(getComponentAndActivateAsParticipant(ComponentName::Trsw)));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationCancelForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}
