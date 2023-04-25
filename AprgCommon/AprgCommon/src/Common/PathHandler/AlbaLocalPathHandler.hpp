#pragma once

#ifdef OS_WINDOWS // you could also use __has_include as well
#include <Common/PathHandler/AlbaWindowsPathHandler.hpp>
#endif

#ifdef OS_LINUX
#include <Common/PathHandler/AlbaLinuxPathHandler.hpp>
#endif

#if !defined(OS_WINDOWS) && !defined(OS_LINUX)
static_assert(false, "WINDOWS and LINUX are the only supported OS yet.");
#endif

#include <Common/PathHandler/PathContantsAndTypes.hpp>

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

#ifdef OS_WINDOWS
    template<typename... ArgumentTypes>
    AlbaLocalPathHandler(ArgumentTypes&&... arguments)
         : AlbaWindowsPathHandler(std::forward<ArgumentTypes>(arguments)...)
    {}
#endif

#ifdef OS_LINUX
    template<typename... ArgumentTypes>
    AlbaLocalPathHandler(ArgumentTypes&&... arguments)
         : AlbaLinuxPathHandler(std::forward<ArgumentTypes>(arguments)...)
    {}
#endif

    // rule of zero
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
};

}//namespace alba
