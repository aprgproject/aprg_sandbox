#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <functional>

namespace alba
{

namespace algebra
{

class SegregateTermsByConditionInAdditionAndSubtractionRetriever
{
public:
    using ConditionFunction=std::function<bool(Term const&)>;

    SegregateTermsByConditionInAdditionAndSubtractionRetriever(ConditionFunction const& condition);

    Term const& getTermWithCondition() const;
    Term const& getTermWithoutCondition() const;

    void retrieveFromConstant(Constant const& constant);
    void retrieveFromVariable(Variable const& variable);
    void retrieveFromMonomial(Monomial const& monomial);
    void retrieveFromPolynomial(Polynomial const& polynomial);
    void retrieveFromExpression(Expression const& expression);
    void retrieveFromFunction(Function const& functionObject);
    void retrieveFromTerm(Term const& term);
private:
    void saveTerm(Term const& term);
    ConditionFunction m_condition;
    Term m_termWithCondition;
    Term m_termWithoutCondition;
};

}

}
