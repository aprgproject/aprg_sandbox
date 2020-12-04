#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Uml/UmlParticipant.hpp>

#include <sstream>
#include <string>
#include <vector>

namespace DesignDocumentCreator
{

class UmlLogger
{
public:
    using UmlParticipants = std::vector<UmlParticipant>;
    UmlLogger();
    void logMessage(std::string const& senderName, std::string const& receiverName, std::string const& messageName);
    void addParticipant(UmlParticipant const& participant);
    void logNoteOnPreviousMessage(std::string const& note);
    void logNoteOnComponent(ComponentName const componentName, std::string const& note);
    void logNoteOnComponents(ComponentNames const componentName, std::string const& note);
    void logNote(std::string const& note);
    void saveUmlLogsToFile(std::string const& filePath);
    
private:
    std::string getUmlLogsForStart() const;
    std::string getUmlLogsForEnd() const;
    std::stringstream m_umlLogBuffer;
    UmlParticipants m_participants;
};

}
