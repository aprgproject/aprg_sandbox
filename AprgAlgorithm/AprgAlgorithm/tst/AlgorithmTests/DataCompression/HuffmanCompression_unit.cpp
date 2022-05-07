#include <Algorithm/DataCompression/HuffmanCompression.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using CompressionForTest = HuffmanCompression<unsigned int>;
}

TEST(HuffmanCompressionTest, CompressWorksUsingExample1){
    stringstream inputSs;
    inputSs << "ABRACADABRA!";
    stringstream outputSs;    CompressionForTest compression;

    compression.compress(inputSs, outputSs);

    EXPECT_EQ("504A22434350AA400000018DD68DD4", getHexEquivalentOfCharacters(outputSs.str()));
}

TEST(HuffmanCompressionTest, ExpandWorksUsingExample1)
{
    stringstream inputSs;
    stringstream outputSs;
    AlbaStreamBitWriter initialWriter(inputSs);
    initialWriter.writeHexDigitData("504A22434350AA400000018DD68DD4");
    initialWriter.flush();
    CompressionForTest compression;

    compression.expand(inputSs, outputSs);

    EXPECT_EQ("ABRACADABRA!", outputSs.str());
}

TEST(HuffmanCompressionTest, CompressWorksUsingExample2)
{
    stringstream inputSs;
    inputSs << "it was the best of times it was the worst of times";
    stringstream outputSs;
    CompressionForTest compression;

    compression.compress(inputSs, outputSs);

    EXPECT_EQ("0B6DDECB202E6B7AD1660B15CAC369BA000000196F4731F62E0676AEFD031DE8E63EC51AC676AEFD0300", getHexEquivalentOfCharacters(outputSs.str()));
}

TEST(HuffmanCompressionTest, ExpandWorksUsingExample2)
{
    stringstream inputSs;
    stringstream outputSs;
    AlbaStreamBitWriter initialWriter(inputSs);
    initialWriter.writeHexDigitData("0B6DDECB202E6B7AD1660B15CAC369BA000000196F4731F62E0676AEFD031DE8E63EC51AC676AEFD0300");
    initialWriter.flush();
    CompressionForTest compression;

    compression.expand(inputSs, outputSs);

    EXPECT_EQ("it was the best of times it was the worst of times", outputSs.str());
}

}

}
