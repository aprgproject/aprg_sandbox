#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
namespace alba
{
namespace algebra
{

class OneEquationOneUnknownNonEqualitySolver
{
public:
    OneEquationOneUnknownNonEqualitySolver(Equation const& equation);

    bool isSolved() const;
    bool isACompleteSolution() const;

    SolutionSet calculateSolutionAndReturnSolutionSet();

private:
    void setAsCompleteSolution();
    void setAsIncompleteSolution();
    void processWhenEquationIsAlwaysSatisfied(SolutionSet & result);
    void calculateWhenEquationIsSometimesSatisfied(SolutionSet & result);
    AlbaNumbers getValuesToCheck(PolynomialOverPolynomial const& pop);
    bool m_isSolved;
    bool m_isACompleteSolution;
    Equation m_equation;
};

}

}