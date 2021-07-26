#pragma once

#include <vector>

namespace alba
{

namespace algebra
{

enum class TermAssociationType
{
    Positive,
    Negative
};

using TermAssociationTypes = std::vector<TermAssociationType>;

}

}
