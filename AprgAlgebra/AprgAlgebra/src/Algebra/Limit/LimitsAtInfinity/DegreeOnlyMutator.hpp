#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>

namespace alba
{

namespace algebra
{

class DegreeOnlyMutator final : public BaseMutator
{
public:
    DegreeOnlyMutator(std::string const& variableName);
    void mutateTerm(Term & term) const override;
    void mutateMonomial(Monomial & monomial) const override;
    void mutatePolynomial(Polynomial & polynomial) const override;
    void mutateExpression(Expression & expression) const override;

private:
    Monomial getReducedMonomialWithDegree(AlbaNumber const& degree) const;
    std::string m_variableName;
};

}

}
