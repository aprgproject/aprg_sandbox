#pragma once

#include <string>

namespace alba
{

enum class AlbaGrepStringEvaluatorTermType
{
    Unknown,
    BooleanResult,
    StringToFind
};

class AlbaGrepStringEvaluatorTerm
{
public:
    static void setMainString(std::string const& mainString);

    AlbaGrepStringEvaluatorTerm();
    AlbaGrepStringEvaluatorTerm(std::string const& stringToFind);
    AlbaGrepStringEvaluatorTerm(bool const result);
    bool getResult() const;

private:
    static std::string s_mainString;
    AlbaGrepStringEvaluatorTermType m_type;
    bool m_savedResult;
    std::string m_stringToFind;
};

}
