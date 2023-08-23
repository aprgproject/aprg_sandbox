#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class TupcIlm : public Component {
public:
    TupcIlm(ComponentName const componentName);

private:
    void handleStartup();
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);
};

}  // namespace DesignDocumentCreator
