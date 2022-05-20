#include "PolynomialHelpers.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Retrieval/ExponentsRetriever.hpp>
#include <Algebra/Retrieval/NumbersRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Common/Math/AlbaMathHelper.hpp>
#include <algorithm>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

bool doesThePolynomialHaveOnlyOneConstant(
        Polynomial const& polynomial)
{
    bool result(false);
    if(isOneMonomial(polynomial))
    {
        result = isConstantOnly(getFirstMonomial(polynomial));
    }
    return result;
}

bool doesThePolynomialHaveOnlyOneVariable(
        Polynomial const& polynomial)
{
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromPolynomial(polynomial);
    return variableNamesRetriever.getSavedData().size() == 1;
}

bool doesThePolynomialHaveDoubleValue(
        Polynomial const& polynomial)
{
    bool result(false);
    NumbersRetriever retriever;
    retriever.retrieveFromPolynomial(polynomial);
    AlbaNumbersSet const& numbers(retriever.getSavedDataReference());
    result = any_of(numbers.cbegin(), numbers.cend(), [](AlbaNumber const& number)
    {return number.isDoubleType();});
    return result;
}

bool doesOnePolynomialHaveADoubleValue(
        Polynomials const& polynomials)
{
    return any_of(polynomials.cbegin(), polynomials.cend(), [](Polynomial const& polynomial)
    {return doesThePolynomialHaveDoubleValue(polynomial);});
}

bool hasAMonomialWithMultipleVariables(
        Polynomial const& polynomial)
{
    bool result(false);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        if(monomial.getVariablesToExponentsMapConstReference().size() >= 2)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool hasAMonomialWithDegreeMoreThanOneOrFractional(
        Polynomial const& polynomial)
{
    bool result(false);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        AlbaNumber degree(getDegree(monomial));
        if(degree > 1 || !degree.isIntegerType())
        {
            result = true;
            break;
        }
    }
    return result;
}

bool isOneMonomial(Polynomial const& polynomial)
{
    return polynomial.getMonomialsConstReference().size() == 1;
}

bool isVariableExponentInMonomialFound(
        Polynomial const& polynomial,
        Monomial const& monomial)
{
    bool result(false);
    for(Monomial const& monomialInternal : polynomial.getMonomialsConstReference())
    {
        if(monomial.getVariablesToExponentsMapConstReference()
                == monomialInternal.getVariablesToExponentsMapConstReference())
        {
            result = true;
            break;
        }
    }
    return result;
}

bool isPolynomialLinear(Polynomial const& polynomial)
{
    ExponentsRetriever exponentsRetriever;
    exponentsRetriever.retrieveFromPolynomial(polynomial);
    AlbaNumbersSet const& exponents(exponentsRetriever.getSavedData());
    return all_of(exponents.cbegin(), exponents.cend(), [](AlbaNumber const& exponent)
    {
        return exponent==0 || exponent==1;
    });
}

Monomial getFirstMonomial(
        Polynomial const& polynomial)
{    Monomial result;
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    if(!monomials.empty())
    {        result = monomials.front();
    }
    return result;
}

AlbaNumber getMaxDegree(
        Polynomial const& polynomial)
{
    bool isFirst(true);
    AlbaNumber maxDegree(0);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        if(isFirst)
        {
            maxDegree = getDegree(monomial);
            isFirst=false;
        }
        else
        {
            maxDegree = max(maxDegree, getDegree(monomial));
        }
    }
    return maxDegree;
}

std::pair<AlbaNumber, AlbaNumber> getMinmaxDegree(
        Polynomial const& polynomial)
{
    bool isFirst(true);
    std::pair<AlbaNumber, AlbaNumber> result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        if(isFirst)
        {
            result.first = getDegree(monomial);
            result.second = result.first;
            isFirst=false;
        }
        else
        {
            result.first = min(result.first, getDegree(monomial));
            result.second = max(result.second, getDegree(monomial));
        }
    }
    return result;
}

AlbaNumber getDegreeForVariable(
        Polynomial const& polynomial,
        string const& variableName){
    bool isFirst(true);
    AlbaNumber maxDegree(0);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())    {
        if(isFirst)
        {
            maxDegree = monomial.getExponentForVariable(variableName);
            isFirst=false;
        }
        else
        {
            maxDegree = max(maxDegree, monomial.getExponentForVariable(variableName));
        }
    }
    return maxDegree;
}

AlbaNumber getCoefficientOfVariableExponent(
        Polynomial const& polynomial,
        Monomial const& monomial)
{
    AlbaNumber coefficient;
    for(Monomial const& monomialInternal : polynomial.getMonomialsConstReference())
    {
        if(monomial.getVariablesToExponentsMapConstReference()
                == monomialInternal.getVariablesToExponentsMapConstReference())
        {
            coefficient = monomialInternal.getConstantConstReference();
            break;
        }
    }
    return coefficient;
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


AlbaNumbers getRoots(
        RootType const rootType,
        Polynomial const& polynomial)
{
    AlbaNumbers result;
    if(doesThePolynomialHaveOnlyOneVariable(polynomial))
    {
        Polynomial const& polynomialToFactorize(polynomial);
        Polynomials factorizedPolynomials(factorizeAPolynomial(polynomialToFactorize));
        for(Polynomial const& factorizedPolynomial : factorizedPolynomials)
        {
            Monomials const& monomialsToCheck(factorizedPolynomial.getMonomialsConstReference());
            AlbaNumber maxDegree(getMaxDegree(factorizedPolynomial));
            if(monomialsToCheck.size() == 1 && maxDegree > 0)
            {
                result.emplace_back(AlbaNumber(0));
            }
            else if(monomialsToCheck.size() == 2)
            {
                Monomial firstMonomial(monomialsToCheck.at(0));
                Monomial secondMonomial(monomialsToCheck.at(1));
                if(isConstantOnly(secondMonomial))
                {
                    AlbaNumber constant(-secondMonomial.getConstantConstReference());
                    constant = constant/firstMonomial.getConstantConstReference();
                    constant = constant^(AlbaNumber(1)/getMaxExponent(firstMonomial));

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

void removeEmptyPolynomials(
        Polynomials & polynomials)
{
    polynomials.erase(remove_if(polynomials.begin(), polynomials.end(), [](
                                Polynomial const& polynomial)
    {
                          return polynomial.isEmpty();
                      }), polynomials.end());
}

}

}
