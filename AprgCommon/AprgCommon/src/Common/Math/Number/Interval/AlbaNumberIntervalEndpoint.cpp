#include "AlbaNumberIntervalEndpoint.hpp"

#include <Common/Macros/AlbaMacros.hpp>

using namespace std;

namespace alba
{

AlbaNumberIntervalEndpoint::AlbaNumberIntervalEndpoint(
        AlbaNumberIntervalEndpoint::Type const type,
        AlbaNumber const value)
    : m_type(type)
    , m_value(value)
{}

bool AlbaNumberIntervalEndpoint::operator==(AlbaNumberIntervalEndpoint const& second) const
{
    return m_type==second.m_type
            && m_value==second.m_value;
}

bool AlbaNumberIntervalEndpoint::isOpen() const
{
    return Type::Open==m_type;
}

bool AlbaNumberIntervalEndpoint::isClose() const
{
    return Type::Close==m_type;
}

AlbaNumberIntervalEndpoint::Type AlbaNumberIntervalEndpoint::getType() const
{
    return m_type;
}

AlbaNumber const& AlbaNumberIntervalEndpoint::getValue() const
{
    return m_value;
}

string AlbaNumberIntervalEndpoint::getTypeString() const
{
    switch(m_type)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(Type::Open, "Open")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(Type::Close, "Close")
            default:
        return "default";
    }
}

void AlbaNumberIntervalEndpoint::setType(Type const type)
{
    m_type = type;
}

ostream & operator<<(ostream & out, AlbaNumberIntervalEndpoint const& endpoint)
{
    out << "(" << endpoint.getTypeString() << "," << endpoint.m_value << ")";
    return out;
}

}
