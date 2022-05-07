#include <Algorithm/String/Alphabet/Alphabet.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace algorithm
{

namespace
{
Alphabet<unsigned char> getBinaryAlphabet()
{
    return Alphabet<unsigned char>("01");
}

Alphabet<unsigned char> getDnaAlphabet()
{
    return Alphabet<unsigned char>("ACTG");
}

Alphabet<unsigned char> getOctalAlphabet()
{
    return Alphabet<unsigned char>("01234567");
}

Alphabet<unsigned char> getDecimalAlphabet()
{
    return Alphabet<unsigned char>("0123456789");
}

Alphabet<unsigned char> getHexadecimalAlphabet()
{
    return Alphabet<unsigned char>("0123456789ABCDEF");
}

Alphabet<unsigned char> getProteinAlphabet()
{
    return Alphabet<unsigned char>("ACDEFGHIKLMNPQRSTVWY");
}

Alphabet<unsigned char> getLowerCaseAlphabet()
{
    return Alphabet<unsigned char>("abcdefghijklmnopqrstuvwxyz");
}

Alphabet<unsigned char> getUpperCaseAlphabet()
{
    return Alphabet<unsigned char>("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
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
