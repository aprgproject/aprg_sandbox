#pragma once

#include <Math/AlbaNumber.hpp>
#include <Math/AlbaNumberInterval.hpp>
#include <Optional/AlbaOptional.hpp>

#include <set>
#include <vector>

namespace alba
{

using AlbaNumbersSet=std::set<AlbaNumber>;
using AlbaNumbers=std::vector<AlbaNumber>;
using AlbaNumberOptional=AlbaOptional<AlbaNumber>;
using AlbaNumberIntervals=std::vector<AlbaNumberInterval>;using AlbaNumberIntervalOptional=AlbaOptional<AlbaNumberInterval>;

}