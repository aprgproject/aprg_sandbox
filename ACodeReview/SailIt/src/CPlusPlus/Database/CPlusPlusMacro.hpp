#pragma once

#include <Optional/AlbaOptional.hpp>
#include <string>
#include <map>
#include "../Utilities.hpp"
using std::string;
using std::map;
using std::pair;
namespace codeReview
{

typedef map<int, int> MapOfPositionToParameter;

class CPlusPlusMacro
{
public:
    bool isPositionInMap(int const positionIndex) const;
    bool isEqualToVariadicParameterIndex(int const parameterIndex) const;
    VectorOfTerms& getMacroEquivalent();
    VectorOfStrings& getMacroParameters();
    MapOfPositionToParameter& getPositionToParameter();
    void mapThisPositionToThisParameter(int const positionIndex, int const parameterIndex);
    void addMacroEquivalent(Term const& term);
    void setVariadicParameterIndex(int const parameterIndex);

private:
    alba::AlbaOptional<int> m_variadicParameterIndexOptional;
    VectorOfTerms m_macroEquivalent;
    VectorOfStrings m_macroParameters;
    MapOfPositionToParameter m_positionToParameter;
};

}
