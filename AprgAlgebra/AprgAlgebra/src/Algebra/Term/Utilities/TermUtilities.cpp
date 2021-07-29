#include "TermUtilities.hpp"

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

AlbaNumbers getRoots(Polynomial const& polynomial)
{
    AlbaNumbers result;
    VariableNamesSet variableNames;
    retrieveVariableNames(variableNames, polynomial);
    if(variableNames.size() == 1)
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

AlbaNumber getMaxDegreeOfPolynomials(Polynomials const& polynomials)
{
    AlbaNumber maxDegree;
    for(Polynomial const& polynomial : polynomials)
    {
        maxDegree = max(maxDegree, polynomial.getMaxDegree());
    }
    return maxDegree;
}

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        string const& variableName,
        Term const& term)
{
    AlbaNumberPairs result;
    SubstitutionOfVariablesToValues substitution;
    for(AlbaNumber const& number : numbers)
    {
        substitution.putVariableWithValue(variableName, number);
        Term substituteTerm(substitution.performSubstitutionTo(term));
        if(substituteTerm.isConstant())
        {
            result.emplace_back(number, substituteTerm.getConstantConstReference().getNumberConstReference());
        }
    }
    return result;
}

}

}
