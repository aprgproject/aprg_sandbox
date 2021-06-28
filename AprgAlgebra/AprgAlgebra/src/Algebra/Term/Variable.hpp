#pragma once

#include <Algebra/Term/BaseTermData.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class Variable : public BaseTermData
{
    friend std::ostream & operator<<(std::ostream & out, Variable const& variable);
public:
    Variable();
    Variable(std::string const& variableName);

    bool operator==(Variable const& second) const;
    bool operator!=(Variable const& second) const;
    bool operator<(Variable const& second) const;

    std::string getVariableName() const;
    std::string getDisplayableString() const;

    void setVariableName(std::string const& variableName);

private:
    std::string m_variableName;
};

std::ostream & operator<<(std::ostream & out, Variable const& variable);

}

}
