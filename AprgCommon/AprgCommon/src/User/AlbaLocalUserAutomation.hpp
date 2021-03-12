#pragma once

#ifdef OS_WINDOWS
#include <User/AlbaWindowsUserAutomation.hpp>
#endif

#ifdef OS_LINUX
#include <User/AlbaLinuxUserAutomation.hpp>
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
