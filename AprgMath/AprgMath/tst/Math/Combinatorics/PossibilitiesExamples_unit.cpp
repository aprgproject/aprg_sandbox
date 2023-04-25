#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace math {

TEST(PossibilitiesExamplesTest, BasicExamplesWorks) {
    // Get number of possible DNA strings of length 7

    // Solution: 4*4*4*4*4*4*4 = 4^7 = possibilities of 4 choices with 7 times

    EXPECT_EQ(16384U, getNumberOfPossibilities(4U, 7U));
}

TEST(PossibilitiesExamplesTest, StringWithTwoRepeatingLetters) {
    // Get number of possible ABC strings of length 3 with two repeating letters

    // Solution:
    // Since 2 letters are repeating we can use balls and boxes approach and determine the number combinations.
    // Using combinations we can multiply the number of letters to it and sets it as the repeating part of string.
    // |o|o| |    Positions: {1, 2}
    // |o| |o|    Positions: {1, 3}
    // | |o|o|    Positions: {2, 3}
    // Repeating part = (combination of 3 taken 2) * number of choices = 3 * 3 = 9
    // The non repeating part is equal to possibilities of 3 choices with 1 time.
    // Non repeating part = possibilities of 2 choices with 1 time
    // Final answer = (Repeating part) * (Non repeating part) = 9 * 2 = 18

    // The final list of possibilities:
    // AAB, AAC, ABA, ACA, BAA, CAA
    // BBA, BBC, BAB, BCB, ABB, CBB
    // CCA, CCB, CAC, CBC, ACC, BCC

    EXPECT_EQ(18U, getNumberOfCombinations(3U, 1U) * 3U * getNumberOfPossibilities(2U, 1U));
}

TEST(PossibilitiesExamplesTest, StringWithTwoSetsOfTwoRepeatingLetters) {
    // Get number of possible ABCDE strings of length 5 with two distinct sets of two repeating letters

    // Solution:
    // Since 2 sets of 2 letters are repeating we can use balls and boxes approach twice and determine the number
    // combinations. The combinations for the 4 positions is combination of 5 taken 4 In those 4 positions, there are
    // two equal letter pairs. The position of the equal pairs is combination of 4 taken 2. In two sets of eqyak pairs,
    // the combinations of pair of letters is combination 5 taken 2 In the fifth position, the possibilities is 3
    // letters with 1 time

    // Final answer = (combination of 5 taken 4) * (combination of 4 taken 2) * (combination 5 taken 2) * (3 letters
    // with 1 time) Final answer = 5 * 6 * 10 * 3 = 900

    // Some sub examples:
    // -> For (combination of 5 taken 4 = 5):
    // ---> |o|o|o|o| |    Positions: {1, 2, 3, 4}
    // ---> |o|o|o| |o|    Positions: {1, 2, 3, 5}
    // ---> |o|o| |o|o|    Positions: {1, 2, 4, 5}
    // ---> |o| |o|o|o|    Positions: {1, 3, 4, 5}
    // ---> | |o|o|o|o|    Positions: {2, 3, 4, 5}
    // -> For (combination of 4 taken 2 = 6):
    // ---> |o|o| | |    Positions: {1, 2}
    // ---> |o| |o| |    Positions: {1, 3}
    // ---> |o| | |o|    Positions: {1, 4}
    // ---> | |o|o| |    Positions: {2, 3}
    // ---> | |o| |o|    Positions: {2, 4}
    // ---> | | |o|o|    Positions: {3, 4}
    // -> For (combination of 5 taken 2 = 10):
    // ---> AB, AC, AD, AE, BC, BD, BE, CD, CE, DE
    // -> For (3 letters with 1 time = 3):
    // ---> ****[ABCDE remove 2]

    // First example:
    // AABBC

    EXPECT_EQ(
        900U, getNumberOfCombinations(5U, 4U) * getNumberOfCombinations(4U, 2U) * getNumberOfCombinations(5U, 2U) *
                  getNumberOfPossibilities(3U, 1U));
}

TEST(PossibilitiesExamplesTest, StringWithThreeSetsOfTwoRepeatingLetters) {
    // Get number of possible ABCDEFGH strings of length 8 with three distinct sets of two repeating letters

    // Solution:
    // Since 3 sets of 2 letters are repeating we can use seats and people approach and determine the number
    // combinations. Use "123456" in 8 seats and get all permutations. This is 8 taken 6 = 20160. Get all permutations
    // of "12", "34" and "36" = That is (2 taken 2) * (2 taken 2) * (2 taken 2) = 8 In those permutations, there are
    // three equal letter pairs. This is 720 / 8 = 90. In three sets of equal pairs, the combinations of trio of letters
    // is combination 8 taken 3 In the fifth position, the possibilities is 5 letters with 1 times = 5 In the sixth
    // position, the possibilities is 4 letters with 1 times = 4

    // Final answer = (combination of 8 taken 6)
    // * (permutation of 6 taken 6) / ((permutation 2 taken 2)*(permutation 2 taken 2)*(permutation 2 taken 2))
    // * (5 letters with 2 time)
    // Final answer = 28 * 720/8 * 56 * 25 = 2822400

    // Some sub examples:
    // -> For (combination of 8 taken 6 = 20160):
    // ---> |1|2|3|4|5|6| | |    Positions: {1, 2, 3, 4, 5, 6}
    // ---> |1|2|3|4|5| |6| |    Positions: {1, 2, 3, 4, 5, 7}
    // ---> ...
    // -> For (permutation of 2 taken 1) * (permutation of 2 taken 1) * (permutation of 2 taken 1) = 2 * 2 * 2 = 8:
    // ---> {"12", "34", "56"}, {"12", "34", "65"}
    // ---> {"12", "43", "56"}, {"12", "43", "65"}
    // ---> {"21", "34", "56"}, {"21", "34", "65"}
    // ---> {"21", "43", "56"}, {"21", "43", "65"}
    // For (permutation of 8 taken 6) / ((permutation 2 taken 2)*(permutation 2 taken 2)*(permutation 2 taken 2))
    // --> These are equal("AABBCCXX"): "123456XX", "123465XX", "124356XX", "124365XX", "213456XX", "213465XX",
    // "214356XX", "214365XX"
    // --> These are equal("ABABCCXX"): "132456XX", "132465XX", "142356XX", "142365XX", "231456XX", "231465XX",
    // "241356XX", "241365XX"
    // ---> AABBCCXX, ABABCCXX, ABBACCXX, ABBCACXX, ABBCCAXX ...
    // -> For (combination of 8 taken 3 = 56):
    // ---> ABC, ABD, ABE, ABF, ABG, ABH, ACD, ...
    // -> For (5 letters with 1 times = 5) and (4 letters with 1 times = 1):
    // ---> ******[ABCDEFGH remove 3][ABCDEFGH remove 4]

    // First example:
    // AABBCCDE

    EXPECT_EQ(
        2822400U, getNumberOfPermutations(8U, 6U) / getNumberOfPermutations(2U, 1U) / getNumberOfPermutations(2U, 1U) /
                      getNumberOfPermutations(2U, 1U) * getNumberOfCombinations(8U, 3U) *
                      getNumberOfPossibilities(5U, 1U) * getNumberOfPossibilities(4U, 1U));
}

}  // namespace math

}  // namespace alba
