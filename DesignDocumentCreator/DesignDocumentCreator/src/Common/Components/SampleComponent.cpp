#include <Common/Components/SampleComponent.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

SampleComponent::SampleComponent()
    : m_componentName(ComponentName::EMPTY)
{}

SampleComponent::SampleComponent(ComponentName const componentName)
    : m_componentName(componentName)
{}

void SampleComponent::handleMessageEvent(GenericMessage const& genericMessage)
{
    cout<<"Handle Message, messageName: "<<StringHelpers::convertToString(genericMessage.getMessageName())<<endl;
}

void SampleComponent::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<StringHelpers::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
