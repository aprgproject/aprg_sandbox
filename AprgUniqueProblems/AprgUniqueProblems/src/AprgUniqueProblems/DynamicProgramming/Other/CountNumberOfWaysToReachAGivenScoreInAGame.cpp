#include "CountNumberOfWaysToReachAGivenScoreInAGame.hpp"

#include <AprgUniqueProblems/DynamicProgramming/Other/CoinProblem.hpp>

using namespace std;

namespace alba
{

CountNumberOfWaysToReachAGivenScoreInAGame::CountNumberOfWaysToReachAGivenScoreInAGame(
        Value const targetScore)
    : m_targetScore(targetScore)
{}

CountNumberOfWaysToReachAGivenScoreInAGame::Value CountNumberOfWaysToReachAGivenScoreInAGame::getMinimumCostUsingIterativeDP() const
{
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(1)

    constexpr array<Value, 3> moveScores{3, 5, 10};

    Values countsPerScore(m_targetScore+1, 0);
    countsPerScore[0]=1;
    for(Value const& moveScore : moveScores)
    {
        for(Value partialScore=moveScore; partialScore<=m_targetScore; partialScore++)
        {
            countsPerScore[partialScore] += countsPerScore.at(partialScore-moveScore);
        }
    }
    return countsPerScore.back();
}

CountNumberOfWaysToReachAGivenScoreInAGame::Value CountNumberOfWaysToReachAGivenScoreInAGame::getMinimumCostUsingCoinProblemSolutions() const
{
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(1)

    CoinProblem::Coins moveScores{3, 5, 10};

    CoinProblem coinProblem(moveScores);
    return coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(m_targetScore);
}

}
