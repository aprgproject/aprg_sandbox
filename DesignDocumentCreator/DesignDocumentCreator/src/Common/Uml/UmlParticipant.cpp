#include "UmlParticipant.hpp"

#include <String/AlbaStringHelper.hpp>

#include <string>

using namespace alba;
using namespace std;

namespace DesignDocumentCreator
{

UmlParticipant::UmlParticipant(string const& name, UmlParticipantType const type)
    : m_name(name)
    , m_type(type)
{}

string UmlParticipant::getParticipantLog() const
{
    return getParticipantTypeString() + " " + m_name;
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
