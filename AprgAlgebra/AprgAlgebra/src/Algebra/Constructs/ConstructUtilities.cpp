#include "ConstructUtilities.hpp"

#include <Algebra/Constructs/PolynomialRaiseToAnUnsignedInt.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

#include <algorithm>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

PolynomialOverPolynomialOptional createPolynomialOverPolynomialFromTermIfPossible(Term const& term) {
    PolynomialOverPolynomialOptional result;
    if (canBeConvertedToPolynomial(term)) {
        result.emplace(createPolynomialIfPossible(term), createPolynomialFromNumber(1));
    } else if (term.isExpression()) {
        Expression const& expression(term.getAsExpression());
        if (OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel()) {
            bool canBeConvertedToPolynomialOverPolynomial(true);
            Polynomial numerator(createPolynomialFromNumber(1));
            Polynomial denominator(createPolynomialFromNumber(1));
            for (TermWithDetails const& termWithDetails : expression.getTermsWithAssociation().getTermsWithDetails()) {
                Term const& termInExpression(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
                if (canBeConvertedToPolynomial(termInExpression)) {
                    if (termWithDetails.hasPositiveAssociation()) {
                        numerator.multiplyPolynomial(createPolynomialIfPossible(termInExpression));
                    } else {
                        denominator.multiplyPolynomial(createPolynomialIfPossible(termInExpression));
                    }
                } else {
                    canBeConvertedToPolynomialOverPolynomial = false;
                    break;
                }
            }
            if (canBeConvertedToPolynomialOverPolynomial) {
                result.emplace(numerator, denominator);
            }
        }
    }
    if (result) {
        result->simplify();
    }
    return result;
}

TermsOverTerms createTermsOverTermsFromTerm(Term const& term) {
    TermsOverTerms result;
    bool isResultUpdatedWithContent(false);
    if (term.isExpression()) {
        Expression const& expression(term.getAsExpression());
        if (OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel()) {
            result = TermsOverTerms(expression.getTermsWithAssociation().getTermsWithDetails());
            isResultUpdatedWithContent = true;
        }
    }
    if (!isResultUpdatedWithContent) {
        result = TermsOverTerms({term}, {1});
    }
    result.simplify();
    return result;
}

TermRaiseToANumber createTermRaiseToANumberFromTerm(Term const& term) {
    TermRaiseToANumber result;
    if (term.isMonomial()) {
        result = createTermRaiseToANumberFromMonomial(term.getAsMonomial());
    } else if (term.isPolynomial()) {
        result = createTermRaiseToANumberFromPolynomial(term.getAsPolynomial());
    } else if (term.isExpression()) {
        result = createTermRaiseToANumberFromExpression(term.getAsExpression());
    }
    if (result.isEmpty()) {
        result = TermRaiseToANumber(term, 1);
    }
    result.getBaseReference().simplify();
    return result;
}

TermRaiseToANumber createTermRaiseToANumberFromMonomial(Monomial const& monomial) {
    Monomial newMonomial(monomial);
    Monomial::VariablesToExponentsMap const& variablesToExponentsMap(newMonomial.getVariablesToExponentsMap());
    AlbaNumber exponent = (variablesToExponentsMap.size() == 1) ? (variablesToExponentsMap.cbegin())->second
                                                                : getGcfOfExponentsInMonomial(newMonomial);
    newMonomial.raiseToPowerNumber(AlbaNumber(1) / exponent);    return TermRaiseToANumber(Term(newMonomial), exponent);
}

TermRaiseToANumber createTermRaiseToANumberFromPolynomial(Polynomial const& polynomial) {    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);
    return TermRaiseToANumber(
        Term(polynomialRaiseToAnUnsignedInt.getBase()), polynomialRaiseToAnUnsignedInt.getExponent());
}

TermRaiseToANumber createTermRaiseToANumberFromExpression(Expression const& expression) {
    TermRaiseToANumber result;
    if (OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel()) {
        createTermRaiseToANumberFromRaiseToPowerExpression(result, expression);
    } else if (OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel()) {
        createTermRaiseToANumberFromMultiplicationAndDivisionExpression(result, expression);
    }
    if (result.isEmpty()) {
        result = TermRaiseToANumber(convertExpressionToSimplestTerm(expression), 1);
    }
    return result;
}

void createTermRaiseToANumberFromRaiseToPowerExpression(TermRaiseToANumber& result, Expression const& expression) {
    TermsWithDetails raiseToPowerTerms(expression.getTermsWithAssociation().getTermsWithDetails());
    if (raiseToPowerTerms.size() == 1) {
        Term const& base(getTermConstReferenceFromUniquePointer(raiseToPowerTerms.back().baseTermPointer));
        result = TermRaiseToANumber(base, 1);
    } else if (raiseToPowerTerms.size() >= 2) {
        AlbaNumber combinedExponentValue(1);
        for (auto it = raiseToPowerTerms.begin() + 1; it != raiseToPowerTerms.end(); it++) {
            Term& exponentTerm(getTermReferenceFromUniquePointer(it->baseTermPointer));
            if (exponentTerm.isConstant()) {
                combinedExponentValue = combinedExponentValue * exponentTerm.getAsNumber();
                exponentTerm.getAsConstantReference().setNumber(1);
            } else if (exponentTerm.isMonomial()) {
                combinedExponentValue = combinedExponentValue * exponentTerm.getAsMonomial().getCoefficient();
                exponentTerm.getAsMonomialReference().setConstant(1);
            }
        }        raiseToPowerTerms.erase(
            remove_if(
                raiseToPowerTerms.begin() + 1, raiseToPowerTerms.end(),
                [&](TermWithDetails const& raiseToPowerTerm) {                    Term const& exponentTerm(getTermConstReferenceFromUniquePointer(raiseToPowerTerm.baseTermPointer));
                    return willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(exponentTerm);
                }),
            raiseToPowerTerms.end());

        Term newBase(createTermWithRaiseToPowerTermsWithDetails(raiseToPowerTerms));
        newBase.simplify();
        result = TermRaiseToANumber(newBase, combinedExponentValue);
        // how about if exponent is polynomial or expression? how do we extract constant? should we introduce
        // factorization here?
    }
}

void createTermRaiseToANumberFromMultiplicationAndDivisionExpression(
    TermRaiseToANumber& result, Expression const& expression) {
    TermsOverTerms originalTot(createTermsOverTermsFromTerm(Term(expression)));
    originalTot.setAsShouldSimplifyToFactors(true);
    TermsRaiseToNumbers termsRaiseToNumbers(originalTot.getTermsRaiseToNumbers());

    bool isFirst(true);
    AlbaNumber commonExponent(1);
    bool areAllExponentsNegative(true);
    for (auto const& [base, exponent] : termsRaiseToNumbers.getBaseToExponentMap()) {
        if (!base.isConstant()) {
            if (exponent > 0) {
                areAllExponentsNegative = false;            }
            if (isFirst) {
                commonExponent = exponent;
                isFirst = false;            } else {
                commonExponent = getGreatestCommonFactor(commonExponent, exponent);
            }
        }
    }
    if (areAllExponentsNegative && commonExponent > 0) {
        commonExponent *= -1;
    }
    for (auto const& [base, exponent] : termsRaiseToNumbers.getBaseToExponentMap()) {
        termsRaiseToNumbers.setBaseAndExponent(base, exponent / commonExponent);
    }

    TermsOverTerms totWithoutCommonExponent(        termsRaiseToNumbers.getTermWithDetailsInMultiplicationAndDivisionOperation());
    totWithoutCommonExponent.setAsShouldSimplifyToFactors(true);
    result = TermRaiseToANumber(totWithoutCommonExponent.getCombinedTerm(), commonExponent);
}
TermRaiseToTerms createTermRaiseToTermsFromTerm(Term const& term) {
    TermRaiseToTerms result;
    if (term.isMonomial()) {
        TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromMonomial(term.getAsMonomial()));
        result.setBaseAndExponent(termRaiseToANumber.getBase(), termRaiseToANumber.getExponent());
    } else if (term.isPolynomial()) {
        TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromPolynomial(term.getAsPolynomial()));
        result.setBaseAndExponent(termRaiseToANumber.getBase(), termRaiseToANumber.getExponent());
    } else if (term.isExpression()) {
        result = createTermRaiseToTermsFromExpression(term.getAsExpression());    }
    if (result.isEmpty()) {
        result = TermRaiseToTerms(term, 1);
    }    result.getBaseReference().simplify();
    return result;
}

TermRaiseToTerms createTermRaiseToTermsFromExpression(Expression const& expression) {
    TermRaiseToTerms result;
    if (OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel()) {
        createTermRaiseToTermsFromRaiseToPowerExpression(result, expression);
    } else if (OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel()) {
        createTermRaiseToTermsFromMultiplicationAndDivisionExpression(result, expression);
    }
    if (result.isEmpty()) {
        result = TermRaiseToTerms(convertExpressionToSimplestTerm(expression), 1);
    }
    return result;
}

void createTermRaiseToTermsFromRaiseToPowerExpression(TermRaiseToTerms& result, Expression const& expression) {
    result = TermRaiseToTerms(expression.getTermsWithAssociation().getTermsWithDetails());
}

void createTermRaiseToTermsFromMultiplicationAndDivisionExpression(
    TermRaiseToTerms& result, Expression const& expression) {
    Terms originalBases;
    AlbaNumbers constantFactorsOfExponents;
    vector<TermsRaiseToNumbers> nonConstantFactorsOfExponents;
    TermsRaiseToNumbers commonNonConstantFactorsOfExponents;
    Term commonExponent;

    TermsOverTerms originalTot(createTermsOverTermsFromTerm(Term(expression)));
    originalTot.setAsShouldSimplifyToFactors(true);
    TermsRaiseToTerms originalTermsRaiseToTerms(originalTot.getTermsRaiseToTerms());

    AlbaNumbers originalConstants;
    TermsWithDetails originalExponentsWithDetails;
    for (auto const& [base, exponent] : originalTermsRaiseToTerms.getBaseToExponentMap()) {
        if (base.isConstant() && exponent.isConstant()) {
            originalConstants.emplace_back(base.getAsNumber() ^ exponent.getAsNumber());
        } else {
            originalBases.emplace_back(base);
            originalExponentsWithDetails.emplace_back(exponent, TermAssociationType::Positive);        }
    }
    retrieveConstantAndNonConstantFactors(
        nonConstantFactorsOfExponents, constantFactorsOfExponents, originalExponentsWithDetails);    bool areAllConstantFactorsNegative(all_of(
        constantFactorsOfExponents.cbegin(), constantFactorsOfExponents.cend(),
        [](AlbaNumber const& constantFactor) { return constantFactor < 0; }));
    AlbaNumber constantGcf(getGcfOfConstants(constantFactorsOfExponents));
    if (areAllConstantFactorsNegative) {
        constantGcf = constantGcf * -1;
    }
    retrieveCommonNonConstantFactors(commonNonConstantFactorsOfExponents, nonConstantFactorsOfExponents);

    if (!originalConstants.empty()) {
        commonNonConstantFactorsOfExponents.clear();
    }
    commonExponent = commonNonConstantFactorsOfExponents.getCombinedTerm() * constantGcf;

    bool shouldContinueToGetCommonExponent(true);
    TermsWithDetails finalBasesWithDetails;
    for (AlbaNumber const& originalConstant : originalConstants) {
        AlbaNumber newConstantBase(originalConstant ^ (AlbaNumber(1) / constantGcf));
        if (newConstantBase.isIntegerType()) {
            finalBasesWithDetails.emplace_back(Term(newConstantBase), TermAssociationType::Positive);
        } else {
            shouldContinueToGetCommonExponent = false;
        }
    }

    if (shouldContinueToGetCommonExponent) {
        for (int i = 0;
             i < static_cast<int>(constantFactorsOfExponents.size()) &&
             i < static_cast<int>(nonConstantFactorsOfExponents.size()) && i < static_cast<int>(originalBases.size());
             i++) {
            AlbaNumber uniqueConstantExponent(constantFactorsOfExponents[i] / constantGcf);
            TermsRaiseToNumbers remainingNonConstantFactors(nonConstantFactorsOfExponents[i]);
            remainingNonConstantFactors.subtractExponents(commonNonConstantFactorsOfExponents);
            remainingNonConstantFactors.simplify();
            Term uniqueExponent(Term(uniqueConstantExponent) * remainingNonConstantFactors.getCombinedTerm());
            uniqueExponent.simplify();
            TermRaiseToTerms originalBaseToUniqueExponent(originalBases[i], uniqueExponent);
            finalBasesWithDetails.emplace_back(
                originalBaseToUniqueExponent.getCombinedTerm(), TermAssociationType::Positive);
        }

        Term finalBase(convertExpressionToSimplestTerm(
            Expression(OperatorLevel::MultiplicationAndDivision, finalBasesWithDetails)));
        finalBase.simplify();
        commonExponent.simplify();
        result = TermRaiseToTerms(finalBase, commonExponent);
    } else {
        result = TermRaiseToTerms(Term(expression), 1);
    }
}

}  // namespace algebra

}  // namespace alba
