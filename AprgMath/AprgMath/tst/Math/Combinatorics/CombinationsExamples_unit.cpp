#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

TEST(CombinationsExamplesTest, BasicExamplesWorks)
{
    // How many different sums of money can be made by taking one coin from a penny, a nickel, a dime, and a quarter?
    // Solution: Combinations of 4 taken 1
    EXPECT_EQ(4U, getNumberOfCombinations(4U, 1U));

    // How many different sums of money can be made by taking two coins from a penny, a nickel, a dime, and a quarter?
    // Solution: Combinations of 4 taken 2
    EXPECT_EQ(6U, getNumberOfCombinations(4U, 2U));

    // How many different sums of money can be made from a penny, a nickel, a dime, and a quarter?
    // Solution: Sum of "Combinations of 4 taken 1", "Combinations of 4 taken 2", "Combinations of 4 taken 3", "Combinations of 4 taken 4"
    EXPECT_EQ(15U, getNumberOfCombinations(4U, 1U) + getNumberOfCombinations(4U, 2U) + getNumberOfCombinations(4U, 3U) + getNumberOfCombinations(4U, 4U));

    // In a class of 15 boys and 10 girls, in how many ways may a committee made up of 3 boys and 2 girls be selected?
    // Solution: Split the problem in to two parts (boys and girls)
    // Combinations for boys: Combinations of 15 taken 3
    // Combinations for girls: Combinations of 10 taken 2
    // All combinations: [Combinations for boys] * [Combinations for girls]
    EXPECT_EQ(20475U, getNumberOfCombinations(15U, 3U) * getNumberOfCombinations(10U, 2U));

    // On a certain examination, the student must answer 8 out of the 12 question, including 5 of the first 6.
    // How many ways may he write the examination?
    // Solution: Split the problem in to two parts (first 6 questions and last 6 questions)
    // Combinations for first 6 questions: Combinations of 6 taken 5
    // Combinations for last 6 questions: Combinations of 6 taken 3
    // All combinations: [Combinations for first 6 questions] * [Combinations for last 6 questions]
    EXPECT_EQ(120U, getNumberOfCombinations(6U, 5U) * getNumberOfCombinations(6U, 3U));
}

TEST(CombinationsExamplesTest, BoxesAndBallsExampleScenario1Works)
{
    // Scenario 1: Each box can contain at most one ball.

    // For example, when n=5(boxes) and k=2(balls), there are 10 solutions:
    // |o|o| | | |    Positions: {1, 2}
    // |o| |o| | |    Positions: {1, 3}
    // |o| | |o| |    Positions: {1, 4}
    // |o| | | |o|    Positions: {1, 5}
    // | |o|o| | |    Positions: {2, 3}
    // | |o| |o| |    Positions: {2, 4}
    // | |o| | |o|    Positions: {2, 5}
    // | | |o|o| |    Positions: {3, 4}
    // | | |o| |o|    Positions: {3, 5}
    // | | | |o|o|    Positions: {4, 5}

    // Solution: Based from the positions, the solution is combinations of 5 taken 2
    EXPECT_EQ(10U, getNumberOfCombinations(5U, 2U));
}

TEST(CombinationsExamplesTest, BoxesAndBallsExampleScenario2Works)
{
    // Scenario 2: A box can contain multiple balls.

    // For example, when n=5(boxes) and k=2(balls), there are 15 solutions:
    // |oo|  |  |  |  |    Positions: {1, 1}    Representation: o o > > > >
    // |o |o |  |  |  |    Positions: {1, 2}    Representation: o > o > > >
    // |o |  |o |  |  |    Positions: {1, 3}    Representation: o > > o > >
    // |o |  |  |o |  |    Positions: {1, 4}    Representation: o > > > o >
    // |o |  |  |  |o |    Positions: {1, 5}    Representation: o > > > > o
    // |  |oo|  |  |  |    Positions: {2, 2}    Representation: > o o > > >
    // |  |o |o |  |  |    Positions: {2, 3}    Representation: > o > o > >
    // |  |o |  |o |  |    Positions: {2, 4}    Representation: > o > > o >
    // |  |o |  |  |o |    Positions: {2, 5}    Representation: > o > > > o
    // |  |  |oo|  |  |    Positions: {3, 3}    Representation: > > o o > >
    // |  |  |o |o |  |    Positions: {3, 4}    Representation: > > o > o >
    // |  |  |o |  |o |    Positions: {3, 5}    Representation: > > o > > o
    // |  |  |  |oo|  |    Positions: {4, 4}    Representation: > > > o o >
    // |  |  |  |o |o |    Positions: {4, 5}    Representation: > > > o > o
    // |  |  |  |  |oo|    Positions: {5, 5}    Representation: > > > > o o

    // Observation: Based from the positions, there are combinations with repeat values.

    // Solution:
    // The process of placing the balls in the boxes can be represented as a string that consists of symbols 'o' and '>'.
    // Initially, assume that we are standing at the leftmost box.
    // The symbol 'o' means that we place a ball in the current box, and the symbol '>' means that we move to the next box to the right.
    // Using this notation, each solution is a string that contains k times the symbol 'o' and n-1 times the symbol '>'.
    // This reduces to the problem in scenario 1 when there are k+n-1 boxes and k balls.
    // Thus, the number of solutions is (k+n-1, k)

    // The formula for the solution on this case is combinations of k+n-1 taken k
    // So its combinations of 2+5-1=6 taken 2
    EXPECT_EQ(15U, getNumberOfCombinations(6U, 2U));
}

TEST(CombinationsExamplesTest, BoxesAndBallsExampleScenario3Works_Example1)
{
    // Scenario 3: Each box may contain at most one ball, and in addition, no two adjacent boxes may both contain a ball.

    // For example, when n=5(boxes) and k=2(balls), there are 6 solutions:
    // |o| |o| | |    Positions: {1, 3}    Representation: |o|_|o| | |    |o|o| | |
    // |o| | |o| |    Positions: {1, 4}    Representation: |o|_| |o| |    |o| |o| |
    // |o| | | |o|    Positions: {1, 5}    Representation: |o|_| | |o|    |o| | |o|
    // | |o| |o| |    Positions: {2, 4}    Representation: | |o|_|o| |    | |o|o| |
    // | |o| | |o|    Positions: {2, 5}    Representation: | |o|_| |o|    | |o| |o|
    // | | |o| |o|    Positions: {3, 5}    Representation: | | |o|_|o|    | | |o|o|

    // Solution:
    // In this scenario, we can assume that k balls are initially placed in boxes and there is an empty box between each two adjacent boxes.
    // The remaining task is to choose the positions for the remaining empty boxes.

    // To simplify this problem, adjacent empty boxes can be removed on each combination.
    // When empty boxes are removed, this can be reduced to the problem on scenario 1.
    // Thus we need to figure out the new number of boxes and new number of balls

    // Question is how many empty boxes can be removed?
    // If there are 2 balls, empty boxes to remove is 1.
    // If there are 3 balls, empty boxes to remove is 2.
    // If there are 4 balls, empty boxes to remove is 3.
    // So the empty boxes to remove is k-1.
    // Hence, the new number of boxes = old number of boxes - empty boxes to remove = n-(k-1) = n-k+1

    // This can be simplified further because removing boxes might result to number of spaces to be less that number of balls.
    // So we can switch the spaces with the balls and vice versa
    // Hence, the new number of balls = number of spaces = new number of boxes - old number of balls = n-k+1 - k = n-2k+1

    // There are two formulas for the solution on this case:
    // Using number of balls: The formula is combinations of n-k+1 taken k
    // Using number of spaces: The formula is combinations of n-k+1 taken n-2k+1
    // Note that "isNumberOfCombinationsEqualToItsCounterpart" is true: (n, k) = (n, n-k)

    // The result using formula using balls is combinations of 5-2+1=4 taken 2
    EXPECT_EQ(6U, getNumberOfCombinations(4U, 2U));

    // The result using formula using spaces is combinations of 5-2+1=4 taken 5-2*2+1=2
    EXPECT_EQ(6U, getNumberOfCombinations(4U, 2U));
}

TEST(CombinationsExamplesTest, BoxesAndBallsExampleScenario3Works_Example2)
{
    // Scenario 3: Each box may contain at most one ball, and in addition, no two adjacent boxes may both contain a ball.

    // For example, when n=6(boxes) and k=3(balls), there are 6 solutions:
    // |o| |o| |o| |    Positions: {1, 3, 5}    Representation: |o|_|o|_|o| |    |o|o|o| |
    // |o| |o| | |o|    Positions: {1, 3, 6}    Representation: |o|_|o|_| |o|    |o|o| |o|
    // |o| | |o| |o|    Positions: {1, 4, 6}    Representation: |o|_| |o|_|o|    |o| |o|o|
    // | |o| |o| |o|    Positions: {2, 4, 6}    Representation: | |o|_|o|_|o|    | |o|o|o|

    // Solution:
    // As described above, by removing adjacent empty boxes this reduces to the problem in scenario 1.
    // Thus there are [n-k+1 boxes and k balls] or [n-k+1 boxes and n-2k+1 balls]
    // Note that "isNumberOfCombinationsEqualToItsCounterpart" is true: (n, k) = (n, n-k)

    // The result using formula using balls is combinations of 6-3+1=4 taken 3
    EXPECT_EQ(4U, getNumberOfCombinations(4U, 3U));

    // The result using formula using spaces is combinations of 6-3+1=4 taken 6-2*3+1=1
    EXPECT_EQ(4U, getNumberOfCombinations(4U, 1U));
}

TEST(CombinationsExamplesTest, BoxesAndBallsExampleScenario3Works_Example3)
{
    // Scenario 3: Each box may contain at most one ball, and in addition, no two adjacent boxes may both contain a ball.

    // This variation gets of count for all balls(so boxes=balls).

    // For example, n=k=3, when n=3(boxes) and k=1..3(balls), there are total of 5 solutions:
    // If k==0:
    // | | | |    Positions: {    }    Representation: | | | |    | | | |
    // If k==1:
    // |o| | |    Positions: {1   }    Representation: |o| | |    |o| | |
    // | |o| |    Positions: {2   }    Representation: | |o| |    | |o| |
    // | | |o|    Positions: {3   }    Representation: | | |o|    | | |o|
    // If k==2:
    // |o| |o|    Positions: {1, 3}    Representation: |o|_|o|    |o|o|
    // If k==3:
    // No solutions.

    // Solution:
    // There are Combinations(n-k+1 boxes, k balls)
    // If k==0: the count is Combinations(4, 0) = 1
    // If k==1: the count is Combinations(3, 1) = 3
    // If k==2: the count is Combinations(2, 2) = 1
    // If k==3: the count is Combinations(1, 3) = 0 (not valid)
    // Total=5
    EXPECT_EQ(5U, getNumberOfCombinations(4U, 0U) + getNumberOfCombinations(3U, 1U) + getNumberOfCombinations(2U, 2U));

    // The patterns are the same with the fibonacci numbers.
    // EXPECT_EQ(5U, getNthFibonacciNumber(n+2));
}

TEST(CombinationsExamplesTest, CatalanNumbersFormulaWorks)
{
    // There are a total of (2n, n) ways to construct a (not necessarily valid)
    // parenthesis expression that contains n left parentheses and n right parentheses.

    // This formula is correct because its reduces to boxes and balls formula.
    // For example when n=3, we can assign balls to left parentheses and boxes to right parentheses, so its 6 taken 3:    // ALL:
    // ((())) -> |o|o|o| | | |
    // (()()) -> |o|o| |o| | |
    // (())() -> |o|o| | |o| |
    // (()))( -> |o|o| | | |o|
    // ()(()) -> |o| |o|o| | |
    // ()()() -> |o| |o| |o| |
    // ()())( -> |o| |o| | |o|
    // ())(() -> |o| | |o|o| |
    // ())()( -> |o| | |o| |o|
    // ()))(( -> |o| | | |o|o|
    // )((()) -> | |o|o|o| | |
    // )(()() -> | |o|o| |o| |
    // )(())( -> | |o|o| | |o|
    // )()(() -> | |o| |o|o| |
    // )()()( -> | |o| |o| |o|
    // )())(( -> | |o| | |o|o|
    // ))((() -> | | |o|o|o| |
    // ))(()( -> | | |o|o| |o|
    // ))()(( -> | | |o| |o|o|
    // )))((( -> | | | |o|o|o|
    EXPECT_EQ(20U, getNumberOfCombinations(6U, 3U));


    // This proof uses André's reflection method, which was originally used in connection with Bertrand's ballot theorem.
    // The reflection principle has been widely attributed to Désiré André,
    // but his method did not actually use reflections and the reflection method is a variation due to Aebly and Mirimanoff.

    // We count the number of paths which start and end on the diagonal of a n×n grid.
    // All such paths have n-right steps (lets assign it to left parentheses) and n-up steps (lets assign it to right parentheses).
    // Since we can choose which of the 2*n steps are up or right, there are in total (2*n, n) monotonic paths of this type.
    // A bad path crosses the main diagonal and touches the next higher (fatal) diagonal ('F' in the illustration).

    // Illustration of nxn grid :
    // | | | |F|x|
    // | | |F|x| |
    // | |F|x| | |
    // |F|x| | | |
    // |x| | | | |

    // The part of the path after the fatal touch is flipped about the fatal diagonal.
    // This SWAPS all the right steps to up steps and vice versa.
    // In the section of the path that is not reflected, there is one more up step than right steps,
    // so therefore the remaining section of the bad path has one more right step than up steps.
    // When this portion of the path is reflected, it will have one more up step than right steps.

    // Since there are still 2n steps, there are now be n+1 up steps (right parentheses) and n−1 right steps (left parentheses).
    // So, instead of reaching (n, n), all bad paths after reflection end at (n−1, n+1).
    // Because every monotonic path in the (n−1) × (n+1) grid meets the fatal diagonal,
    // and because the reflection process is reversible,
    // the reflection is therefore a bijection between bad paths in the original grid and monotonic paths in the new grid.

    // After reflection:
    // The number of right parentheses=n+1 and the number of left parentheses=n-1.
    // The number of bad paths is therefore:
    // (n+1+n-1, n+1) = (2*n, n-1) = (2*n, n+1)

    // This formula is correct because its reduces to boxes and balls formula.
    // For example when n=3, we can assign balls to left parentheses and boxes to right parentheses, so its 6 taken 2 (or 6 taken 4):
    // INVALID:
    // (()))( -> non reflected part:[(())] + fatal part:[)] + reflected part:[)] -> |o|o| | | | |
    // ()())( -> non reflected part:[()()] + fatal part:[)] + reflected part:[)] -> |o| |o| | | |
    // ()))(( -> non reflected part:[()] + fatal part:[)] + reflected part:[())] -> |o| | |o| | |
    // ())()( -> non reflected part:[()] + fatal part:[)] + reflected part:[)()] -> |o| | | |o| |
    // ())(() -> non reflected part:[()] + fatal part:[)] + reflected part:[))(] -> |o| | | | |o|
    // )))((( -> non reflected part:[] + fatal part:[)] + reflected part:[(()))] -> | |o|o| | | |
    // ))()(( -> non reflected part:[] + fatal part:[)] + reflected part:[()())] -> | |o| |o| | |
    // ))(()( -> non reflected part:[] + fatal part:[)] + reflected part:[())()] -> | |o| | |o| |
    // ))((() -> non reflected part:[] + fatal part:[)] + reflected part:[()))(] -> | |o| | | |o|
    // )())(( -> non reflected part:[] + fatal part:[)] + reflected part:[)(())] -> | | |o|o| | |
    // )()()( -> non reflected part:[] + fatal part:[)] + reflected part:[)()()] -> | | |o| |o| |
    // )()(() -> non reflected part:[] + fatal part:[)] + reflected part:[)())(] -> | | |o| | |o|
    // )(())( -> non reflected part:[] + fatal part:[)] + reflected part:[))(()] -> | | | |o|o| |
    // )(()() -> non reflected part:[] + fatal part:[)] + reflected part:[))()(] -> | | | |o| |o|
    // )((()) -> non reflected part:[] + fatal part:[)] + reflected part:[)))((] -> | | | | |o|o|
    EXPECT_EQ(15U, getNumberOfCombinations(6U, 2U));


    // Thus, the number of valid parenthesis expressions can be calculated using the formula
    // (2n, n) - (2n, n+1) = (2n, n) - (2n, n) * n/(n+1) = (2n, n) * (n+1-n)/(n+1) = (2n, n)/(n+1)
    // VALID:
    // ((())) -> |o|o|o| | | |
    // (()()) -> |o|o| |o| | |
    // (())() -> |o|o| | |o| |
    // ()(()) -> |o| |o|o| | |
    // ()()() -> |o| |o| |o| |
    EXPECT_EQ(5U, getNumberOfCombinations(6U, 3U)/(3+1));
}

}

}
