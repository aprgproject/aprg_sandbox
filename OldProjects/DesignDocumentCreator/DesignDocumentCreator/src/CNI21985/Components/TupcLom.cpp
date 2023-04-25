#include "TupcLom.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <FakeFramework/FakeFrameworkHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator {

TupcLom::TupcLom(ComponentName const componentName) : Component(componentName) {}

void TupcLom::handleStartup() {
    logNoteOnComponent("TUPC/LOM **automatically**  starts when TUPCexe starts.\nThis is same with legacy.");
}

void TupcLom::handleHwConfigurationMessage(GenericMessage const& genericMessage) {
    Environment& environment(Environment::getInstance());
    logNoteOnPreviousMessage(
        "OAM sends this message to only one TUPC instance.\nThe receiver will be the location of TUPC/CM.");
    logNoteOnComponent("TUPC/LOM saves hardware configuration.");
    saveAddresses(genericMessage);
    logNoteOnComponents(
        ComponentNames{ComponentName::TupcLom, ComponentName::TupcCm}, "TUPC/LOM starts TUPC/CM on the same location.");
    environment.getComponentPointer(ComponentName::TupcCm)
        ->pushBackEvent(Event(OtherEvent(OtherEventType::SubProcessStartup)));
}

void TupcLom::saveAddresses(GenericMessage const& genericMessage) {
    logNoteOnComponent(
        "TUPC/LOM saves the addresses based from the sender and receiver of this message.\n"
        "The receiver of this message is the address of TUPC/CM and this address will be the only active TUPC/LOM "
        "instance and TUPC/CM instance.\n"
        "The sender of this message is the address of OAM and this as the address of TUPC/ILM as well.\n");
    SpecificStaticMessage<MessageName::OAM_ATM_HW_CONFIGURATION_MSG> hwConfigurationMessage(
        convertGenericToSpecificStatic<MessageName::OAM_ATM_HW_CONFIGURATION_MSG>(genericMessage));
    TAaSysComSicad senderSicad(FakeFrameworkHelpers::getAddress(hwConfigurationMessage.getSender()));
    TAaSysComSicad receiverSicad(FakeFrameworkHelpers::getAddress(hwConfigurationMessage.getReceiver()));
    m_oamAddress = senderSicad;
    m_tupcIlmAddress = FakeFrameworkHelpers::createSicad(
        FakeFrameworkHelpers::getNid(senderSicad), FakeFrameworkHelpers::getTask(ComponentName::TupcIlm));
    m_tupcCmAddress = FakeFrameworkHelpers::createSicad(
        FakeFrameworkHelpers::getNid(receiverSicad), FakeFrameworkHelpers::getTask(ComponentName::TupcCm));
}

void TupcLom::handleTcomDeploymentMessage(GenericMessage const& genericMessage) {
    SpecificStaticMessage<MessageName::TC_TCOM_DEPLOYMENT_IND_MSG> message(
        convertGenericToSpecificStatic<MessageName::TC_TCOM_DEPLOYMENT_IND_MSG>(genericMessage));
    STcomDeploymentIndMsg const& payload(message.getStaticPayloadReference());
    logNoteOnComponent(
        "TUPC/LOM determines TUPC/TBM instances based from RLH instances from TC_TCOM_DEPLOYMENT_IND_MSG");
    FakeFrameworkHelpers::TAaSysComNids rlhNids(FakeFrameworkHelpers::getRlhNids(payload.wamAddressInd));
    log("loop For all RLH instances");
    for (TAaSysComNid const rlhNid : rlhNids) {
        TAaSysComSicad tupcTbmAddress(
            FakeFrameworkHelpers::createSicad(rlhNid, FakeFrameworkHelpers::getTask(ComponentName::TupcTbm)));
        sendTupcTbmConfigurationMsg(tupcTbmAddress);
    }
    log("end loop");
}

void TupcLom::sendTupcTbmConfigurationMsg(TAaSysComSicad const) const {
    SpecificStaticMessage<MessageName::TUPC_TBM_CONFIGURATION_MSG> specificMessage;
    STupcTbmConfigurationMsg& payload(specificMessage.getStaticPayloadReference());
    payload.tupcCmSicad = m_tupcCmAddress;
    send(ComponentName::TupcTbm, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/LOM sends TUPC_TBM_CONFIGURATION_MSG to TUPC/TBM.");
}

void TupcLom::handleMessageEvent(GenericMessage const& genericMessage) {
    MessageName messageName(genericMessage.getMessageName());
    switch (messageName) {
        case MessageName::OAM_ATM_HW_CONFIGURATION_MSG:
            handleHwConfigurationMessage(genericMessage);
            break;
        case MessageName::TC_TCOM_DEPLOYMENT_IND_MSG:
            handleTcomDeploymentMessage(genericMessage);
            break;
        default:
            cout << "No handler for messageName: " << genericMessage.getMessageNameInString()
                 << " in component: " << getComponentNameInString() << "\n";
            break;
    }
}

void TupcLom::handleTimerEvent(Timer const& timer) {
    cout << "Handle Timer, timerType: " << convertToString(timer.getType()) << " timerId:" << (int)timer.getId()
         << "\n";
}

void TupcLom::handleOtherEvent(OtherEvent const& otherEvent) {
    switch (otherEvent.getType()) {
        case OtherEventType::MainProcessStartup:
            handleStartup();
            break;
        default:
            cout << "No handler for handleOtherEvent \n";
            break;
    }
}

/*
    //TUP_TbmConfigurationCmd //new message for TBM?
    //rename all of this shit.
    //const TMessageId TUP_CmConfigurationCmd_Msg = ATM_MESSAGE_BASE + 0x0118;
    //const TMessageId TUP_CmConfigurationResp_Msg = ATM_MESSAGE_BASE + 0x0119;
    //const TMessageId TUP_FspInfoUpdatedInd_Msg = ATM_MESSAGE_BASE + 0x011A;
    //const TMessageId TUP_FspInfoUpdatedIndResp_Msg = ATM_MESSAGE_BASE + 0x011B;
*/
}  // namespace DesignDocumentCreator
