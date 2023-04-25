#include "FindingsBuffer.hpp"

#include <iostream>

namespace codeReview {

FindingsBuffer::FindingsBuffer() {
    m_findingsBuffer.emplace_back();
    m_currentIndex = 0;
}

void FindingsBuffer::createNewTemporaryFindingsBuffer() {
    m_findingsBuffer.emplace_back();
    m_currentIndex++;
}

void FindingsBuffer::deleteCurrentBuffer() {
    if (m_currentIndex > 0) {
        m_findingsBuffer.pop_back();
        m_currentIndex--;
    }
}

void FindingsBuffer::saveCurrentFindings() {
    if (m_currentIndex > 0) {
        m_findingsBuffer[m_currentIndex - 1].copyFindings(m_findingsBuffer.back());
    }
}

void FindingsBuffer::copyCurrentFindings(Findings& findings) { findings.copyFindings(m_findingsBuffer.back()); }

void FindingsBuffer::copyAllFindings(Findings& findings) {
    for (Findings& findingsBufferContent : m_findingsBuffer) {
        findings.copyFindings(findingsBufferContent);
    }
}

void FindingsBuffer::printFindings() {
    for (Findings& findingsBufferContent : m_findingsBuffer) {
        findingsBufferContent.printFindings(std::cout);
    }
}

void FindingsBuffer::clearAll() {
    m_findingsBuffer.clear();
    FindingsBuffer();
}

void FindingsBuffer::addFinding(
    unsigned int const lineNumber, string const& fileLocator, string const& content, string const& locator) {
    m_findingsBuffer[m_currentIndex].addFinding(lineNumber, fileLocator, content, locator);
}

}  // namespace codeReview
