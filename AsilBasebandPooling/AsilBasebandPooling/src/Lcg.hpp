#pragma once

#include <set>
#include <vector>

namespace alba
{

class Lcg
{
public:
    Lcg(unsigned int const lcgId, unsigned int const percentageShare);
    bool operator<(Lcg const& lcg) const;
    unsigned int getLcgId() const;
    unsigned int getPercentageShare() const;

private:
    unsigned int m_lcgId;
    unsigned int m_percentageShare;
};

using LcgInitializerList = std::initializer_list<Lcg>;
using SetOfLcgs = std::set<Lcg>;
using VectorOfLcgs = std::vector<Lcg>;


}
