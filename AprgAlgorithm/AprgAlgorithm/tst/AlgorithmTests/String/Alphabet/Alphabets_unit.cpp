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

    EXPECT_EQ('A', alphabet.getCharacter(0));
    EXPECT_EQ('B', alphabet.getCharacter(1));
    EXPECT_EQ('C', alphabet.getCharacter(2));
    EXPECT_EQ('D', alphabet.getCharacter(3));
    EXPECT_EQ('E', alphabet.getCharacter(4));
    EXPECT_EQ('F', alphabet.getCharacter(5));
    EXPECT_EQ('\0', alphabet.getCharacter(6));
}

TEST(AlphabetsTest, GetDigitValueWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ(0, alphabet.getDigitValue('A'));
    EXPECT_EQ(1, alphabet.getDigitValue('B'));
    EXPECT_EQ(2, alphabet.getDigitValue('C'));
    EXPECT_EQ(3, alphabet.getDigitValue('D'));
    EXPECT_EQ(4, alphabet.getDigitValue('E'));
    EXPECT_EQ(5, alphabet.getDigitValue('F'));
    EXPECT_EQ(0, alphabet.getDigitValue('G'));
}

TEST(AlphabetsTest, GetRadixWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ(6, alphabet.getRadix());
}

TEST(AlphabetsTest, ConvertStringToDigitValuesWorks) {
    AlphabetForTest alphabet("ABCDEF");

    AlphabetForTest::DigitValues values{1, 1, 0, 0, 5, 3, 3, 0, 4};
    EXPECT_EQ(values, alphabet.convertStringToDigitValues("BBAGFDDGE"));
}

TEST(AlphabetsTest, ConvertDigitValuesToStringWorks) {
    AlphabetForTest alphabet("ABCDEF");
    AlphabetForTest::DigitValues values{1, 1, 0, 5, 3, 4};

    EXPECT_EQ("BBAFDE", alphabet.convertDigitValuesToString(values));
}

TEST(AlphabetsTest, GetCharactersWorks) {
    AlphabetForTest alphabet("ABCDEF");

    EXPECT_EQ("ABCDEF", alphabet.getCharacters());
}

}  // namespace algorithm

}  // namespace alba
