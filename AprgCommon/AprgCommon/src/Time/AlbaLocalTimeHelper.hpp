#pragma once

#ifdef OS_WINDOWS
#include <Time/AlbaWindowsTimeHelper.hpp>
#else
static_assert(false, "WINDOWS is only the supported OS yet.");
#endif

namespace alba
{

#ifdef OS_WINDOWS
class AlbaLocalTimeHelper: public AlbaWindowsTimeHelper
#endif
{
};

}//namespace alba
