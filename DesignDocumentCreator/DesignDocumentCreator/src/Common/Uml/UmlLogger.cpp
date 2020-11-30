#include "UmlLogger.hpp"

#include <Common/Uml/UmlArrow.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <fstream>
#include <string>

using namespace std;
using namespace alba;

namespace DesignDocumentCreator
{

UmlLogger::UmlLogger()
{}

void UmlLogger::logMessage(string const& senderName, string const& receiverName, string const& messageName)
{
    m_umlLogBuffer<<senderName<<" "<<UmlArrow::getArrowBaseFromMessageName(messageName)<<" "<<receiverName<<" : "<<messageName<<endl;
}

void UmlLogger::addParticipant(UmlParticipant const& participant)
{
    m_participants.emplace_back(participant);
}

void UmlLogger::saveUmlLogsToFile(string const& filePath)
{
    AlbaLocalPathHandler pathHandler(filePath);
    ofstream outputFile(pathHandler.getFullPath());
    outputFile<<getUmlLogsForStart()<<endl;
    outputFile<<m_umlLogBuffer.str()<<endl;
    outputFile<<getUmlLogsForEnd()<<endl;
}

string UmlLogger::getUmlLogsForStart() const
{
    stringstream startStream;
    startStream<<"@startuml"<<endl;
    startStream<<"hide footbox"<<endl;
    for(UmlParticipant participant : m_participants)
    {
        startStream<<participant.getParticipantLog()<<endl;
    }
    return startStream.str();
}

string UmlLogger::getUmlLogsForEnd() const
{
    stringstream endStream;
    endStream<<"@enduml"<<endl;
    return endStream.str();
}

}
