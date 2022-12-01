#include "StabilityCheckObject.hpp"

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

bool StabilityCheckObject::operator!=(
        StabilityCheckObject const& object) const
{
    return !operator==(object);
}

bool StabilityCheckObject::operator<(
        StabilityCheckObject const& object) const
{    return m_visiblePart < object.m_visiblePart;
}

StabilityCheckObject StabilityCheckObject::operator+(StabilityCheckObject const& second) const{
    return StabilityCheckObject(m_visiblePart+second.m_visiblePart, 0U);
}

StabilityCheckObject StabilityCheckObject::operator-(StabilityCheckObject const& second) const
{
    return StabilityCheckObject(m_visiblePart-second.m_visiblePart, 0U);
}

double StabilityCheckObject::operator*(double const multiplier) const
{
    return m_visiblePart*multiplier;
}

char StabilityCheckObject::getVisiblePart() const
{
    return m_visiblePart;
}

unsigned int StabilityCheckObject::getNotVisiblePart() const
{
    return m_notVisiblePart;
}

double operator/(double const dividend, StabilityCheckObject const& divisor)
{
    return dividend / divisor.m_visiblePart;
}

ostream & operator<<(ostream & out, StabilityCheckObject const& object)
{
    out << "(" << object.m_visiblePart << object.m_notVisiblePart << ")";
    return out;
}

}

}
