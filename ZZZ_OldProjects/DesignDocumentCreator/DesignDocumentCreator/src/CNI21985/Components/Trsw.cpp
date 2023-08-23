#include "Trsw.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator {

Trsw::Trsw(ComponentName const componentName) : Component(componentName) {}

void Trsw::handleMessageEvent(GenericMessage const& genericMessage) {
    MessageName messageName(genericMessage.getMessageName());
    switch (messageName) {
        default:
            cout << "No handler for messageName: " << genericMessage.getMessageNameInString()
                 << " in component: " << getComponentNameInString() << "\n";
    }
}

void Trsw::handleTimerEvent(Timer const& timer) {
    cout << "Handle Timer, timerType: " << convertToString(timer.getType()) << " timerId:" << (int)timer.getId()
         << "\n";
}

}  // namespace DesignDocumentCreator
