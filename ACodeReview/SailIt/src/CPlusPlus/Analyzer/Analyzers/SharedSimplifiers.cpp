#include <iostream>
#include "../Findings/TemporaryFindings.hpp"
#include "../TermAnalyzer.hpp"
#include "../TermAnalyzerTemplateFunctions.hpp"
#include "../../Database/CPlusPlusMacro.hpp"
#include "../../Term/TermChecker.hpp"

using namespace std;

namespace codeReview
{

void TermAnalyzer::checkCondition(Looper const& startLooper)
{
    Looper conditionLooper(startLooper);
    simplifyExpressions(startLooper);
    if(CheckerHelpers::isValue(conditionLooper.getContentReference()))
    {
        if("bool"!=conditionLooper.getContentReference().getValueType().getTypeName())
        {
            addFinding(constructFileLocator(__FILE__, __LINE__), "Term in condition is not bool", conditionLooper);
        }
        conditionLooper++;
        if(conditionLooper.isNotFinished())
        {
            addFinding(constructFileLocator(__FILE__, __LINE__), "Multiple Terms In the Condition", conditionLooper);
        }
    }
    else
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Unprocessed term in condition", conditionLooper);
    }
}

bool TermAnalyzer::isClosingPartnerFoundAndMoveLooper(Looper& movableLooper, string const& openingOperator, string const& closingOperator)
{
    //remember isClosingPartnerFoundAndMoveLooper moves iterator to the next of the closing operator
    int openingClosingCount = 1;
    Looper searchLooper(movableLooper);
    while(searchLooper.isNotFinished())
    {
        Term const& term = searchLooper.getContentReference();
        if(openingOperator == term.getString())
        {
            openingClosingCount++;
        }
        else if(closingOperator == term.getString())
        {
            openingClosingCount--;
        }
        if(openingClosingCount==0)
        {
            movableLooper.setCurrentIndex(searchLooper);
            movableLooper++;
            return true;
        }
        searchLooper++;
    }
    return false;
}

template <LooperConnector looperConnector> void TermAnalyzer::connectLooper(Looper&)
{}
template void TermAnalyzer::connectLooper<LooperConnector::None>(Looper&);
template <> void TermAnalyzer::connectLooper<LooperConnector::WhiteSpaceAndNewLine>(Looper& movableLooper)
{
    incrementLooperIfWhiteSpaceAndNewLine<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(movableLooper);
}

}// namespace codeReview
