#include <Algorithm/String/Alphabet/Alphabet.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
Alphabet<uint8_t> getBinaryAlphabet() { return Alphabet<uint8_t>("01"); }

Alphabet<uint8_t> getDnaAlphabet() { return Alphabet<uint8_t>("ACTG"); }

Alphabet<uint8_t> getOctalAlphabet() { return Alphabet<uint8_t>("01234567"); }

Alphabet<uint8_t> getDecimalAlphabet() { return Alphabet<uint8_t>("0123456789"); }

Alphabet<uint8_t> getHexadecimalAlphabet() { return Alphabet<uint8_t>("0123456789ABCDEF"); }

Alphabet<uint8_t> getProteinAlphabet() { return Alphabet<uint8_t>("ACDEFGHIKLMNPQRSTVWY"); }

Alphabet<uint8_t> getLowerCaseAlphabet() { return Alphabet<uint8_t>("abcdefghijklmnopqrstuvwxyz"); }

Alphabet<uint8_t> getUpperCaseAlphabet() { return Alphabet<uint8_t>("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); }
}  // namespace

TEST(KnownAlphabetsTest, GetBinaryAlphabetWorks) {
    auto alphabet(getBinaryAlphabet());

    EXPECT_EQ("01", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetDnaAlphabetWorks) {
    auto alphabet(getDnaAlphabet());

    EXPECT_EQ("ACTG", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetOctalAlphabetWorks) {
    auto alphabet(getOctalAlphabet());

    EXPECT_EQ("01234567", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetDecimalAlphabetWorks) {
    auto alphabet(getDecimalAlphabet());

    EXPECT_EQ("0123456789", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetHexadecimalAlphabetWorks) {
    auto alphabet(getHexadecimalAlphabet());

    EXPECT_EQ("0123456789ABCDEF", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetProteinAlphabetWorks) {
    auto alphabet(getProteinAlphabet());

    EXPECT_EQ("ACDEFGHIKLMNPQRSTVWY", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetLowerCaseAlphabetWorks) {
    auto alphabet(getLowerCaseAlphabet());

    EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetUpperCaseAlphabetWorks) {
    auto alphabet(getUpperCaseAlphabet());

    EXPECT_EQ("ABCDEFGHIJKLMNOPQRSTUVWXYZ", alphabet.getCharacters());
}

}  // namespace algorithm

}  // namespace alba
