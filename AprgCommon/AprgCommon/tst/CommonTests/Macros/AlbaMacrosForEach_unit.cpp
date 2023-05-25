#include <Common/Macros/AlbaMacrosForEach.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {
TEST(AlbaMacrosForEachTest, AlbaMacrosForEachWorks) {
#define CREATE_CONST_CHAR_ARRAY(parameter) char const *parameter##_string = #parameter;

    ALBA_MACROS_FOR_EACH(CREATE_CONST_CHAR_ARRAY, foo, bar, baz);

    EXPECT_EQ("foo", foo_string);
    EXPECT_EQ("bar", bar_string);
    EXPECT_EQ("baz", baz_string);
}

TEST(AlbaMacrosForEachTest, AlbaMacrosForEachListWorks) {
#define CREATE_PARAMETER_LIST(x) int x

    auto sampleSumFunction = [](ALBA_MACROS_FOR_EACH_WITH_COMMA(CREATE_PARAMETER_LIST, foo, bar, baz)) {
        return foo + bar + baz;
    };

    EXPECT_EQ(0, sampleSumFunction(0, 0, 0));
    EXPECT_EQ(3, sampleSumFunction(1, 1, 1));
    EXPECT_EQ(6, sampleSumFunction(1, 2, 3));
}

}  // namespace alba