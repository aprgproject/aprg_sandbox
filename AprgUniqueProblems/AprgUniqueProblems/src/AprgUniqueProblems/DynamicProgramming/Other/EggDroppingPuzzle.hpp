#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba {

class EggDroppingPuzzle {
public:
    using Count = unsigned int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count MAX_COUNT = std::numeric_limits<Count>::max();

    EggDroppingPuzzle(Count const numberOfEggs, Count const numberOfFloors);

    Count getMinimumNumberOfTrialsUsingNaiveRecursion() const;
    Count getMinimumNumberOfTrialsUsingMemoizationDP() const;
    Count getMinimumNumberOfTrialsUsingIterativeDP() const;

private:
    Count getMinimumNumberOfTrialsUsingNaiveRecursion(Count const remainingEggs, Count const floorIndexPlusOne) const;
    Count getMinimumNumberOfTrialsUsingMemoizationDP(
        CountMatrix& valueMatrix, Count const remainingEggs, Count const floorIndexPlusOne) const;
    Count const m_numberOfEggs;
    Count const m_numberOfFloors;
};

}  // namespace alba

// The following is a description of the instance of this famous puzzle involving n=2 eggs and a building with k=36
// floors. Suppose that we wish to know which stories in a 36-story building are safe to drop eggs from, and which will
// cause the eggs to break on landing. We make a few assumptions:
// -> An egg that survives a fall can be used again.
// -> A broken egg must be discarded.
// -> The effect of a fall is the same for all eggs.
// -> If an egg breaks when dropped, then it would break if dropped from a higher floor.
// -> If an egg survives a fall then it would survive a shorter fall.
// -> It is not ruled out that the first-floor windows break eggs, nor is it ruled out that the 36th-floor do not cause
// an egg to break.

// If only one egg is available and we wish to be sure of obtaining the right result,
// the experiment can be carried out in only one way.
// Drop the egg from the first-floor window; if it survives, drop it from the second-floor window.
// Continue upward until it breaks. In the worst case, this method may require 36 droppings.
// Suppose 2 eggs are available.
// What is the least number of egg-droppings that is guaranteed to work in all cases?

// The problem is not actually to find the critical floor,
// but merely to decide floors from which eggs should be dropped so that the total number of trials are minimized.

// In this post, we will discuss a solution to a general problem with ‘n’ eggs and ‘k’ floors.
// The solution is to try dropping an egg from every floor(from 1 to k)
// and recursively calculate the minimum number of droppings needed in the worst case.
// The floor which gives the minimum value in the worst case is going to be part of the solution.

// In the following solutions, we return the minimum number of trials in the worst case;
// these solutions can be easily modified to print floor numbers of every trial also.

// Meaning of a worst-case scenario:
// -> Worst case scenario gives the user the surety of the threshold floor.
// -> For example- If we have ‘1’ egg and ‘k’ floors,
// -> we will start dropping the egg from the first floor till the egg breaks suppose on the ‘kth’ floor so the number
// of tries to give us surety is ‘k’. 1) Optimal Substructure: When we drop an egg from a floor x, there can be two
// cases (1) The egg breaks (2) The egg doesn’t break.
// -> 1) If the egg breaks after dropping from ‘xth’ floor, then we only need to check for floors lower than ‘x’ with
// remaining eggs as some floor should exist lower than ‘x’ in which egg would not break; so the problem reduces to x-1
// floors and n-1 eggs.
// -> 2) If the egg doesn’t break after dropping from the ‘xth’ floor, then we only need to check for floors higher than
// ‘x’; so the problem reduces to ‘k-x’ floors and n eggs.

// Since we need to minimize the number of trials in worst case, we take the maximum of two cases.
// We consider the max of above two cases for every floor and choose the floor which yields minimum number of trials.

// k ==> Number of floors
// n ==> Number of Eggs
// eggDrop(n, k) ==> Minimum number of trials needed to find the critical floor in worst case.
// eggDrop(n, k) = 1 + min{max(eggDrop(n – 1, x – 1), eggDrop(n, k – x)), where x is in {1, 2, …, k}}
// Concept of worst case:
// -> For example :
// -> Let there be ‘2’ eggs and ‘2’ floors then-:
// -> If we try throwing from ‘1st’ floor:
// -> Number of tries in worst case= 1+max(0, 1)
// -> 0 => If the egg breaks from first floor then it is threshold floor (best case possibility).
// -> 1 => If the egg does not break from first floor we will now have ‘2’ eggs and 1 floor to test which will give
// answer as
// -> ‘1’.(worst case possibility)
// -> We take the worst case possibility in account, so 1+max(0, 1)=2
// -> If we try throwing from ‘2nd’ floor:
// -> Number of tries in worst case= 1+max(1, 0)
// -> 1 => If the egg breaks from second floor then we will have 1 egg and 1 floor to find threshold floor.(Worst Case)
// -> 0 => If egg does not break from second floor then it is threshold floor.(Best Case)
// -> We take worst case possibility for surety, so 1+max(1, 0)=2.
// -> The final answer is min(1st, 2nd, 3rd….., kth floor)
// -> So answer here is ‘2’.
