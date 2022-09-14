#include "ChineseRemainderTheorem.hpp"

#include <Math/NumberTheory/ModularArithmetic.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace math
{

ChineseRemainderTheorem::ChineseRemainderTheorem(
        UnsignedIntegers const& numbers,
        UnsignedIntegers const& modulos)
    : m_solutionValue{}
{
    solve(numbers, modulos);
}

UnsignedInteger ChineseRemainderTheorem::getSolutionValue() const
{
    return m_solutionValue;
}

UnsignedInteger ChineseRemainderTheorem::getAnotherSolutionValue(UnsignedInteger const multiplier) const
{
    return m_solutionValue + multiplier*m_productOfModulos;
}

void ChineseRemainderTheorem::solve(
        UnsignedIntegers const& numbers,
        UnsignedIntegers const& modulos)
{
    if(numbers.size() == modulos.size())
    {
        // fk = (m1*m2*m3...mn)/mk
        // x = a1*f1*(inverse of f1 with modulo m1) + a2*f2*(inverse of f2 with modulo m2) + ... an*fn*(inverse of fn with modulo mn)

        m_productOfModulos = std::accumulate(modulos.cbegin(), modulos.cend(), UnsignedInteger(1), std::multiplies<UnsignedInteger>());
        for(unsigned int i=0; i<numbers.size(); i++)
        {
            UnsignedInteger const& number(numbers.at(i));
            UnsignedInteger const& modulo(modulos.at(i));
            UnsignedInteger fk = m_productOfModulos/modulo;
            UnsignedInteger modularInverseOfFk = getModularInverse(fk, modulo);
            m_solutionValue += number * fk * modularInverseOfFk;
        }
    }
}

}

}
