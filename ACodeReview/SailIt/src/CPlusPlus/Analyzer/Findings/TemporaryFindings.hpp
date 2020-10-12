#pragma once

#include "FindingsBuffer.hpp"

namespace codeReview
{
class TemporaryFindings
{
public:    TemporaryFindings(FindingsBuffer& findingsBuffer);
    ~TemporaryFindings();
    void copyCurrentFindings(Findings& findings);
    void saveCurrentFindings();
private:
    FindingsBuffer& m_findingsBuffer;
};

}
