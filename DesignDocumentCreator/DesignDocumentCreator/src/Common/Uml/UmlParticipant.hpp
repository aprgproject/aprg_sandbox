#pragma once

#include <string>

namespace DesignDocumentCreator
{

enum class UmlParticipantType
{
    actor,
    boundary,
    control,
    entity,
    database,
    participant
};

class UmlParticipant
{
public:
    UmlParticipant(std::string const& name, UmlParticipantType const type);
    std::string getParticipantLog() const;
    std::string getParticipantTypeString() const;
private:
    std::string m_name;
    UmlParticipantType m_type;
};


}
