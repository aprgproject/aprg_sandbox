#include <UniqueProblems/DynamicProgramming/Other/ElevatorWeightProblem.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace {
using People = ElevatorWeightProblem::People;
using ListOfPeople = ElevatorWeightProblem::ListOfPeople;
}  // namespace

TEST(ElevatorWeightProblemTest, GetNumberOfOptimalRidesWorksOnExample1) {
    ElevatorWeightProblem queryForTest(10, {2, 3, 3, 5, 6});

    EXPECT_EQ(2, queryForTest.getNumberOfOptimalRides());
}

}  // namespace alba
