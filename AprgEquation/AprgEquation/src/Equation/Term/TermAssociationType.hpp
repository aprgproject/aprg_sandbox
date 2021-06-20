#pragma once

#include <vector>

namespace alba
{
namespace equation
{

enum class TermAssociationType
{
    Positive,
    Negative
};

using TermAssociationTypes = std::vector<TermAssociationType>;

}

}