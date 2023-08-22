#include <UniqueProblems/BranchAndBound/EightPuzzlePossibleProblem.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(EightPuzzlePossibleProblemTest, PrintStepsToSolveWorksOnExample1) {
    EightPuzzlePossibleProblem::NumberMatrix start(3, 3, {{1, 2, 3, 5, 6, 0, 7, 8, 4}});
    EightPuzzlePossibleProblem::NumberMatrix target(3, 3, {{1, 2, 3, 5, 8, 6, 0, 7, 4}});
    EightPuzzlePossibleProblem queryForTest(start, target);

    queryForTest.printStepsToSolve();
}

}  // namespace alba
