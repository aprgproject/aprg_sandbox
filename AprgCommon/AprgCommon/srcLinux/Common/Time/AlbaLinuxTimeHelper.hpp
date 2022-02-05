#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <ctime>

namespace alba
{

void sleep(unsigned int const milliSeconds);
AlbaDateTime getCurrentDateTime();
AlbaDateTime convertSystemTimeToAlbaDateTime(struct timespec const& timeSpec);

}//namespace alba
