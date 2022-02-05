#pragma once

namespace alba
{

class AlbaRandomizer
{
public:
    AlbaRandomizer();
    void resetRandomSeed();//remove windows here get local timer
    int getRandomValueInUniformDistribution(int const first, int const second) const;
};

}//namespace alba
