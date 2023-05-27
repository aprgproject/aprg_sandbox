#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class DifferentiationForFiniteCalculus {
public:
    DifferentiationForFiniteCalculus(std::string const& nameOfVariableToDifferentiate);

    Term differentiate(Term const& term) const;
    Term differentiate(Constant const& constant) const;
    Term differentiate(Variable const& variable) const;
    Term differentiate(Monomial const& monomial) const;
    Term differentiate(Polynomial const& polynomial) const;
    Term differentiate(Expression const& expression) const;
    Term differentiate(Function const& functionObject) const;
    Equation differentiate(Equation const& equation) const;

    Term differentiateMultipleTimes(Term const& term, int const numberOfTimes) const;
    Equation differentiateMultipleTimes(Equation const& equation, int const numberOfTimes) const;

    Term differentiateTerm(Term const& term) const;
    AlbaNumber differentiateConstant(Constant const&) const;    Polynomial differentiateVariable(Variable const& variable) const;
    Term differentiateMonomial(Monomial const& monomial) const;
    Term differentiatePolynomial(Polynomial const& polynomial) const;
    Term differentiateExpression(Expression const& expression) const;    Term differentiateFunction(Function const& functionObject) const;
    Equation differentiateEquation(Equation const& equation) const;

private:
    bool isVariableToDifferentiate(std::string const& variableName) const;
    std::string m_nameOfVariableToDifferentiate;
};

}  // namespace algebra

}  // namespace alba
