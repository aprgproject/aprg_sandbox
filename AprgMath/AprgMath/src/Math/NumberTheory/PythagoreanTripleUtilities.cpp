#include "PythagoreanTripleUtilities.hpp"

#include <Common/Math/AlbaMathHelper.hpp>
#include <Math/NumberTheory/PrimeAndFactorUtilities.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

bool isPythagoreanTriple(PythagoreanTriple const& triple)
{
    // A Pythagorean triple is a triple (a,b, c) that satisfies the Pythagorean theorem a^2 + b^2 = c^2,
    // which means that there is a right triangle with side lengths a, b and c.

    return get<0>(triple)*get<0>(triple) + get<1>(triple)*get<1>(triple) == get<2>(triple)*get<2>(triple);
}

bool isPrimitive(PythagoreanTriple const& triple)
{
    // A Pythagorean triple is primitive if a, b and c are coprime,
    // and all Pythagorean triples can be constructed from primitive triples using a multiplier k.

    UnsignedNumber gcfOfABC = getGreatestCommonFactor(getGreatestCommonFactor(get<0>(triple), get<1>(triple)), get<2>(triple));
    return gcfOfABC == 1;
}

PythagoreanTriple getNewPythagoreanTripleUsingMultiplier(PythagoreanTriple const& triple, UnsignedNumber const multiplier)
{
    // If (a,b,c) is a Pythagorean triple, all triples of the form (ka,kb,kc) are also Pythagorean triples where k > 1.

    PythagoreanTriple result;
    if(multiplier > 1)
    {
        result = triple;
        get<0>(result) *= multiplier;
        get<1>(result) *= multiplier;
        get<2>(result) *= multiplier;
    }
    return result;
}

PythagoreanTriple getPrimitivePythagoreanTripleUsingEuclidFormula(UnsignedNumber const seedValueM, UnsignedNumber const seedValueN)
{
    // Euclid’s formula can be used to produce ALL primitive Pythagorean triples.
    // Each such triple is of the form (n^2 - m^2, 2*n*m, n^2 + m^2),
    // where 0<m<n, n and m are coprime and at least one of n and m is even.

    // For example, when m=1 and n=2, the formula produces the SMALLEST Pythagorean triple (4-1,2*2*1,4+1) = (3,4,5).

    PythagoreanTriple result;
    if(0<seedValueM && seedValueM<seedValueN
            && isCoPrime(seedValueM, seedValueN)
            && (isEven(seedValueM) || isEven(seedValueN)))
    {
        UnsignedNumber mSquared = seedValueM*seedValueM;
        UnsignedNumber nSquared = seedValueN*seedValueN;
        result = PythagoreanTriple{nSquared-mSquared, 2*seedValueN*seedValueM, nSquared+mSquared};
    }
    return result;
}

}

}
