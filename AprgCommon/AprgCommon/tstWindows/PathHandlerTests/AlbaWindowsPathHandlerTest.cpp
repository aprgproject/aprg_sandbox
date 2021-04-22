#include <PathHandlerTests/AlbaWindowsPathHandlerTest.hpp>

#include <String/AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

AlbaWindowsPathHandlerTest::AlbaWindowsPathHandlerTest()
    : pathOfAprgDirectory(APRG_DIR)
{}

string AlbaWindowsPathHandlerTest::convertToSimplestPath(string const& path){
    return stringHelper::getCorrectPathWithoutDoublePeriod<'\\'>(stringHelper::getCorrectPathWithReplacedSlashCharacters<'\\'>(path));
}

string AlbaWindowsPathHandlerTest::getDriveOfAprgDir()
{
    return stringHelper::getStringBeforeThisString(pathOfAprgDirectory, ":");
}

}