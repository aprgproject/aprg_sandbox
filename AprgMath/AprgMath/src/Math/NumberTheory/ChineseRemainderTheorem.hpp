#pragma once

#include <Math//NumberTheory/Types.hpp>

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

    ChineseRemainderTheorem(UnsignedNumbers const& numbers, UnsignedNumbers const& modulos);

    UnsignedNumber getSolutionValue() const;
    UnsignedNumber getAnotherSolutionValue(UnsignedNumber const multiplier) const;

private:
    void solve(UnsignedNumbers const& numbers, UnsignedNumbers const& modulos);
    UnsignedNumber m_solutionValue;
    UnsignedNumber m_productOfModulos;
};

}

}
