#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

TEST(PermutationsExamplesTest, BasicExamplesWorks)
{
    // Find the number of permutations of a two digit number with values 1, 2, 3, and 4.
    // Solution: Permutations of 4 taken 2
    EXPECT_EQ(12U, getNumberOfPermutations(4U, 2U));

    // If four people enter a bus in which there are ten vacant seats, how many ways are there for the four to be seated?
    // Solution: We can convert this problem to position of the four people.
    // [Position of first person][Position of second person][Position of third person][Position of fourth person]
    // This reduces to permutations of 10 taken 4.
    // This is the same SeatsWithPeople problem (dicussion is on the next tests)
    EXPECT_EQ(5040U, getNumberOfPermutations(10U, 4U));

    // In how many ways may five books to be arranged on a shelf?
    // Solution: Permutations of 5 taken 5
    EXPECT_EQ(120U, getNumberOfPermutations(5U, 5U));

    // Find the number of permutations of the eight letters of the word "gargling".
    // Solution: Split the problem in to two parts ("1ar2lin3" and "ggg")
    // Permutations for "1ar2lin3": Permutations of 8 taken 8
    // Permutations to cancel out "ggg": Permutations of 3 taken 3
    // All permutations: [Permutations for "1ar2lin3"] / [Permutations to cancel out "ggg"]
    EXPECT_EQ(6720U, getFactorial(8U)/getFactorial(3U));

    // Find the number of permutations of the string "AAAABBBCCD".
    // Solution: Split the problem in to four parts ("1234567890" and "AAAA" and "BBB" and "CC")
    // Permutations for "1234567890": Permutations of 10 taken 10
    // Permutations to cancel out "AAAA": Permutations of 4 taken 4
    // Permutations to cancel out "BBB": Permutations of 3 taken 3
    // Permutations to cancel out "CC": Permutations of 2 taken 2
    // All permutations: [Permutations for "1234567890"] / [Permutations to cancel out "AAAA"] / [Permutations to cancel out "BBB"] / [Permutations to cancel out "CC"]
    EXPECT_EQ(12600U, getFactorial(10U)/getFactorial(4U)/getFactorial(3U)/getFactorial(2U));

    // Find the number of permutations of the 11 letters of the word "mississippi".
    // Solution: Split the problem in to multiple parts ("m123456789A", "iiii", "ssss", "pp")
    // Permutations for "m123456789A": Permutations of 11 taken 11
    // Permutations to cancel out "iiii": Permutations of 4 taken 4
    // Permutations to cancel out "ssss": Permutations of 4 taken 4
    // Permutations to cancel out "pp": Permutations of 2 taken 2
    // All permutations: [Permutations for "m123456789A"] / ([Permutations to cancel out "iiii"] * [Permutations to cancel out "ssss"] * [Permutations to cancel out "pp"])
    EXPECT_EQ(34650U, getFactorial(11U)/(getFactorial(4U)*getFactorial(4U)*getFactorial(2U)));

    // How many ways can four boys and three girls be seated in a row containing seven seats if the boys and girls must alternate?
    // Solution: Split the problem in to two parts (boys and girls)
    // Permutations for boys: Permutations of 4 taken 4
    // Permutations for girls: Permutations of 3 taken 3
    // All permutations: [Permutations for boys] * [Permutations for girls]
    EXPECT_EQ(144U, getFactorial(4U)*getFactorial(3U));

    // In how many ways can 4 people be seated around a circular table?
    // Solution: Split the problem in to two parts (linear table and loop around)
    // Permutations for linear table: Permutations of 4 taken 4
    // Permutations to cancel out for loop around": Permutations of 4 taken 1
    // -> This is true because these loop around permutations are equal in circular table: {1,2,3,4} {2,3,4,1} {3,4,1,2} {4,1,2,3}
    // All permutations: [Permutations for linear table] / [Permutations to cancel out for loop around]
    EXPECT_EQ(6U, getFactorial(4U)/4U);


    // What is the number of permutations of the characters in LILAC so that no character appears in its original position,
    // if the two L’s are indistinguishable?
    // There are 3 choices for the first slot, and then 2 for the third slot.
    // That leaves one letter out of I,A,C unchosen and there are 2 slots that one might occupy.
    // After that, the L′s must go in the 2 unfilled slots.
    // Hence the answer is, 3×2×1×2 = 12
    EXPECT_EQ(12U, 3U*2U*1U*2U);
}

TEST(PermutationsExamplesTest, SeatsWithPeopleExampleScenario1Works)
{
    // Scenario 1: Each seat can contain at most one person.

    // For example, when n=4(seats) and k=2(people), there are 12 solutions:
    // |A|B| | |    Positions{A,B}: {1, 2}
    // |A| |B| |    Positions{A,B}: {1, 3}
    // |A| | |B|    Positions{A,B}: {1, 4}
    // |B|A| | |    Positions{A,B}: {2, 1}
    // | |A|B| |    Positions{A,B}: {2, 3}
    // | |A| |B|    Positions{A,B}: {2, 4}
    // |B| |A| |    Positions{A,B}: {3, 1}
    // | |B|A| |    Positions{A,B}: {3, 2}
    // | | |A|B|    Positions{A,B}: {3, 4}
    // |B| | |A|    Positions{A,B}: {4, 1}
    // | |B| |A|    Positions{A,B}: {4, 2}
    // | | |B|A|    Positions{A,B}: {4, 3}

    // Solution: Based from the positions, the solution is permutations of 5 taken 2
    EXPECT_EQ(12U, getNumberOfPermutations(4U, 2U));
}

TEST(PermutationsExamplesTest, SeatsWithPeopleExampleScenario2Works)
{
    // Scenario 2: Each seat can contain multiple people

    // For example, when n=3(seats) and k=2(people), there are 10 solutions:
    // |AB|  |  |    Positions{A,B}: {1, 1}    Representation: A B > >
    // |A |B |  |    Positions{A,B}: {1, 2}    Representation: A > B >
    // |A |  |B |    Positions{A,B}: {1, 3}    Representation: A > > B
    // |BA|  |  |    Positions{A,B}: {1, 1}    Representation: B A > >
    // |B |A |  |    Positions{A,B}: {2, 1}    Representation: B > A >
    // |B |  |A |    Positions{A,B}: {3, 1}    Representation: B > > A
    // |  |AB|  |    Positions{A,B}: {2, 2}    Representation: > A B >
    // |  |A | B|    Positions{A,B}: {2, 3}    Representation: > A > B
    // |  |BA|  |    Positions{A,B}: {2, 2}    Representation: > B A >
    // |  |B |A |    Positions{A,B}: {3, 2}    Representation: > B > A
    // |  |  |AB|    Positions{A,B}: {3, 3}    Representation: > > A B
    // |  |  |BA|    Positions{A,B}: {3, 3}    Representation: > > B A

    // Observation: Based from the positions, there are permutations with repeat values.

    // Solution:
    // The process of putting the people in to seats can be represented as a string that consists of symbols of the person and '>'.
    // Initially, assume that we are standing at the leftmost box.
    // The symbol of the person means that we put a person in to the seat, and the symbol '>' means that we move to the next seat to the right.
    // Using this notation, each solution is a string that contains k times the symbol of the people and n-1 times the symbol '>'.
    // This reduces to the problem in scenario 1 when there are k+n-1 seats and k people.
    // Thus, the number of solutions is (k+n-1, k)

    // The formula for the solution on this case is permutations of k+n-1 taken k
    // So its permutations of 2+3-1=4 taken 2
    EXPECT_EQ(12U, getNumberOfPermutations(4U, 2U));
}

TEST(PermutationsExamplesTest, SeatsWithPeopleExampleScenario3Works_Example1)
{
    // Scenario 3: Each seat can contain at most one person, and in addition, no two adjacent seats may both contain a person.

    // For example, when n=5(seats) and k=2(people), there are 12 solutions:
    // |A| |B| | |    Positions{A,B}: {1, 3}    Representation: |A|_|B| | |    |A|B| | |
    // |A| | |B| |    Positions{A,B}: {1, 4}    Representation: |A|_| |B| |    |A| |B| |
    // |A| | | |B|    Positions{A,B}: {1, 5}    Representation: |A|_| | |B|    |A| | |B|
    // |B| |A| | |    Positions{A,B}: {3, 1}    Representation: |B|_|A| | |    |B|A| | |
    // |B| | |A| |    Positions{A,B}: {4, 1}    Representation: |B|_| |A| |    |B| |A| |
    // |B| | | |A|    Positions{A,B}: {5, 1}    Representation: |B|_| | |A|    |B| | |A|
    // | |A| |B| |    Positions{A,B}: {2, 4}    Representation: | |A|_|B| |    | |A|B| |
    // | |A| | |B|    Positions{A,B}: {2, 5}    Representation: | |A|_| |B|    | |A| |B|
    // | |B| |A| |    Positions{A,B}: {4, 2}    Representation: | |B|_|A| |    | |B|A| |
    // | |B| | |A|    Positions{A,B}: {5, 2}    Representation: | |B|_| |A|    | |B| |A|
    // | | |A| |B|    Positions{A,B}: {3, 5}    Representation: | | |A|_|B|    | | |A|B|
    // | | |B| |A|    Positions{A,B}: {5, 3}    Representation: | | |B|_|A|    | | |B|A|

    // Solution:
    // In this scenario, we can assume that k people are initially placed in seats and there is an empty box between each two adjacent seats.
    // The remaining task is to choose the positions for the remaining empty seats.

    // To simplify this problem, adjacent empty seats can be removed on each permutation.
    // When empty seats are removed, this can be reduced to the problem on scenario 1.
    // Thus we need to figure out the new number of seats and new number of people

    // Question is how many empty seats can be removed?
    // If there are 2 people, empty seats to remove is 1.
    // If there are 3 people, empty seats to remove is 2.
    // If there are 4 people, empty seats to remove is 3.
    // So the empty seats to remove is k-1.
    // Hence, the new number of seats = old number of seats - empty seats to remove = n-(k-1) = n-k+1

    // The formula for the solution on this case is permutations of n-k+1 taken k
    // So its permutations of 5-2+1=4 taken 2
    EXPECT_EQ(12U, getNumberOfPermutations(4U, 2U));
}

TEST(PermutationsExamplesTest, SeatsWithPeopleExampleScenario3Works_Example2)
{
    // Scenario 3: Each seat can contain at most one person, and in addition, no two adjacent seats may both contain a person.

    // For example, when n=6(seats) and k=3(people), there are 24 solutions:
    // |A| |B| |C| |    Positions{A,B,C}: {1, 3, 5}    Representation: |A|_|B|_|C| |    |A|B|C| |
    // |A| |B| | |C|    Positions{A,B,C}: {1, 3, 6}    Representation: |A|_|B|_| |C|    |A|B| |C|
    // |A| |C| |B| |    positions{A,B,C}: {1, 5, 3}    Representation: |A|_|C|_|B| |    |A|C|B| |
    // |A| |C| | |B|    positions{A,B,C}: {1, 6, 3}    Representation: |A|_|C|_| |B|    |A|C| |B|
    // |A| | |B| |C|    Positions{A,B,C}: {1, 4, 6}    Representation: |A|_| |B|_|C|    |A| |B|C|
    // |A| | |C| |B|    positions{A,B,C}: {1, 6, 4}    Representation: |A|_| |C|_|B|    |A| |C|B|
    // |B| |A| |C| |    positions{A,B,C}: {3, 1, 5}    Representation: |B|_|A|_|C| |    |B|A|C| |
    // |B| |A| | |C|    positions{A,B,C}: {3, 1, 6}    Representation: |B|_|A|_| |C|    |B|A| |C|
    // |B| |C| |A| |    positions{A,B,C}: {5, 1, 3}    Representation: |B|_|C|_|A| |    |B|C|A| |
    // |B| |C| | |A|    positions{A,B,C}: {6, 1, 3}    Representation: |B|_|C|_| |A|    |B|C| |A|
    // |B| | |A| |C|    positions{A,B,C}: {4, 1, 6}    Representation: |B|_| |A|_|C|    |B| |A|C|
    // |B| | |C| |A|    positions{A,B,C}: {6, 1, 4}    Representation: |B|_| |C|_|A|    |B| |C|A|
    // |C| |A| |B| |    positions{A,B,C}: {3, 5, 1}    Representation: |C|_|A|_|B| |    |C|A|B| |
    // |C| |A| | |B|    positions{A,B,C}: {3, 6, 1}    Representation: |C|_|A|_| |B|    |C|A| |B|
    // |C| |B| |A| |    positions{A,B,C}: {5, 3, 1}    Representation: |C|_|B|_|A| |    |C|B|A| |
    // |C| |B| | |A|    positions{A,B,C}: {6, 3, 1}    Representation: |C|_|B|_| |A|    |C|B| |A|
    // |C| | |A| |B|    positions{A,B,C}: {4, 6, 1}    Representation: |C|_| |A|_|B|    |C| |A|B|
    // |C| | |B| |A|    positions{A,B,C}: {6, 4, 1}    Representation: |C|_| |B|_|A|    |C| |B|A|
    // | |A| |B| |C|    Positions{A,B,C}: {2, 4, 6}    Representation: | |A|_|B|_|C|    | |A|B|C|
    // | |A| |C| |B|    positions{A,B,C}: {2, 6, 4}    Representation: | |A|_|C|_|B|    | |A|C|B|
    // | |B| |A| |C|    positions{A,B,C}: {4, 6, 2}    Representation: | |B|_|A|_|C|    | |B|A|C|
    // | |B| |C| |A|    positions{A,B,C}: {6, 4, 2}    Representation: | |B|_|C|_|A|    | |B|C|A|
    // | |C| |A| |B|    positions{A,B,C}: {4, 6, 2}    Representation: | |C|_|A|_|B|    | |C|A|B|
    // | |C| |B| |A|    positions{A,B,C}: {6, 4, 2}    Representation: | |C|_|B|_|A|    | |C|B|A|

    // Solution:
    // As described above, by removing adjacent empty seats this reduces to the problem in scenario 1.
    // Thus there are n-k+1 seats and k people

    // The formula for the solution on this case is permutations of n-k+1 taken k
    // So its permutations of 6-3+1=4 taken 3
    EXPECT_EQ(24U, getNumberOfPermutations(4U, 3U));
}

}

}
