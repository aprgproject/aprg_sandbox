#include <PathHandlerTests/AlbaLinuxPathHandlerTest.hpp>

#include <String/AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

AlbaLinuxPathHandlerTest::AlbaLinuxPathHandlerTest()
{}

string AlbaLinuxPathHandlerTest::convertToSimplestPath(string const& path)
{
    return stringHelper::getCorrectPathWithoutDoublePeriod<'/'>(stringHelper::getCorrectPathWithReplacedSlashCharacters<'/'>(path));
}

}
