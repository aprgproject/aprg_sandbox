#include <iostream>
#include <array>
#include "../Findings/TemporaryFindings.hpp"
#include "../TermAnalyzer.hpp"
#include "../TermAnalyzerTemplateFunctions.hpp"
#include "../../Database/CPlusPlusDatabase.hpp"
#include "../../Term/TermChecker.hpp"

using namespace std;

namespace codeReview
{

bool TermAnalyzer::isModifiedDueToStatements(Looper const& startLooper)
{
    DBGPRINT1("isModifiedDueToStatements");
    bool isModified = true;
    if(isModifiedDueToVariableDeclaration(startLooper));
    else if(isModifiedDueToCStyleArrayDeclaration(startLooper));
    else if(isModifiedDueToAssignment(startLooper));
    else if(isModifiedDueToRValueCanBeALine(startLooper));
    else if(isModifiedDueToUsingNamespaceKeyword(startLooper));
    else if(isModifiedDueToTypeDefStatement(startLooper));
    else
    {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToVariableDeclaration(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToVariableDeclaration");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{TC(TermCheckerType::isCPlusPlusType), TC(T(TermType::WhiteSpace))};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
    {
        CPlusPlusType type(startLooper.getContentReference().getValueTypeReference());
        VectorOfStrings variableNames;
        if(areVariableFoundForVariableDeclarationAndMoveLooper(compareLooper, variableNames))
        {
            for(string const& variableName : variableNames)
            {
                m_database.addVariable(variableName, type);
            }
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToCStyleArrayDeclaration(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToVariableDeclaration");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 7> const termCheckers{TC(TermCheckerType::isCPlusPlusType), TC(T(TermType::WhiteSpace)),
                TC({T(TermType::Identifier), T(TermType::Variable)}), TC(T(TermType::Operator, "[")),
                TC(T(TermType::Constant_Number)), TC(T(TermType::Operator, "]")),
                TC(T(TermType::Operator, ";"))};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
    {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        string const variableName(terms[2].getString());
        CPlusPlusType elementType(startLooper.getContentReference().getValueTypeReference());
        CPlusPlusTemplateClass & cStyleArrayTemplateClass = m_database.getTemplateClassReference("__CStyleArray");
        CPlusPlusClassTemplateSignature cPlusPlusClassTemplateSignature;
        cPlusPlusClassTemplateSignature.addParameter(elementType, "ElementType");
        CPlusPlusType instantiationType(cStyleArrayTemplateClass.getTemplateClassInstantiationType(cPlusPlusClassTemplateSignature));

        m_database.addVariable(variableName, instantiationType);
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToAssignment(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToAssignment");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 6> const termCheckers{TC(TermCheckerType::isValue), TC(T(TermType::WhiteSpace)),
                TC(TermCheckerType::isAssignmentOperator), TC(T(TermType::WhiteSpace)),
                TC(TermCheckerType::isValue), TC(T(TermType::Operator, ";"))};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
    {
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToRValueCanBeALine(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToRValueCanBeALine");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 2> const expectedTerms{T(TermType::Value_RValue_CanBeALine), T(TermType::Operator, ";")};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToUsingNamespaceKeyword(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToUsingNamespaceKeyword");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 6> const expectedTerms{T(TermType::Keyword, "using"), T(TermType::WhiteSpace),
                T(TermType::Keyword, "namespace"), T(TermType::WhiteSpace),
                T(TermType::Namespace), T(TermType::Operator, ";")};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        VectorOfTerms terms(getTerms(startLooper, expectedTerms));
        m_database.addUsingNamespace(terms[4].getString());
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeDefStatement(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToTypeDefStatement");
    Looper compareLooper(startLooper);
    array<Term, 2> const termCheckers{T(TermType::Keyword, "typedef"), T(TermType::WhiteSpace)};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
    {
        simplifyPrimitiveTypesForCurrentStatement(compareLooper);
        bool isModified = true;
        if(isModifiedDueToTypeDefWithNormalParameters(startLooper, compareLooper));
        else if(isModifiedDueToTypeDefWithStructAndBracesCStyleStatement(startLooper, compareLooper));
        else
        {
            isModified = false;
        }
        return isModified;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeDefWithNormalParameters(Looper const& startLooper, Looper const& nextLooper)
{
    DBGPRINT2("isModifiedDueToTypeDefWithNormalParameters");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(nextLooper);
    array<TermChecker, 2> const termCheckers{TC(TermCheckerType::isCPlusPlusType), TC(T(TermType::WhiteSpace))};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(compareLooper, termCheckers))
    {
        VectorOfTerms terms(getTerms(nextLooper, termCheckers));
        CPlusPlusType const& cPlusPlusType(terms[0].getValueTypeReference());
        MapOfCPlusPlusTypesForTypedef typeMap;
        if(areTypesFoundForTypedefThenFillAndMoveLooper(compareLooper, cPlusPlusType, typeMap))
        {
            for(auto const& typePair : typeMap)
            {
                m_database.addType(typePair.first, typePair.second);
            }
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeDefWithStructAndBracesCStyleStatement(Looper const& startLooper, Looper const& nextLooper)
{
    DBGPRINT2("isModifiedDueToCStyleTypeDefWtihStructWithBracesStatement");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(nextLooper);
    array<TermChecker, 3> const termCheckers{TC(T(TermType::Keyword, "struct")), TC(T(TermType::WhiteSpace)),
                TC({T(TermType::Identifier), T(TermType::Class)})};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(compareLooper, termCheckers))
    {
        VectorOfTerms terms(getTerms(nextLooper, termCheckers));
        string structName(string("struct ")+terms[2].getString());
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if(isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(compareLooper, afterOpeningBraces, afterClosingBraces))
        {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
            Looper afterSemiColon(afterClosingBraces);
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterSemiColon);
            CPlusPlusType cPlusPlusType(structName, CPlusPlusTypeType::Class);
            MapOfCPlusPlusTypesForTypedef typeMap;
            if(areTypesFoundForTypedefThenFillAndMoveLooper(afterSemiColon, cPlusPlusType, typeMap))
            {
                m_database.performInClass(structName, [&]()
                {
                    analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces-1));
                });
                for(auto const& typePair : typeMap)
                {
                    m_database.addType(typePair.first, typePair.second);
                }
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterSemiColon);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterSemiColon, TermType::ProcessedTerm);
                return true;
            }
        }
    }
    return false;
}

bool TermAnalyzer::areVariableFoundForVariableDeclarationAndMoveLooper(Looper& movableLooper, VectorOfStrings& variableNames)
{
    array<TermChecker, 5> const variableWithValueChecker{TC({T(TermType::Identifier), T(TermType::Variable)}), TC(T(TermType::WhiteSpace)),
                TC(TermCheckerType::isAssignmentOperator), TC(T(TermType::WhiteSpace)), TC(TermCheckerType::isValue)};
    array<TermChecker, 1> const variableChecker{TC({T(TermType::Identifier), T(TermType::Variable)})};
    array<Term, 2> const separator{T(TermType::Operator, ","), T(TermType::WhiteSpace)};
    array<Term, 1> const finisher{T(TermType::Operator, ";")};
    bool isNextVariableExpected(true);
    while (movableLooper.isNotFinished())
    {
        Looper movableLooperCopy(movableLooper);
        if(isNextVariableExpected)
        {
            if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(movableLooper, variableWithValueChecker))
            {
                variableNames.emplace_back(movableLooperCopy.getContentReference().getString());
                isNextVariableExpected = false;
            }
            else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(movableLooper, variableChecker))
            {
                variableNames.emplace_back(movableLooperCopy.getContentReference().getString());
                isNextVariableExpected = false;
            }
        }
        else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(movableLooper, separator))
        {
            isNextVariableExpected = true;
        }
        else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(movableLooper, finisher))
        {
            return true;
        }
        if(movableLooperCopy.getCurrentIndex() == movableLooper.getCurrentIndex())
        {
            return false;
        }
    }
    return false;
}

bool TermAnalyzer::areTypesFoundForTypedefThenFillAndMoveLooper(Looper& movableLooper, CPlusPlusType const& type, MapOfCPlusPlusTypesForTypedef& typeMap)
{
    array<TermChecker, 1> const typeChecker{TC({T(TermType::Identifier), T(TermType::Type), T(TermType::Class)})};
    array<TermChecker, 2> const typePointerChecker{TC(T(TermType::Operator, "*")), TC({T(TermType::Identifier), T(TermType::Type), T(TermType::Class)})};
    array<Term, 1> const separator1{T(TermType::WhiteSpace)};
    array<Term, 1> const separator2{T(TermType::Operator, ",")};
    array<Term, 1> const finisher{T(TermType::Operator, ";")};
    bool isNextTypeExpected(true);
    while(movableLooper.isNotFinished())
    {
        Looper movableLooperCopy(movableLooper);
        Looper afterOpeningParenthesis(movableLooper);
        Looper afterClosingParenthesis(movableLooper);
        if(isNextTypeExpected && isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, typeChecker))
        {
            typeMap.emplace(movableLooperCopy.getContentReference().getString(), type);
            isNextTypeExpected = false;
        }
        else if(isNextTypeExpected && isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, typePointerChecker))
        {
            VectorOfTerms terms(getTerms(movableLooperCopy, typePointerChecker));
            CPlusPlusType pointerType(type);
            pointerType.incrementPointerCount();
            typeMap.emplace(terms[1].getString(), pointerType);
            isNextTypeExpected = false;
        }
        else if(isNextTypeExpected && isBothParenthesesFoundAndMoveLoopers<LooperConnector::None>(movableLooper, afterOpeningParenthesis, afterClosingParenthesis))
        {
            movableLooper.copyLooper(afterClosingParenthesis);
            isNextTypeExpected = false;
        }
        else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, separator1))
        {
            isNextTypeExpected = true;
        }
        else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, separator2))
        {
            isNextTypeExpected = true;
        }
        else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, finisher))
        {
            return true;
        }
        else
        {
            incrementLooperIfWhiteSpaceAndNewLine<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(movableLooper);
            if(movableLooperCopy.getCurrentIndex() == movableLooper.getCurrentIndex())
            {
                return false;
            }
        }
    }
    return false;
}

}// namespace codeReview
