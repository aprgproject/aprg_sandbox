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
        UnsignedNumbers const& numbers,
        UnsignedNumbers const& modulos)
    : m_solutionValue{}
{
    solve(numbers, modulos);
}

UnsignedNumber ChineseRemainderTheorem::getSolutionValue() const
{
    return m_solutionValue;
}

UnsignedNumber ChineseRemainderTheorem::getAnotherSolutionValue(UnsignedNumber const multiplier) const
{
    return m_solutionValue + multiplier*m_productOfModulos;
}

void ChineseRemainderTheorem::solve(
        UnsignedNumbers const& numbers,
        UnsignedNumbers const& modulos)
{
    if(numbers.size() == modulos.size())
    {
        // fk = (m1*m2*m3...mn)/mk
        // x = a1*f1*(inverse of f1 with modulo m1) + a2*f2*(inverse of f2 with modulo m2) + ... an*fn*(inverse of fn with modulo mn)

        m_productOfModulos = std::accumulate(modulos.cbegin(), modulos.cend(), UnsignedNumber(1), std::multiplies<UnsignedNumber>());
        for(unsigned int i=0; i<numbers.size(); i++)
        {
            UnsignedNumber const& number(numbers.at(i));
            UnsignedNumber const& modulo(modulos.at(i));
            UnsignedNumber fk = m_productOfModulos/modulo;
            UnsignedNumber modularInverseOfFk = getModularInverse(fk, modulo);
            m_solutionValue += number * fk * modularInverseOfFk;
        }
    }
}

}

}
