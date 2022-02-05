#pragma once

#ifdef OS_WINDOWS
#include <Common/PathHandlers/AlbaWindowsPathHandler.hpp>
#endif

#ifdef OS_LINUX
#include <Common/PathHandlers/AlbaLinuxPathHandler.hpp>
#endif

#if !defined(OS_WINDOWS) && !defined(OS_LINUX)
static_assert(false, "WINDOWS and LINUX are the only supported OS yet.");
#endif

#include <Common/PathHandlers/PathContantsAndTypes.hpp>

#include <functional>
#include <set>
#include <string>

namespace alba
{

#ifdef OS_WINDOWS
class AlbaLocalPathHandler: public AlbaWindowsPathHandler
#endif

#ifdef OS_LINUX
class AlbaLocalPathHandler: public AlbaLinuxPathHandler
#endif
{
public:
    AlbaLocalPathHandler(PathInitialValueSource const initialValueSource);
    AlbaLocalPathHandler(std::string const& path);
    virtual ~AlbaLocalPathHandler();
};

}//namespace alba
