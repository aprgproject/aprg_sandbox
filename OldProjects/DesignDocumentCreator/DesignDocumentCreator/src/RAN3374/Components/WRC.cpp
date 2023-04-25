#include <Common/Utils/StringHelpers.hpp>
#include <RAN3374/Components/WRC.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator {

WRC::WRC() : m_componentName(ComponentName::EMPTY) {}

WRC::WRC(ComponentName const componentName) : m_componentName(componentName) {}

void WRC::handleMessageEvent(GenericMessage const& genericMessage) {
    MessageName messageName(genericMessage.getMessageName());
    switch (messageName) {
        case MessageName::TC_LTX_TELECOM_MSG:
            cout << "Handle Message, TC_LTX_TELECOM_MSG: \n";
        default:
            cout << "Handle Message, messageName: " << StringHelpers::genericMessage.getMessageNameInString() << "\n";
    }
}

void WRC::handleTimerEvent(Timer const& timer) {
    cout << "Handle Timer, timerType: " << StringHelpers::convertToString(timer.getType())
         << " timerId:" << (int)timer.getId() << "\n";
}

}  // namespace DesignDocumentCreator
