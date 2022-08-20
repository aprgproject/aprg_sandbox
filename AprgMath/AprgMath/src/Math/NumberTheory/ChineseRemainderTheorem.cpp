#include "ChineseRemainderTheorem.hpp"

#include <Common/Math/AlbaMathHelper.hpp>
#include <Math/NumberTheory/ModularArithmetic.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

ChineseRemainderTheorem::ChineseRemainderTheorem(
        Numbers const& numbers,
        Numbers const& modulos)
    : m_solutionValue{}
{
    solve(numbers, modulos);
}

Number ChineseRemainderTheorem::getSolutionValue() const
{
    return m_solutionValue;
}

Number ChineseRemainderTheorem::getAnotherSolutionValue(Number const multiplier) const
{
    return m_solutionValue + multiplier*m_productOfModulos;
}

void ChineseRemainderTheorem::solve(
        Numbers const& numbers,
        Numbers const& modulos)
{
    if(numbers.size() == modulos.size())
    {
        // fk = (m1*m2*m3...mn)/mk
        // x = a1*f1*(inverse of f1 with modulo m1) + a2*f2*(inverse of f2 with modulo m2) + ... an*fn*(inverse of fn with modulo mn)

        m_productOfModulos = std::accumulate(modulos.cbegin(), modulos.cend(), Number(1), std::multiplies<Number>());
        for(unsigned int i=0; i<numbers.size(); i++)
        {
            Number const& number(numbers.at(i));
            Number const& modulo(modulos.at(i));
            Number fk = m_productOfModulos/modulo;
            Number modularInverseOfFk = getModularInverse(fk, modulo);
            m_solutionValue += number * fk * modularInverseOfFk;
        }
    }
}

}

}
