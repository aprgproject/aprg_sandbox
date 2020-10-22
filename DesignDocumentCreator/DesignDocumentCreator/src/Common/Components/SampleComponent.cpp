#include <Common/Components/SampleComponent.hpp>
#include <Common/Utils/EnumHelper.hpp>
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
    cout<<"Handle Message, messageName: "<<EnumHelper::convertToString(genericMessage.getMessageName())<<endl;
}

void SampleComponent::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<EnumHelper::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
