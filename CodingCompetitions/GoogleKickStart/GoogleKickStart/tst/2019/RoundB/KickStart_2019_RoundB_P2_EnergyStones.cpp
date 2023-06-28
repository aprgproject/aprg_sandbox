// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundB_P2_EnergyStones.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <climits>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundB_P2_EnergyStones {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

struct Stone {
    int timeToConsume;
    int energy;
    int rateOfLoss;
    /*friend ALBA_DEBUG_CLASS_OUTPUT_OPERATOR_DEFINITION(
            Stone const& stone,
            "{" << stone.timeToConsume << " " << stone.energy << " " << stone.rateOfLoss << "}");*/
};
using Stones = vector<Stone>;

int numberOfStones;
vector<int> savedEnergies;  // Dynamic Programming
Stones stones;
int maxTime;

/*
// My solution but its wrong
int getIndex(int const left, int const right, int const time)
{
    return left*numberOfStones*maxTime + right*maxTime + time;
}

int getMaxEnergy(
        int const left,
        int const right,
        int const elapsedTime)
{
    int & savedEnergy(savedEnergies[getIndex(left, right, elapsedTime)]);
    if(savedEnergy == INT_MAX)
    {
        int maxTotalEnergy=0;
        for(int i=left; i<=right; i++)
        {
            Stone const& stone(stones[i]);
            int energyOfStone=0;
            if(stone.energy > (stone.rateOfLoss*elapsedTime))
            {
                energyOfStone = stone.energy - (stone.rateOfLoss*elapsedTime);
            }
            int maxNextEnergy=0;
            if(left<i)
            {
                maxNextEnergy = getMaxEnergy(left, i-1, elapsedTime+stone.timeToConsume);
            }
            if(i<right)
            {
                maxNextEnergy = max(maxNextEnergy, getMaxEnergy(i+1, right, elapsedTime+stone.timeToConsume));
            }
            maxTotalEnergy = max(maxTotalEnergy, energyOfStone+maxNextEnergy);
        }
        savedEnergy = maxTotalEnergy;
    }
    return savedEnergy;
}

void runTestCase(int const testCaseNumber)
{
    my_cin >> numberOfStones;

    int totalConsumptionTime=0;
    stones.clear();
    stones.reserve(numberOfStones);
    for(int y=0; y<numberOfStones; ++y)
    {
        Stone stone;
        my_cin >> stone.timeToConsume >> stone.energy >> stone.rateOfLoss;
        totalConsumptionTime += stone.timeToConsume;
        stones.emplace_back(stone);
    }
    maxTime=totalConsumptionTime;

    savedEnergies.assign(numberOfStones*numberOfStones*maxTime, INT_MAX);

    int maxEnergy = getMaxEnergy(0, numberOfStones-1, 0);

    my_cout << "Case #" << testCaseNumber << ": " << maxEnergy << '\n';
}*/

// Solution recommended by kickstart
int getIndex(int const index, int const time) { return index * maxTime + time; }

int getMaxEnergy(int const index, int const elapsedTime) {
    if (index < (int)stones.size()) {
        int& savedEnergy(savedEnergies[getIndex(index, elapsedTime)]);
        if (savedEnergy == INT_MAX) {
            Stone stone(stones[index]);
            int remainingEnergyOfStone = max(0, stone.energy - (stone.rateOfLoss * elapsedTime));
            int energyIfEaten = getMaxEnergy(index + 1, elapsedTime + stone.timeToConsume) + remainingEnergyOfStone;
            int energyIfSkipped = getMaxEnergy(index + 1, elapsedTime);
            savedEnergy = max(energyIfEaten, energyIfSkipped);
        }
        return savedEnergy;
    } else {
        return 0;
    }
}

void runTestCase(int const testCaseNumber) {
    my_cin >> numberOfStones;

    int totalConsumptionTime = 0;
    stones.clear();
    stones.reserve(numberOfStones);
    for (int y = 0; y < numberOfStones; ++y) {
        Stone stone;
        my_cin >> stone.timeToConsume >> stone.energy >> stone.rateOfLoss;
        totalConsumptionTime += stone.timeToConsume;
        stones.emplace_back(stone);
    }
    maxTime = totalConsumptionTime;

    // Observe that SiLj is the total loss of energy if i is used first.
    // Likewise, SjLi is the loss if j is used first.
    // Thus, if SiLj < SjLi then taking i first leads to a smaller overall loss of energy.
    // It may not be obvious that we should always take i before j even if it leads to a smaller loss of energy.

    sort(stones.begin(), stones.end(), [](Stone const& stone1, Stone const& stone2) {
        return stone2.timeToConsume * stone1.rateOfLoss > stone1.timeToConsume * stone2.rateOfLoss;
    });

    savedEnergies.assign(numberOfStones * maxTime, INT_MAX);

    int maxEnergy = getMaxEnergy(0, 0);

    my_cout << "Case #" << testCaseNumber << ": " << maxEnergy << '\n';
}

void runAllTestCases() {
    int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
        runTestCase(testCaseNumber);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}  // namespace KickStart_2019_RoundB_P2_EnergyStones
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
