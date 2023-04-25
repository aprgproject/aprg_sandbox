#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <STCWamAddressInd.h>

namespace DesignDocumentCreator {

class Trsw : public Component {
public:
    Trsw(ComponentName const componentName);

private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
};

}  // namespace DesignDocumentCreator
