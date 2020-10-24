#include "TermAnalyzer.hpp"

#include <String/AlbaStringHelper.hpp>
#include <algorithm>
#include "Findings/TemporaryFindings.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include "../Database/CPlusPlusDatabase.hpp"
#include "../Term/CheckerHelpers.hpp"
#include "../Term/TermChecker.hpp"

using namespace std;
using namespace alba::stringHelper;

namespace codeReview
{

TermAnalyzer::TermAnalyzer(
        DequeOfTerms& terms,
        CPlusPlusDatabase& database,
        Findings& findings)
    : m_terms(terms)
    , m_database(database)
    , m_findings(findings)
    , m_findingsBuffer()
    , m_isTermsModified(false)
    , m_modifyDetails()
{}

TermAnalyzer::TermAnalyzer(
        DequeOfTerms& terms,
        CPlusPlusDatabase& database,
        Findings& findings,
        SailIt& sailIt)
    : m_terms(terms)
    , m_database(database)
    , m_findings(findings)
    , m_findingsBuffer()
    , m_optionalSailIt(sailIt)
    , m_isTermsModified(false)
    , m_modifyDetails()
{}

void TermAnalyzer::setFileName(string const& directory, string const& fileName)
{
    m_baseDirectory = directory;
    m_fileName = fileName;
    m_uniqueFileId = generateUniqueId(m_baseDirectory+m_fileName);
}

void TermAnalyzer::analyze()
{
    if(m_optionalSailIt)
    {
        cout << "analyze file=["<<m_baseDirectory+m_fileName<<"]"<<endl;
    }
    if(!m_terms.empty())
    {
        analyzeThisScope(Looper(m_terms, m_uniqueFileId));
    }
    m_findingsBuffer.copyAllFindings(m_findings);
    m_findingsBuffer.clearAll();
}

void TermAnalyzer::analyzeThisScope(Looper const& startLooper)
{
    //Make the common case fast!
    Looper mainLooper(startLooper);
    LooperIndex previousUpdatedIndexForMacro(startLooper.getCurrentIndex());
    LooperIndex previousUpdatedIndexForOthers(startLooper.getCurrentIndex());
    LooperIndex previousModifiedIndex(startLooper.getCurrentIndex());
    m_findingsBuffer.createNewTemporaryFindingsBuffer();
    while(mainLooper.isNotFinished())
    {
        DBGPRINT1("analyzeThisScope file=["<<m_fileName<<"] mainLooper:["<<mainLooper<<" size:"<<m_terms.size()<<" "<<mainLooper.getContentReference()<<"]");
        clearFlagsForAnotherIteration();

        if(isModifiedDueToUpdatedIdentifiers(mainLooper, previousUpdatedIndexForMacro, previousUpdatedIndexForOthers));
        else if(isModifiedDueToMacros(mainLooper));
        else if(isModifiedDueToExpressions(mainLooper));
        else if(isModifiedDueToStatements(mainLooper));
        else if(isModifiedDueToControlStructures(mainLooper));
        else if(isModifiedDueToFunctions(mainLooper));
        else if(isModifiedDueToClasses(mainLooper));
        else if(isModifiedDueToNamespaces(mainLooper));
        else if(isModifiedDueToCStyleStruct(mainLooper));
        else if(isSingleLineOrMultiLineComment(mainLooper));
        else if(isUnexpectedWhiteSpace(mainLooper));
        else if(isUnexpectedNewLine(mainLooper));
        else {addFindingForUnprocessedFirstTerm(mainLooper);}

        updateAfterOneIteration(mainLooper, previousModifiedIndex);
    }
    m_findingsBuffer.saveCurrentFindings();
    m_findingsBuffer.deleteCurrentBuffer();
}

bool TermAnalyzer::isModifiedDueToCStyleStruct(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToStructCStyle");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{TC(T(TermType::Keyword, "struct")), TC(T(TermType::WhiteSpace)),
                TC({T(TermType::Class), T(TermType::Identifier)})};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
    {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        string const className(string("struct ")+terms[2].getString());
        m_database.addClass(className);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Class, m_database.getClassReferenceWithAlias(className).getTypeReference());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isSingleLineOrMultiLineComment(Looper const& startLooper)
{
    DBGPRINT1("isSingleLineOrMultiLineComment");
    if(CheckerHelpers::isSingleLineOrMultiLineComment(startLooper.getContentReference().getTermType()))
    {
        Looper afterNewLine(startLooper+1);
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::UnexpectsWhiteSpace>(afterNewLine);
        combineToASingleTerm(startLooper, afterNewLine, TermType::Comment);
        return true;
    }
    return false;
}

bool TermAnalyzer::isUnexpectedWhiteSpace(Looper const& startLooper)
{
    DBGPRINT1("isUnexpectedWhiteSpace");
    if(CheckerHelpers::isWhiteSpace(startLooper.getContentReference()))
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected white space", startLooper);
        return true;
    }
    return false;
}

bool TermAnalyzer::isUnexpectedNewLine(Looper const& startLooper)
{
    DBGPRINT1("isUnexpectedNewLine");
    if(CheckerHelpers::isNewLine(startLooper.getContentReference()))
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected new line", startLooper);
        return true;
    }
    return false;
}

void TermAnalyzer::addFindingForUnprocessedFirstTerm(Looper const& startLooper)
{
    DBGPRINT1("addFindingForUnprocessedFirstTerm");
    if(!CheckerHelpers::isProcessed(startLooper.getContentReference()))
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Unprocessed term", startLooper);
    }
}

void TermAnalyzer::updateAfterOneIteration(Looper& movableLooper, LooperIndex& previousModifiedIndex)
{
    DBGPRINT1("updateAfterOneIteration");
    bool canProceedToNext(true);
    if(m_isTermsModified)
    {
        Looper::fixLoopers(m_uniqueFileId, m_modifyDetails);
        canProceedToNext = false;
    }
    if(m_moveBackType == MoveBackType::GotoPreviousModifiedTerm)
    {
        moveLooperToPreviousModifiedIndex(movableLooper, previousModifiedIndex);
        m_findingsBuffer.deleteCurrentBuffer();
        m_findingsBuffer.createNewTemporaryFindingsBuffer();
        canProceedToNext = false;
    }
    else if(m_isTermsModified)
    {
        m_findingsBuffer.saveCurrentFindings();
        m_findingsBuffer.deleteCurrentBuffer();
        m_findingsBuffer.createNewTemporaryFindingsBuffer();
        previousModifiedIndex = movableLooper.getCurrentIndex();
    }
    if(canProceedToNext)
    {
        movableLooper++;
    }
}

bool TermAnalyzer::isStringFoundInLooper(Looper const& startLooper, string const& stringToCompare)
{
    Looper searchLooper(startLooper);
    while(searchLooper.isNotFinished())
    {
        string currentString(searchLooper.getContentReference().getString());
        if(stringToCompare == currentString) return true;
        else if(m_database.isMacro(currentString))
        {
            if(isStringFoundInMacro(currentString, stringToCompare)) return true;
        }
        searchLooper++;
    }
    return false;
}

bool TermAnalyzer::isStringFoundInMacro(string const& macroName, string const& stringToCompare)
{
    VectorOfTerms& macroEquivalent = m_database.getMacroReference(macroName).getMacroEquivalent();
    for(Term const& term : macroEquivalent)
    {
        string currentString(term.getString());
        if(currentString == stringToCompare) return true;
        else if(m_database.isMacro(macroName))
        {
            if(isStringFoundInMacro(macroName, currentString)) return true;
        }
    };
    return false;
}

void TermAnalyzer::moveLooperToPreviousModifiedIndex(Looper& movableLooper, LooperIndex const previousModifiedIndex)
{
    DBGPRINT2("moveLooperToPreviousModifiedIndex");
    Looper checkLooper(movableLooper);
    checkLooper.hardSetCurrentIndex(previousModifiedIndex);
    if(checkLooper.isNotFinishedWhenBackward() && checkLooper.isNotFinished())
    {
        movableLooper.setCurrentIndex(checkLooper);
    }
}

string TermAnalyzer::getLocatorString(Looper const& startLooper)
{
    Term firstTerm(startLooper.getContentReference());
    string locator = string("[   |Content:[")+firstTerm.getPrintableString()+"] Type:["+firstTerm.getTermTypeString()+"]|   ]";
    Looper printBackward(startLooper-1);
    int numberOfCharactersLeftToPrint = 50;
    while(printBackward.isNotFinishedWhenBackward())
    {
        Term const& term = printBackward.getContentReference();
        string stringToPrint(term.getPrintableString());
        int length = stringToPrint.length();
        if(length > numberOfCharactersLeftToPrint)
        {
            locator=stringToPrint.substr(length-numberOfCharactersLeftToPrint)+locator;
            break;
        }
        else
        {
            locator=stringToPrint+locator;
            numberOfCharactersLeftToPrint-=length;
        }
        printBackward--;
    }
    Looper printForward(startLooper+1);
    numberOfCharactersLeftToPrint = 50;
    while(printForward.isNotFinished())
    {
        Term const& term = printForward.getContentReference();
        string stringToPrint(term.getPrintableString());
        int length = stringToPrint.length();
        if(length > numberOfCharactersLeftToPrint)
        {
            locator=locator+stringToPrint.substr(0, numberOfCharactersLeftToPrint);
            break;
        }
        else
        {
            locator=locator+stringToPrint;
            numberOfCharactersLeftToPrint-=length;
        }
        printForward++;
    }
    return locator;
}

string TermAnalyzer::accumulateLooperContentsToString(Looper const& startLooper)
{
    //remember getEquivalentString is [begin, end)
    return std::accumulate(startLooper.getCurrentIterator(), startLooper.getEndIterator(), string(""), [&](string stringParam, Term & term)
    {
        return stringParam + term.getString();
    });
}

string TermAnalyzer::accumulateLooperContentsToPrintableString(Looper const& startLooper)
{
    //remember getEquivalentString is [begin, end)
    return std::accumulate(startLooper.getCurrentIterator(), startLooper.getEndIterator(), string(""), [&](string stringParam, Term & term)
    {
        return stringParam + "[" + term.getPrintableString() + "]";
    });
}

}// namespace codeReview
