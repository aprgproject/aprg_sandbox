#include <Common/Components/SampleComponent.hpp>

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{
SampleComponent::SampleComponent()
    : m_componentName(ComponentName::Empty)
{}

SampleComponent::SampleComponent(ComponentName const componentName)
    : m_componentName(componentName)
{}

void SampleComponent::handleMessageEvent(GenericMessage const& genericMessage)
{
    cout<<"Handle Message, messageName: "<<convertToString(genericMessage.getMessageName())<<endl;
}

void SampleComponent::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}