#include "EquationUtilities.hpp"

#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

#include <algorithm>

namespace alba
{

namespace algebra
{

bool isEqual(Term const& leftTerm, Term const& rightTerm)
{
    return leftTerm == rightTerm;
}

bool isNotEqual(Term const& leftTerm, Term const& rightTerm)
{
    return leftTerm != rightTerm;
}

bool isLessThan(Term const& leftTerm, Term const& rightTerm)
{
    bool result(false);
    if(leftTerm.isConstant() && rightTerm.isConstant())
    {
        result = leftTerm.getConstantConstReference().getNumberConstReference()
                < rightTerm.getConstantConstReference().getNumberConstReference();
    }
    return result;
}

bool isGreaterThan(Term const& leftTerm, Term const& rightTerm)
{
    bool result(false);
    if(leftTerm.isConstant() && rightTerm.isConstant())
    {
        result = leftTerm.getConstantConstReference().getNumberConstReference()
                > rightTerm.getConstantConstReference().getNumberConstReference();
    }
    return result;
}

bool isLessThanOrEqual(Term const& leftTerm, Term const& rightTerm)
{
    return isEqual(leftTerm, rightTerm) || isLessThan(leftTerm, rightTerm);
}

bool isGreaterThanOrEqual(Term const& leftTerm, Term const& rightTerm)
{
    return isEqual(leftTerm, rightTerm) || isGreaterThan(leftTerm, rightTerm);
}

bool isEquationOperationSatisfied(
        EquationOperator const& operatorObject,
        Term const& leftTerm,
        Term const& rightTerm)
{
    bool result(false);
    if(operatorObject.isEqual())
    {
        result = isEqual(leftTerm, rightTerm);
    }
    else if(operatorObject.isNotEqual())
    {
        result = isNotEqual(leftTerm, rightTerm);
    }
    else if(operatorObject.isLessThan())
    {
        result = isLessThan(leftTerm, rightTerm);
    }
    else if(operatorObject.isGreaterThan())
    {
        result = isGreaterThan(leftTerm, rightTerm);
    }
    else if(operatorObject.isLessThanOrEqual())
    {
        result = isLessThanOrEqual(leftTerm, rightTerm);
    }
    else if(operatorObject.isGreaterThanOrEqual())
    {
        result = isGreaterThanOrEqual(leftTerm, rightTerm);
    }
    return result;
}

bool doesAllEquationsHaveEqualityOperator(Equations const& equations)
{
    return all_of(equations.cbegin(), equations.cend(), [](Equation const& equation)
    {
        return equation.getEquationOperator().isEqual();
    });
}

VariableNamesSet retrieveAndReturnVariableNames(Equation const& equation)
{
    VariableNamesSet result;
    retrieveVariableNames(result, equation);
    return result;
}

void retrieveVariableNames(VariableNamesSet & variableNames, Equation const& equation)
{
    retrieveVariableNames(variableNames, equation.getLeftHandTerm());
    retrieveVariableNames(variableNames, equation.getRightHandTerm());
}

void retrieveVariableNames(VariableNamesSet & variableNames, Equations const& equations)
{
    for(Equation const& equation : equations)
    {
        retrieveVariableNames(variableNames, equation);
    }
}


}

}
