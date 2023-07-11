#include "MonomialHelpers.hpp"

#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

bool canBeMergedInAMonomialByAdditionOrSubtraction(Term const& term1, Term const& term2) {
    bool result(false);
    if (term1.isConstant() && term2.isConstant()) {
        result = true;
    } else if (term1.isVariable() && term2.isVariable()) {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getAsVariable(), term2.getAsVariable());
    } else if (term1.isMonomial() && term2.isMonomial()) {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getAsMonomial(), term2.getAsMonomial());
    } else if (term1.isMonomial() && term2.isVariable()) {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getAsMonomial(), term2.getAsVariable());
    } else if (term1.isVariable() && term2.isMonomial()) {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term2.getAsMonomial(), term1.getAsVariable());
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2) {
    Monomial::VariablesToExponentsMap const& variablesMap1(monomial1.getVariablesToExponentsMap());
    Monomial::VariablesToExponentsMap const& variablesMap2(monomial2.getVariablesToExponentsMap());
    bool result(false);
    if (variablesMap1.size() == variablesMap2.size()) {
        using MapConstIterator = Monomial::VariablesToExponentsMap::const_iterator;
        using MismatchResultType = pair<MapConstIterator, MapConstIterator>;
        MismatchResultType mismatchResult =
            mismatch(variablesMap1.cbegin(), variablesMap1.end(), variablesMap2.cbegin());
        result = mismatchResult.first == variablesMap1.cend();
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable) {
    Monomial::VariablesToExponentsMap const& variablesMap(monomial.getVariablesToExponentsMap());
    string variableName(variable.getVariableName());
    bool result(false);
    if (variablesMap.size() == 1) {
        if (variablesMap.find(variableName) != variablesMap.cend()) {
            result = variablesMap.at(variableName) == 1;
        }
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2) {
    return variable1 == variable2;
}

bool doesCoefficientsHaveSameSign(Monomial const& monomial1, Monomial const& monomial2) {
    return getSign(monomial1.getCoefficient()) == getSign(monomial2.getCoefficient());
}

bool hasNegativeExponents(Monomial const& monomial) {
    bool result(false);
    for (auto const& [variableName, exponent] : monomial.getVariablesToExponentsMap()) {
        if (exponent < 0) {
            result = true;
            break;
        }    }
    return result;
}
bool isConstantOnly(Monomial const& monomial) {
    Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMap());
    return variableToExponentMap.empty();
}

bool isVariableOnly(Monomial const& monomial) {
    Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMap());
    return monomial.getCoefficient() == 1 && variableToExponentMap.size() == 1 &&
           (variableToExponentMap.cbegin())->second == 1;
}

bool hasASingleVariable(Monomial const& monomial) {
    Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMap());
    return variableToExponentMap.size() == 1;
}

string getFirstVariableName(Monomial const& monomial) {
    Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMap());
    string variableName;
    if (!variableToExponentMap.empty()) {
        variableName = (variableToExponentMap.cbegin())->first;
    }
    return variableName;
}

AlbaNumber getDegree(Monomial const& monomial) {
    AlbaNumber degree;
    for (auto const& [variableName, exponent] : monomial.getVariablesToExponentsMap()) {
        degree = degree + exponent;
    }
    return degree;
}
AlbaNumber getMaxExponent(Monomial const& monomial) {
    AlbaNumber maxExponent;
    auto const& variablesToExponentsMap(monomial.getVariablesToExponentsMap());    if (!variablesToExponentsMap.empty()) {
        auto it = variablesToExponentsMap.cbegin();
        maxExponent = it->second;
        it++;
        for (; it != variablesToExponentsMap.cend(); it++) {
            maxExponent = max(maxExponent, it->second);
        }
    }
    return maxExponent;
}

AlbaNumber getGcfOfExponentsInMonomial(Monomial const& monomial) {
    AlbaNumber commonExponent(1);
    bool isFirst(true);
    for (auto const& [variableName, exponent] : monomial.getVariablesToExponentsMap()) {
        if (exponent.isIntegerOrFractionType()) {
            if (isFirst) {
                commonExponent = exponent;                isFirst = false;
            } else {
                commonExponent = getGreatestCommonFactor(commonExponent, exponent);
            }        }
    }
    return commonExponent;
}

AlbaNumber getGcfOfCoefficientsInMonomials(Monomials const& monomials) {
    AlbaNumber commonCoefficient(1);
    bool isFirst(true);
    for (Monomial const& monomial : monomials) {
        AlbaNumber const& coefficient(monomial.getCoefficient());
        if (coefficient.isIntegerOrFractionType()) {
            if (isFirst) {
                commonCoefficient = coefficient;
                isFirst = false;
            } else {
                commonCoefficient = getGreatestCommonFactor(commonCoefficient, coefficient);
            }
        }
    }
    return commonCoefficient;
}

AlbaNumber getLcmOfCoefficientsInMonomials(Monomials const& monomials) {
    AlbaNumber commonCoefficient(1);
    bool isFirst(true);
    for (Monomial const& monomial : monomials) {
        AlbaNumber const& coefficient(monomial.getCoefficient());
        if (coefficient.isIntegerOrFractionType()) {
            if (isFirst) {
                commonCoefficient = coefficient;
                isFirst = false;
            } else {
                commonCoefficient = getLeastCommonMultiple(commonCoefficient, coefficient);
            }
        }
    }
    return commonCoefficient;
}

AlbaNumber getCommonSignInMonomials(Monomials const& monomials) {
    bool isFirstMonomial(true);
    bool isFirstMonomialNegative(false);
    int negativeSignCount(0);
    for (Monomial const& monomial : monomials) {
        if (monomial.getCoefficient() < AlbaNumber(0)) {
            negativeSignCount++;
            if (isFirstMonomial) {
                isFirstMonomialNegative = true;
            }
        }
        isFirstMonomial = false;
    }
    return (isFirstMonomialNegative ||
            (negativeSignCount > 0 && negativeSignCount == static_cast<int>(monomials.size())))
               ? -1
               : 1;
}

Monomial getGcfMonomialInMonomials(Monomials const& monomials) {
    AlbaNumber commonCoefficient(getGcfOfCoefficientsInMonomials(monomials));
    Monomial minExponentMonomial(getMonomialWithMinimumExponentsInMonomials(monomials));
    if (commonCoefficient != 1) {
        commonCoefficient = getCommonSignInMonomials(monomials) * commonCoefficient;
    }
    minExponentMonomial.setConstant(commonCoefficient);
    minExponentMonomial.simplify();
    return minExponentMonomial;
}

Monomial getLcmMonomialInMonomials(Monomials const& monomials) {
    AlbaNumber lcmCoefficient(getLcmOfCoefficientsInMonomials(monomials));
    Monomial maxExponentMonomial(getMonomialWithMaximumExponentsInMonomials(monomials));
    maxExponentMonomial.setConstant(getCommonSignInMonomials(monomials) * lcmCoefficient);
    maxExponentMonomial.simplify();
    return maxExponentMonomial;
}

Monomial compareMonomialsAndSaveMinimumExponentsForEachVariable(
    Monomial const& firstMonomial, Monomial const& secondMonomial) {
    Monomial::VariablesToExponentsMap newVariableExponentMap;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromMonomial(firstMonomial);
    variableNamesRetriever.retrieveFromMonomial(secondMonomial);
    for (string const& variableName : variableNamesRetriever.getVariableNames()) {
        newVariableExponentMap[variableName] = min(
            firstMonomial.getExponentForVariable(variableName), secondMonomial.getExponentForVariable(variableName));
    }
    return Monomial(1, newVariableExponentMap);
}

Monomial compareMonomialsAndSaveMaximumExponentsForEachVariable(
    Monomial const& firstMonomial, Monomial const& secondMonomial) {
    Monomial::VariablesToExponentsMap newVariableExponentMap;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromMonomial(firstMonomial);
    variableNamesRetriever.retrieveFromMonomial(secondMonomial);
    for (string const& variableName : variableNamesRetriever.getVariableNames()) {
        newVariableExponentMap[variableName] = max(
            firstMonomial.getExponentForVariable(variableName), secondMonomial.getExponentForVariable(variableName));
    }
    return Monomial(1, newVariableExponentMap);
}

Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials) {
    Monomial monomialWithMinimumExponents(1, {});
    if (!monomials.empty()) {
        monomialWithMinimumExponents = monomials.front();
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); it++) {
            monomialWithMinimumExponents =
                compareMonomialsAndSaveMinimumExponentsForEachVariable(monomialWithMinimumExponents, *it);
        }
        monomialWithMinimumExponents.simplify();
    }
    return monomialWithMinimumExponents;
}

Monomial getMonomialWithMaximumExponentsInMonomials(Monomials const& monomials) {
    Monomial monomialWithMaximumExponents(1, {});
    if (!monomials.empty()) {
        monomialWithMaximumExponents = monomials.front();
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); it++) {
            monomialWithMaximumExponents =
                compareMonomialsAndSaveMaximumExponentsForEachVariable(monomialWithMaximumExponents, *it);
        }
        monomialWithMaximumExponents.simplify();
    }
    return monomialWithMaximumExponents;
}

}  // namespace algebra

}  // namespace alba
