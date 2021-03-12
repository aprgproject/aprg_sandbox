#pragma once

#ifdef OS_WINDOWS
#include <Time/AlbaWindowsTimeHelper.hpp>
#endif

#ifdef OS_LINUX
#include <Time/AlbaLinuxTimeHelper.hpp>
#endif

#if !defined(OS_WINDOWS) && !defined(OS_LINUX)
static_assert(false, "WINDOWS and LINUX are the only supported OS yet.");
#endif
