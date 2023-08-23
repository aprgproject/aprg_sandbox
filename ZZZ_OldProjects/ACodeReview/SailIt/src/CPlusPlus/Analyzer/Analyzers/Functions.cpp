#include "../../Database/CPlusPlusDatabase.hpp"
#include "../../Term/TermChecker.hpp"
#include "../Findings/TemporaryFindings.hpp"
#include "../TermAnalyzer.hpp"
#include "../TermAnalyzerTemplateFunctions.hpp"

#include <iostream>

using namespace std;

namespace codeReview {

bool TermAnalyzer::isModifiedDueToFunctions(Looper const& startLooper) {
    DBGPRINT1("isModifiedDueToFunctions");
    bool isModified = true;
    if (isModifiedDueToFunctionDeclaration(startLooper))
        ;
    else if (isModifiedDueToFunctionDefinition(startLooper))
        ;
    else {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToFunctionDeclaration(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToFunctionDeclaration");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TC(TermCheckerType::isCPlusPlusType), TC(T(TermType::WhiteSpace)), TC(T(TermType::Identifier))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        Looper afterOpeningParenthesis(compareLooper);
        Looper afterClosingParenthesis(compareLooper);
        if (isBothParenthesesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningParenthesis, afterClosingParenthesis)) {
            Looper afterSemiColon(afterClosingParenthesis);
            if (isSemiColonFoundAndMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(afterSemiColon)) {
                VectorOfTerms terms(getTerms(startLooper, termCheckers));
                string const functionName(terms[2].getString());
                m_database.addFunction(functionName);
                CPlusPlusFunction& cPlusPlusFunction(m_database.getFunctionReferenceWithAlias(functionName));
                CPlusPlusFunctionSignature cPlusPlusFunctionSignature;
                cPlusPlusFunctionSignature.setReturnType(terms[0].getValueTypeReference());
                fillFunctionSignatureFromFunctionDeclaration(
                    Looper(afterOpeningParenthesis, afterClosingParenthesis - 1), cPlusPlusFunctionSignature);
                cPlusPlusFunction.addFunctionSignature(cPlusPlusFunctionSignature);
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(
                    afterSemiColon);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterSemiColon, TermType::ProcessedTerm);
                return true;
            }
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToFunctionDefinition(Looper const& startLooper) {
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TC(TermCheckerType::isCPlusPlusType), TC(T(TermType::WhiteSpace)),
        TC({T(TermType::Identifier), T(TermType::FunctionName)})};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        Looper afterOpeningParenthesis(compareLooper);
        Looper afterClosingParenthesis(compareLooper);
        if (isBothParenthesesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningParenthesis, afterClosingParenthesis)) {
            Looper afterOpeningBraces(afterClosingParenthesis);
            Looper afterClosingBraces(afterClosingParenthesis);
            if (isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                    afterClosingParenthesis, afterOpeningBraces, afterClosingBraces)) {
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
                VectorOfTerms terms(getTerms(startLooper, termCheckers));
                string const functionName(terms[2].getString());
                m_database.addFunction(functionName);
                CPlusPlusFunction& cPlusPlusFunction(m_database.getFunctionReferenceWithAlias(functionName));
                CPlusPlusFunctionSignature cPlusPlusFunctionSignature;
                cPlusPlusFunctionSignature.setReturnType(terms[0].getValueTypeReference());
                m_database.performInNewScope([&]() {
                    fillFunctionSignatureFromFunctionDeclaration(
                        Looper(afterOpeningParenthesis, afterClosingParenthesis - 1), cPlusPlusFunctionSignature);
                    analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces - 1));
                });
                if (cPlusPlusFunction.isFunctionSignatureExistAndNamesDoesNotMatch(cPlusPlusFunctionSignature)) {
                    addFinding(
                        constructFileLocator(__FILE__, __LINE__), "Names does not match in function database",
                        afterOpeningBraces);
                }
                cPlusPlusFunction.addFunctionSignature(cPlusPlusFunctionSignature);
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBraces);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterClosingBraces, TermType::ProcessedTerm);
                return true;
            }
        }
    }
    return false;
}

void TermAnalyzer::fillFunctionSignatureFromFunctionDeclaration(
    Looper const& startLooper, CPlusPlusFunctionSignature& cPlusPlusFunctionSignature) {
    array<TermChecker, 3> const parameterWithName{
        TC(TermCheckerType::isCPlusPlusType), TC(T(TermType::WhiteSpace)), TC(T(TermType::Identifier))};
    array<TermChecker, 1> const parameterWithoutName{TC(TermCheckerType::isCPlusPlusType)};
    array<TermChecker, 2> const separator{TC(T(TermType::Operator, ",")), TC(T(TermType::WhiteSpace))};
    simplifyExpressions(startLooper);
    bool isNextParameterExpected(true);
    Looper parameterLooper(startLooper);
    while (parameterLooper.isNotFinished()) {
        Looper parameterLooperCopy(parameterLooper);
        if (isNextParameterExpected) {
            if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                    parameterLooper, parameterWithName)) {
                VectorOfTerms terms(getTerms(parameterLooperCopy, parameterWithName));
                cPlusPlusFunctionSignature.addParameter(terms[0].getValueTypeReference(), terms[2].getString());
                isNextParameterExpected = false;
            } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                           parameterLooper, parameterWithoutName)) {
                cPlusPlusFunctionSignature.addParameter(
                    parameterLooperCopy.getContentReference().getValueTypeReference(), "");
                isNextParameterExpected = false;
            }
        } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                       parameterLooper, separator)) {
            isNextParameterExpected = true;
        }
        if (parameterLooperCopy.getCurrentIndex() == parameterLooper.getCurrentIndex()) {
            addFinding(
                constructFileLocator(__FILE__, __LINE__), "Unprocessed term in function declaration/definition",
                parameterLooper);
            break;
        }
    };
    incrementLooperIfWhiteSpaceAndNewLine<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(parameterLooper);
    if (parameterLooper.isNotFinished()) {
        addFinding(
            constructFileLocator(__FILE__, __LINE__),
            "Unrecognized function parameters in function declaration/definition", parameterLooper);
    }
}

void TermAnalyzer::fillFunctionSignatureFromFunctionCall(
    Looper const& startLooper, CPlusPlusFunctionSignature& cPlusPlusFunctionSignature) {
    array<TermChecker, 1> const parameter{TC(TermCheckerType::isValue)};
    array<TermChecker, 2> const separator{TC(T(TermType::Operator, ",")), TC(T(TermType::WhiteSpace))};
    simplifyExpressions(startLooper);
    bool isNextParameterExpected(true);
    Looper parameterLooper(startLooper);
    while (parameterLooper.isNotFinished()) {
        Looper parameterLooperCopy(parameterLooper);
        if (isNextParameterExpected) {
            if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                    parameterLooper, parameter)) {
                cPlusPlusFunctionSignature.addParameter(parameterLooperCopy.getContentReference().getValueType());
                isNextParameterExpected = false;
            }
        } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                       parameterLooper, separator)) {
            isNextParameterExpected = true;
        }
        if (parameterLooperCopy.getCurrentIndex() == parameterLooper.getCurrentIndex()) {
            addFinding(constructFileLocator(__FILE__, __LINE__), "Unprocessed term in function call", parameterLooper);
            break;
        }
    }
    incrementLooperIfWhiteSpaceAndNewLine<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(parameterLooper);
    if (parameterLooper.isNotFinished()) {
        addFinding(
            constructFileLocator(__FILE__, __LINE__), "Incorrect function parameters in function call",
            parameterLooper);
    }
}

}  // namespace codeReview
