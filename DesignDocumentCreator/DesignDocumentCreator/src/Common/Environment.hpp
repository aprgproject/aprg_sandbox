#pragma once

#include <Common/Components/Components.hpp>

namespace DesignDocumentCreator
{
//singleton?

class Environment{
public:
    void execute();
    Components& getComponentReference();
    void send(ComponentName const sender, ComponentName const receiver, GenericMessage const& message);


private:
    Components m_components;
};

}
