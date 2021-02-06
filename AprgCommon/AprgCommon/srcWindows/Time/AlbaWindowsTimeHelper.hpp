#pragma once

#include <Time/AlbaDateTime.hpp>

#include <windows.h>

namespace alba
{

class AlbaWindowsTimeHelper
{
public:
    void sleep(unsigned int const milliSeconds);
    AlbaDateTime getCurrentDateTime();
    AlbaDateTime convertSystemTimeToAlbaDateTime(SYSTEMTIME const& systemTime);
};

}//namespace alba
