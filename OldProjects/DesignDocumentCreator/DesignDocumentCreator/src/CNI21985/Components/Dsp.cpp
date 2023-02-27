#include "Dsp.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

Dsp::Dsp(ComponentName const componentName)
    : Component(componentName)
{}

void Dsp::handleTransportSetupReq(GenericMessage const& )
{
    //I am not coding DSP. :)
    sendTransportSetupResp();
}

void Dsp::handleTransportReleaseReq(GenericMessage const& )
{
    //I am not coding DSP. :)
    sendTransportReleaseResp();
}

void Dsp::handleTransportTransferReq(GenericMessage const& )
{
    //I am not coding DSP. :)
    sendTransportTransferResp();
}

void Dsp::sendTransportSetupResp() const
{
    SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_SETUP_RESP_MSG> specificMessage;
    send(ComponentName::TupcTbm, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("DSP sends TUP_TRANSPORT_CONNECTION_SETUP_RESP_MSG to TUPC/TBM.");
}

void Dsp::sendTransportReleaseResp() const
{
    SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG> specificMessage;
    send(ComponentName::TupcTbm, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("DSP sends TUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG to TUPC/TBM.");
}

void Dsp::sendTransportTransferResp() const
{
    SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_MSG> specificMessage;
    send(ComponentName::TupcTbm, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("DSP sends TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_MSG to TUPC/TBM.");
}

void Dsp::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG:
        handleTransportSetupReq(genericMessage);
        break;
    case MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG:
        handleTransportReleaseReq(genericMessage);
        break;
    case MessageName::TUP_TRANSPORT_CONNECTION_TRANSFER_REQ_MSG:
        handleTransportTransferReq(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<"\n";
    }
}

void Dsp::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<"\n";
}

}