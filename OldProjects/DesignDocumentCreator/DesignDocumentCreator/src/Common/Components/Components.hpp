#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

#include <map>
#include <memory>

namespace DesignDocumentCreator {

// Make this noncopyable

class Components {
public:
    using ComponentMap = std::map<ComponentName, std::unique_ptr<Component>>;
    Components();
    Components(Components const& components) = delete;
    Components& operator=(Components const& components) = delete;
    Component* getComponentPointer(ComponentName const componentName);
    Component& getComponentReference(ComponentName const componentName);
    ComponentMap& getComponentMapReference();
    bool isComponentExisting(ComponentName const componentName);
    void executePendingEvents();

private:
    void executePendingEventsUsingRoundRobin();
    void executeAllPendingEventsPerComponent();
    ComponentMap m_componentsMap;
};

}  // namespace DesignDocumentCreator
