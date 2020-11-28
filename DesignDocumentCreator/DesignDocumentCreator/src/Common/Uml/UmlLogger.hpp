#pragma once

#include <string>

namespace DesignDocumentCreator
{

class UmlLogger
{
public:
    UmlLogger();
    void logMessage(std::string const& senderName, std::string const& receiverName, std::string const& messageName);
private:
    std::string m_umlLogBuffer;
    std::string m_filePath;
};

}
