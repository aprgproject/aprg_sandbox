#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class FindTheMinimumCostToReachDestinationUsingATrain {
public:
    using Index = int;
    using Value = int;
    using Values = std::vector<Value>;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    static constexpr Value UNUSED_VALUE = std::numeric_limits<Value>::max();
    static constexpr Value MAX_VALUE = UNUSED_VALUE - 1;

    FindTheMinimumCostToReachDestinationUsingATrain(ValueMatrix const& prices);

    Value getMinimumCostUsingNaiveRecursion() const;
    Value getMinimumCostUsingMemoizationDP() const;
    Value getMinimumCostUsingIterativeDP() const;

private:
    Value getMinimumCostUsingNaiveRecursion(Index const endStation) const;
    Value getMinimumCostUsingMemoizationDP(Values& savedCosts, Index const endStation) const;
    void clearIfInvalid();
    ValueMatrix m_pricesAtEachStation;
};

}  // namespace alba

// Find the minimum cost to reach destination using a train

// There are N stations on route of a train.
// The train goes from station 0 to N-1.
// The ticket cost for all pair of stations (i, j) is given where j is greater than i.
// Find the minimum cost to reach the destination.

// Example
// Input:
// -> cost[N][N] = { {0, 15, 80, 90},
// ->               {INF, 0, 40, 50},
// ->               {INF, INF, 0, 70},
// ->               {INF, INF, INF, 0}
// ->              };
// -> There are 4 stations and cost[i][j] indicates cost to reach j
// -> from i. The entries where j < i are meaningless.

// Output:
// -> The minimum cost is 65
// -> The minimum cost can be obtained by first going to station 1 from 0.
// -> Then from station 1 to station 3.
