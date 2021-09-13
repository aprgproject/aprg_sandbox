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

bool AlbaNumberInterval::isValueInsideTheInterval(
        AlbaNumber const& value) const
{
    AlbaNumber const& lowerEndpointValue(m_lowerEndpoint.getValue());
    AlbaNumber const& higherEndpointValue(m_higherEndpoint.getValue());
    bool isInsideTheInterval = lowerEndpointValue < value && value < higherEndpointValue;
    bool isEqualToLowerCloseEndpoint = m_lowerEndpoint.isClose() && lowerEndpointValue == value;
    bool isEqualToHigherCloseEndpoint = m_higherEndpoint.isClose() && higherEndpointValue == value;
    return isInsideTheInterval || isEqualToLowerCloseEndpoint || isEqualToHigherCloseEndpoint;
}

bool AlbaNumberInterval::isValueInsideTheIntervalExceptAtTheEndpoints(
        AlbaNumber const& value) const
{
    return m_lowerEndpoint.getValue() < value && value < m_higherEndpoint.getValue();
}

bool AlbaNumberInterval::isEndpointInsideTheInterval(
        AlbaNumberIntervalEndpoint const& endpointToCheck) const
{
    bool result(false);
    AlbaNumber const& endPointValueToCheck(endpointToCheck.getValue());
    if(endpointToCheck.isOpen())
    {
        AlbaNumber const& lowerEndpointValue(m_lowerEndpoint.getValue());
        AlbaNumber const& higherEndpointValue(m_higherEndpoint.getValue());
        if(endPointValueToCheck == lowerEndpointValue || endPointValueToCheck == higherEndpointValue)
        {
            result = true;
        }
        else
        {
            result = isValueInsideTheIntervalExceptAtTheEndpoints(endPointValueToCheck);
        }
    }
    else if(endpointToCheck.isClose())
    {
        result = isValueInsideTheInterval(endPointValueToCheck);
    }
    return result;
}

bool AlbaNumberInterval::isIntervalInsideTheInterval(
        AlbaNumberInterval const& interval) const
{
    return isEndpointInsideTheInterval(interval.getLowerEndpoint())
            && isEndpointInsideTheInterval(interval.getHigherEndpoint());
}

AlbaNumberIntervalEndpoint const& AlbaNumberInterval::getLowerEndpoint() const
{
    return m_lowerEndpoint;}

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
