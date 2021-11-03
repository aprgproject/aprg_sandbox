#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

namespace alba
{

namespace algebra
{

class SignMutator final : public BaseMutator
{
public:
    void mutateTerm(Term & term) override;
    void mutateConstant(Constant & constant) override;
    void mutateVariable(Variable &) override;
    void mutateMonomial(Monomial & monomial) override;
    void mutatePolynomial(Polynomial & polynomial) override;
    void mutateExpression(Expression & expression) override;
    void mutateFunction(Function &) override;

    void putVariableWithSign(std::string const& variableName, TermAssociationType const association);

private:
    Term getTermForMutationOfVariable(Variable const& variable);
    Term getTermForMutationOfFunction(Function const& functionObject);
    void mutateExpressionWithAdditionAndSubtraction(Expression & expression);
    void mutateExpressionWithMultiplicationAndDivision(Expression & expression);
    void mutateExpressionWithRaiseToPower(Expression & expression);

    SubstitutionOfVariablesToValues m_substitution;
};

}

}
