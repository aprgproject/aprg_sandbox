#include "InclusionExclusion.hpp"

using namespace std;

namespace alba
{

namespace math
{

UnsignedInteger getUnionCountOfTwoSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const abIntersection)
{
    return aSize + bSize - abIntersection;
}

UnsignedInteger getIntersectionCountOfTwoSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const abUnion)
{
    return aSize + bSize - abUnion;
}

UnsignedInteger getUnionCountOfThreeSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const cSize,
        UnsignedInteger const abIntersection,
        UnsignedInteger const bcIntersection,
        UnsignedInteger const acIntersection,
        UnsignedInteger const abcIntersection)
{
    return aSize + bSize + cSize - abIntersection - acIntersection  - bcIntersection+ abcIntersection;
}

UnsignedInteger getIntersectionCountOfThreeSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const cSize,
        UnsignedInteger const abIntersection,
        UnsignedInteger const bcIntersection,
        UnsignedInteger const acIntersection,
        UnsignedInteger const abcUnion)
{
    return abcUnion - aSize - bSize - cSize + abIntersection + acIntersection + bcIntersection;
}

}

}
