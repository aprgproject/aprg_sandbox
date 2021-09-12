#include <PathHandlerTests/AlbaWindowsPathHandlerTest.hpp>
#include <String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

AlbaWindowsPathHandlerTest::AlbaWindowsPathHandlerTest()
    : pathOfAprgDirectory(APRG_DIR)
{}

string AlbaWindowsPathHandlerTest::convertToSimplestPath(string const& path)
{
    return getCorrectPathWithoutDoublePeriod<'\\'>(getCorrectPathWithReplacedSlashCharacters<'\\'>(path));
}

string AlbaWindowsPathHandlerTest::getDriveOfAprgDir()
{
    return getStringBeforeThisString(pathOfAprgDirectory, ":");
}

}
