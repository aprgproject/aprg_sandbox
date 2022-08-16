#include <Common/Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

TEST(AprgMathModuloTest, ModuloCanBeDistributedInAddition)
{
    // (a + b) mod m = (a mod m + b mod m) mod m

    unsigned int a=5, b=10, m=4;
    unsigned int left = (a+b)%m;
    unsigned int right = (a%m + b%m)%m;
    EXPECT_EQ(left, right);
}

TEST(AprgMathModuloTest, ModuloCanBeDistributedInSubtraction)
{
    // (a - b) mod m = (a mod m - b mod m) mod m

    unsigned int a=5, b=10, m=4;
    unsigned int left = (a-b)%m;
    unsigned int right = (a%m - b%m)%m;
    EXPECT_EQ(left, right);
}

TEST(AprgMathModuloTest, ModuloCanBeDistributedInMultiplication)
{
    // (a * b) mod m = ((a mod m) * (b mod m)) mod m

    unsigned int a=5, b=10, m=4;
    unsigned int left = (a*b)%m;
    unsigned int right = ((a%m) * (b%m))%m;
    EXPECT_EQ(left, right);
}

TEST(AprgMathModuloTest, ModuloCanBeDoneInEveryIterationOfFactorial)
{
    // (a * b) mod m = ((a mod m) * (b mod m)) mod m

    unsigned int n=5, m=4;
    unsigned int factorialWithModulo=1;
    for(unsigned int i=2; i<=n; i++)
    {
        factorialWithModulo = (factorialWithModulo*i)%m;
    }
    EXPECT_EQ(getFactorial(n)%m, factorialWithModulo);
}

}
