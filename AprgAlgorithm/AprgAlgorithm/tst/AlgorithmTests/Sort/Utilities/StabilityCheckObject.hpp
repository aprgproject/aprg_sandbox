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
    StabilityCheckObject operator+(StabilityCheckObject const& second) const;
    StabilityCheckObject operator-(StabilityCheckObject const& second) const;
    double operator*(double const multiplier) const; // needed for bucket sort
    char getVisiblePart() const;
    unsigned int getNotVisiblePart() const;

    friend double operator/(double const dividend, StabilityCheckObject const& divisor); // needed for bucket sort
    friend std::ostream & operator<<(std::ostream & out, StabilityCheckObject const& object);

private:
    char m_visiblePart;
    unsigned int m_notVisiblePart;
};

}

}
