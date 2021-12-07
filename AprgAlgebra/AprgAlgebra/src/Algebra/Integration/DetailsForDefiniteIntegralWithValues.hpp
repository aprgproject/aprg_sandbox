#pragma once

#include <Math/Number/AlbaNumber.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

struct DetailsForDefiniteIntegralWithValues
{
    std::string variableName;
    AlbaNumber lowerEnd;
    AlbaNumber higherEnd;
};

using DetailsForDefiniteIntegralsWithValues = std::vector<DetailsForDefiniteIntegralWithValues>;

}

}
