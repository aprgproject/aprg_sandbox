#pragma once

#ifdef OS_WINDOWS
#include <User/AlbaWindowsUserAutomation.hpp>
#elsestatic_assert(false, "WINDOWS is only the supported OS yet.");
#endif

namespace alba{

#ifdef OS_WINDOWS
class AlbaLocalUserAutomation: public AlbaWindowsUserAutomation
#endif
{
};

}
