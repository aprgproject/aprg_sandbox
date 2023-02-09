#include <Algorithm/DataCompression/LzwCompression.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;
namespace alba
{
namespace algorithm
{

namespace
{
using CompressionForTest = LzwCompression<unsigned int>;
}

TEST(LzwCompressionTest, CompressWorksUsingExample1)
{
    stringstream inputSs;
    inputSs << "ABRACADABRA!";
    stringstream outputSs;
    CompressionForTest compression;

    compression.compress(inputSs, outputSs);

    EXPECT_EQ("0410420520410430410441011030211000", getHexEquivalentOfCharacters(outputSs.str()));
}

TEST(LzwCompressionTest, ExpandWorksUsingExample1)
{
    stringstream inputSs;
    stringstream outputSs;
    AlbaStreamBitWriter initialWriter(inputSs);
    initialWriter.writeHexDigitData("0410420520410430410441011030211000");
    initialWriter.flush();
    CompressionForTest compression;

    compression.expand(inputSs, outputSs);

    EXPECT_EQ("ABRACADABRA!", outputSs.str());
}

TEST(LzwCompressionTest, CompressWorksUsingExample2)
{
    stringstream inputSs;
    inputSs << "it was the best of times it was the worst of times";
    stringstream outputSs;
    CompressionForTest compression;

    compression.compress(inputSs, outputSs);

    EXPECT_EQ("06907402007706107302007406806502006206507310206F06610706906D10D02010110310510710910306F07210E0201101121140731000", getHexEquivalentOfCharacters(outputSs.str()));
}

TEST(LzwCompressionTest, ExpandWorksUsingExample2)
{
    stringstream inputSs;
    stringstream outputSs;
    AlbaStreamBitWriter initialWriter(inputSs);
    initialWriter.writeHexDigitData("06907402007706107302007406806502006206507310206F06610706906D10D02010110310510710910306F07210E0201101121140731000");
    initialWriter.flush();
    CompressionForTest compression;

    compression.expand(inputSs, outputSs);

    EXPECT_EQ("it was the best of times it was the worst of times", outputSs.str());
}

}

}
