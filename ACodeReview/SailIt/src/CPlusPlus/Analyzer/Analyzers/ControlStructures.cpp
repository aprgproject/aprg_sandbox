#include "../../Database/CPlusPlusDatabase.hpp"
#include "../Findings/TemporaryFindings.hpp"
#include "../TermAnalyzer.hpp"
#include "../TermAnalyzerTemplateFunctions.hpp"

#include <iostream>

using namespace std;

namespace codeReview
{

bool TermAnalyzer::isModifiedDueToControlStructures(Looper const& startLooper)
{
    DBGPRINT1("isModifiedDueToControlStructures");
    bool isModified = true;
    if(isModifiedDueToIfClauseAndMoveLooper(startLooper));
    else if(isModifiedDueToElseIfClauseAndMoveLooper(startLooper));
    else if(isModifiedDueToElseClauseAndMoveLooper(startLooper));
    else if(isModifiedDueToIfElseIfChainClause(startLooper));
    else if(isModifiedDueToIfElseChainStopClause(startLooper));
    else if(isModifiedDueToWhileLoopAndMoveLooper(startLooper));
    else
    {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToIfClauseAndMoveLooper(Looper const& startLooper)
{
    array<Term, 1> const expectedTerms{T(TermType::Keyword, "if")};
    return isModifiedDueToOneConditionConstructAndMoveLooper(startLooper, expectedTerms, TermType::MultiLine_IfElseIfStartChain_Ignorable);
}

bool TermAnalyzer::isModifiedDueToElseIfClauseAndMoveLooper(Looper const& startLooper)
{
    array<Term, 3> const expectedTerms{T(TermType::Keyword, "else"), T(TermType::WhiteSpace), T(TermType::Keyword, "if")};
    if(isModifiedDueToOneConditionConstructAndMoveLooper(startLooper, expectedTerms, TermType::MultiLine_ElseIfClause))
    {
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToElseClauseAndMoveLooper(Looper const& startLooper)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 1> const expectedTerms{T(TermType::Keyword, "else")};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if(isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(compareLooper, afterOpeningBraces, afterClosingBraces))
        {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
            m_database.performInNewScope([&]()
            {
                analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces-1));
            });
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBraces);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterClosingBraces, TermType::MultiLine_ElseClause);
            m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
            return true;
        }
        Looper afterSemiColon(compareLooper);
        if(isSemiColonFoundAndMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(afterSemiColon))
        {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::UnexpectsWhiteSpace>(afterSemiColon);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterSemiColon, TermType::MultiLine_ElseClause);
            m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToIfElseIfChainClause(Looper const& startLooper)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 2> const expectedTerms{T(TermType::MultiLine_IfElseIfStartChain_Ignorable), T(TermType::MultiLine_ElseIfClause)};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::MultiLine_IfElseIfStartChain_Ignorable);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToIfElseChainStopClause(Looper const& startLooper)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 2> const expectedTerms{T(TermType::MultiLine_IfElseIfStartChain_Ignorable), T(TermType::MultiLine_ElseClause)};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToWhileLoopAndMoveLooper(Looper const& startLooper)
{
    array<Term, 1> const expectedTerms{T(TermType::Keyword, "while")};
    return isModifiedDueToOneConditionConstructAndMoveLooper(startLooper, expectedTerms, TermType::ProcessedTerm);
}

template <class container>
bool TermAnalyzer::isModifiedDueToOneConditionConstructAndMoveLooper(
        Looper const& startLooper,
        container const& termCheckers,
        TermType const newTermType)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
    {
        Looper afterOpeningParenthesis(compareLooper);
        Looper afterClosingParenthesis(compareLooper);
        if(isBothParenthesesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(compareLooper, afterOpeningParenthesis, afterClosingParenthesis))
        {
            Looper afterOpeningBraces(afterClosingParenthesis);
            Looper afterClosingBraces(afterClosingParenthesis);
            Looper afterSemiColon(afterClosingParenthesis);
            if(isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(afterClosingParenthesis, afterOpeningBraces, afterClosingBraces))
            {
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
                m_database.performInNewScope([&]()
                {
                    checkCondition(Looper(afterOpeningParenthesis, afterClosingParenthesis-1));
                    analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces-1));
                });
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBraces);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterClosingBraces, newTermType);
                return true;
            }
            else if(isSemiColonFoundAndMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(afterSemiColon))
            {
                checkCondition(Looper(afterOpeningParenthesis, afterClosingParenthesis-1));
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::UnexpectsWhiteSpace>(afterSemiColon);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterSemiColon, newTermType);
                return true;
            }
        }
    }
    return false;
}

}// namespace codeReview
