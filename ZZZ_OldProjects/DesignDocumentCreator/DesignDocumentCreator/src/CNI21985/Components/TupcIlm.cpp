#include "TupcIlm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator {

TupcIlm::TupcIlm(ComponentName const componentName) : Component(componentName) {}

void TupcIlm::handleStartup() {
    logNoteOnComponent(
        "TupcIlm **starts_only**  when its deployed on board 0x10 or 0x20(for FSM r4).\nThis is same with legacy "
        "Aalman.");
    /*if(AaSysComNmapGetBoard(sicad) == FSM1_FCT || AaSysComNmapGetBoard(sicad) == FSM2_FCT)
    {
        StartAalman();
    }*/
}

void TupcIlm::handleMessageEvent(GenericMessage const& genericMessage) {
    MessageName messageName(genericMessage.getMessageName());
    switch (messageName) {
        default:
            cout << "No handler for messageName: " << genericMessage.getMessageNameInString()
                 << " in component: " << getComponentNameInString() << "\n";
    }
}

void TupcIlm::handleTimerEvent(Timer const& timer) {
    cout << "Handle Timer, timerType: " << convertToString(timer.getType()) << " timerId:" << (int)timer.getId()
         << "\n";
}

void TupcIlm::handleOtherEvent(OtherEvent const& otherEvent) {
    switch (otherEvent.getType()) {
        case OtherEventType::MainProcessStartup:
            handleStartup();
            break;
        default:
            cout << "No handler for handleOtherEvent \n";
            break;
    }
}

}  // namespace DesignDocumentCreator
