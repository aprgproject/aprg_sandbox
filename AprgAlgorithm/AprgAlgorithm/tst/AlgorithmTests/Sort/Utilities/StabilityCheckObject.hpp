#pragma once

#include <ostream>

namespace alba
{

namespace algorithm
{

class StabilityCheckObject
{
public:
    StabilityCheckObject(char const visiblePart, unsigned int const notVisiblePart);

    bool operator==(StabilityCheckObject const& object) const;
    bool operator<(StabilityCheckObject const& object) const;
    char getVisiblePart() const;
    unsigned int getNotVisiblePart() const;

    friend std::ostream & operator<<(std::ostream & out, StabilityCheckObject const& object);

private:
    char m_visiblePart;
    unsigned int m_notVisiblePart;
};

}

}
