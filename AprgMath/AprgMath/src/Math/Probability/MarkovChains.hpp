#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <array>
#include <map>

namespace alba {
template <int MAX_STATE_VALUE>
class MarkovChains {
public:    // A Markov chain is a random process that consists of states and transitions between them.
    // For each state, we know the probabilities for moving to other states.
    // A Markov chain can be represented as a graph whose nodes are states and edges are transitions.

    using ProbabilityMatrix = matrix::AlbaMatrix<AlbaNumber>;
    using ProbabilityDistribution = std::array<AlbaNumber, MAX_STATE_VALUE>;
    using DistributionToDistributionMap = std::map<ProbabilityDistribution, ProbabilityDistribution>;

    MarkovChains() : m_probabilityMatrix(MAX_STATE_VALUE, MAX_STATE_VALUE) {}

    AlbaNumber getProbability(int const currentState, int const nextState) const {
        return m_probabilityMatrix.getEntry(currentState, nextState);
    }

    void setProbability(int const currentState, int const nextState, AlbaNumber const& probability) {
        m_probabilityMatrix.setEntry(currentState, nextState, probability);
    }

    ProbabilityDistribution getNextProbabilityDistribution(ProbabilityDistribution const& current) {
        // The probability distribution of a Markov chain is a vector [p1, p2,..., pn],
        // where pk is the probability that the current state is k.
        // The formula p1+p2+...+pn = 1 always holds.

        ProbabilityDistribution result;
        auto it = m_nextDistributionMap.find(current);
        if (it == m_nextDistributionMap.cend()) {
            result = calculateNextProbabilityDistribution(current);
            m_nextDistributionMap.emplace(current, result);
        } else {
            result = it->second;
        }
        return result;
    }

    ProbabilityDistribution getNextProbabilityDistribution(
        ProbabilityDistribution const& current, int const numberOfSteps) {
        ProbabilityDistribution result(current);
        for (int i = 0; i < numberOfSteps; i++) {
            result = getNextProbabilityDistribution(result);
        }
        return result;
    }

private:
    ProbabilityDistribution calculateNextProbabilityDistribution(ProbabilityDistribution const& current) {
        ProbabilityMatrix inputMatrix(1U, MAX_STATE_VALUE);
        for (int i = 0; i < MAX_STATE_VALUE; i++) {
            inputMatrix.setEntry(0U, i, current[i]);
        }
        ProbabilityMatrix outputMatrix = m_probabilityMatrix * inputMatrix;
        ProbabilityDistribution result;
        for (int i = 0; i < MAX_STATE_VALUE; i++) {
            result[i] = outputMatrix.getEntry(0U, i);
        }
        return result;
    }

    ProbabilityMatrix m_probabilityMatrix;
    DistributionToDistributionMap m_nextDistributionMap;
};

// An efficient way to simulate the walk in a Markov chain is to use dynamic programming.
// The idea is to maintain the probability distribution, and at each step go through all possibilities how we can move.
// Using this method, we can simulate a walk of m steps in O(n2m) time.
// The transitions of a Markov chain can also be represented as a matrix that updates the probability distribution.
// By calculating matrix powers efficiently, we can calculate the distribution after m steps in O(n3 logm) time.

}  // namespace alba
