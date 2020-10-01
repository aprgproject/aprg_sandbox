#include <iostream>
#include <iterator>
#include "../TermAnalyzer.hpp"
#include "../TermAnalyzerTemplateFunctions.hpp"
#include "../../Database/CPlusPlusDatabase.hpp"

using namespace std;

namespace codeReview
{

bool TermAnalyzer::isModifiedDueToUpdatedIdentifiers(Looper const& startLooper, LooperIndex& previousUpdatedIndexForMacro, LooperIndex& previousUpdatedIndexForOthers)
{
    DBGPRINT1("isModifiedDueToUpdatedIdentifiers");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper replaceLooper(startLooper);
    while(replaceLooper.isNotFinished())
    {
        Term& term = replaceLooper.getContentReference();
        string identifierName = term.getString();
        if(TermType::Identifier == term.getTermType())
        {
            if(m_database.isMacro(identifierName))
            {
                replaceTermWithMacroEquivalent(replaceLooper, m_database.getMacroReference(identifierName));
                temporaryFindings.copyCurrentFindings(m_findings);
                return true;
            }
            else if(m_database.isNamespaceWithAlias(identifierName))
            {
                term.setTermType(TermType::Namespace);
            }
            else if(m_database.isClassWithAlias(identifierName))
            {
                term.setTermType(TermType::Class);
                term.setValueType(m_database.getClassReferenceWithAlias(identifierName).getTypeReference());
            }
            else if(m_database.isType(identifierName))
            {
                term.setTermType(TermType::Type);
                term.setValueType(m_database.getTypeReferenceWithAlias(identifierName));
            }
            else if(m_database.isFunctionWithAlias(identifierName))
            {
                term.setTermType(TermType::FunctionName);
            }
            else if(m_database.isVariableWithAlias(identifierName))
            {
                term.setTermType(TermType::Variable);
                term.setValueType(m_database.getVariableReferenceWithAlias(identifierName).getType());
            }
        }
        else if(TermType::Macro == term.getTermType())
        {
            previousUpdatedIndexForMacro = replaceLooper.getCurrentIndex();
            previousUpdatedIndexForOthers = replaceLooper.getCurrentIndex();
            break;
        }
        replaceLooper++;
    }
    m_database.clearIsDatabaseModified();
    return false;
}

void TermAnalyzer::combineToASingleTerm(Looper const& startLooper, Looper const& endLooper, TermType const termType)
{
    DBGPRINT3("combineToASingleTerm");
    Looper combineLooper(startLooper, endLooper);
    Term & firstTerm = startLooper.getContentReference();
    firstTerm.setString(accumulateLooperContentsToString(combineLooper));
    firstTerm.setTermType(termType);
    firstTerm.clearValueType();
    combineLooper++;
    eraseTermsAndSetModifiedFlag(combineLooper);
}

void TermAnalyzer::combineToASingleTermWithValueType(Looper const& startLooper, Looper const& endLooper, TermType const termType, CPlusPlusType const& valueType)
{
    DBGPRINT3("combineToASingleTermWithValueType");
    Looper combineLooper(startLooper, endLooper);
    Term & firstTerm = startLooper.getContentReference();
    firstTerm.setString(accumulateLooperContentsToString(combineLooper));
    firstTerm.setTermType(termType);
    firstTerm.setValueType(valueType);
    combineLooper++;
    eraseTermsAndSetModifiedFlag(combineLooper);
}

void TermAnalyzer::replaceLooperContentsWithASingleTerm(Looper const& startLooper, Looper const& endLooper, Term const& term)
{
    Looper combineLooper(startLooper, endLooper);
    Term & firstTerm = startLooper.getContentReference();
    firstTerm = term;
    combineLooper++;
    eraseTermsAndSetModifiedFlag(combineLooper);
}

void TermAnalyzer::eraseTermAndSetModifiedFlag(Looper const& eraseLooper)
{
    m_isTermsModified = true;
    m_modifyDetails.setModifyDetails(eraseLooper.getCurrentIndex(), -1);
    m_terms.erase(eraseLooper.getCurrentIterator());
}

void TermAnalyzer::eraseTermsAndSetModifiedFlag(Looper const& eraseLooper)
{
    //remember eraseTermsAndUpdateModifyDetails is [begin, end)
    m_isTermsModified = true;
    m_modifyDetails.setModifyDetails(eraseLooper.getCurrentIndex(), -eraseLooper.getLength());
    m_terms.erase(eraseLooper.getCurrentIterator(), eraseLooper.getEndIterator());
}

void TermAnalyzer::replaceTermWithMacroEquivalent(Looper const& replaceLooper, CPlusPlusMacro& cPlusPlusMacro)
{
    Looper eraseLooper(replaceLooper, replaceLooper+1);
    Looper afterOpeningParenthesis(replaceLooper+1);
    Looper afterClosingParenthesis(afterOpeningParenthesis);
    Looper parameterUsageLooper(afterOpeningParenthesis, afterOpeningParenthesis);
    incrementLooperIfWhiteSpaceForMacro<FindingsToAdd::None>(afterOpeningParenthesis);
    if(isBothParenthesesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(afterOpeningParenthesis, afterOpeningParenthesis, afterClosingParenthesis))
    {
        eraseLooper.setEndIndex(afterClosingParenthesis);
        parameterUsageLooper.setCurrentIndex(afterOpeningParenthesis);
        parameterUsageLooper.setEndIndex(afterClosingParenthesis-1);
    }
    replaceTermWithMacroEquivalent(eraseLooper, parameterUsageLooper, cPlusPlusMacro);
}

void TermAnalyzer::replaceTermWithMacroEquivalent(Looper const& eraseLooper, Looper const& parameterUsageLooper, CPlusPlusMacro& cPlusPlusMacro)
{
    Looper insertLooper(eraseLooper);
    VectorOfTerms& macroEquivalent = cPlusPlusMacro.getMacroEquivalent();
    MapOfMacroUsageParameters macroUsageParameters;
    checkMacroUsageParameters(parameterUsageLooper, cPlusPlusMacro, macroUsageParameters);
    m_isTermsModified = true;
    int modifyLength = -eraseLooper.getLength();
    m_terms.erase(eraseLooper.getCurrentIterator(), eraseLooper.getEndIterator());
    unsigned int lineNumber = eraseLooper.getContentReference().getLineNumber();
    auto positionToParameter = cPlusPlusMacro.getPositionToParameter();
    int positionIndex=0;
    for(Term& term : macroEquivalent)
    {
        term.setLineNumber(lineNumber);
        if(cPlusPlusMacro.isPositionInMap(positionIndex))
        {
            int parameterIndexToReplace = positionToParameter[positionIndex];
            VectorOfTerms& macroUsageParameter = macroUsageParameters[parameterIndexToReplace];
            m_terms.insert(insertLooper.getCurrentIterator(), macroUsageParameter.begin(), macroUsageParameter.end());
            modifyLength += macroUsageParameter.size();
            insertLooper.copyLooper(insertLooper + macroUsageParameter.size());
        }
        else
        {
            m_terms.insert(insertLooper.getCurrentIterator(), term);
            modifyLength++;
            insertLooper++;
        }
        positionIndex++;
    }
    m_modifyDetails.setModifyDetails(eraseLooper.getCurrentIndex(), modifyLength);
}

void TermAnalyzer::checkMacroUsageParameters(Looper const& parameterLooper, CPlusPlusMacro& cPlusPlusMacro, MapOfMacroUsageParameters& macroUsageParameters)
{
    Looper parameterUsageLooper(parameterLooper);
    int macroUsageParametersIndex = 0;
    bool shouldIgnoreWhiteSpace(false);
    macroUsageParameters.emplace(macroUsageParametersIndex, VectorOfTerms());
    while(parameterUsageLooper.isNotFinished())
    {
        Term const& term = parameterUsageLooper.getContentReference();
        if(cPlusPlusMacro.isEqualToVariadicParameterIndex(macroUsageParametersIndex))
        {
            if(shouldIgnoreWhiteSpace && CheckerHelpers::isWhiteSpace(term));
            else
            {
                shouldIgnoreWhiteSpace = false;
                macroUsageParameters[macroUsageParametersIndex].push_back(parameterUsageLooper.getContentReference());
            }
        }
        else
        {
            if(T(TermType::Operator, ",") == term)
            {
                shouldIgnoreWhiteSpace = true;
                macroUsageParametersIndex++;
                macroUsageParameters.emplace(macroUsageParametersIndex, VectorOfTerms());
            }
            else if(shouldIgnoreWhiteSpace && CheckerHelpers::isWhiteSpace(term));
            else
            {
                shouldIgnoreWhiteSpace = false;
                macroUsageParameters[macroUsageParametersIndex].push_back(parameterUsageLooper.getContentReference());
            }
        }
        parameterUsageLooper++;
    }

    int numOfParametersInUsage = 0;
    if(parameterLooper.getLength() != 0)
    {
            numOfParametersInUsage = macroUsageParametersIndex + 1;
    }
    int numOfParametersInDefinition = cPlusPlusMacro.getMacroParameters().size();
    if(numOfParametersInUsage != numOfParametersInDefinition)
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "The number of parameters in Macro definition does not match Macro usage", parameterLooper);
    }
}

void TermAnalyzer::clearFlagsForAnotherIteration()
{
    m_isTermsModified = false;
    m_moveBackType = MoveBackType::Empty;
}

}// namespace codeReview
