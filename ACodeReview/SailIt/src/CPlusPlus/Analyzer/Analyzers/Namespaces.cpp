#include "../../Database/CPlusPlusDatabase.hpp"
#include "../../Term/TermChecker.hpp"
#include "../Findings/TemporaryFindings.hpp"
#include "../TermAnalyzer.hpp"
#include "../TermAnalyzerTemplateFunctions.hpp"

#include <iostream>

using namespace std;

namespace codeReview
{

bool TermAnalyzer::isModifiedDueToNamespaces(Looper const& startLooper)
{
    DBGPRINT1("isModifiedDueToNamespaces");
    bool isModified = true;
    if(isModifiedDueToNamespaceDefinition(startLooper));
    else if(isModifiedDueToExternBlock(startLooper));
    else
    {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToNamespaceDefinition(Looper const& startLooper)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 3> const expectedTerms{T(TermType::Keyword, "namespace"), T(TermType::WhiteSpace), T(TermType::Identifier)};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if(isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(compareLooper, afterOpeningBraces, afterClosingBraces))
        {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
            VectorOfTerms terms(getTerms(startLooper, expectedTerms));
            m_database.performInNamespace(terms[2].getString(), [&]()
            {
                analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces-1));
            });
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBraces);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterClosingBraces, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToExternBlock(Looper const& startLooper)
{
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{TC(T(TermType::Keyword, "extern")), TC(T(TermType::WhiteSpace)),
                TC({T(TermType::Constant_String, "\"C\""), T(TermType::Constant_String, "\"C++\"")})};
    if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
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
            combineToASingleTerm(startLooper, afterClosingBraces, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

}// namespace codeReview
