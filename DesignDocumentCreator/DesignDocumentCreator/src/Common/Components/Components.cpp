#include <Common/Components/Components.hpp>
#include <Common/Components/SampleComponent.hpp>
#include <FeatureSpecificFiles/ComponentsIncludes.hpp>

using namespace std;

namespace DesignDocumentCreator
{

Components::Components()
{
#define COMPONENT_NAME_MACRO(COMPONENT_NAME) m_components[ComponentName:: COMPONENT_NAME].reset(new COMPONENT_NAME(ComponentName:: COMPONENT_NAME));
    COMPONENT_NAME_MACRO(SampleComponent)
    #include <FeatureSpecificFiles/ComponentNameMacro.hpp>
#undef COMPONENT_NAME_MACRO
}

Component* Components::getComponentPointer(ComponentName const componentName)
{
    if(isComponentExisting(componentName))
    {
        return m_components[componentName].get();
    }
    return nullptr;
}

bool Components::isComponentExisting(ComponentName const componentName)
{
    return m_components.find(componentName) != m_components.end();
}

void Components::executePendingEvents()
{
    executePendingEventsUsingRoundRobin();
}

void Components::executePendingEventsUsingRoundRobin()
{
    bool isNotChanged(true);
    while(isNotChanged)
    {
        isNotChanged = false;
        for(ComponentMap::iterator componentIterator = m_components.begin(); componentIterator != m_components.end(); componentIterator++)
        {
            Component* componentPointer((componentIterator->second).get());
            if(!componentPointer->isEventQueueEmpty())
            {
                isNotChanged=true;
                componentPointer->handleOneEvent();
            }
        }
    }
}

void Components::executeAllPendingEventsPerComponent()
{
    for(ComponentMap::iterator componentIterator = m_components.begin(); componentIterator != m_components.end(); componentIterator++)
    {
        Component* componentPointer((componentIterator->second).get());
        if(!componentPointer->isEventQueueEmpty())
        {
            componentPointer->handleAllEvents();
        }
    }
}

}
