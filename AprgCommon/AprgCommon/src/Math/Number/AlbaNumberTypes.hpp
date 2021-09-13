#pragma once

#include <Math/Number/AlbaNumber.hpp>
#include <Math/Number/Interval/AlbaNumberInterval.hpp>
#include <Optional/AlbaOptional.hpp>

#include <map>
#include <set>
#include <vector>

namespace alba
{

using AlbaNumbersSet=std::set<AlbaNumber>;
using AlbaNumberMap=std::map<AlbaNumber, AlbaNumber>;
using AlbaNumbers=std::vector<AlbaNumber>;
using AlbaNumberPairs=std::vector<std::pair<AlbaNumber, AlbaNumber>>;
using AlbaNumberOptional=AlbaOptional<AlbaNumber>;
using AlbaNumberIntervals=std::vector<AlbaNumberInterval>;
using AlbaNumberIntervalOptional=AlbaOptional<AlbaNumberInterval>;

}
