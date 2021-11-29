#include "EquationUtilities.hpp"

#include <Algebra/Equation/EquationBuilder.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

bool isEquationOperatorString(string const& stringToCheck)
{
    return "=" == stringToCheck || "==" == stringToCheck || "!=" == stringToCheck
            || "<" == stringToCheck || ">" == stringToCheck || "<=" == stringToCheck || ">=" == stringToCheck;
}

bool isEquationOperatorCharacterString(string const& stringToCheck)
{
    return "=" == stringToCheck || "!" == stringToCheck
            || "<" == stringToCheck || ">" == stringToCheck;
}

bool doesNegativeVariableSubstitutionYieldsToTheSameEquation(
        Equation const& equation,
        strings const& variableNames)
{
    Equation equation1(equation);
    equation1.simplify();
    SubstitutionOfVariablesToTerms substitution;
    for(string const& variableName : variableNames)
    {
        substitution.putVariableWithTerm(variableName, Term(Monomial(-1, {{variableName, 1}})));
    }
    Equation equation2(substitution.performSubstitutionTo(equation1));
    return equation1 == equation2;
}

bool isSymmetricAlongXAxis(Equation const& equation)
{
    return doesNegativeVariableSubstitutionYieldsToTheSameEquation(equation, {"y"});
}

bool isSymmetricAlongYAxis(Equation const& equation)
{
    return doesNegativeVariableSubstitutionYieldsToTheSameEquation(equation, {"x"});
}

bool isSymmetricOnOrigin(Equation const& equation)
{
    return doesNegativeVariableSubstitutionYieldsToTheSameEquation(equation, {"x", "y"});
}

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
        result = leftTerm.getConstantValueConstReference() < rightTerm.getConstantValueConstReference();
    }
    return result;
}

bool isGreaterThan(Term const& leftTerm, Term const& rightTerm)
{
    bool result(false);
    if(leftTerm.isConstant() && rightTerm.isConstant())
    {
        result = leftTerm.getConstantValueConstReference() > rightTerm.getConstantValueConstReference();
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

AlbaNumber getDegree(Equation const& equation)
{
    return max(getDegree(equation.getLeftHandTerm()), getDegree(equation.getRightHandTerm()));
}

string getEquationOperatorCharacters()
{
    return "!=<>";
}

string getReverseEquationOperatorString(string const& equationOperatorString)
{
    string result(equationOperatorString);
    if("<" == equationOperatorString)
    {
        result = ">";
    }
    else if(">" == equationOperatorString)
    {
        result = "<";
    }
    else if("<=" == equationOperatorString)
    {
        result = ">=";
    }
    else if(">=" == equationOperatorString)
    {
        result = "<=";
    }
    return result;
}

Term getEquivalentTermByReducingItToAVariable(
        string const& variableName,
        Term const& termWithVariable,
        Term const& termWithWithoutVariable)
{
    Term result;
    if(termWithVariable.isVariable())
    {
        result = termWithWithoutVariable;
    }
    else if(termWithVariable.isMonomial())
    {
        Monomial const& monomialWithVariable(termWithVariable.getMonomialConstReference());
        AlbaNumber exponent(monomialWithVariable.getExponentForVariable(variableName));
        exponent = exponent^(-1);
        result = termWithWithoutVariable^Term(exponent);
    }
    return result;
}

Equation buildEquationIfPossible(string const& equationString)
{
    EquationBuilder builder(equationString);
    return builder.getEquation();
}

void segregateEquationsWithAndWithoutVariable(
        Equations const& equationsToSegregate,
        string const& variableName,
        Equations & equationsWithVariable,
        Equations & equationsWithoutVariable)
{
    for(Equation const& equationToSegregate : equationsToSegregate)
    {
        VariableNamesRetriever namesRetriever;
        namesRetriever.retrieveFromEquation(equationToSegregate);
        VariableNamesSet const& names(namesRetriever.getSavedData());
        if(names.find(variableName) != names.cend())
        {
            equationsWithVariable.emplace_back(equationToSegregate);
        }
        else
        {
            equationsWithoutVariable.emplace_back(equationToSegregate);
        }
    }
}


}

}
