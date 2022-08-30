#pragma once

namespace alba
{

namespace mathHelper
{

enum class RootType
{
    RealRootsOnly,
    RealAndImaginaryRoots,
};

struct FractionDetails
{
    int sign;
    unsigned int numerator;
    unsigned int denominator;
};

}//namespace mathHelper

}//namespace alba
