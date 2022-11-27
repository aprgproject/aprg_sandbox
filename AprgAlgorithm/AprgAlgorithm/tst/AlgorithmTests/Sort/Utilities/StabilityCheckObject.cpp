#include "StabilityCheckObject.hpp"

#include <sstream>

using namespace std;

namespace alba
{

namespace algorithm
{

StabilityCheckObject::StabilityCheckObject(
        char const partOfLessThan,
        unsigned int const notPartOfLessThan)
    : m_partOfLessThan(partOfLessThan)
    , m_notPartOfLessThan(notPartOfLessThan)
{}

bool StabilityCheckObject::operator==(
        StabilityCheckObject const& object) const
{
    return m_partOfLessThan == object.m_partOfLessThan && m_notPartOfLessThan == object.m_notPartOfLessThan;
}

bool StabilityCheckObject::operator<(
        StabilityCheckObject const& object) const
{
    return m_partOfLessThan < object.m_partOfLessThan;
}

char StabilityCheckObject::getPartOfLessThan() const
{
    return m_partOfLessThan;
}

unsigned int StabilityCheckObject::getNotPartOfLessThan() const
{
    return m_notPartOfLessThan;
}

ostream & operator<<(ostream & out, StabilityCheckObject const& object)
{
    out << "(" << object.m_partOfLessThan << object.m_notPartOfLessThan << ")";
    return out;
}

}

}
