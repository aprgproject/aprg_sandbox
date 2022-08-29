#include <Common/Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

TEST(PermutationsExamplesTest, BasicExamplesWorks)
{
    //Find the number of permutations of a two digit number with values 1, 2, 3, and 4.
    // Solution: Permutations of 4 taken 2
    EXPECT_EQ(12U, getNumberOfPermutations(4U, 2U));

    //If four people enter a bus in which there are ten vacant seats, how many ways are there for the four to be seated?
    // Solution: 10 vacancy and put 4 distinct people -> Permutations of 10 taken 4
    EXPECT_EQ(5040U, getNumberOfPermutations(10U, 4U));

    //In how many ways may five books to be arranged on a shelf?
    // Solution: Permutations of 5 taken 5
    EXPECT_EQ(120U, getNumberOfPermutations(5U, 5U));

    //Find the number of permutations of the eight letters of the word "gargling".
    // Solution: Split the problem in to two parts ("1ar2lin3" and "ggg")
    // Permutations for "1ar2lin3": Permutations of 8 taken 8
    // Permutations to cancel out "ggg": Permutations of 3 taken 3
    // All combinations: [Permutations for "1ar2lin3"] / [Permutations to cancel out "ggg"]
    EXPECT_EQ(6720U, getFactorial(8U)/getFactorial(3U));

    //Find the number of permutations of the 11 letters of the word "mississippi".
    // Solution: Split the problem in to multiple parts ("m123456789A", "iiii", "ssss", "pp")
    // Permutations for "m123456789A": Permutations of 11 taken 11
    // Permutations to cancel out "iiii": Permutations of 4 taken 4
    // Permutations to cancel out "ssss": Permutations of 4 taken 4
    // Permutations to cancel out "pp": Permutations of 2 taken 2
    // All combinations: [Permutations for "m123456789A"] / ([Permutations to cancel out "iiii"] * [Permutations to cancel out "ssss"] * [Permutations to cancel out "pp"])
    EXPECT_EQ(34650U, getFactorial(11U)/(getFactorial(4U)*getFactorial(4U)*getFactorial(2U)));

    //How many ways can four boys and three girls be seated in a row containing seven seats if the boys and girls must alternate?
    // Solution: Split the problem in to two parts (boys and girls)
    // Permutations for boys: Permutations of 4 taken 4
    // Permutations for girls: Permutations of 3 taken 3
    // All combinations: [Permutations for boys] * [Permutations for girls]
    EXPECT_EQ(144U, getFactorial(4U)*getFactorial(3U));

    //In how many ways can 8 people be seated around a circular table?
    // Solution: Split the problem in to two parts (linear table and loop around)
    // Permutations for linear table: Permutations of 8 taken 8
    // Permutations to cancel out for loop around": Permutations of 8 taken 1
    // All combinations: [Permutations for linear table] / [Permutations to cancel out for loop around]
    EXPECT_EQ(5040U, getFactorial(8U)/8U);
}

}

}
