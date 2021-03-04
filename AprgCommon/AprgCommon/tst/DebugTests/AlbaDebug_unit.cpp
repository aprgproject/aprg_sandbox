#include <Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaDebug, DISABLED_PrintTest)
{
    unsigned int Mark=0,Earvin=0,Alba=0;
    ALBA_PRINT3(Mark, Earvin, Alba);
}

}