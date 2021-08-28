#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Optional/AlbaOptional.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

class SimplificationMutator final : public BaseMutator
{
public:
    SimplificationMutator();

    void putSimplification(SimplificationOfExpression const& simplification);

    void mutateEquation(Equation & equation) const override;
    void mutateTerm(Term & term) const override;
    void mutateMonomial(Monomial & monomial) const override;
    void mutatePolynomial(Polynomial & polynomial) const override;
    void mutateExpression(Expression & expression) const override;
    void mutateFunction(Function & functionObject) const override;

private:
    AlbaOptional<SimplificationOfExpression> m_simplificationOfExpressionOptional;
};

}

}

}
