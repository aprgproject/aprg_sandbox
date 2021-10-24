#pragma once

#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class AxisRotation
{
public:
    AxisRotation(std::string const& xName, std::string const& yName, double const angle, bool const doRotationBack);

    Term rotateTermByAngle(Term const& term);
    Term rotateConstantByAngle(Constant const& constant);
    Term rotateVariableByAngle(Variable const& variable);
    Term rotateMonomialByAngle(Monomial const& monomial);
    Term rotatePolynomialByAngle(Polynomial const& polynomial);
    Term rotateExpressionByAngle(Expression const& expression);
    Term rotateFunctionByAngle(Function const& functionObject);

private:
    void initializeSubstitution(std::string const& xName, std::string const& yName, double const angle, bool const doRotationBack);
    SubstitutionOfVariablesToTerms m_substitution;
};

}

}
