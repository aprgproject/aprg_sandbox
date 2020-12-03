#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class TupcCm : public Component
{
public:
    TupcCm(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);    virtual void handleTimerEvent(Timer const& timer);
};

}