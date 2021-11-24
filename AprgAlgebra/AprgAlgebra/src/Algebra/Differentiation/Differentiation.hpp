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

    Term differentiateWithDefiniteValue(
            Term const& term,
            AlbaNumber const& value) const;

    Term differentiateMultipleTimes(Term const& term, unsigned int const numberOfTimes) const;
    Equation differentiateMultipleTimes(Equation const& equation, unsigned int const numberOfTimes) const;

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
    void separateNonChangingAndChangingVariables(
            Monomial & unaffectedVariablesAndConstant,
            Monomial & affectedVariables,
            Monomial const& monomial) const;
    Polynomial differentiateMonomialWithChangingVariables(
            Monomial const& affectedVariables) const;
    Term differentiateAsTermOrExpressionIfNeeded(
            Expression const& expression) const;
    Term differentiateSimplifiedExpressionOnly(
            Expression const& expression) const;
    Term differentiateTermsInAdditionOrSubtraction(
            Expression const& expression) const;
    Term differentiateTermsInMultiplicationOrDivision(
            Expression const& expression) const;
    Term differentiateByProcessingAsPolynomialsOverPolynomials(
            Term const& term) const;
    Term differentiateTermsInMultiplicationOrDivisionTermByTerm(
            TermsWithDetails const& termsWithDetails) const;
    Term differentiateTermsInRaiseToPower(
            Expression const& expression) const;
    Term differentiateNonChangingTermRaiseToChangingTerm(
            Term const& base,
            Term const& exponent) const;
    Term differentiateChangingTermRaiseToNonChangingTerm(
            Term const& base,
            Term const& exponent) const;
    Term differentiateChangingTermRaiseToChangingTerm(
            Term const& firstTerm,
            Term const& secondTerm) const;
    Term differentiateFunctionOnly(
            Function const& functionObject) const;
    bool isVariableToDifferentiate(std::string const& variableName) const;
    bool isDependentVariable(std::string const& variableName) const;
    bool isDerivativeVariableNameAndAffectedByThisDifferentiation(            DerivativeVariableName const& derivativeVariable) const;
    bool isChangingVariableName(std::string const& variableName) const;
    bool isChangingTerm(Term const& term) const;
    std::string m_nameOfVariableToDifferentiate;    VariableNamesSet m_namesOfDependentVariables;
};

}

}
