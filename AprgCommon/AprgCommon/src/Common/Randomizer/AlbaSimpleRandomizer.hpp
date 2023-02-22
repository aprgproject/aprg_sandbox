#pragma once

namespace alba
{

class AlbaSimpleRandomizer
{
public:
    AlbaSimpleRandomizer();
    void resetRandomSeed();
    int getRandomValueInUniformDistribution(int const first, int const second) const;
};

}//namespace alba
