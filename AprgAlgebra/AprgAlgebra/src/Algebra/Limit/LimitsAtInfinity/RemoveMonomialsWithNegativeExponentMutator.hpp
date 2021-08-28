#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>

namespace alba
{

namespace algebra
{

class RemoveMonomialsWithNegativeExponentMutator final : public BaseMutator
{
public:
    RemoveMonomialsWithNegativeExponentMutator(std::string const& variableName);
    void mutateTerm(Term & term) const override;
    void mutateMonomial(Monomial & monomial) const override;
    void mutatePolynomial(Polynomial & polynomial) const override;
    void mutateExpression(Expression & expression) const override;
    void mutateFunction(Function & functionObject) const override;

private:
    bool isMonomialToBeRemoved(Monomial const& monomial) const;
    std::string m_variableName;
};

}

}
