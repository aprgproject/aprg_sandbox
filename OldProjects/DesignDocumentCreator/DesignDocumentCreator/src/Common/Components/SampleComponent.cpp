#include <Common/Components/SampleComponent.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

SampleComponent::SampleComponent(ComponentName const componentName)
    : Component(componentName)
{}

void SampleComponent::handleMessageEvent(GenericMessage const& genericMessage)
{
    cout<<"Handle Message, messageName: "<<genericMessage.getMessageNameInString()<<"\n";
}

void SampleComponent::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<"\n";
}

}