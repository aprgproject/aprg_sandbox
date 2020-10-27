#pragma once

#include "../Term/CheckerHelpers.hpp"
#include "Findings/TemporaryFindings.hpp"
#include "TermAnalyzer.hpp"

#include <String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;
using alba::stringHelper::constructFileLocator;

namespace codeReview
{

template<LooperConnector looperConnector, class Container>
bool TermAnalyzer::isSingleLineComparisonSatisfiedThenMoveLooper(Looper& movableLooper, Container const& expectedTerms)
{
    DBGPRINT3("isSingleLineComparisonSatisfiedThenMoveLooper");
    connectLooper<looperConnector>(movableLooper);
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    auto itExpected = expectedTerms.begin();
    Looper compareLooper(movableLooper);
    Term& firstTerm = compareLooper.getContentReference();
    if(firstTerm != *itExpected)
    {
        return false;
    }
    while (compareLooper.isNotFinished() && itExpected!=expectedTerms.end())
    {
        if(compareLooper.getContentReference() == *itExpected)
        {
            compareLooper++;
            itExpected++;
        }
        else if(isTheMismatchWithIgnorableTermAndMoveLooper(compareLooper, itExpected));
        else if(isTheMismatchWithWhiteSpaceAndMoveLooper(compareLooper, itExpected));
        else
        {
            return false;
        }
    }
    if(itExpected==expectedTerms.end())
    {
        movableLooper.setCurrentIndex(compareLooper);
        temporaryFindings.saveCurrentFindings();
        return true;
    }
    return false;
}

template<LooperConnector looperConnector, class Container>
bool TermAnalyzer::isMultiLineComparisonSatisfiedThenMoveLooper(Looper& movableLooper, Container const& expectedTerms)
{
    DBGPRINT3("compareMultiLineAndMoveLooper");
    connectLooper<looperConnector>(movableLooper);
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    auto itExpected = expectedTerms.begin();
    Looper compareLooper(movableLooper);
    Term& firstTerm = compareLooper.getContentReference();
    if(firstTerm != *itExpected)
    {
        return false;
    }
    while (compareLooper.isNotFinished() && itExpected!=expectedTerms.end())
    {
        if(compareLooper.getContentReference() == *itExpected)
        {
            compareLooper++;
            itExpected++;
        }
        else if(isTheMismatchWithIgnorableTermAndMoveLooper(compareLooper, itExpected));
        else if(isTheMismatchWithWhiteSpaceAndMoveLooper(compareLooper, itExpected));
        else if(isTheMismatchWithNewLineAndMoveLooper(compareLooper, itExpected));
        else
        {
            return false;
        }
    }
    if(itExpected==expectedTerms.end())
    {
        movableLooper.setCurrentIndex(compareLooper);
        temporaryFindings.saveCurrentFindings();
        return true;
    }
    return false;
}

template<typename ExpectedTermsIteratorType>
bool TermAnalyzer::isTheMismatchWithWhiteSpaceAndMoveLooper(Looper& movableLooper, ExpectedTermsIteratorType& itExpected)
{
    DBGPRINT3("isTheMismatchWithWhiteSpaceAndMoveLooper");
    bool isWhiteSpaceInExpectedTerms = CheckerHelpers::isWhiteSpace(*itExpected);
    bool isWhiteSpaceInMainTerms = CheckerHelpers::isWhiteSpace(movableLooper.getContentReference());

    if(isWhiteSpaceInExpectedTerms && !isWhiteSpaceInMainTerms)
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Expected white space", movableLooper);
    }
    else if(!isWhiteSpaceInExpectedTerms && isWhiteSpaceInMainTerms)
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected white space", movableLooper);
    }
    if(isWhiteSpaceInExpectedTerms)
    {
        itExpected++;
    }
    if(isWhiteSpaceInMainTerms)
    {
        movableLooper++;
    }
    return isWhiteSpaceInExpectedTerms || isWhiteSpaceInMainTerms;
}

template<typename ExpectedTermsIteratorType>
bool TermAnalyzer::isTheMismatchWithNewLineAndMoveLooper(Looper& movableLooper, ExpectedTermsIteratorType& itExpected)
{
    DBGPRINT3("isTheMismatchWithNewLineAndMoveLooper");
    bool isNewLineInExpectedTerms = CheckerHelpers::isNewLine(*itExpected);
    bool isNewLineInMainTerms = CheckerHelpers::isNewLine(movableLooper.getContentReference());

    if(isNewLineInExpectedTerms && !isNewLineInMainTerms)
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Expected new line", movableLooper);
    }
    else if(!isNewLineInExpectedTerms && isNewLineInMainTerms)
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected new line", movableLooper);
    }
    if(isNewLineInExpectedTerms)
    {
        itExpected++;
    }
    if(isNewLineInMainTerms)
    {
        movableLooper++;
    }
    return isNewLineInExpectedTerms || isNewLineInMainTerms;
}

template<typename ExpectedTermsIteratorType>
bool TermAnalyzer::isTheMismatchWithIgnorableTermAndMoveLooper(Looper& movableLooper, ExpectedTermsIteratorType& itExpected)
{
    DBGPRINT3("isTheMismatchWithIgnorableTermAndMoveLooper");
    bool isIgnorableInExpectedTerms = CheckerHelpers::isIgnorable(*itExpected);
    bool isIgnorableInMainTerms = CheckerHelpers::isIgnorable(movableLooper.getContentReference());

    if(isIgnorableInExpectedTerms)
    {
        itExpected++;
    }
    if(isIgnorableInMainTerms)
    {
        movableLooper++;
    }
    return isIgnorableInExpectedTerms || isIgnorableInMainTerms;
}

template <LooperConnector looperConnector> bool TermAnalyzer::isBothBracketsFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningBracket, Looper& afterClosingBracket)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterNewLineAndWhiteSpaces(startLooper);
    connectLooper<looperConnector>(afterNewLineAndWhiteSpaces);
    if(afterNewLineAndWhiteSpaces.isNotFinished() && (T(TermType::Operator, "[") == afterNewLineAndWhiteSpaces.getContentReference()))
    {
        afterOpeningBracket.setCurrentIndex(afterNewLineAndWhiteSpaces+1);
        afterClosingBracket.copyLooper(afterOpeningBracket);
        if(isClosingPartnerFoundAndMoveLooper(afterClosingBracket, "[", "]"))
        {
            temporaryFindings.saveCurrentFindings();
            return true;
        }
    }
    return false;
}

template <LooperConnector looperConnector> bool TermAnalyzer::isBothParenthesesFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningParenthesis, Looper& afterClosingParenthesis)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterNewLineAndWhiteSpaces(startLooper);
    connectLooper<looperConnector>(afterNewLineAndWhiteSpaces);
    if(afterNewLineAndWhiteSpaces.isNotFinished() && (T(TermType::Operator, "(") == afterNewLineAndWhiteSpaces.getContentReference()))
    {
        afterOpeningParenthesis.setCurrentIndex(afterNewLineAndWhiteSpaces+1);
        afterClosingParenthesis.copyLooper(afterOpeningParenthesis);
        if(isClosingPartnerFoundAndMoveLooper(afterClosingParenthesis, "(", ")"))
        {
            temporaryFindings.saveCurrentFindings();
            return true;
        }
    }
    return false;
}

template <LooperConnector looperConnector> bool TermAnalyzer::isBothAngleBracketsFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningAngleBracket, Looper& afterClosingAngleBracket)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterNewLineAndWhiteSpaces(startLooper);
    connectLooper<looperConnector>(afterNewLineAndWhiteSpaces);
    if(afterNewLineAndWhiteSpaces.isNotFinished() && (T(TermType::Operator, "<") == afterNewLineAndWhiteSpaces.getContentReference()))
    {
        afterOpeningAngleBracket.setCurrentIndex(afterNewLineAndWhiteSpaces+1);
        afterClosingAngleBracket.copyLooper(afterOpeningAngleBracket);
        if(isClosingPartnerFoundAndMoveLooper(afterClosingAngleBracket, "<", ">"))
        {
            temporaryFindings.saveCurrentFindings();
            return true;
        }
    }
    return false;
}

template <LooperConnector looperConnector> bool TermAnalyzer::isBothBracesFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningBraces, Looper& afterClosingBraces)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterNewLineAndWhiteSpaces(startLooper);
    incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterNewLineAndWhiteSpaces);
    connectLooper<looperConnector>(afterNewLineAndWhiteSpaces);
    if(afterNewLineAndWhiteSpaces.isNotFinished() && (T(TermType::Operator, "{") == afterNewLineAndWhiteSpaces.getContentReference()))
    {
        afterOpeningBraces.setCurrentIndex(afterNewLineAndWhiteSpaces+1);
        afterClosingBraces.copyLooper(afterOpeningBraces);
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterClosingBraces);
        if(isClosingPartnerFoundAndMoveLooper(afterClosingBraces, "{", "}"))
        {
            Looper afterClosingBracesAndNewLine(afterClosingBraces);
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterClosingBracesAndNewLine);
            temporaryFindings.saveCurrentFindings();
            return true;
        }
    }
    return false;
}

template <LooperConnector looperConnector> bool TermAnalyzer::isBothBracesFoundWithSemicolonAndMoveLoopers(
        Looper const& startLooper,
        Looper& afterOpeningBraces,
        Looper& afterClosingBraces,
        Looper& afterSemiColon)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterNewLineAndWhiteSpaces(startLooper);
    incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterNewLineAndWhiteSpaces);
    connectLooper<looperConnector>(afterNewLineAndWhiteSpaces);
    if(afterNewLineAndWhiteSpaces.isNotFinished() && (T(TermType::Operator, "{") == afterNewLineAndWhiteSpaces.getContentReference()))
    {
        afterOpeningBraces.setCurrentIndex(afterNewLineAndWhiteSpaces+1);
        afterClosingBraces.copyLooper(afterOpeningBraces);
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterClosingBraces);
        if(isClosingPartnerFoundAndMoveLooper(afterClosingBraces, "{", "}"))
        {
            afterSemiColon.copyLooper(afterClosingBraces);
            if(T(TermType::Operator, ";") == afterSemiColon.getContentReference())
            {
                afterSemiColon++;
            }
            else
            {
                addFinding(constructFileLocator(__FILE__, __LINE__), "Expected semi-colon", afterSemiColon);
            }
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterSemiColon);
            temporaryFindings.saveCurrentFindings();
            return true;
        }
    }
    return false;
}

template <LooperConnector looperConnector> bool TermAnalyzer::isSemiColonFoundAndMoveLooper(Looper& afterSemiColon)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterNewLineAndWhiteSpaces(afterSemiColon);
    connectLooper<looperConnector>(afterNewLineAndWhiteSpaces);
    if(afterNewLineAndWhiteSpaces.isNotFinished() && (T(TermType::Operator, ";") == afterNewLineAndWhiteSpaces.getContentReference()))
    {
        temporaryFindings.saveCurrentFindings();
        afterSemiColon.setCurrentIndex(afterNewLineAndWhiteSpaces+1);
        return true;
    }
    return false;
}

template<class Container>
VectorOfTerms TermAnalyzer::getTerms(Looper const& startLooper, Container const& expectedTerms)
{
    DBGPRINT3("updateExpectedTerms");
    VectorOfTerms terms;
    Looper updateLooper(startLooper);
    auto termIterator = expectedTerms.begin();
    while(updateLooper.isNotFinished() && termIterator != expectedTerms.end()) //copy if anyone?
    {
        Term const& termInLooper = updateLooper.getContentReference();
        Term const& termInExpectedTerms = *termIterator;
        if(*termIterator == termInLooper)
        {
            terms.push_back(termInLooper);
            updateLooper++;
            termIterator++;
        }
        else if(CheckerHelpers::isIgnorable(termInExpectedTerms) || CheckerHelpers::isWhiteSpace(termInExpectedTerms) || CheckerHelpers::isNewLine(termInExpectedTerms))
        {
            terms.push_back(termInExpectedTerms);
            termIterator++;
        }
        else
        {
            updateLooper++;
        }
    }
    return terms;
}

template <FindingsToAdd findingsToAdd> void TermAnalyzer::incrementLooperIfWhiteSpaceForMacro(Looper& movableLooper)
{
    while(movableLooper.isNotFinished())
    {
        if(CheckerHelpers::isWhiteSpace(movableLooper.getContentReference()))
        {
            addFindingsForUnexpectedWhiteSpaceIfNeeded<findingsToAdd>(movableLooper);
        }
        else if(CheckerHelpers::isIgnorable(movableLooper.getContentReference()));
        else
        {
            break;
        }
        movableLooper++;
    }
}

template <FindingsToAdd findingsToAdd> void TermAnalyzer::incrementLooperIfWhiteSpaceAndOneNewLine(Looper& movableLooper)
{
    while(movableLooper.isNotFinished())
    {
        if(CheckerHelpers::isWhiteSpace(movableLooper.getContentReference()))
        {
            addFindingsForUnexpectedWhiteSpaceIfNeeded<findingsToAdd>(movableLooper);
        }
        else if(CheckerHelpers::isNewLine(movableLooper.getContentReference()))
        {
            movableLooper++;
            break;
        }
        else if(CheckerHelpers::isIgnorable(movableLooper.getContentReference()));
        else
        {
            addFindingsForExpectedNewLineIfNeeded<findingsToAdd>(movableLooper);
            break;
        }
        movableLooper++;
    }
}

template <FindingsToAdd findingsToAdd> void TermAnalyzer::incrementLooperIfWhiteSpaceAndNewLine(Looper& movableLooper)
{
    while(movableLooper.isNotFinished())
    {
        Term const& currentTerm = movableLooper.getContentReference();
        if(CheckerHelpers::isWhiteSpace(currentTerm))
        {
            addFindingsForUnexpectedWhiteSpaceIfNeeded<findingsToAdd>(movableLooper);
        }
        else if(CheckerHelpers::isNewLine(currentTerm))
        {
            addFindingsForUnexpectedNewLineIfNeeded<findingsToAdd>(movableLooper);
        }
        else if(CheckerHelpers::isIgnorable(movableLooper.getContentReference()));
        else
        {
            break;
        }
        movableLooper++;
    }
}

template <FindingsToAdd findingsToAdd> void TermAnalyzer::decrementLooperIfWhiteSpaceAndNewLine(Looper& movableLooper)
{
    while(movableLooper.isNotFinishedWhenBackward())
    {
        Term const& currentTerm = movableLooper.getContentReference();
        if(CheckerHelpers::isWhiteSpace(currentTerm))
        {
            addFindingsForUnexpectedWhiteSpaceIfNeeded<findingsToAdd>(movableLooper);
        }
        else if(CheckerHelpers::isNewLine(currentTerm))
        {
            addFindingsForUnexpectedNewLineIfNeeded<findingsToAdd>(movableLooper);
        }
        else if(CheckerHelpers::isIgnorable(movableLooper.getContentReference()));
        else
        {
            break;
        }
        movableLooper--;
    }
}

}// namespace codeReview
