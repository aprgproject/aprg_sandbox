#include "FactorizationBySplitting.hpp"

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

Polynomials factorizeBySplittingToSmallerPolynomials(Polynomial const& polynomial) {
    Polynomials result;
    factorizeBySplittingToSmallerPolynomialsIfPossible(result, polynomial);
    simplifyAndEmplaceBackPolynomialIfListIsEmpty(result, polynomial);
    return result;
}

void factorizeBySplittingToSmallerPolynomialsIfPossible(Polynomials& result, Polynomial const& polynomial) {
    factorizeIfPossibleBySplittingByPolynomialDegree(result, polynomial);
    if (result.empty()) {
        factorizeIfPossibleBySplittingByDivisibilityOfExponents(result, polynomial);
        if (result.empty()) {
            factorizeIfPossibleBySplittingByFirstVariable(result, polynomial);
        }
    }
}

void factorizeIfPossibleBySplittingByPolynomialDegree(Polynomials& result, Polynomial const& polynomial) {
    Polynomials smallerPolynomials;
    splitPolynomialsByPolynomialDegree(smallerPolynomials, polynomial);
    factorizeSmallerPolynomials(result, smallerPolynomials);
}

void factorizeIfPossibleBySplittingByDivisibilityOfExponents(Polynomials& result, Polynomial const& polynomial) {
    Polynomials smallerPolynomials;
    splitPolynomialsByDivisibilityOfExponents(smallerPolynomials, polynomial);
    factorizeSmallerPolynomials(result, smallerPolynomials);
}

void factorizeIfPossibleBySplittingByFirstVariable(Polynomials& result, Polynomial const& polynomial) {
    Polynomials smallerPolynomials;
    splitPolynomialsByFirstVariable(smallerPolynomials, polynomial);
    factorizeSmallerPolynomials(result, smallerPolynomials);
}

void splitPolynomialsByPolynomialDegree(Polynomials& result, Polynomial const& polynomial) {
    Monomials monomials(polynomial.getMonomialsConstReference());
    Polynomial partialPolynomial;
    if (!monomials.empty()) {
        AlbaNumber previousDegree(getDegree(monomials.front()));
        for (Monomial const& monomial : monomials) {
            AlbaNumber monomialDegree(getDegree(monomial));
            if (previousDegree != monomialDegree) {
                previousDegree = monomialDegree;
                result.emplace_back(partialPolynomial);
                partialPolynomial.clear();
            }
            partialPolynomial.addMonomial(monomial);
        }
    }
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, partialPolynomial);
}

void splitPolynomialsByDivisibilityOfExponents(Polynomials& result, Polynomial const& polynomial) {
    Polynomials collectedPolynomials;
    AlbaNumber polynomialDegree(getMaxDegree(polynomial));
    if (polynomialDegree.isIntegerType() && polynomialDegree > 0) {
        Monomials remainingMonomials = polynomial.getMonomialsConstReference();
        long long int degree = polynomialDegree.getInteger();
        for (; degree >= 2; degree--) {
            Polynomial partialPolynomial;
            Monomials collectedMonomials;
            for (Monomial const& remainingMonomial : remainingMonomials) {
                if (areExponentsDivisible(remainingMonomial, degree)) {
                    partialPolynomial.addMonomial(remainingMonomial);
                } else {
                    collectedMonomials.emplace_back(remainingMonomial);
                }
            }
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(collectedPolynomials, partialPolynomial);
            remainingMonomials = collectedMonomials;
        }
        simplifyThenEmplaceBackIfPolynomialIsNotEmpty(collectedPolynomials, Polynomial(remainingMonomials));
    }
    if (collectedPolynomials.size() > 1) {
        result = collectedPolynomials;
    }
}

void splitPolynomialsByFirstVariable(Polynomials& result, Polynomial const& polynomial) {
    Monomials monomials(polynomial.getMonomialsConstReference());
    Polynomial partialPolynomial;
    string firstVariableName;
    bool isFirst(true);
    for (Monomial const& monomial : monomials) {
        string monomialFirstVariableName(getFirstVariableName(monomial));
        if (!monomialFirstVariableName.empty()) {
            if (isFirst) {
                firstVariableName = monomialFirstVariableName;
                isFirst = false;
            }
            if (firstVariableName != monomialFirstVariableName) {
                firstVariableName = monomialFirstVariableName;
                result.emplace_back(partialPolynomial);
                partialPolynomial.clear();
            }
        }
        partialPolynomial.addMonomial(monomial);
    }
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, partialPolynomial);
}

void factorizeSmallerPolynomials(Polynomials& result, Polynomials const& smallerPolynomials) {
    factorizeSmallerPolynomialsByFactoringOutCommonFactors(result, smallerPolynomials);
    if (result.empty()) {
        factorizeSmallerPolynomialsBySubstitutingCommonFactorsToNewVariables(result, smallerPolynomials);
    }
}

void factorizeSmallerPolynomialsByFactoringOutCommonFactors(
    Polynomials& result, Polynomials const& smallerPolynomials) {
    if (smallerPolynomials.size() > 1) {
        Polynomials commonFactors;
        getCommonFactorsInThesePolynomials(commonFactors, smallerPolynomials);
        if (!commonFactors.empty() && !doesContainOnlyConstants(commonFactors)) {
            Polynomials remainingSmallerPolynomials;
            getPolynomialsWithRemovedCommonFactors(remainingSmallerPolynomials, smallerPolynomials, commonFactors);
            combinePolynomialsByAdditionThenEmplaceFactoredPolynomialIfNeeded(result, remainingSmallerPolynomials);
            for (Polynomial const& commonFactor : commonFactors) {
                simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, commonFactor);
            }
        }
    }
}

void factorizeSmallerPolynomialsBySubstitutingCommonFactorsToNewVariables(
    Polynomials& result, Polynomials const& smallerPolynomials) {
    SubstitutionOfVariablesToTerms variableSubstitution;
    if (smallerPolynomials.size() > 1) {
        Polynomial newPolynomialWithVariables(
            getNewPolynomialWithNewVariables(variableSubstitution, smallerPolynomials));
        if (!variableSubstitution.isEmpty()) {
            factorizePolynomialWithNewVariables(result, newPolynomialWithVariables, variableSubstitution);
            if (IsEmptyOrContainConstantsOrOneNonConstant(result)) {
                result.clear();
            }
        }
    }
}

void factorizePolynomialWithNewVariables(
    Polynomials& result, Polynomial const& newPolynomialWithVariables,
    SubstitutionOfVariablesToTerms const& variableSubstitution) {
    Polynomials factorizedPolynomialsWithVariables(factorizeAPolynomial(newPolynomialWithVariables));
    if (factorizedPolynomialsWithVariables.size() > 1) {
        for (Polynomial const& factorizedPolynomialWithVariables : factorizedPolynomialsWithVariables) {
            Polynomial finalPolynomial(createPolynomialIfPossible(
                variableSubstitution.performSubstitutionTo(factorizedPolynomialWithVariables)));
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, finalPolynomial);
        }
    }
}

void getCommonFactorsInThesePolynomials(Polynomials& commonFactors, Polynomials const& smallerPolynomials) {
    if (!smallerPolynomials.empty()) {
        commonFactors = factorizeAPolynomial(smallerPolynomials.front());
        for (auto it = smallerPolynomials.cbegin() + 1; it != smallerPolynomials.cend(); it++) {
            Polynomials commonFactorsOfAPolynomial(factorizeAPolynomial(*it));
            updateToGetSubsetOfFactors(commonFactors, commonFactorsOfAPolynomial);
        }
    }
}

Polynomial getNewPolynomialWithNewVariables(
    SubstitutionOfVariablesToTerms& variableSubstitution, Polynomials const& smallerPolynomials) {
    Polynomial newPolynomialWithVariables;
    for (Polynomial const& smallerPolynomial : smallerPolynomials) {
        Polynomial newSmallerPolynomialWithVariables(createPolynomialFromNumber(1));
        Polynomials factors(factorizeAPolynomial(smallerPolynomial));
        for (Polynomial const& factor : factors) {
            if (isOneMonomial(factor)) {
                newSmallerPolynomialWithVariables.multiplyMonomial(getFirstMonomial(factor));
            } else {
                string variableNameForSubstitution(createVariableNameForSubstitution(Term(factor)));
                variableSubstitution.putVariableWithTerm(variableNameForSubstitution, factor);
                newSmallerPolynomialWithVariables.multiplyMonomial(
                    createMonomialFromVariable(Variable(variableNameForSubstitution)));
            }
        }
        newPolynomialWithVariables.addPolynomial(newSmallerPolynomialWithVariables);
    }
    return newPolynomialWithVariables;
}

void getPolynomialsWithRemovedCommonFactors(
    Polynomials& result, Polynomials const& polynomialsWithCommonFactors, Polynomials const& commonFactors) {
    for (Polynomial const& polynomialWithCommonFactors : polynomialsWithCommonFactors) {
        Polynomial resultPolynomial(polynomialWithCommonFactors);
        for (Polynomial const& commonFactor : commonFactors) {
            PolynomialOverPolynomial divideProcess(resultPolynomial, commonFactor);
            PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(divideProcess.divide());
            if (isTheValue(quotientAndRemainder.remainder, 0)) {
                resultPolynomial = quotientAndRemainder.quotient;
            }
        }
        result.emplace_back(resultPolynomial);
    }
}

void updateToGetSubsetOfFactors(Polynomials& commonFactors, Polynomials const& commonFactorsOfAPolynomial) {
    Polynomials previousCommonFactors(commonFactors);
    Polynomials currentCommonFactors(commonFactorsOfAPolynomial);
    commonFactors.clear();
    for (int i = 0; i < static_cast<int>(previousCommonFactors.size()); i++) {
        bool isFound(false);
        Polynomial const& previousCommonFactor(previousCommonFactors.at(i));
        for (int j = 0; j < static_cast<int>(currentCommonFactors.size()); j++) {
            Polynomial const& currentCommonFactor(currentCommonFactors.at(j));
            if (isOneMonomial(previousCommonFactor) && isOneMonomial(currentCommonFactor)) {
                Monomial gcfMonomial(getGcfMonomialInMonomials(                    {getFirstMonomial(previousCommonFactor), getFirstMonomial(currentCommonFactor)}));
                gcfMonomial.simplify();
                if (!isTheValue(gcfMonomial, 1)) {
                    commonFactors.emplace_back(Polynomial{gcfMonomial});                    isFound = true;
                }
            } else if (previousCommonFactor == currentCommonFactor) {
                commonFactors.emplace_back(currentCommonFactor);
                isFound = true;
            }
            if (isFound) {
                currentCommonFactors.erase(currentCommonFactors.begin() + j);
                break;
            }
        }
        if (isFound) {
            previousCommonFactors.erase(previousCommonFactors.begin() + i);
            i--;
        }
    }
}

void combinePolynomialsByAdditionThenEmplaceFactoredPolynomialIfNeeded(
    Polynomials& result, Polynomials const& smallerPolynomials) {
    Polynomial combinedPolynomial;
    for (Polynomial const& smallerPolynomial : smallerPolynomials) {
        combinedPolynomial.addPolynomial(smallerPolynomial);
    }
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, combinedPolynomial);
}

}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
