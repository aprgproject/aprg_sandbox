#pragma once

#include <functional>
#include <string>
#include <windows.h>

#ifdef OS_WINDOWS
#include <User/AlbaWindowsUserAutomation.hpp>
#endif

namespace alba
{

#ifdef OS_WINDOWS
class AlbaLocalUserAutomation: public AlbaWindowsUserAutomation
#endif
{
};

}
