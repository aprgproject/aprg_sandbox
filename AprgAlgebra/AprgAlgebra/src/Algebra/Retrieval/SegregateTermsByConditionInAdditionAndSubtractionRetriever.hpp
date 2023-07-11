#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>

#include <functional>
namespace alba {

namespace algebra {

class SegregateTermsByConditionInAdditionAndSubtractionRetriever : public BaseRetriever {
public:
    using ConditionFunction = std::function<bool(Term const&)>;
    SegregateTermsByConditionInAdditionAndSubtractionRetriever(ConditionFunction const& condition);

    Term const& getTermWithCondition() const;
    Term const& getTermWithoutCondition() const;

    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;

private:
    void saveTerm(Term const& term);    ConditionFunction m_condition;
    Term m_termWithCondition;
    Term m_termWithoutCondition;
};
}  // namespace algebra

}  // namespace alba
