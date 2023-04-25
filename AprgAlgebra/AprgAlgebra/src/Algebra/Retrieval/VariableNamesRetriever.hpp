#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace algebra {

using BaseVariableNamesRetriever = BaseRetriever<VariableNamesSet>;

class VariableNamesRetriever final : public BaseVariableNamesRetriever {
public:
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
};

}  // namespace algebra

}  // namespace alba
