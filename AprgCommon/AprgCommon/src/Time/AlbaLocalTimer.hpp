#pragma once

#ifdef OS_WINDOWS
#include <Time/AlbaWindowsTimer.hpp>
#endif

#ifdef OS_LINUX
#include <Time/AlbaLinuxTimer.hpp>
#endif

#if !defined(OS_WINDOWS) && !defined(OS_LINUX)
static_assert(false, "WINDOWS and LINUX are the only supported OS yet.");
#endif

namespace alba
{


#ifdef OS_WINDOWS
class AlbaLocalTimer: public AlbaWindowsTimer
#endif

#ifdef OS_LINUX
class AlbaLocalTimer: public AlbaLinuxTimer
#endif
{
};

}//namespace alba
