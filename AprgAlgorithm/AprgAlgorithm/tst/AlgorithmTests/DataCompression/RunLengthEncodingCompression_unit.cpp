#include <Algorithm/DataCompression/RunLengthEncodingCompression.hpp>
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
using Index = unsigned int;
using CompressionForTest = RunLengthEncodingCompression<256>;
}

TEST(RunLengthEncodingCompressionTest, CompressWorksUsingExample1){
    bitset<40> initialValue(0B0000000000000001111111000000011111111111);
    stringstream inputSs;
    stringstream outputSs;    AlbaStreamBitWriter initialWriter(inputSs);
    initialWriter.writeBitsetData(initialValue, 39, 0);
    initialWriter.flush();
    CompressionForTest compression;

    compression.compress(inputSs, outputSs);

    EXPECT_EQ("0F07070B", getHexEquivalentOfCharacters(outputSs.str()));
}

TEST(RunLengthEncodingCompressionTest, ExpandWorksUsingExample1)
{
    stringstream inputSs;
    stringstream outputSs;
    AlbaStreamBitWriter initialWriter(inputSs);
    initialWriter.writeHexDigitData("0F07070B");
    initialWriter.flush();
    CompressionForTest compression;
    compression.expand(inputSs, outputSs);

    EXPECT_EQ("0001FC07FF", getHexEquivalentOfCharacters(outputSs.str()));}

}

}
