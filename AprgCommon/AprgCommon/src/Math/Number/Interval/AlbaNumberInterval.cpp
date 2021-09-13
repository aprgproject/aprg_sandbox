#include "AlbaNumberInterval.hpp"

#include <sstream>

using namespace std;

namespace alba
{

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

ostream & operator<<(ostream & out, AlbaNumberInterval const& interval)
{
    out << interval.getDisplayableString();
    return out;
}

}
