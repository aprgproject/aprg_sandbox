#include "CPlusPlusMacro.hpp"

namespace codeReview
{

bool CPlusPlusMacro::isPositionInMap(int const positionIndex) const
{
    return m_positionToParameter.find(positionIndex) != m_positionToParameter.end();
}

bool CPlusPlusMacro::isEqualToVariadicParameterIndex(int const parameterIndex) const
{
    if(m_variadicParameterIndexOptional)
    {
        return m_variadicParameterIndexOptional.get() == parameterIndex;
    }
    return false;
}

VectorOfTerms& CPlusPlusMacro::getMacroEquivalent()
{
    return m_macroEquivalent;
}

VectorOfStrings& CPlusPlusMacro::getMacroParameters()
{
    return m_macroParameters;
}

MapOfPositionToParameter& CPlusPlusMacro::getPositionToParameter()
{
    return m_positionToParameter;
}

void CPlusPlusMacro::mapThisPositionToThisParameter(int const positionIndex, int const parameterIndex)
{
    m_positionToParameter[positionIndex] = parameterIndex;
}

void CPlusPlusMacro::addMacroEquivalent(Term const& term)
{
    m_macroEquivalent.push_back(term);
}

void CPlusPlusMacro::setVariadicParameterIndex(int const parameterIndex)
{
    m_variadicParameterIndexOptional.setValue(parameterIndex);
}


}


