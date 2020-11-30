#pragma once

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
    void saveUmlLogsToFile(std::string const& filePath);

private:
    std::string getUmlLogsForStart() const;
    std::string getUmlLogsForEnd() const;
    std::stringstream m_umlLogBuffer;
    UmlParticipants m_participants;
};

}
