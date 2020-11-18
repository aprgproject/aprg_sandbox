#include <Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

using namespace std;

TEST(AlbaDebug, GetStringLiteralTest)
{
    unsigned int Mark=0,Earvin=0,Alba=0;

    string testString(ALBA_DEBUG_GET_STRING_LITERALS3(Mark, Earvin, Alba));
    EXPECT_EQ("MarkEarvinAlba", testString);
}

TEST(AlbaDebug, DISABLED_PrintTest)
{
    unsigned int Mark=0,Earvin=0,Alba=0;

    ALBA_DEBUG_PRINT3(Mark, Earvin, Alba);
}


