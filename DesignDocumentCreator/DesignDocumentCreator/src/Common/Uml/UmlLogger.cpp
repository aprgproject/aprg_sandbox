#include "UmlLogger.hpp"

#include <Common/Uml/UmlArrow.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <math/AlbaMathHelper.hpp>

#include <fstream>
#include <iostream>
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

void UmlLogger::logNoteOnPreviousMessage(std::string const& note)
{
    m_umlLogBuffer<<"note right"<<endl;
    logNote(note);
    m_umlLogBuffer<<"end note"<<endl;
}

void UmlLogger::logNoteOnComponent(ComponentName const componentName, std::string const& note)
{
    m_umlLogBuffer<<"rnote over "<<StringHelpers::convertToString(componentName)<<" #white"<<endl;
    logNote(note);
    m_umlLogBuffer<<"end note"<<endl;
}

void UmlLogger::logNoteOnComponents(ComponentNames const componentNames, std::string const& note)
{
    m_umlLogBuffer<<"rnote over "<<StringHelpers::convertToString(componentNames)<<" #white"<<endl;
    logNote(note);
    m_umlLogBuffer<<"end note"<<endl;
}

void UmlLogger::logNote(std::string const& note)
{
    stringHelper::strings linesInNote;
    stringHelper::strings linesInNoteWithTargetLength;
    stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(linesInNote, note, "\n");
    unsigned int optimizedTargetLength(getOptimizedTargetLength(linesInNote));
    for(string const& lineInNote: linesInNote)
    {
        stringHelper::splitLinesToAchieveTargetLength(linesInNoteWithTargetLength, lineInNote, optimizedTargetLength);
    }
    for(string const& line: linesInNoteWithTargetLength)
    {
        m_umlLogBuffer<<line<<endl;
    }
}

void UmlLogger::saveUmlLogsToFile(string const& filePath)
{
    AlbaLocalPathHandler pathHandler(filePath);
    ofstream outputFile(pathHandler.getFullPath());
    cout<<"Uml logs saved to file: "<<pathHandler.getFullPath()<<endl;
    if(outputFile.is_open())
    {
        outputFile<<getUmlLogsForStart()<<endl;
        outputFile<<m_umlLogBuffer.str()<<endl;
        outputFile<<getUmlLogsForEnd()<<endl;
    }
}

unsigned int UmlLogger::getOptimizedTargetLength(stringHelper::strings const& linesInNote)
{
    unsigned int targetLengthWithSmallestDifference=20;
    unsigned int smallestDifference=50;
    for(unsigned int targetLength=20; targetLength<60; targetLength++)
    {
        unsigned int totalDifference(0);
        for(string const& lineInNote: linesInNote)
        {
            totalDifference+=mathHelper::getDifferenceFromGreaterMultiple(targetLength, lineInNote.length());
        }
        if(smallestDifference>totalDifference)
        {
            smallestDifference = totalDifference;
            targetLengthWithSmallestDifference = targetLength;
        }
    }
    return targetLengthWithSmallestDifference;
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
