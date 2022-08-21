#pragma once

#include <Math/NumberTheory/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

using PythagoreanTriple = std::tuple<UnsignedNumber, UnsignedNumber, UnsignedNumber>; //{a,b,c}

bool isPythagoreanTriple(PythagoreanTriple const& triple);
bool isPrimitive(PythagoreanTriple const& triple);

PythagoreanTriple getNewPythagoreanTripleUsingMultiplier(PythagoreanTriple const& triple, UnsignedNumber const multiplier);
PythagoreanTriple getPrimitivePythagoreanTripleUsingEuclidFormula(UnsignedNumber const seedValueM, UnsignedNumber const seedValueN);

}

}
