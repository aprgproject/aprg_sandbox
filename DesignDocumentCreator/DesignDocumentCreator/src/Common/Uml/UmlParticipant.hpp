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
    UmlParticipant(UmlParticipantType const type, std::string const& name, std::string const& alias);
    std::string getParticipantLog() const;
    std::string getParticipantTypeString() const;
private:
    UmlParticipantType m_type;
    std::string m_name;
    std::string m_alias;
};

}