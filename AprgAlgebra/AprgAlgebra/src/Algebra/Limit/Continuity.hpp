#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
{

enum class ContinuityType
{
    Unknown,
    Continuous,
    DiscontinuousWithRemovableDiscontinuity,
    DiscontinuousWithEssentialDiscontinuity
};

bool isContinuousAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

ContinuityType getContinuityTypeAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

}

}
