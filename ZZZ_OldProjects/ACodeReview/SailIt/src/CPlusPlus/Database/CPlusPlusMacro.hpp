#pragma once

#include "../Utilities.hpp"

#include <map>
#include <optional>
#include <string>

using std::map;
using std::pair;
using std::string;

namespace codeReview {

typedef map<int, int> MapOfPositionToParameter;

class CPlusPlusMacro {
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
    std::optional<int> m_variadicParameterIndexOptional;
    VectorOfTerms m_macroEquivalent;
    VectorOfStrings m_macroParameters;
    MapOfPositionToParameter m_positionToParameter;
};

}  // namespace codeReview
