#pragma once

#include <Math/Types.hpp>

namespace alba
{
namespace math
{
class ChineseRemainderTheorem
{
public:
    // The Chinese remainder theorem solves a group of equations of the form
    // x = a1 mod m1
    // x = a2 mod m2
    // ...
    // x = an mod mn
    // This algorithm solves for x.

    ChineseRemainderTheorem(UnsignedIntegers const& numbers, UnsignedIntegers const& modulos);

    UnsignedInteger getSolutionValue() const;
    UnsignedInteger getAnotherSolutionValue(UnsignedInteger const multiplier) const;

private:
    void solve(UnsignedIntegers const& numbers, UnsignedIntegers const& modulos);
    UnsignedInteger m_solutionValue;
    UnsignedInteger m_productOfModulos;
};

}
}