#pragma once

namespace alba
{

class AlbaRandomizer
{
public:
    AlbaRandomizer();
    void resetRandomSeed();//remove windows here get local timer
    int getRandomValueInUniformDistribution(int const min, int const max) const;
};

}//namespace alba
