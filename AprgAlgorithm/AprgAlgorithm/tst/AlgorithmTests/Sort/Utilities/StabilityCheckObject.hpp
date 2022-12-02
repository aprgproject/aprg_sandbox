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
    StabilityCheckObject(int const value);

    bool operator==(StabilityCheckObject const& object) const;
    bool operator!=(StabilityCheckObject const& object) const;
    bool operator<(StabilityCheckObject const& object) const;
    operator int() const;
    StabilityCheckObject operator+(StabilityCheckObject const& second) const;
    StabilityCheckObject operator-(StabilityCheckObject const& second) const;
    StabilityCheckObject operator+(int const second) const;
    StabilityCheckObject operator-(int const second) const;
    double operator*(double const multiplier) const;

    char getVisiblePart() const;
    unsigned int getNotVisiblePart() const;

    friend double operator/(double const dividend, StabilityCheckObject const& divisor);
    friend bool areObjectsEqualOnVisibleAndNotVisiblePart(StabilityCheckObject const& object1, StabilityCheckObject const& object2);
    friend std::ostream & operator<<(std::ostream & out, StabilityCheckObject const& object);

private:    char m_visiblePart;
    unsigned int m_notVisiblePart;
};

bool areObjectsEqualOnVisibleAndNotVisiblePart(StabilityCheckObject const& object1, StabilityCheckObject const& object2);

}

}