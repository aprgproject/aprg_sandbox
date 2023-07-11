#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>
#include <unordered_map>

namespace alba {

namespace algebra {

class SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever : public BaseRetriever {
public:
    using VariableNameToTermMap = std::unordered_map<std::string, Term>;

    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever(stringHelper::strings const& variableNames);

    VariableNameToTermMap const& getVariableNameToTermMap() const;
    Term const& getTermWithMultipleVariableNames() const;
    Term const& getRemainingTerm() const;

    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;

private:
    void initializeWithVariableNames(stringHelper::strings const& namesInOrder);
    void saveTerm(Term const& term, int numberOfTimesFound, std::string const& variableName);
    VariableNameToTermMap m_variableNameToTermMap;
    Term m_termWithMultipleVariableNames;
    Term m_remainingTerm;
};

}  // namespace algebra

}  // namespace alba
