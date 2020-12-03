#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class TupcTbm : public Component
{
public:
    TupcTbm(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);    virtual void handleTimerEvent(Timer const& timer);
};

}