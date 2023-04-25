#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class CountNumberOfWaysToReachAGivenScoreInAGame {
public:
    using Index = unsigned int;
    using Value = unsigned int;
    using Values = std::vector<Value>;

    CountNumberOfWaysToReachAGivenScoreInAGame(Value const targetScore);

    Value getMinimumCostUsingIterativeDP() const;
    Value getMinimumCostUsingCoinProblemSolutions() const;

private:
    Value m_targetScore;
};

}  // namespace alba

// Count number of ways to reach a given score in a game

// Consider a game where a player can score 3 or 5 or 10 points in a move. Given a total score n, find number of ways to
// reach the given score.

// Examples:
// Input: n = 20
// -> Output: 4
// -> There are following 4 ways to reach 20
// -> (10, 10)
// -> (5, 5, 10)
// -> (5, 5, 5, 5)
// -> (3, 3, 3, 3, 3, 5)
// Input: n = 13
// ->Output: 2
// ->There are following 2 ways to reach 13
// ->(3, 5, 5)
// ->(3, 10)
