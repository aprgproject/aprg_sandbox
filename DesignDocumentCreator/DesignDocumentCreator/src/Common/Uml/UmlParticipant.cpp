#include "UmlParticipant.hpp"

#include <String/AlbaStringHelper.hpp>

#include <string>

using namespace alba;
using namespace std;

namespace DesignDocumentCreator
{

UmlParticipant::UmlParticipant(UmlParticipantType const type, string const& name, std::string const& alias)
    : m_type(type)
    , m_name(name)
    , m_alias(alias)
{}

string UmlParticipant::getParticipantLog() const
{
    return getParticipantTypeString() + " " + m_name + " as " + m_alias;
}

string UmlParticipant::getParticipantTypeString() const
{
        string result;
        switch(m_type)
        {
#define GET_ENUM_STRING(en) case en: result = #en; break;
        GET_ENUM_STRING(UmlParticipantType::actor)
                GET_ENUM_STRING(UmlParticipantType::boundary)
                GET_ENUM_STRING(UmlParticipantType::control)
                GET_ENUM_STRING(UmlParticipantType::entity)
                GET_ENUM_STRING(UmlParticipantType::database)
                GET_ENUM_STRING(UmlParticipantType::participant)
#undef GET_ENUM_STRING
        }
        return stringHelper::getStringAfterThisString(result, "UmlParticipantType::");
}

}
