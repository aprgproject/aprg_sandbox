#include "Lagrange.hpp"

#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

Terms getLagrangeMultipliers(
        Term const& term,
        strings const& coordinateNames,
        Terms const& lagrangeFunctions)
{
    strings lagrangeMultiplierNames(getLagrangeMultiplierNames(lagrangeFunctions.size()));
    Term termWithLagrangeFunctions(getTermWithLagrangeFunctions(term, lagrangeFunctions, lagrangeMultiplierNames));
    Equations lagrangeEquations;
    calculateLagrangeEquations(lagrangeEquations, termWithLagrangeFunctions, coordinateNames, lagrangeMultiplierNames);

    Terms result;
    IsolationOfOneVariableOnEqualityEquations isolation(lagrangeEquations);
    for(string const& lagrangeMultiplierName : lagrangeMultiplierNames)
    {
        result.emplace_back(isolation.getEquivalentTermByIsolatingAVariable(lagrangeMultiplierName));
    }
    return result;
}

void calculateLagrangeEquations(
        Equations & lagrangeEquations,
        Term const& termWithLagrangeFunctions,
        strings const& coordinateNames,
        strings const& lagrangeMultiplierNames)
{
    for(string const& coordinateName : coordinateNames)
    {
        lagrangeEquations.emplace_back(getPartialDerivative(termWithLagrangeFunctions, coordinateName), "=", Term(0));
    }
    for(string const& lagrangeMultiplierName : lagrangeMultiplierNames)
    {
        lagrangeEquations.emplace_back(getPartialDerivative(termWithLagrangeFunctions, lagrangeMultiplierName), "=", Term(0));
    }
}

Term getTermWithLagrangeFunctions(
        Term const& term,
        Terms const& lagrangeFunctions,
        strings const& lagrangeMultiplierNames)
{
    unsigned int size(min(lagrangeFunctions.size(), lagrangeMultiplierNames.size()));
    Term result(term);
    for(unsigned int i=0; i<size; i++)
    {
        result += lagrangeFunctions.at(i) * Term(lagrangeMultiplierNames.at(i));
    }
    return result;
}

strings getLagrangeMultiplierNames(unsigned int const size)
{
    strings result;
    for(unsigned int i=0; i<size; i++)
    {
        result.emplace_back(getLagrangeMultiplierName(i));
    }
    return result;
}

string getLagrangeMultiplierName(unsigned int const index)
{
    NumberToStringConverter converter;
    converter.setFieldWidth(3);
    converter.setFillCharacter('0');
    return "multiplier" + converter.convert(index);
}


}

}