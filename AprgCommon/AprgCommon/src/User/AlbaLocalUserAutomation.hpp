#pragma once

#include <windows.h>

#include <functional>
#include <string>

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



