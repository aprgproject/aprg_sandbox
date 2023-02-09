#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <windows.h>

namespace alba
{

AlbaDateTime convertSystemTimeToAlbaDateTime(SYSTEMTIME const& systemTime);

}//namespace alba