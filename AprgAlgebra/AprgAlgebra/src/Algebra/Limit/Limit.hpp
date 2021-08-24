#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
{

Term getLimitAsVariableApproachesTheValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

}

}
