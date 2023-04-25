#include <Algorithm/String/Alphabet/Alphabet.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using AlphabetForTest = Alphabet<unsigned char>;
}

TEST(AlphabetsTest, ContainsWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_TRUE(alphabet.contains('A'));
    EXPECT_TRUE(alphabet.contains('B'));
    EXPECT_TRUE(alphabet.contains('C'));
    EXPECT_TRUE(alphabet.contains('D'));
    EXPECT_TRUE(alphabet.contains('E'));
    EXPECT_TRUE(alphabet.contains('F'));
    EXPECT_FALSE(alphabet.contains('G'));
}

TEST(AlphabetsTest, GetCharacterWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ('A', alphabet.getCharacter(0U));
    EXPECT_EQ('B', alphabet.getCharacter(1U));
    EXPECT_EQ('C', alphabet.getCharacter(2U));
    EXPECT_EQ('D', alphabet.getCharacter(3U));
    EXPECT_EQ('E', alphabet.getCharacter(4U));
    EXPECT_EQ('F', alphabet.getCharacter(5U));
    EXPECT_EQ('\0', alphabet.getCharacter(6U));
}

TEST(AlphabetsTest, GetDigitValueWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ(0U, alphabet.getDigitValue('A'));
    EXPECT_EQ(1U, alphabet.getDigitValue('B'));
    EXPECT_EQ(2U, alphabet.getDigitValue('C'));
    EXPECT_EQ(3U, alphabet.getDigitValue('D'));
    EXPECT_EQ(4U, alphabet.getDigitValue('E'));
    EXPECT_EQ(5U, alphabet.getDigitValue('F'));
    EXPECT_EQ(0U, alphabet.getDigitValue('G'));
}

TEST(AlphabetsTest, GetRadixWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ(6U, alphabet.getRadix());
}

TEST(AlphabetsTest, ConvertStringToDigitValuesWorks) {
    AlphabetForTest alphabet("ABCDEF");

    AlphabetForTest::DigitValues values{1U, 1U, 0U, 0U, 5U, 3U, 3U, 0U, 4U};
    EXPECT_EQ(values, alphabet.convertStringToDigitValues("BBAGFDDGE"));
}

TEST(AlphabetsTest, ConvertDigitValuesToStringWorks) {
    AlphabetForTest alphabet("ABCDEF");
    AlphabetForTest::DigitValues values{1U, 1U, 0U, 5U, 3U, 4U};

    EXPECT_EQ("BBAFDE", alphabet.convertDigitValuesToString(values));
}

TEST(AlphabetsTest, GetCharactersWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ("ABCDEF", alphabet.getCharacters());
}

}  // namespace algorithm

}  // namespace alba
