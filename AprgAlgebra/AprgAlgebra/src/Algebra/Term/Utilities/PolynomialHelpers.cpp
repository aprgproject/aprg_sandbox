#include "PolynomialHelpers.hpp"

#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Retrieval/NumbersRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

bool doesThePolynomialHaveOnlyOneConstant(Polynomial const& polynomial)
{
    bool result(false);
    if(polynomial.isOneMonomial())
    {
        result = polynomial.getFirstMonomial().isConstantOnly();
    }
    return result;
}

bool doesThePolynomialHaveOnlyOneVariable(Polynomial const& polynomial)
{
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromPolynomial(polynomial);
    return variableNamesRetriever.getSavedData().size() == 1;
}

bool doesThePolynomialHaveDoubleValue(Polynomial const& polynomial)
{
    bool result(false);
    NumbersRetriever retriever;
    retriever.retrieveFromPolynomial(polynomial);
    AlbaNumbersSet const& numbers(retriever.getSavedDataReference());
    result = any_of(numbers.cbegin(), numbers.cend(), [](AlbaNumber const& number)
    {return number.isDoubleType();});
    return result;
}

bool doesOnePolynomialHaveADoubleValue(Polynomials const& polynomials)
{
    return any_of(polynomials.cbegin(), polynomials.cend(), [](Polynomial const& polynomial)
    {return doesThePolynomialHaveDoubleValue(polynomial);});
}

AlbaNumber getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(
        Polynomial const& polynomial,
        AlbaNumber const& value)
{
    //remainder theorem
    AlbaNumber remainder;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromPolynomial(polynomial);
    VariableNamesSet const& variableNames(variableNamesRetriever.getSavedData());
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();
        SubstitutionOfVariablesToValues substitution;
        substitution.putVariableWithValue(variableName, value);
        Term substitutedTerm(substitution.performSubstitutionTo(polynomial));
        if(substitutedTerm.isConstant())
        {
            remainder = substitutedTerm.getConstantValueConstReference();
        }
    }
    return remainder;
}


AlbaNumbers getRoots(RootType const rootType, Polynomial const& polynomial)
{
    AlbaNumbers result;
    if(doesThePolynomialHaveOnlyOneVariable(polynomial))
    {
        Polynomial const& polynomialToFactorize(polynomial);
        Polynomials factorizedPolynomials(factorize(polynomialToFactorize));
        for(Polynomial const& factorizedPolynomial : factorizedPolynomials)
        {
            Monomials const& monomialsToCheck(factorizedPolynomial.getMonomialsConstReference());
            AlbaNumber maxDegree(factorizedPolynomial.getMaxDegree());
            if(monomialsToCheck.size() == 1 && maxDegree > 0)
            {
                result.emplace_back(AlbaNumber(0));
            }
            else if(monomialsToCheck.size() == 2)
            {
                Monomial firstMonomial(monomialsToCheck.at(0));
                Monomial secondMonomial(monomialsToCheck.at(1));
                if(secondMonomial.isConstantOnly())
                {
                    AlbaNumber constant(-secondMonomial.getConstantConstReference());
                    constant = constant/firstMonomial.getConstantConstReference();
                    constant = constant^(AlbaNumber(1)/firstMonomial.getMaxExponent());

                    if(constant.isAFiniteValue())
                    {
                        if(RootType::RealAndImaginaryRoots == rootType)
                        {
                            result.emplace_back(constant);
                        }
                        else if(RootType::RealRootsOnly == rootType)
                        {
                            if(!constant.isComplexNumberType())
                            {
                                result.emplace_back(constant);
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

Polynomial raiseBinomialToAPowerUsingBinomialExpansion(
        Polynomial const& binomial,
        unsigned int const power)
{
    Polynomial result;
    Monomials const& monomials(binomial.getMonomialsConstReference());
    if(monomials.size() == 2U)
    {
        Monomial const& firstMonomial(monomials.at(0));
        Monomial const& secondMonomial(monomials.at(1));
        for(unsigned int i=0; i<=power; i++)
        {
            unsigned int firstPower=i;
            unsigned int secondPower=power-i;
            Monomial firstPart(firstMonomial);
            Monomial secondPart(secondMonomial);
            firstPart.raiseToPowerNumber(AlbaNumber(firstPower));
            secondPart.raiseToPowerNumber(AlbaNumber(secondPower));
            firstPart.multiplyMonomial(secondPart);
            firstPart.multiplyNumber(AlbaNumber(getValueAtPascalTriangle(power, i)));
            firstPart.simplify();
            result.addMonomial(firstPart);
        }
    }
    result.simplify();
    return result;
}

void removeEmptyPolynomials(Polynomials & polynomials)
{
    polynomials.erase(remove_if(polynomials.begin(), polynomials.end(), [](
                                Polynomial const& polynomial)
    {
                          return polynomial.isEmpty();
                      }), polynomials.end());
}

}

}
