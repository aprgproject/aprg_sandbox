#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Components/Component.hpp>
#include <map>
#include <memory>

namespace DesignDocumentCreator
{

//Make this noncopyable

class Components
{
public:
    Components();
    Components(Components const& components) = delete;
    Components& operator=(Components const& components) = delete;
    Component* getComponentPointer(ComponentName const componentName);
    bool isComponentExisting(ComponentName const componentName);
    void executePendingEvents();

private:
    void executePendingEventsUsingRoundRobin();
    void executeAllPendingEventsPerComponent();
    using ComponentMap = std::map<ComponentName, std::unique_ptr<Component>>;
    ComponentMap m_components;
};

}
