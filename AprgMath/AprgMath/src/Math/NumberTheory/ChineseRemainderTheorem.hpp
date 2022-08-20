#pragma once

#include <Math/NumberTheory/Types.hpp>

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

    ChineseRemainderTheorem(Numbers const& numbers, Numbers const& modulos);

    Number getSolutionValue() const;
    Number getAnotherSolutionValue(Number const multiplier) const;

private:
    void solve(Numbers const& numbers, Numbers const& modulos);
    Number m_solutionValue;
    Number m_productOfModulos;


};

}

}
