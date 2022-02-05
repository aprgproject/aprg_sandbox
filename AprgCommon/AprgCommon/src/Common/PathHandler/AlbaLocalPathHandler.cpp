#include "AlbaLocalPathHandler.hpp"

using namespace std;

namespace alba
{

#ifdef OS_WINDOWS
AlbaLocalPathHandler::AlbaLocalPathHandler(PathInitialValueSource const initialValueSource)
    : AlbaWindowsPathHandler(initialValueSource)
{}
AlbaLocalPathHandler::AlbaLocalPathHandler(std::string const& path)
    : AlbaWindowsPathHandler(path)
{}
#endif

#ifdef OS_LINUX
AlbaLocalPathHandler::AlbaLocalPathHandler(PathInitialValueSource const initialValueSource)
    : AlbaLinuxPathHandler(initialValueSource)
{}
AlbaLocalPathHandler::AlbaLocalPathHandler(std::string const& path)
    : AlbaLinuxPathHandler(path)
{}
#endif

AlbaLocalPathHandler::~AlbaLocalPathHandler()
{}

}//namespace alba