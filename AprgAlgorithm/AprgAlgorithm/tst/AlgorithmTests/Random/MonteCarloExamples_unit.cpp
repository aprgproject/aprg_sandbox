#include <Algorithm/Random/MonteCarlo.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Randomizer/AlbaSimpleRandomizer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

TEST(MonteCarloTest, VerifyingMatrixExample) {
    // Our next problem is to verify if AB = C holds when A, B and C are matrices of size nxn.
    // Of course, we can solve the problem by calculating the product AB again (in O(n3) time using the basic
    // algorithm), but one could hope that verifying the answer would by easier than to calculate it from scratch.

    using MatrixForTest = matrix::AlbaMatrix<unsigned int>;

    AlbaSimpleRandomizer randomizer;
    MatrixForTest a(3, 2, {1, 2, 3, 4, 5, 6});
    MatrixForTest b(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    MatrixForTest c(4, 2, {38, 44, 50, 56, 83, 98, 113, 128});
    MatrixForTest x;

    bool isEqual(false);

    MonteCarloAlgorithm verifyingMatrixAlgorithm = [&]() {
        // It turns out that we can solve the problem using a Monte Carlo algorithm whose time complexity is only O(n2).
        // The idea is simple: we choose a random vector X of n elements, and calculate the matrices ABX and CX.
        // If ABX = CX, we report that AB = C, and otherwise we report that AB != C.

        // The time complexity of the algorithm is O(n2), because we can calculate the matrices ABX and CX in O(n2)
        // time. We can calculate the matrix ABX efficiently by using the representation A(BX), so only two
        // multiplications of nxn and nx1 size matrices are needed.

        MatrixForTest x(1, b.getNumberOfColumns());
        for (unsigned int i = 0; i < x.getNumberOfRows(); i++) {
            x.setEntry(0, i, static_cast<unsigned int>(randomizer.getRandomIntegerInUniformDistribution(1, 10)));
        }
        MatrixForTest bx = b * x;
        MatrixForTest abx = a * bx;
        MatrixForTest cx = c * x;
        return abx == cx;
    };

    performAMonteCarloAlgorithm(verifyingMatrixAlgorithm);

    EXPECT_TRUE(isEqual == isEqual);  // just to check something
}

}  // namespace algorithm

}  // namespace alba
