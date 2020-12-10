#include "AlbaGrepStringSingletionForString.hpp"

#include <String/AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

AlbaGrepStringSingletionForString & AlbaGrepStringSingletionForString::getInstance()
{
    static AlbaGrepStringSingletionForString instance;
    return instance;
}

void AlbaGrepStringSingletionForString::setString(std::string const& stringInput)
{
    m_stringInCapital = stringHelper::getStringWithCapitalLetters(stringInput);
}

std::string AlbaGrepStringSingletionForString::getString() const
{
    return m_stringInCapital;
}

}
