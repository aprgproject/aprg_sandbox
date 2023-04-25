#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTests/PathHandler/AlbaLinuxPathHandlerTest.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

string AlbaLinuxPathHandlerTest::convertToSimplestPath(string const& path) {
    return getCorrectPathWithoutDoublePeriod<'/'>(getCorrectPathWithReplacedSlashCharacters<'/'>(path));
}

}  // namespace alba
