#include "TupcLom.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Utils/AddressHelper.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcLom::TupcLom(ComponentName const componentName)
    : Component(componentName)
{}

void TupcLom::handleStartup()
{
    logNoteOnComponent("TupcLom is **automatically**  starts when TUPCexe starts.\nThis is same with legacy.");
}

void TupcLom::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
        case MessageName::OAM_ATM_HW_CONFIGURATION_MSG:
            handleHwConfiguration(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<endl;
        break;
    }
}

void TupcLom::handleHwConfiguration(GenericMessage const& genericMessage)
{
    Environment & environment(Environment::getInstance());

    SpecificStaticMessage<MessageName::OAM_ATM_HW_CONFIGURATION_MSG> hwConfigurationMessage(convertGenericToSpecificStatic<MessageName::OAM_ATM_HW_CONFIGURATION_MSG>(genericMessage));
    //SAtmHwConfigurationMsgFake& payload(hwConfigurationMessage.getPayloadReference());
    logNoteOnPreviousMessage("OAM sends OAM_ATM_HW_CONFIGURATION_MSG to a one TUPC instance.\nThe receiver will be the location of TupcCm.");
    logNoteOnComponent("TupcLom saves hardware configuration.\nThe receiver of this message is the only active TupcLom instance.\nTupcLom saves the address of OAM (sender address).\nTupcLom saves this as the address of TupcIlm as well.");
    m_oamAddress = AddressHelper::getAddress(hwConfigurationMessage.getSender());
    logNoteOnComponents(ComponentNames{ComponentName::TupcLom, ComponentName::TupcCm}, "TupcLom starts TupcCm on the same location.");
    environment.getComponentPointer(ComponentName::TupcCm)->pushBackEvent(Event(OtherEvent(OtherEventType::SubProcessStartup)));
}

void TupcLom::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

void TupcLom::handleOtherEvent(OtherEvent const& otherEvent)
{
   switch(otherEvent.getType())
   {
   case OtherEventType::MainProcessStartup:
       handleStartup();
       break;
   default:
       cout<<"No handler for handleOtherEvent "<<endl;
       break;
   }
}

}
