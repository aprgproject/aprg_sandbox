#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class TupcLom : public Component
{
public:
    TupcLom();
    TupcLom(ComponentName const componentName);
    void handleHwConfiguration(GenericMessage const& genericMessage);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    TAaSysComSicad m_oamAddress;
};

}
