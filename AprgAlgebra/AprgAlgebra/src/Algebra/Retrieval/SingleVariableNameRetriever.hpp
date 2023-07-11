#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <string>

namespace alba {

namespace algebra {

class SingleVariableNameRetriever final : public BaseRetriever {
public:
    SingleVariableNameRetriever();

    std::string const& getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty() const;
    bool hasNoVariables() const;
    bool hasOnlyASingleVariable() const;
    bool hasMultipleVariables() const;

    void retrieveFromEquations(Equations const& equations) override;
    void retrieveFromEquation(Equation const& equation) override;
    void retrieveFromTerm(Term const& term) override;
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromPolynomial(Polynomial const& polynomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& function) override;
    void retrieveFromPolynomials(Polynomials const& polynomials) override;

    // private:
    void putVariableIfPossible(std::string const& variableName);
    bool m_hasEncounteredAVariable;
    bool m_hasMultipleVariables;
    std::string m_singleVariableName;
};

template <typename DataType>
bool hasOnlyASingleVariable(DataType const& dataType) {
    SingleVariableNameRetriever retriever;
    retriever.retrieve(dataType);
    return retriever.hasOnlyASingleVariable();
}

template <typename DataType>
bool hasNoVariables(DataType const& dataType) {
    SingleVariableNameRetriever retriever;
    retriever.retrieve(dataType);
    return retriever.hasNoVariables();
}

template <typename DataType>
std::string getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty(DataType const& dataType) {
    SingleVariableNameRetriever retriever;
    retriever.retrieve(dataType);
    return retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty();
}

}  // namespace algebra

}  // namespace alba
