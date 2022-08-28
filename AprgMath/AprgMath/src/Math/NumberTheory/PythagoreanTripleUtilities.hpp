#pragma once

#include <Math/Types.hpp>

namespace alba
{

namespace math
{

using PythagoreanTriple = std::tuple<UnsignedInteger, UnsignedInteger, UnsignedInteger>; //{a,b,c}

bool isPythagoreanTriple(PythagoreanTriple const& triple);
bool isPrimitive(PythagoreanTriple const& triple);

PythagoreanTriple getNewPythagoreanTripleUsingMultiplier(PythagoreanTriple const& triple, UnsignedInteger const multiplier);
PythagoreanTriple getPrimitivePythagoreanTripleUsingEuclidFormula(UnsignedInteger const seedValueM, UnsignedInteger const seedValueN);

}

}
