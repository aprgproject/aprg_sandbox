#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace algebra {

class VariableNamesRetriever final : public BaseRetriever {
public:
    VariableNamesSet const& getVariableNames() const;

    VariableNamesSet& getVariableNamesReference();
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;

private:
    VariableNamesSet m_variableNames;
};

}  // namespace algebra
}  // namespace alba