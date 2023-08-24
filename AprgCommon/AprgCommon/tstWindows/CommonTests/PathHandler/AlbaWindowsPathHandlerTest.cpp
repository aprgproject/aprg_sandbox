#include "AlbaWindowsPathHandlerTest.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaWindowsPathHandlerTest::AlbaWindowsPathHandlerTest() : pathOfAprgDirectory(APRG_DIR R"(\)") {}

string AlbaWindowsPathHandlerTest::convertToSimplestPath(string_view path) {
    return getCorrectPathWithoutDoublePeriod<'\\'>(getCorrectPathWithReplacedSlashCharacters<'\\'>(path));
}

string AlbaWindowsPathHandlerTest::getDriveOfAprgDir() { return getStringBeforeThisString(pathOfAprgDirectory, ":"); }

}  // namespace alba
