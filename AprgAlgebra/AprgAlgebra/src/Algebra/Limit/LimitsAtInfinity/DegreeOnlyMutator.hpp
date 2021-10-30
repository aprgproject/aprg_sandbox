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
    void mutateTerm(Term & term) override;
    void mutateMonomial(Monomial & monomial) override;
    void mutatePolynomial(Polynomial & polynomial) override;
    void mutateExpression(Expression & expression) override;
    
private:
    AlbaNumber getMaxDegreeForVariable(Polynomial const& polynomial);
    Monomial getMonomialWithDegree(AlbaNumber const& degree) const;
    std::string m_variableName;
};

}

}
