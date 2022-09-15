#pragma once

#include <Math/Types.hpp>

namespace alba
{

namespace math
{

UnsignedInteger getUnionCountOfTwoSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const abIntersection);

UnsignedInteger getIntersectionCountOfTwoSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const abUnion);

UnsignedInteger getUnionCountOfThreeSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const cSize,
        UnsignedInteger const abIntersection,
        UnsignedInteger const bcIntersection,
        UnsignedInteger const acIntersection,
        UnsignedInteger const abcIntersection);

UnsignedInteger getIntersectionCountOfThreeSets(
        UnsignedInteger const aSize,
        UnsignedInteger const bSize,
        UnsignedInteger const cSize,
        UnsignedInteger const abIntersection,
        UnsignedInteger const bcIntersection,
        UnsignedInteger const acIntersection,
        UnsignedInteger const abcUnion);

}

}
