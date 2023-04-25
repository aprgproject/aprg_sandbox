#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class TOAM : public Component {
public:
    TOAM(ComponentName const componentName);

private:
    void handleMessage1(GenericMessage const& genericMessage);
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    void handleOtherEvent(OtherEvent const& otherEvent) override;
};

}  // namespace DesignDocumentCreator
