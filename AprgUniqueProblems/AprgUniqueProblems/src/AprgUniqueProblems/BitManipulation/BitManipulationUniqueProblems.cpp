#include "BitManipulationUniqueProblems.hpp"

using namespace std;

namespace alba
{

namespace BitManipulation
{

unsigned int changeKthBitToOne(unsigned int const value, unsigned int const k)
{
    return value | (1 << k);
}

unsigned int changeKthBitToZero(unsigned int const value, unsigned int const k)
{
    return value & ~(1 << k);
}

unsigned int invertKthBit(unsigned int const value, unsigned int const k)
{
    return value ^ (1 << k);
}

unsigned int changeLastOneToZero(unsigned int const value)
{
    return value & (value-1);
}

unsigned int changeAllOnesToZeroExceptForLast(unsigned int const value)
{
    return value & (-value);
}

unsigned int invertAllBitsAfterTheLastOne(unsigned int const value)
{
    return value | (value-1);
}

bool isPowerOfTwo(unsigned int const value)
{
    return (value & (value-1))==0;
}

}

}
