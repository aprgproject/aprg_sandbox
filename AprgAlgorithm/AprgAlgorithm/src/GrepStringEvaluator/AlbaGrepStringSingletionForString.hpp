#pragma once

#include <string>

namespace alba
{

class AlbaGrepStringSingletionForString
{
public:
    static AlbaGrepStringSingletionForString & getInstance();
    void setString(std::string const& stringInput);
    std::string getString() const;
private:
    std::string m_stringInCapital;
};

}
