#include "PolynomialHelpers.hpp"

#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

using namespace alba::algebra::Factorization;
using namespace std;

namespace alba
{

namespace algebra
{

bool doesThePolynomialHaveOnlyOneVariable(Polynomial const& polynomial)
{
    VariableNamesSet variableNames;
    retrieveVariableNames(variableNames, polynomial);
    return variableNames.size() == 1;
}

AlbaNumber getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(
        Polynomial const& polynomial,
        AlbaNumber const& value)
{
    //remainder theorem
    AlbaNumber remainder;
    VariableNamesSet variableNames;
    retrieveVariableNames(variableNames, polynomial);
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();
        SubstitutionOfVariablesToValues substitution;
        substitution.putVariableWithValue(variableName, value);
        Term substitutedTerm(substitution.performSubstitutionTo(polynomial));
        if(substitutedTerm.isConstant())
        {
            remainder = substitutedTerm.getConstantConstReference().getNumberConstReference();
        }
    }
    return remainder;
}


AlbaNumbers getRoots(Polynomial const& polynomial)
{
    AlbaNumbers result;
    if(doesThePolynomialHaveOnlyOneVariable(polynomial))
    {
        Polynomial polynomialToFactorize(polynomial);
        Polynomials factorizedPolynomials(factorize(polynomialToFactorize));
        for(Polynomial const& factorizedPolynomial : factorizedPolynomials)
        {
            Monomials const& monomials(factorizedPolynomial.getMonomialsConstReference());
            AlbaNumber maxDegree(factorizedPolynomial.getMaxDegree());
            if(monomials.size() == 1 && maxDegree > 0)
            {
                result.emplace_back(AlbaNumber(0));
            }
            else if(monomials.size() == 2)
            {
                Monomial firstMonomial(monomials.at(0));
                Monomial secondMonomial(monomials.at(1));
                if(secondMonomial.isConstantOnly())
                {
                    AlbaNumber constant(-secondMonomial.getConstantConstReference());
                    constant = constant/firstMonomial.getConstantConstReference();
                    constant = constant^(AlbaNumber(1)/firstMonomial.getMaxExponent());
                    if(constant.isAFiniteValue())
                    {
                        result.emplace_back(constant);
                    }
                }
            }
        }
    }
    return result;
}
}

}
