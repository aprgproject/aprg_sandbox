#pragma once

namespace alba{

class AlbaRandomizer
{
public:
    AlbaRandomizer();
    void resetRandomSeed();
    int getRandomValueInUniformDistribution(int const min, int const max) const;
};

}//namespace alba
