#pragma once

#ifdef OS_WINDOWS
#include <ScreenMonitoring/AlbaWindowsScreenMonitoring.hpp>
#endif

#ifdef OS_LINUX
#include <ScreenMonitoring/AlbaLinuxScreenMonitoring.hpp>
#endif

#if !defined(OS_WINDOWS) && !defined(OS_LINUX)
static_assert(false, "WINDOWS and LINUX are the only supported OS yet.");
#endif

namespace alba {

#ifdef OS_WINDOWS
class AlbaLocalScreenMonitoring : public AlbaWindowsScreenMonitoring
#endif

#ifdef OS_LINUX
                                class AlbaLocalScreenMonitoring : public AlbaLinuxScreenMonitoring
#endif
{
};

}  // namespace alba
