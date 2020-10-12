#pragma once

#include "../../Findings/Findings.hpp"
#include <vector>

namespace codeReview
{
class FindingsBuffer
{
public:    FindingsBuffer();
    void createNewTemporaryFindingsBuffer();
    void deleteCurrentBuffer();
    void saveCurrentFindings();
    void copyCurrentFindings(Findings& findings);
    void copyAllFindings(Findings& findings);
    void printFindings();
    void addFinding(unsigned int const lineNumber, string const& fileLocator, string const& content, string const& locator);
    void clearAll();
private:
    std::vector<Findings> m_findingsBuffer;
    int m_currentIndex;
};
}