#include <CrnccIdMapping.hpp>

#include <Debug/AlbaDebug.hpp>
#include <Randomizer/AlbaRandomizer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SampleTest, PerformanceAccessTestWithRandomValues)
{
    constexpr unsigned int initialSize=2500;
    constexpr unsigned int accessIterations=1000000;

    AlbaRandomizer randomizer;
    vector<unsigned int> crnccIds;
    for(unsigned int currentSize=0; currentSize<initialSize; currentSize++)
    {
        TCRNCCommunicationContextId crnccId = randomizer.getRandomValueInUniformDistribution(1,65536);
        TNbccId nbccId = randomizer.getRandomValueInUniformDistribution(1,2500);
        crnccIds.emplace_back(crnccId);
        setCrnccIdMapping(crnccId, nbccId);
        ALBA_PRINT2(crnccId, nbccId);
    }


    for(unsigned int iteration=0; iteration<accessIterations; iteration++)
    {
        TCRNCCommunicationContextId crnccIdAccess = crnccIds[randomizer.getRandomValueInUniformDistribution(0, crnccIds.size()-1)];
        TNbccId nbccIdAccess = getNbccIdFromCrnccId(crnccIdAccess);
        ALBA_PRINT2(crnccIdAccess, nbccIdAccess);
    }
}

TEST(SampleTest, DISABLED_PerformanceAddTestWithRandomValues)
{
    constexpr unsigned int initialSize=1000000;

    AlbaRandomizer randomizer;
    vector<unsigned int> crnccIds;
    for(unsigned int currentSize=0; currentSize<initialSize; currentSize++)
    {
        TCRNCCommunicationContextId crnccId = randomizer.getRandomValueInUniformDistribution(1,65536);
        TNbccId nbccId = randomizer.getRandomValueInUniformDistribution(1,2500);
        crnccIds.emplace_back(crnccId);
        setCrnccIdMapping(crnccId, nbccId);
        ALBA_PRINT2(crnccId, nbccId);
    }
}

}
