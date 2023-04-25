#pragma once

#include <vector>

namespace alba {

class BuildingBridges {
public:
    using Index = unsigned int;
    using Value = unsigned int;
    using Bridge = std::pair<unsigned int, unsigned int>;
    using Bridges = std::vector<Bridge>;
    using IndexToIndex = std::vector<Index>;
    using IndexToValue = std::vector<Value>;

    BuildingBridges(Bridges const& sequence);

    Index getNumberOfPossibleBridges() const;
    Bridges getPossibleBridges() const;

private:
    Bridges m_bridges;
};

}  // namespace alba

// VARIANT OF: Longest Increasing Subsequence

// Building Bridges

// Consider a 2-D map with a horizontal river passing through its center.
// There are n cities on the southern bank with x-coordinates a(1) … a(n) and n cities on the northern bank with
// x-coordinates b(1) … b(n). You want to connect as many north-south pairs of cities as possible with bridges such that
// no two bridges cross. When connecting cities, you can only connect city a(i) on the northern bank to city b(i) on the
// southern bank. Maximum number of bridges that can be built to connect north-south pairs with the aforementioned
// constraints.

// The values in the upper bank can be considered as the northern x-coordinates of the cities
// and the values in the bottom bank can be considered as the corresponding southern x-coordinates
// of the cities to which the northern x-coordinate city can be connected.

// -> Examples:

// -> Input : 6 4 2 1
// ->         2 3 6 5
// ---> Output : Maximum number of bridges = 2
// ---> Explanation: Let the north-south x-coordinates be written in increasing order.
// 1  2  3  4  5  6
// #  #
//   #  #            For the north-south pairs
//     #  #          (2, 6) and (1, 5)
//       #  #        the bridges can be built.
//         #  #      We can consider other pairs also,
//          #  #     but then only one bridge can be built
//           #  #    because more than one bridge built will
//            #  #   then cross each other.
//             #  #
// 1  2  3  4  5  6

// -> Input : 8 1 4 3 5 2 6 7
// --->       1 2 3 4 5 6 7 8
// --->Output : Maximum number of bridges = 5
// Approach: It is a variation of LIS problem. The following are the steps to solve the problem.
// 1) Sort the north-south pairs on the basis of increasing order of south x-coordinates.
// 2) If two south x-coordinates are same, then sort on the basis of increasing order of north x-coordinates.
// 3) Now find the Longest Increasing Subsequence of the north x-coordinates.
// 4) One thing to note that in the increasing subsequence a value can be greater as well as can be equal to its
// previous value. We can also sort on the basis of north x-coordinates and find the LIS on the south x-coordinates.
