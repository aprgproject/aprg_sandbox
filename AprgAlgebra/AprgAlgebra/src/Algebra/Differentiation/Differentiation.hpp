#pragma once

#include <Algebra/Differentiation/DerivativeVariableName.hpp>
#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba
{

namespace algebra
{

class Differentiation
{
public:
    Differentiation(std::string const& nameOfVariableToDifferentiate);
    Differentiation(
            std::string const& nameOfVariableToDifferentiate,
            VariableNamesSet const& namesOfDependentVariables);

    Term differentiate(Term const& term) const;
    Term differentiate(Constant const& constant) const;
    Term differentiate(Variable const& variable) const;
    Term differentiate(Monomial const& monomial) const;
    Term differentiate(Polynomial const& polynomial) const;
    Term differentiate(Expression const& expression) const;
    Term differentiate(Function const& functionObject) const;
    Equation differentiate(Equation const& equation) const;

    Term differentiateMultipleTimes(Term const& term, unsigned int const numberOfTimes) const;
    Equation differentiateMultipleTimes(Equation const& equation, unsigned int const numberOfTimes) const;

    Term differentiateTerm(Term const& term) const;
    AlbaNumber differentiateConstant(Constant const&) const;
    Monomial differentiateVariable(Variable const& variable) const;
    Polynomial differentiateMonomial(Monomial const& monomial) const;
    Polynomial differentiatePolynomial(Polynomial const& polynomial) const;
    Term differentiateExpression(Expression const& expression) const;
    Term differentiateFunction(Function const& functionObject) const;
    Equation differentiateEquation(Equation const& equation) const;

    Term differentiateTwoMultipliedTerms(Term const& term1, Term const& term2) const;
    Term differentiateTwoDividedTerms(Term const& numerator, Term const& denominator) const;


private:
    bool isVariableToDifferentiate(std::string const& variableName) const;
    bool isDependentVariable(std::string const& variableName) const;    bool isDerivativeVariableNameAndAffectedByThisDifferentiation(
            DerivativeVariableName const& derivativeVariable) const;
    Term differentiateAsTermOrExpressionIfNeeded(
            Expression const& expression) const;    Term differentiateSimplifiedExpressionOnly(
            Expression const& expression) const;
    Term differentiateTermsInAdditionOrSubtraction(
            TermsWithDetails const& termsWithDetails) const;
    Term differentiateTermsInMultiplicationOrDivision(
            TermsWithDetails const& termsWithDetails) const;
    Term differentiateTermsInRaiseToPower(
            TermsWithDetails const& termsWithDetails) const;
    Term differentiateConstantRaiseToTerm(
            AlbaNumber const& number,
            Term const& term) const;
    Term differentiateTermRaiseToConstant(
            Term const& term,
            AlbaNumber const& number) const;
    Term differentiateTermRaiseToTerm(
            Term const& firstTerm,
            Term const& secondTerm) const;
    Term differentiateFunctionOnly(Function const& functionObject) const;
    void simplifyToFactors(Term& term) const;
    std::string m_nameOfVariableToDifferentiate;
    VariableNamesSet m_namesOfDependentVariables;
};
}

}