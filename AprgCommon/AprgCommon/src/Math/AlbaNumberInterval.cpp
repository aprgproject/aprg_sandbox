#include "AlbaNumberInterval.hpp"

#include <Macros/AlbaMacros.hpp>

#include <algorithm>
#include <sstream>

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

string AlbaNumberIntervalEndpoint::getDisplayableString() const
{
    stringstream result;
    result << "(" << getTypeString() << ", " << m_value << ")";
    return result.str();
}

void AlbaNumberIntervalEndpoint::setType(Type const type)
{
    m_type = type;
}

AlbaNumberInterval::AlbaNumberInterval(
        AlbaNumberIntervalEndpoint const& firstEndpoint,
        AlbaNumberIntervalEndpoint const& secondEndpoint)
    : m_lowerEndpoint(firstEndpoint)
    , m_higherEndpoint(secondEndpoint)
{
    if(m_lowerEndpoint.getValue() > m_higherEndpoint.getValue())
    {
        swap(m_lowerEndpoint, m_higherEndpoint);
    }
}

bool AlbaNumberInterval::operator==(AlbaNumberInterval const& second) const
{
    return m_lowerEndpoint==second.m_lowerEndpoint
            && m_higherEndpoint==second.m_higherEndpoint;
}

AlbaNumberIntervalEndpoint const& AlbaNumberInterval::getLowerEndpoint() const
{
    return m_lowerEndpoint;
}

AlbaNumberIntervalEndpoint const& AlbaNumberInterval::getHigherEndpoint() const
{
    return m_higherEndpoint;
}

string AlbaNumberInterval::getDisplayableString() const
{
    stringstream result;
    string startPrefix = m_lowerEndpoint.isOpen() ? "(" : "[";
    string endPostfix = m_higherEndpoint.isOpen() ? ")" : "]";
    result << startPrefix << m_lowerEndpoint.getValue() << ", " << m_higherEndpoint.getValue() << endPostfix;
    return result.str();
}

void AlbaNumberInterval::setNewEndpoint(AlbaNumberIntervalEndpoint const& endpoint)
{
    if(endpoint.getValue() < m_lowerEndpoint.getValue())
    {
        m_lowerEndpoint = endpoint;
    }
    else if(endpoint.getValue() > m_higherEndpoint.getValue())
    {
        m_higherEndpoint = endpoint;
    }
    else if(endpoint.getValue() == m_lowerEndpoint.getValue()
            && (endpoint.isClose() || m_lowerEndpoint.isClose()))
    {
        m_lowerEndpoint.setType(AlbaNumberIntervalEndpoint::Type::Close);
    }
    else if(endpoint.getValue() == m_higherEndpoint.getValue()
            && (endpoint.isClose() || m_higherEndpoint.isClose()))
    {
        m_higherEndpoint.setType(AlbaNumberIntervalEndpoint::Type::Close);
    }
}

ostream & operator<<(ostream & out, AlbaNumberIntervalEndpoint const& endpoint)
{
    out << endpoint.getDisplayableString();
    return out;
}

ostream & operator<<(ostream & out, AlbaNumberInterval const& interval)
{
    out << interval.getDisplayableString();
    return out;
}

AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint)
{
    return isCloseEndpoint ? AlbaNumberIntervalEndpoint::Type::Close : AlbaNumberIntervalEndpoint::Type::Open;
}

AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value)
{
    return AlbaNumberIntervalEndpoint(AlbaNumberIntervalEndpoint::Type::Open, value);
}

AlbaNumberIntervalEndpoint createCloseEndpoint(AlbaNumber const value)
{
    return AlbaNumberIntervalEndpoint(AlbaNumberIntervalEndpoint::Type::Close, value);
}

AlbaNumberIntervalEndpoint createEndpoint(
        bool const isCloseEndpoint,
        AlbaNumber const value)
{
    return AlbaNumberIntervalEndpoint(getEndpointTypeWithCheckingIfItsClosed(isCloseEndpoint), value);
}

AlbaNumberInterval createAllRealValuesInterval()
{
    return AlbaNumberInterval(
                createOpenEndpoint(AlbaNumber::Value::NegativeInfinity),
                createOpenEndpoint(AlbaNumber::Value::PositiveInfinity));
}

}
