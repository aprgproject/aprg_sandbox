#pragma once

#ifdef OS_WINDOWS
#include <Timer/AlbaWindowsTimer.hpp>
#endif

namespace alba
{

#ifdef OS_WINDOWS
class AlbaLocalTimer: public AlbaWindowsTimer
#endif
{
};

}//namespace alba
