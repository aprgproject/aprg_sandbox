#pragma once

#include <BooleanAlgebra/Retrieval/BaseRetriever.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba
{

namespace booleanAlgebra
{

using BaseVariableNamesRetriever = BaseRetriever<VariableNamesSet>;

class VariableNamesRetriever final : public BaseVariableNamesRetriever
{
public:
    void retrieveFromVariableTerm(VariableTerm const& variableTerm) override;
};

}

}
