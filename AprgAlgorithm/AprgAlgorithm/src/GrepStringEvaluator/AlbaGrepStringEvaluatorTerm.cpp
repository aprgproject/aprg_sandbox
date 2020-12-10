#include "AlbaGrepStringEvaluatorTerm.hpp"

#include <GrepStringEvaluator/AlbaGrepStringSingletionForString.hpp>
#include <String/AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm()
    : m_stringToFind()
    , m_result(false)
{}

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(string const& stringToFind)
    : m_stringToFind(stringToFind)
    , m_result(false)
{}

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(bool const result)
    : m_stringToFind()
    , m_result(result)
{}

bool AlbaGrepStringEvaluatorTerm::getResult() const
{
    return m_result;
}

void AlbaGrepStringEvaluatorTerm::performFindOperationAndSaveResult()
{
    AlbaGrepStringSingletionForString const& singletionForString(AlbaGrepStringSingletionForString::getInstance());
    m_result = stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(singletionForString.getString(), m_stringToFind);
}

}
