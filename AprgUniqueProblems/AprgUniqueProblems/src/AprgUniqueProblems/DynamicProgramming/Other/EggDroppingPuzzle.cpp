#include "EggDroppingPuzzle.hpp"

using namespace std;

namespace alba
{

EggDroppingPuzzle::EggDroppingPuzzle(
        Count const numberOfEggs,
        Count const numberOfFloors)
    : m_numberOfEggs(numberOfEggs)
    , m_numberOfFloors(numberOfFloors)
{}

EggDroppingPuzzle::Count EggDroppingPuzzle::getMinimumNumberOfTrialsUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are n calls per iteration:  O(m^n)
    // Auxiliary Space: Constant

    return getMinimumNumberOfTrialsUsingNaiveRecursion(m_numberOfEggs, m_numberOfFloors);
}

EggDroppingPuzzle::Count EggDroppingPuzzle::getMinimumNumberOfTrialsUsingMemoizationDP() const
{
    // Time Complexity: O(n*k^2) (should be same as Iterative DP)
    // Auxiliary Space: O(n*k)

    CountMatrix countMatrix(m_numberOfEggs+1, m_numberOfFloors+1, static_cast<Count>(MAX_COUNT));
    return getMinimumNumberOfTrialsUsingMemoizationDP(countMatrix, m_numberOfEggs, m_numberOfFloors);
}

EggDroppingPuzzle::Count EggDroppingPuzzle::getMinimumNumberOfTrialsUsingIterativeDP() const
{
    // Time Complexity: O(n*k^2).
    // -> Where ‘n’ is the number of eggs and ‘k’ is the number of floors, as we use a nested for loop ‘k^2’ times for each egg
    // Auxiliary Space: O(n*k).
    // -> As a 2-D array of size ‘n*k’ is used for storing elements.

    CountMatrix countMatrix(m_numberOfEggs+1, m_numberOfFloors+1, 0U);
    for(Count remainingEggs=1; remainingEggs<=m_numberOfEggs; remainingEggs++)
    {
        countMatrix.setEntry(remainingEggs, 1, 1);
    }
    for(Count floorIndexPlusOne=1; floorIndexPlusOne<=m_numberOfFloors; floorIndexPlusOne++)
    {
        countMatrix.setEntry(1, floorIndexPlusOne, floorIndexPlusOne);
    }
    for(Count remainingEggs=2; remainingEggs<=m_numberOfEggs; remainingEggs++)
    {
        for(Count floorIndexPlusOne=2; floorIndexPlusOne<=m_numberOfFloors; floorIndexPlusOne++)
        {
            Count minimumCount(MAX_COUNT);
            for(unsigned int currentFloor=1; currentFloor<=floorIndexPlusOne; currentFloor++)
            {
                Count countForFloor = max(countMatrix.getEntry(remainingEggs-1, currentFloor-1),
                                          countMatrix.getEntry(remainingEggs, floorIndexPlusOne-currentFloor));
                minimumCount = min(minimumCount, countForFloor);
            }
            countMatrix.setEntry(remainingEggs, floorIndexPlusOne, minimumCount+1);
        }
    }
    return countMatrix.getEntry(m_numberOfEggs, m_numberOfFloors);
}

EggDroppingPuzzle::Count EggDroppingPuzzle::getMinimumNumberOfTrialsUsingNaiveRecursion(
        Count const remainingEggs,
        Count const floorIndexPlusOne) const
{
    if(floorIndexPlusOne<=1 || remainingEggs == 1)
    {
        // If there are no floors, then no trials needed.
        // OR if there is one floor, one trial needed.

        // We need k trials for one egg and k floors.
        return floorIndexPlusOne;
    }
    else
    {
        // Consider all droppings from 1st floor to kth floor and return the minimum of these values plus 1.
        Count minimumCount(MAX_COUNT);
        for(unsigned int currentFloor=1; currentFloor<=floorIndexPlusOne; currentFloor++)
        {
            Count countForFloor = max(getMinimumNumberOfTrialsUsingNaiveRecursion(remainingEggs-1, currentFloor-1),
                                      getMinimumNumberOfTrialsUsingNaiveRecursion(remainingEggs, floorIndexPlusOne-currentFloor));
            minimumCount = min(minimumCount, countForFloor);
        }
        return minimumCount+1;
    }
}

EggDroppingPuzzle::Count EggDroppingPuzzle::getMinimumNumberOfTrialsUsingMemoizationDP(
        CountMatrix & countMatrix,
        Count const remainingEggs,
        Count const floorIndexPlusOne) const
{
    Count result = countMatrix.getEntry(remainingEggs, floorIndexPlusOne);
    if(MAX_COUNT == result)
    {
        if(floorIndexPlusOne<=1 || remainingEggs == 1)
        {
            result = floorIndexPlusOne;
        }
        else
        {
            // result is already MAX_COUNT
            for(unsigned int currentFloor=1; currentFloor<=floorIndexPlusOne; currentFloor++)
            {
                Count countForFloor = max(getMinimumNumberOfTrialsUsingMemoizationDP(countMatrix, remainingEggs-1, currentFloor-1),
                                          getMinimumNumberOfTrialsUsingMemoizationDP(countMatrix, remainingEggs, floorIndexPlusOne-currentFloor));
                result = min(result, countForFloor);
            }
            result++;
        }
        countMatrix.setEntry(remainingEggs, floorIndexPlusOne, result);
    }
    return result;

}

}
