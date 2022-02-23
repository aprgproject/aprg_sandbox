#pragma once

#ifdef OS_WINDOWS
#include <UserAutomation/AlbaWindowsUserAutomation.hpp>
#endif

#ifdef OS_LINUX
#include <UserAutomation/AlbaLinuxUserAutomation.hpp>
#endif

#if !defined(OS_WINDOWS) && !defined(OS_LINUX)
static_assert(false, "WINDOWS and LINUX are the only supported OS yet.");
#endif

namespace alba
{

#ifdef OS_WINDOWS
class AlbaLocalUserAutomation: public AlbaWindowsUserAutomation
#endif

#ifdef OS_LINUX
class AlbaLocalUserAutomation: public AlbaLinuxUserAutomation
#endif
{
};

}
