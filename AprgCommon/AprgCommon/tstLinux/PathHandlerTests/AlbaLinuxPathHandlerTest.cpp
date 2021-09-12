#include <PathHandlerTests/AlbaLinuxPathHandlerTest.hpp>
#include <String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba{

AlbaLinuxPathHandlerTest::AlbaLinuxPathHandlerTest()
{}

string AlbaLinuxPathHandlerTest::convertToSimplestPath(string const& path)
{
    return getCorrectPathWithoutDoublePeriod<'/'>(getCorrectPathWithReplacedSlashCharacters<'/'>(path));
}

}