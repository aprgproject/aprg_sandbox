#include "SimplificationUtilities.hpp"

#include <BooleanAlgebra/Algorithm/QuineMcCluskey/QuineMcCluskey.hpp>
#include <BooleanAlgebra/Algorithm/QuineMcCluskey/Utilities/Utilities.hpp>
#include <BooleanAlgebra/Mutation/DualOperationMutator.hpp>
#include <BooleanAlgebra/Operations/AccumulateOperations.hpp>
#include <BooleanAlgebra/Simplification/SimplificationOfExpression.hpp>
#include <BooleanAlgebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <algorithm>

using namespace std;

namespace alba {

namespace booleanAlgebra {

namespace Simplification {

using Minterm = uint64_t;
using QuineMcCluskey = QuineMcCluskey<Minterm>;
using Implicant = QuineMcCluskey::Implicant;
using Implicants = QuineMcCluskey::Implicants;

// utilties functions for this file
namespace {
Implicants getBestPrimeImplicantsUsingQuineMcCluskey(Term const& term, VariableNamesSet const& variableNames) {
    int numberOfBits = variableNames.size();
    QuineMcCluskey qmc;
    SubstitutionOfVariablesToValues substitution;
    for (Minterm minterm = 0; minterm < static_cast<Minterm>(1 << numberOfBits); minterm++) {
        int i = 0;
        for (string const& variableName : variableNames) {
            bool value = (minterm & (1 << i++)) > 0;
            substitution.putVariableWithValue(variableName, value);
        }
        Term output(substitution.performSubstitutionTo(term));
        if (output.isConstant()) {
            qmc.setInputOutput(minterm, getLogicalValue(output.getBooleanValue()));
        }
    }
    qmc.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qmc.findAllCombinations();
    Implicants primeImplicants(qmc.getAllPrimeImplicants());
    Implicants bestPrimeImplicants(qmc.getBestPrimeImplicants(primeImplicants));
    return bestPrimeImplicants;
}

void simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
    WrappedTerms& newWrappedTerms, OperatorLevel& mainOperatorLevel, Expression const& subExpression) {
    OperatorLevel subExpressionOperatorLevel(subExpression.getCommonOperatorLevel());
    if (subExpression.containsOnlyOneTerm() || OperatorLevel::Unknown == mainOperatorLevel ||
        subExpressionOperatorLevel == mainOperatorLevel) {
        if (OperatorLevel::Unknown == mainOperatorLevel) {
            mainOperatorLevel = subExpressionOperatorLevel;
        }
        simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
            newWrappedTerms, mainOperatorLevel, subExpression.getWrappedTerms());
    } else {
        newWrappedTerms.emplace_back(Term(subExpression));
    }
}

void distributeTermsWithRecursion(
    Term& outputTerm, Terms& innerTermsCombinations, Expressions const& innerExpressions, Term const& outerFactor,
    OperatorLevel const outerOperation, OperatorLevel const innerOperation, int const index) {
    if (index < static_cast<int>(innerExpressions.size())) {
        for (WrappedTerm const& subExpressionTerm : innerExpressions[index].getWrappedTerms()) {
            innerTermsCombinations.emplace_back(
                getTermConstReferenceFromUniquePointer(subExpressionTerm.baseTermPointer));
            distributeTermsWithRecursion(
                outputTerm, innerTermsCombinations, innerExpressions, outerFactor, outerOperation, innerOperation,
                index + 1);
            innerTermsCombinations.pop_back();
        }
    } else {
        Term partialTerm(outerFactor);
        accumulateTerms(partialTerm, innerTermsCombinations, outerOperation);
        accumulateTerms(outputTerm, {partialTerm}, innerOperation);
    }
}

Terms getTermOrSubTerms(Term const& term) {
    Terms terms;
    if (term.isExpression()) {
        for (WrappedTerm const& subTerm : term.getExpressionConstReference().getWrappedTerms()) {
            terms.emplace_back(getTermConstReferenceFromUniquePointer(subTerm.baseTermPointer));
        }
    } else {
        terms.emplace_back(term);
    }
    return terms;
}

OperatorLevel getSubOperatorLevel(Term const& term1, Term const& term2) {
    OperatorLevel result(OperatorLevel::Unknown);
    if (term1.isExpression()) {
        result = term1.getExpressionConstReference().getCommonOperatorLevel();
    } else if (term2.isExpression()) {
        result = term2.getExpressionConstReference().getCommonOperatorLevel();
    }
    return result;
}
}  // namespace

void simplifyTermWithOuterOrAndInnerAnd(Term& term) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

void simplifyTermWithOuterAndAndInnerOr(Term& term) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

void simplifyByQuineMcKluskey(Term& term) {
    VariableNamesSet variableNames(getVariableNames(term));
    int numberOfBits = variableNames.size();
    if (numberOfBits > 0 && numberOfBits <= static_cast<int>(AlbaBitValueUtilities<Minterm>::getNumberOfBits())) {
        // cannot be used if number of bits is beyond limit
        OperatorLevel targetOuter, targetInner;
        retrieveTargetOperations(targetOuter, targetInner);
        if (OperatorLevel::And == targetOuter && OperatorLevel::Or == targetInner) {
            DualOperationMutator mutator;
            mutator.mutateTerm(term);  // get dual if target is "outer and" "inner or"
        }
        Implicants bestPrimeImplicants(getBestPrimeImplicantsUsingQuineMcCluskey(term, variableNames));
        if (!bestPrimeImplicants.empty()) {
            Expression newExpression;
            for (Implicant const& bestPrimeImplicant : bestPrimeImplicants) {
                Expression implicantExpression;
                string bitString(bestPrimeImplicant.getEquivalentString(variableNames.size()));
                int i = variableNames.size() - 1;
                for (string const& variableName : variableNames) {
                    char primeBit(bitString[i]);
                    implicantExpression.putTerm(
                        getTermFromVariableAndPrimeValue(variableName, primeBit),
                        targetInner);  // if "outer and" "inner or", its the saved as dual
                    i--;
                }
                newExpression.putTerm(
                    Term(implicantExpression), targetOuter);  // if "outer and" "inner or", its the saved as dual
            }
            term = Term(newExpression);
        }
    }
}

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
    WrappedTerms& newWrappedTerms, OperatorLevel& mainOperatorLevel, WrappedTerms const& oldWrappedTerms) {
    for (WrappedTerm const& oldWrappedTerm : oldWrappedTerms) {
        Term const& term(getTermConstReferenceFromUniquePointer(oldWrappedTerm.baseTermPointer));
        if (term.isExpression()) {
            Expression subExpression(term.getExpressionConstReference());
            subExpression.simplify();
            simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
                newWrappedTerms, mainOperatorLevel, subExpression);
        } else if (isNonEmptyOrNonOperatorType(term)) {
            Term newTerm(term);
            newTerm.simplify();
            newWrappedTerms.emplace_back(newTerm);
        }
    }
}

Terms createUniqueTerms(WrappedTerms const& terms) {
    Terms result;
    result.reserve(terms.size());
    transform(terms.cbegin(), terms.cend(), back_inserter(result), [](WrappedTerm const& wrappedTerm) {
        return getTermConstReferenceFromUniquePointer(wrappedTerm.baseTermPointer);
    });
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}

void combineComplementaryTerms(Terms& termsToCombine, OperatorLevel const operatorLevel) {
    // Convert complimentary terms
    // x & x’ = 0
    // x | x’ = 1
    Terms negatedTerms(termsToCombine);
    for (Term& negatedTerm : negatedTerms) {
        negatedTerm.negate();
    }
    for (int i = 0; i < static_cast<int>(termsToCombine.size()); i++) {
        bool hasComplimentary(false);
        for (int j = i + 1; j < static_cast<int>(termsToCombine.size()); j++) {
            if (termsToCombine[i] == negatedTerms[j]) {
                termsToCombine.erase(termsToCombine.begin() + j);
                negatedTerms.erase(negatedTerms.begin() + j);
                hasComplimentary = true;
            }
        }
        if (hasComplimentary) {
            termsToCombine[i] = Term(getShortCircuitValueEffectInOperation(operatorLevel));
        }
    }
}

void combineTermsByCheckingCommonFactor(Terms& termsToCombine, OperatorLevel const operatorLevel) {
    for (int i = 0; i < static_cast<int>(termsToCombine.size()); i++) {
        for (int j = i + 1; j < static_cast<int>(termsToCombine.size()); j++) {
            Term combinedTerm(
                combineTwoTermsByCheckingCommonFactorIfPossible(termsToCombine[i], termsToCombine[j], operatorLevel));
            if (!combinedTerm.isEmpty()) {
                termsToCombine[i] = combinedTerm;
                termsToCombine.erase(termsToCombine.begin() + j);
                i--;
                break;
            }
        }
    }
}

Term combineTwoTermsByCheckingCommonFactorIfPossible(
    Term const& term1, Term const& term2, OperatorLevel const operatorLevel) {
    Term result;
    bool isOneOfTheTermANonExpression = !term1.isExpression() || !term2.isExpression();
    bool doesOperatorLevelMatchIfBothExpressions = term1.isExpression() && term2.isExpression() &&
                                                   term1.getExpressionConstReference().getCommonOperatorLevel() ==
                                                       term2.getExpressionConstReference().getCommonOperatorLevel();
    if (isOneOfTheTermANonExpression || doesOperatorLevelMatchIfBothExpressions) {
        Terms commonFactors;
        Terms uniqueTerms1(getTermOrSubTerms(term1));
        Terms uniqueTerms2(getTermOrSubTerms(term2));
        for (int i1 = 0; i1 < static_cast<int>(uniqueTerms1.size()); i1++) {
            for (int i2 = 0; i2 < static_cast<int>(uniqueTerms2.size()); i2++) {
                if (uniqueTerms1[i1] == uniqueTerms2[i2]) {
                    commonFactors.emplace_back(uniqueTerms1[i1]);
                    uniqueTerms1.erase(uniqueTerms1.begin() + i1);
                    uniqueTerms2.erase(uniqueTerms2.begin() + i2);
                    i1--;
                    break;
                }
            }
        }
        if (!commonFactors.empty()) {
            OperatorLevel subOperatorLevel(getSubOperatorLevel(term1, term2));
            Term uniqueTerm1(getNoEffectValueInOperation(subOperatorLevel));
            Term uniqueTerm2(getNoEffectValueInOperation(subOperatorLevel));
            accumulateTerms(uniqueTerm1, uniqueTerms1, subOperatorLevel);
            accumulateTerms(uniqueTerm2, uniqueTerms2, subOperatorLevel);
            Term combinedUniqueTerm;
            accumulateTerms(combinedUniqueTerm, {uniqueTerm1, uniqueTerm2}, operatorLevel);
            combinedUniqueTerm.simplify();
            if (!combinedUniqueTerm.isExpression()) {
                accumulateTerms(result, commonFactors, subOperatorLevel);
                accumulateTerms(result, {combinedUniqueTerm}, subOperatorLevel);
            }
        }
    }
    return result;
}

void distributeTermsIfNeeded(
    Term& outputTerm, Terms const& inputTerms, OperatorLevel const distributeOuterOperation,
    OperatorLevel const distributeInnerOperation) {
    if (!inputTerms.empty()) {
        OperatorLevel targetOuter, targetInner;
        retrieveTargetOperations(targetOuter, targetInner);
        if (distributeOuterOperation == targetInner &&
            distributeInnerOperation == targetOuter)  // distribute only if its different from target
        {
            Terms outerFactors;
            Expressions innerExpressions;
            for (Term const& inputTerm : inputTerms) {
                if (inputTerm.isExpression()) {
                    Expression const& subExpression(inputTerm.getExpressionConstReference());
                    if (distributeInnerOperation == subExpression.getCommonOperatorLevel()) {
                        innerExpressions.emplace_back(subExpression);
                    } else if (distributeOuterOperation == subExpression.getCommonOperatorLevel()) {
                        for (WrappedTerm const& subExpressionTerm : subExpression.getWrappedTerms()) {
                            outerFactors.emplace_back(
                                getTermConstReferenceFromUniquePointer(subExpressionTerm.baseTermPointer));
                        }
                    }
                } else {
                    outerFactors.emplace_back(inputTerm);
                }
            }
            if (!innerExpressions.empty()) {
                Term outerFactor;
                accumulateTerms(outerFactor, outerFactors, distributeOuterOperation);
                Terms innerTermsCombinations;
                distributeTermsWithRecursion(
                    outputTerm, innerTermsCombinations, innerExpressions, outerFactor, distributeOuterOperation,
                    distributeInnerOperation, 0U);
            }
        }
    }
}

void retrieveTargetOperations(OperatorLevel& targetOuter, OperatorLevel& targetInner) {
    if (SimplificationOfExpression::shouldSimplifyWithOuterOrAndInnerAnd()) {
        targetOuter = OperatorLevel::Or;
        targetInner = OperatorLevel::And;
    } else if (SimplificationOfExpression::shouldSimplifyWithOuterAndAndInnerOr()) {
        targetOuter = OperatorLevel::And;
        targetInner = OperatorLevel::Or;
    } else {
        targetOuter = OperatorLevel::Or;
        targetInner = OperatorLevel::And;
    }
}

}  // namespace Simplification

}  // namespace booleanAlgebra

}  // namespace alba
