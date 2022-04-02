#include <Algorithm/String/Alphabet/Alphabet.hpp>
#include <Common/Bit/AlbaBitField.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
Alphabet<AlbaSingleBitField<unsigned char, 1U>> getBinaryAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 1U>>("01");
}

Alphabet<AlbaSingleBitField<unsigned char, 2U>> getDnaAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 2U>>("ACTG");
}

Alphabet<AlbaSingleBitField<unsigned char, 3U>> getOctalAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 3U>>("01234567");
}

Alphabet<AlbaSingleBitField<unsigned char, 4U>> getDecimalAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 4U>>("0123456789");
}

Alphabet<AlbaSingleBitField<unsigned char, 4U>> getHexadecimalAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 4U>>("0123456789ABCDEF");
}

Alphabet<AlbaSingleBitField<unsigned char, 5U>> getProteinAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 5U>>("ACDEFGHIKLMNPQRSTVWY");
}

Alphabet<AlbaSingleBitField<unsigned char, 5U>> getLowerCaseAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 5U>>("abcdefghijklmnopqrstuvwxyz");
}

Alphabet<AlbaSingleBitField<unsigned char, 5U>> getUpperCaseAlphabet()
{
    return Alphabet<AlbaSingleBitField<unsigned char, 5U>>("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}
}

TEST(KnownAlphabetsTest, GetBinaryAlphabetWorks)
{
    auto alphabet(getBinaryAlphabet());

    EXPECT_EQ("01", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetDnaAlphabetWorks)
{
    auto alphabet(getDnaAlphabet());

    EXPECT_EQ("ACTG", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetOctalAlphabetWorks)
{
    auto alphabet(getOctalAlphabet());

    EXPECT_EQ("01234567", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetDecimalAlphabetWorks)
{
    auto alphabet(getDecimalAlphabet());

    EXPECT_EQ("0123456789", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetHexadecimalAlphabetWorks)
{
    auto alphabet(getHexadecimalAlphabet());

    EXPECT_EQ("0123456789ABCDEF", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetProteinAlphabetWorks)
{
    auto alphabet(getProteinAlphabet());

    EXPECT_EQ("ACDEFGHIKLMNPQRSTVWY", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetLowerCaseAlphabetWorks)
{
    auto alphabet(getLowerCaseAlphabet());

    EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", alphabet.getCharacters());
}

TEST(KnownAlphabetsTest, GetUpperCaseAlphabetWorks)
{
    auto alphabet(getUpperCaseAlphabet());

    EXPECT_EQ("ABCDEFGHIJKLMNOPQRSTUVWXYZ", alphabet.getCharacters());
}

}

}
