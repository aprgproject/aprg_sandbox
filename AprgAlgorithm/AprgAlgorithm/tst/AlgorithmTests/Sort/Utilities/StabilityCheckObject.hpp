#pragma once

#include <ostream>

namespace alba
{

namespace algorithm
{

class StabilityCheckObject
{
public:
    StabilityCheckObject(char const partOfLessThan, unsigned int const notPartOfLessThan);

    bool operator==(StabilityCheckObject const& object) const;
    bool operator<(StabilityCheckObject const& object) const;
    char getPartOfLessThan() const;
    unsigned int getNotPartOfLessThan() const;

    friend std::ostream & operator<<(std::ostream & out, StabilityCheckObject const& object);

private:
    char m_partOfLessThan;
    unsigned int m_notPartOfLessThan;
};

}

}
