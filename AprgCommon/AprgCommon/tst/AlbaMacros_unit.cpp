#include <Macros/AlbaMacros.hpp>

#include <gtest/gtest.h>

using namespace std;

TEST(AlbaMacroArgumentCounter, IntegerTest)
{
    EXPECT_EQ(1, ALBA_MACROS_COUNT_ARGS(1));
    EXPECT_EQ(3, ALBA_MACROS_COUNT_ARGS(8237, 23458, 28749));
    EXPECT_EQ(4, ALBA_MACROS_COUNT_ARGS(0x1, 0x2, 0x3, 0x4));
}

TEST(AlbaMacroArgumentCounter, VariableTest)
{
    int i1=1, i2=2, i3=3;
    EXPECT_EQ(1, ALBA_MACROS_COUNT_ARGS(i1));
    EXPECT_EQ(2, ALBA_MACROS_COUNT_ARGS(i1, i2));
    EXPECT_EQ(3, ALBA_MACROS_COUNT_ARGS(i1, i2, i3));
    i1=i2; i2=i3; i3=i1;
}

TEST(AlbaMacroArgumentCounter, StringTest)
{
    EXPECT_EQ(1, ALBA_MACROS_COUNT_ARGS("one"));
    EXPECT_EQ(2, ALBA_MACROS_COUNT_ARGS("one", "two"));
    EXPECT_EQ(3, ALBA_MACROS_COUNT_ARGS("one", "two", "three"));
}

TEST(AlbaMacros, DisplayMessageTest)
{
    #define ALBA_MACROS_DISPLAY_VALUE_PRAGMA_MESSAGE_SAMPLE_MACRO 10000
    EXPECT_EQ("ALBA_MACROS_DISPLAY_VALUE_PRAGMA_MESSAGE_SAMPLE_MACRO=10000", ALBA_MACROS_DISPLAY_VALUE_PRAGMA_MESSAGE(ALBA_MACROS_DISPLAY_VALUE_PRAGMA_MESSAGE_SAMPLE_MACRO));
    #pragma message(ALBA_MACROS_DISPLAY_VALUE_PRAGMA_MESSAGE(ALBA_MACROS_DISPLAY_VALUE_PRAGMA_MESSAGE_SAMPLE_MACRO))
}

TEST(AlbaMacros, GetStringLiteral)
{
    enum class SampleEnumClass
    {
        Type1,
        Type2
    };

    EXPECT_EQ("12345", ALBA_MACROS_GET_STRING_LITERAL(12345));
    EXPECT_EQ("SampleEnumClass::Type1", ALBA_MACROS_GET_STRING_LITERAL(SampleEnumClass::Type1));
    EXPECT_EQ("SampleEnumClass::Type2", ALBA_MACROS_GET_STRING_LITERAL(SampleEnumClass::Type2));
}

TEST(AlbaMacros, CaseEnumStringLiteral)
{
    enum class SampleEnumClass
    {
        Type1,
        Type2
    };
    struct SampleClass
    {
        string getString(SampleEnumClass const enumValue)
        {
            switch(enumValue)
            {
            ALBA_MACROS_CASE_ENUM_STRING(SampleEnumClass::Type1)
                    ALBA_MACROS_CASE_ENUM_STRING(SampleEnumClass::Type2)
            }
        }
    };
    SampleEnumClass enumValue1 = SampleEnumClass::Type1;
    SampleEnumClass enumValue2 = SampleEnumClass::Type2;

    SampleClass sampleObject;
    EXPECT_EQ("SampleEnumClass::Type1", sampleObject.getString(enumValue1));
    EXPECT_EQ("SampleEnumClass::Type2", sampleObject.getString(enumValue2));
}


