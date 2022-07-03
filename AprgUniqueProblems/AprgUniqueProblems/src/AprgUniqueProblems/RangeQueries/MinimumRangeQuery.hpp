#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class MinimumRangeQuery
{
public:
    // Minimum queries
    // Minimum queries are more difficult to process than sum queries.
    // Still, there is a quite simple O(nlogn) time preprocessing method after which we can answer any minimum query in O(1) time1.
    //Note that since minimum and maximum queries can be processed similarly, we can focus on minimum queries.

    using Index = unsigned int;
    using Value = unsigned int;
    using Values = std::vector<Value>;
    using ValueMatrix = matrix::AlbaMatrix<Value>;

    MinimumRangeQuery(Values const& valuesToCheck);

    Value getMinimumFromStartToEnd(Index const start, Index const end) const;
private:
    Index getCielOfLogOf2(Index const index) const;
    Index getPowOf2(Index const index) const;
    void initialize(Values const& valuesToCheck);
    ValueMatrix m_minimumValues;
};
}