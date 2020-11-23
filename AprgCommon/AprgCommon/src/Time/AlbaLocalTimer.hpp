#pragma once

#ifdef OS_WINDOWS
#include <Time/AlbaWindowsTimer.hpp>
#else
static_assert(false, "WINDOWS is only the supported OS yet.");
#endif

namespace alba
{

#ifdef OS_WINDOWS
class AlbaLocalTimer: public AlbaWindowsTimer
#endif
{
};

}//namespace alba
