#pragma once

#include "CPlusPlusType.hpp"

#include <string>

using std::string;

namespace codeReview
{

class CPlusPlusVariable
{
public:
    CPlusPlusVariable();
    CPlusPlusVariable(CPlusPlusType const& cPlusPlusType);
    CPlusPlusType getType() const;
private:
    CPlusPlusType m_type;
};

}


