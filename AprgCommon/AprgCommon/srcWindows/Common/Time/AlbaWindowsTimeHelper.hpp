#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <windows.h>

namespace alba
{

void sleep(unsigned int const milliSeconds);
AlbaDateTime getCurrentDateTime();
AlbaDateTime convertSystemTimeToAlbaDateTime(SYSTEMTIME const& systemTime);

}//namespace alba
