#include <AlbaStringHelper.hpp>
#include "FindingsToAddHelper.hpp"
#include <iostream>
#include "../TermAnalyzer.hpp"

using namespace std;
using alba::stringHelper::constructFileLocator;

namespace codeReview
{

void TermAnalyzer::addFinding(string const& fileLocator, string const& content, Looper const& findingLooper)
{
    m_findingsBuffer.addFinding(findingLooper.getContentReference().getLineNumber(), fileLocator, content, getLocatorString(findingLooper));
}

template <FindingsToAdd findingsToAdd> void TermAnalyzer::addFindingsForExpectedNewLineIfNeeded(Looper const&)
{}
template void TermAnalyzer::addFindingsForExpectedNewLineIfNeeded<FindingsToAdd::None>(Looper const&);
template void TermAnalyzer::addFindingsForExpectedNewLineIfNeeded<FindingsToAdd::UnexpectsWhiteSpace>(Looper const&);
template void TermAnalyzer::addFindingsForExpectedNewLineIfNeeded<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(Looper const&);
template <> void TermAnalyzer::addFindingsForExpectedNewLineIfNeeded<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(Looper const& findingLooper)
{
    addFinding(constructFileLocator(__FILE__, __LINE__), "New line is expected", findingLooper);
}

template <FindingsToAdd findingsToAdd> void TermAnalyzer::addFindingsForUnexpectedWhiteSpaceIfNeeded(Looper const&)
{}
template void TermAnalyzer::addFindingsForUnexpectedWhiteSpaceIfNeeded<FindingsToAdd::None>(Looper const&);
template <> void TermAnalyzer::addFindingsForUnexpectedWhiteSpaceIfNeeded<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(Looper const& findingLooper)
{
    addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected white space", findingLooper);
}
template <> void TermAnalyzer::addFindingsForUnexpectedWhiteSpaceIfNeeded<FindingsToAdd::UnexpectsWhiteSpace>(Looper const& findingLooper)
{
    addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected white space", findingLooper);
}
template <> void TermAnalyzer::addFindingsForUnexpectedWhiteSpaceIfNeeded<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(Looper const& findingLooper)
{
    addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected white space", findingLooper);
}

template <FindingsToAdd findingsToAdd> void TermAnalyzer::addFindingsForUnexpectedNewLineIfNeeded(Looper const&)
{}
template void TermAnalyzer::addFindingsForUnexpectedNewLineIfNeeded<FindingsToAdd::None>(Looper const&);
template void TermAnalyzer::addFindingsForUnexpectedNewLineIfNeeded<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(Looper const&);
template void TermAnalyzer::addFindingsForUnexpectedNewLineIfNeeded<FindingsToAdd::UnexpectsWhiteSpace>(Looper const&);
template <> void TermAnalyzer::addFindingsForUnexpectedNewLineIfNeeded<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(Looper const& findingLooper)
{
    addFinding(constructFileLocator(__FILE__, __LINE__), "Unexpected new line", findingLooper);
}


}// namespace codeReview
