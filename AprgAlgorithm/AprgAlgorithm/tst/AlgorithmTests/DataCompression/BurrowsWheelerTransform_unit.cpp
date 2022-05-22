#include <Algorithm/DataCompression/BurrowsWheelerTransform.hpp>

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
using TransformForTest = BurrowsWheelerTransform<Index, '_'>; // '_' is the end character
}

TEST(BurrowsWheelerTransformTest, EncodeWorksUsingExample1)
{
    stringstream inputSs;
    inputSs << "^BANANA|";
    stringstream outputSs;
    TransformForTest transform;

    transform.encode(inputSs, outputSs);

    EXPECT_EQ("BNN^AA_|A", outputSs.str());
}

TEST(BurrowsWheelerTransformTest, DecodeWorksUsingExample1)
{
    stringstream inputSs;
    inputSs << "BNN^AA_|A";
    stringstream outputSs;
    TransformForTest transform;

    transform.decode(inputSs, outputSs);

    EXPECT_EQ("^BANANA|", outputSs.str());
}

TEST(BurrowsWheelerTransformTest, EncodeWorksUsingExample2)
{
    stringstream inputSs;
    inputSs << "ABRACADABRA!";
    stringstream outputSs;
    TransformForTest transform;

    transform.encode(inputSs, outputSs);

    EXPECT_EQ("ARD_RCAAAABB!", outputSs.str());
}

TEST(BurrowsWheelerTransformTest, DecodeWorksUsingExample2)
{
    stringstream inputSs;
    inputSs << "ARD_RCAAAABB!";
    stringstream outputSs;
    TransformForTest transform;

    transform.decode(inputSs, outputSs);

    EXPECT_EQ("ABRACADABRA!", outputSs.str());
}

}

}
