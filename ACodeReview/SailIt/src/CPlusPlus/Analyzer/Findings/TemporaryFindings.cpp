#include "TemporaryFindings.hpp"

namespace codeReview
{

TemporaryFindings::TemporaryFindings(FindingsBuffer& findingsBuffer)
    : m_findingsBuffer(findingsBuffer)
{
    m_findingsBuffer.createNewTemporaryFindingsBuffer();
}

TemporaryFindings::~TemporaryFindings()
{
    m_findingsBuffer.deleteCurrentBuffer();
}

void TemporaryFindings::copyCurrentFindings(Findings& findings)
{
    m_findingsBuffer.copyCurrentFindings(findings);
}

void TemporaryFindings::saveCurrentFindings()
{
    m_findingsBuffer.saveCurrentFindings();
}

}//namespace codeReview
