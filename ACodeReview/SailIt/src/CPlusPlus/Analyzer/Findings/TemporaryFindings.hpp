#pragma once

#include "FindingsBuffer.hpp"
#include <vector>

using std::vector;

namespace codeReview
{

class TemporaryFindings
{
public:
    TemporaryFindings(FindingsBuffer& findingsBuffer);
    ~TemporaryFindings();
    void copyCurrentFindings(Findings& findings);
    void saveCurrentFindings();
private:
    FindingsBuffer& m_findingsBuffer;
};

}
