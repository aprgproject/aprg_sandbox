#pragma once

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

    AlbaNumber differentiateConstant(Constant const&) const;
    Monomial differentiateVariable(Variable const& variable) const;
    Monomial differentiateMonomial(Monomial const& monomial) const;
    Polynomial differentiatePolynomial(Polynomial const& polynomial) const;
    Term differentiateExpression(Expression const& expression) const;
    Term differentiateFunction(Function const& functionObject) const;

    Term differentiateTwoMultipliedTerms(Term const& term1, Term const& term2) const;
    Term differentiateTwoDividedTerms(Term const& numerator, Term const& denominator) const;

private:
    bool isDependentVariable(std::string const& variableName) const;
    std::string getNameOfDifferentialOfDependentVariable(std::string const& variableName) const;
    Term differentiateAsTermOrExpressionIfNeeded(
            Expression const& expression) const;
    Term differentiateSimplifiedExpressionOnly(
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
    std::string m_nameOfVariableToDifferentiate;
    VariableNamesSet m_namesOfDependentVariables;

};

}

}