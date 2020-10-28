#pragma once

#include <windows.h>

#include <functional>
#include <string>

#ifdef OS_WINDOWS
#include <User/AlbaWindowsUserAutomation.hpp>
#else
static_assert(false, "WINDOWS is only the supported OS yet.");
#endif

namespace alba{

#ifdef OS_WINDOWS
class AlbaLocalUserAutomation: public AlbaWindowsUserAutomation#endif
{
};

}
