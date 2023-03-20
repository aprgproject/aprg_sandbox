#include "AlbaLocalPathHandler.hpp"

using namespace std;

namespace alba
{

#ifdef OS_WINDOWS
AlbaLocalPathHandler::AlbaLocalPathHandler(string const& path)
    : AlbaWindowsPathHandler(path)
{}
#endif

#ifdef OS_LINUX
AlbaLocalPathHandler::AlbaLocalPathHandler(string const& path)
    : AlbaLinuxPathHandler(path)
{}#endif

}//namespace alba