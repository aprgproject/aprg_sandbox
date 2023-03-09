#include <Common/Randomizer/AlbaSimpleRandomizer.hpp>
#include <CrnccIdMapping.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SampleTest, DISABLED_PerformanceAccessTestWithRandomValues)
{
    constexpr unsigned int initialSize=2500;
    constexpr unsigned int accessIterations=1000000;

    AlbaSimpleRandomizer randomizer;
    vector<unsigned int> crnccIds;
    for(unsigned int currentSize=0; currentSize<initialSize; currentSize++)
    {
        TCRNCCommunicationContextId crnccId = randomizer.getRandomIntegerInUniformDistribution(1,65536);
        TNbccId nbccId = randomizer.getRandomIntegerInUniformDistribution(1,2500);
        crnccIds.emplace_back(crnccId);
        setCrnccIdMapping(crnccId, nbccId);
    }


    for(unsigned int iteration=0; iteration<accessIterations; iteration++)
    {
        TCRNCCommunicationContextId crnccIdAccess = crnccIds[randomizer.getRandomIntegerInUniformDistribution(0, crnccIds.size()-1)];
        TNbccId nbccIdAccess = getNbccIdFromCrnccId(crnccIdAccess);
    }
}

TEST(SampleTest, DISABLED_PerformanceAddTestWithRandomValues)
{
    constexpr unsigned int initialSize=1000000;

    AlbaSimpleRandomizer randomizer;
    vector<unsigned int> crnccIds;
    for(unsigned int currentSize=0; currentSize<initialSize; currentSize++)
    {
        TCRNCCommunicationContextId crnccId = randomizer.getRandomIntegerInUniformDistribution(1,65536);
        TNbccId nbccId = randomizer.getRandomIntegerInUniformDistribution(1,2500);
        crnccIds.emplace_back(crnccId);
        setCrnccIdMapping(crnccId, nbccId);
    }
}

}
