#include "Lcg.hpp"

#include <iterator>

using namespace std;

namespace alba
{

Lcg::Lcg(unsigned int const lcgId, unsigned int const percentageShare)
    : m_lcgId(lcgId)
    , m_percentageShare(percentageShare)
{}

bool Lcg::operator<(Lcg const& lcg) const
{
    return m_lcgId < lcg.m_lcgId;
}

unsigned int Lcg::getLcgId() const
{
    return m_lcgId;
}

unsigned int Lcg::getPercentageShare() const
{
    return m_percentageShare;
}


}
