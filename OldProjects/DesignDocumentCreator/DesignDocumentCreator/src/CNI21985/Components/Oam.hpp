#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class Oam : public Component {
public:
    Oam(ComponentName const componentName);

private:
    void handleHwConfigurationMessageResponse(GenericMessage const& genericMessage) const;
    void handleLinkStatesResponse(GenericMessage const& genericMessage) const;

    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
};

}  // namespace DesignDocumentCreator
