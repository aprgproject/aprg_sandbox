#pragma once

#include <functional>
#include <set>
#include <string>

#ifdef OS_WINDOWS
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#endif

#include <PathHandlers/PathContantsAndTypes.hpp>

namespace alba
{

#ifdef OS_WINDOWS
class AlbaLocalPathHandler: public AlbaWindowsPathHandler
#endif
{
public:
    AlbaLocalPathHandler(PathInitialValueSource const initialValueSource);
    AlbaLocalPathHandler(std::string const& path);
};

}//namespace alba
