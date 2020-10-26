#include <Common/Utils/StringHelpers.hpp>
#include <RAN3374/Components/Rake.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

Rake::Rake()
    : m_componentName(ComponentName::EMPTY)
{}

Rake::Rake(ComponentName const componentName)
    : m_componentName(componentName)
{}

void Rake::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_LTX_TELECOM_MSG:
        cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"Handle Message, messageName: "<<StringHelpers::convertToString(genericMessage.getMessageName())<<endl;
    }
}

void Rake::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<StringHelpers::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}


