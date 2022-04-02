#include <Algorithm/String/Alphabet/Alphabet.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using AlphabetForTest = Alphabet<unsigned char>;
}

TEST(AlphabetsTest, ContainsWorks)
{
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_TRUE(alphabet.contains('A'));
    EXPECT_TRUE(alphabet.contains('B'));
    EXPECT_TRUE(alphabet.contains('C'));
    EXPECT_TRUE(alphabet.contains('D'));
    EXPECT_TRUE(alphabet.contains('E'));
    EXPECT_TRUE(alphabet.contains('F'));
    EXPECT_FALSE(alphabet.contains('G'));
}

TEST(AlphabetsTest, GetCharacterWorks)
{
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ('A', alphabet.getCharacter(0U));
    EXPECT_EQ('B', alphabet.getCharacter(1U));
    EXPECT_EQ('C', alphabet.getCharacter(2U));
    EXPECT_EQ('D', alphabet.getCharacter(3U));
    EXPECT_EQ('E', alphabet.getCharacter(4U));
    EXPECT_EQ('F', alphabet.getCharacter(5U));
    EXPECT_EQ('\0', alphabet.getCharacter(6U));
}

TEST(AlphabetsTest, GetValueWorks)
{
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ(0U, alphabet.getValue('A'));
    EXPECT_EQ(1U, alphabet.getValue('B'));
    EXPECT_EQ(2U, alphabet.getValue('C'));
    EXPECT_EQ(3U, alphabet.getValue('D'));
    EXPECT_EQ(4U, alphabet.getValue('E'));
    EXPECT_EQ(5U, alphabet.getValue('F'));
    EXPECT_EQ(0U, alphabet.getValue('G'));
}

TEST(AlphabetsTest, GetRadixWorks)
{
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ(6U, alphabet.getRadix());
}

TEST(AlphabetsTest, ConvertStringToValuesWorks)
{
    AlphabetForTest alphabet("ABCDEF");

    AlphabetForTest::Values values{1U, 1U, 0U, 0U, 5U, 3U, 3U, 0U, 4U};
    EXPECT_EQ(values, alphabet.convertStringToValues("BBAGFDDGE"));
}

TEST(AlphabetsTest, ConvertValuesToStringWorks)
{
    AlphabetForTest alphabet("ABCDEF");
    AlphabetForTest::Values values{1U, 1U, 0U, 5U, 3U, 4U};

    EXPECT_EQ("BBAFDE", alphabet.convertValuesToString(values));
}

TEST(AlphabetsTest, GetCharactersWorks)
{
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ("ABCDEF", alphabet.getCharacters());
}

}

}
