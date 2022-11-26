#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class Variable : public BaseTermData
{
public:
    Variable();
    Variable(std::string const& variableName);

    bool operator==(Variable const& second) const;
    bool operator!=(Variable const& second) const;
    bool operator<(Variable const& second) const;
    std::string getVariableName() const;

    void setVariableName(std::string const& variableName);

private:
    friend std::ostream & operator<<(std::ostream & out, Variable const& variable);

    std::string m_variableName;
};


}

}
