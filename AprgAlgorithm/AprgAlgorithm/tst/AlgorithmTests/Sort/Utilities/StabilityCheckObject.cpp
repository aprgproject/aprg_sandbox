#include "StabilityCheckObject.hpp"

#include <sstream>

using namespace std;

namespace alba
{

namespace algorithm
{

StabilityCheckObject::StabilityCheckObject(
        char const visiblePart,
        unsigned int const notVisiblePart)
    : m_visiblePart(visiblePart)
    , m_notVisiblePart(notVisiblePart)
{}

bool StabilityCheckObject::operator==(
        StabilityCheckObject const& object) const
{
    return m_visiblePart == object.m_visiblePart && m_notVisiblePart == object.m_notVisiblePart;
}

bool StabilityCheckObject::operator<(
        StabilityCheckObject const& object) const
{
    return m_visiblePart < object.m_visiblePart;
}

char StabilityCheckObject::getVisiblePart() const
{
    return m_visiblePart;
}

unsigned int StabilityCheckObject::getNotVisiblePart() const
{
    return m_notVisiblePart;
}

ostream & operator<<(ostream & out, StabilityCheckObject const& object)
{
    out << "(" << object.m_visiblePart << object.m_notVisiblePart << ")";
    return out;
}

}

}
