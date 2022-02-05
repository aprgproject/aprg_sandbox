#pragma once

#include <string>

#ifdef OS_WINDOWS
#include <Common/Time/AlbaWindowsTimer.hpp>
#endif

#ifdef OS_LINUX
#include <Common/Time/AlbaLinuxTimer.hpp>
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
public:
    std::string getElapsedTimeDisplayableString() const;

};

}//namespace alba
