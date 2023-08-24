#include "AlbaLinuxPathHandlerTest.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;
namespace alba {

string AlbaLinuxPathHandlerTest::convertToSimplestPath(string_view path) {    return getCorrectPathWithoutDoublePeriod<'/'>(getCorrectPathWithReplacedSlashCharacters<'/'>(path));
}

}  // namespace alba
