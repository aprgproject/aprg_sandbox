#include "AlbaGrepStringEvaluatorTerm.hpp"

#include <String/AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

string AlbaGrepStringEvaluatorTerm::s_mainString;

void AlbaGrepStringEvaluatorTerm::setMainString(std::string const& mainString)
{
    s_mainString = stringHelper::getStringWithCapitalLetters(mainString);
}

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm()
    : m_type(AlbaGrepStringEvaluatorTermType::Unknown)
    , m_savedResult(false)
    , m_stringToFind()
{}

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(string const& stringToFind)
    : m_type(AlbaGrepStringEvaluatorTermType::StringToFind)
    , m_savedResult(false)
    , m_stringToFind(stringToFind)
{}

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(bool const result)
    : m_type(AlbaGrepStringEvaluatorTermType::BooleanResult)
    , m_savedResult(result)
    , m_stringToFind()
{}

bool AlbaGrepStringEvaluatorTerm::getResult() const
{
    bool result(false);
    if(AlbaGrepStringEvaluatorTermType::BooleanResult == m_type)
    {
        result = m_savedResult;
    }
    else if(AlbaGrepStringEvaluatorTermType::StringToFind == m_type)
    {
        result = stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(s_mainString, m_stringToFind);
    }
    return result;
}

}
