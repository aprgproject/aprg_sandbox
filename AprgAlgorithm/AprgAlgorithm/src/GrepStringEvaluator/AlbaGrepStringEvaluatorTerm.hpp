#pragma once

#include <string>

namespace alba
{

class AlbaGrepStringEvaluatorTerm
{
public:
    AlbaGrepStringEvaluatorTerm();
    AlbaGrepStringEvaluatorTerm(std::string const& stringToFind);
    AlbaGrepStringEvaluatorTerm(bool const result);
    bool getResult() const;
    void performFindOperationAndSaveResult();

private:
    std::string m_stringToFind;
    bool m_result;
};

}
