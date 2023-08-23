#include <Common/Utils/StringHelpers.hpp>
#include <RAN3374/Components/TOAM.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator {

TOAM::TOAM() : m_componentName(ComponentName::EMPTY) {}

TOAM::TOAM(ComponentName const componentName) : m_componentName(componentName) {}

void TOAM::handleMessageEvent(GenericMessage const& genericMessage) {
    MessageName messageName(genericMessage.getMessageName());
    switch (messageName) {
        case MessageName::TC_LTX_TELECOM_MSG:
            cout << "Handle Message, TC_LTX_TELECOM_MSG: \n";
        default:
            cout << "Handle Message, messageName: " << StringHelpers::genericMessage.getMessageNameInString() << "\n";
    }
}

void TOAM::handleTimerEvent(Timer const& timer) {
    cout << "Handle Timer, timerType: " << StringHelpers::convertToString(timer.getType())
         << " timerId:" << (int)timer.getId() << "\n";
}

}  // namespace DesignDocumentCreator
