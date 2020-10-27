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

}//namespace alba
