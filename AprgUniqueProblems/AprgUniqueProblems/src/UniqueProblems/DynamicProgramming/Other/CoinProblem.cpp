#include "CoinProblem.hpp"

#include <algorithm>

using namespace std;

namespace alba {

CoinProblem::CoinProblem(Coins const& availableCoins) : m_availableCoins(availableCoins) {}

int CoinProblem::getNumberOfFewestCoinsUsingMemoizationDP(Value const total) const {
    CountPerValue countPerValue(getMaxOfTotalAndMaxCoinPlusOne(total), static_cast<int>(UNUSED_COUNT));
    countPerValue[0] = 1;  // null set
    for (Value const availableCoin : m_availableCoins) {
        countPerValue[availableCoin] = 1;
    }
    return getNumberOfFewestCoinsUsingMemoizationDPInternal(countPerValue, total);
}

int CoinProblem::getNumberOfFewestCoinsIterativeDP(Value const total) const {
    CountPerValue countPerValue(getMaxOfTotalAndMaxCoinPlusOne(total), static_cast<int>(UNUSED_COUNT));

    countPerValue[0] = 1;  // null set
    for (Value const availableCoin : m_availableCoins) {
        countPerValue[availableCoin] = 1;
    }
    for (Value partialValue = 1; partialValue <= total; partialValue++) {
        for (Value const availableCoin : m_availableCoins) {
            if (partialValue > availableCoin) {
                int subCount = countPerValue[partialValue - availableCoin];
                if (UNUSED_COUNT != subCount) {
                    countPerValue[partialValue] = min(countPerValue[partialValue], subCount + 1);
                }
            }
        }
    }
    return countPerValue[total];
}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingMemoizationDP(Value const total) const {
    VectorOfCoins fewestCoins(total + 1);
    return getFewestCoinsUsingMemoizationDPInternal(fewestCoins, total);
}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingIterativeDP(Value const total) const {
    VectorOfCoins fewestCoins(total + 1);
    for (Value partialValue = 1; partialValue <= total; partialValue++) {
        Coins& fewestCoinsForValue(fewestCoins[partialValue]);
        for (Value const availableCoin : m_availableCoins) {
            if (partialValue >= availableCoin &&
                (fewestCoins[partialValue].empty()  // has no solution
                 || fewestCoins[partialValue].size() >
                        fewestCoins[partialValue - availableCoin].size() + 1))  // is this solution better
            {
                fewestCoinsForValue = fewestCoins[partialValue - availableCoin];
                fewestCoinsForValue.emplace_back(availableCoin);
                // if only count is required, we can use a counter here here instead of list of
                // coins(fewestCoinsForValue)
            }
        }
    }
    return fewestCoins[total];
}

int CoinProblem::getNumberOfCoinPermutationsMemoizationDP(Value const total) const {
    CountPerValue countPerValue(total + 1, static_cast<int>(UNUSED_COUNT));
    countPerValue[0] = 1;  // null set
    return getNumberOfCoinPermutationsMemoizationDPInternal(countPerValue, total);
}

int CoinProblem::getNumberOfCoinPermutationsIterativeDP(Value const total) const {
    CountPerValue countPerValue(total + 1, 0);
    countPerValue[0] = 1;  // null set
    for (Value partialValue = 1; partialValue <= total; partialValue++) {
        for (Value const availableCoin : m_availableCoins) {
            if (partialValue >= availableCoin) {
                countPerValue[partialValue] += countPerValue[partialValue - availableCoin];
            }
        }
    }
    return countPerValue[total];
}

CoinProblem::CoinPermutations CoinProblem::getCoinPermutationsUsingMemoizationDP(Value const total) const {
    CoinPermutationsPerValue coinPermutationsPerValue(total + 1);
    return getCoinPermutationsUsingMemoizationDPInternal(coinPermutationsPerValue, total);
}

CoinProblem::CoinPermutations CoinProblem::getCoinPermutationsUsingIterativeDP(Value const total) const {
    CoinPermutationsPerValue coinPermutationsPerValue(getMaxOfTotalAndMaxCoinPlusOne(total));

    for (Value const availableCoin : m_availableCoins) {
        coinPermutationsPerValue[availableCoin].emplace(CoinPermutation{availableCoin});
    }
    for (Value partialValue = 0; partialValue < static_cast<Value>(coinPermutationsPerValue.size()); partialValue++) {
        CoinPermutations& coinPermutations(coinPermutationsPerValue[partialValue]);
        for (Value const availableCoin : m_availableCoins) {
            if (partialValue > availableCoin) {
                for (CoinPermutation const& permutationWithoutCoin :
                     coinPermutationsPerValue[partialValue - availableCoin]) {
                    CoinPermutation permutationWithCoin(permutationWithoutCoin);
                    permutationWithCoin.emplace_back(availableCoin);
                    coinPermutations.emplace(permutationWithCoin);
                }
            }
        }
    }
    return coinPermutationsPerValue[total];
}

int CoinProblem::getNumberOfCoinCombinationsUsingMemoizationDP(Value const total) const {
    // Time Complexity: O(M*N)
    // Auxiliary Space: O(M*N)

    CountMatrix countByValueByCoin(total + 1, m_availableCoins.size(), static_cast<int>(UNUSED_COUNT));

    int result(0);
    if (!m_availableCoins.empty()) {
        result = getNumberOfCoinCombinationsUsingMemoizationDPInternal(
            countByValueByCoin, total, m_availableCoins.size() - 1);
    }
    return result;
}

int CoinProblem::getNumberOfCoinCombinationsUsingIterativeDP(Value const total) const {
    // Time Complexity: O(mn)

    int result(0);
    if (!m_availableCoins.empty()) {
        CountMatrix countByValueByCoin(total + 1, m_availableCoins.size(), 0);
        for (int coinIndex = 0; coinIndex < static_cast<int>(m_availableCoins.size()); coinIndex++) {
            countByValueByCoin.setEntry(0, coinIndex, 1);  // null set when partial value is zero
        }
        for (Value partialValue = 1; partialValue <= total; partialValue++) {
            for (int coinIndex = 0; coinIndex < static_cast<int>(m_availableCoins.size()); coinIndex++) {
                Value countWithoutCoin(0), countWithCoin(0);
                if (coinIndex > 0) {
                    countWithoutCoin = countByValueByCoin.getEntry(
                        partialValue, coinIndex - 1);  // possibilities before this coin entry
                }
                if (partialValue >= m_availableCoins[coinIndex])  // if coin can be subtracted to value
                {
                    countWithCoin = countByValueByCoin.getEntry(
                        partialValue - m_availableCoins[coinIndex],
                        coinIndex);  // possibilities with the subtracted value
                }
                countByValueByCoin.setEntry(partialValue, coinIndex, countWithCoin + countWithoutCoin);
            }
        }
        result = countByValueByCoin.getEntry(
            total, m_availableCoins.size() - 1);  // last coin entry should contain all the possibilities
    }
    return result;
}

int CoinProblem::getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(Value const total) const {
    // Time Complexity: O(mn)
    // The auxiliary space required here is O(n) only.

    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one row above,
    // we only really need 1 row (not a matrix) to keep track partial values.

    CountPerValue countPerValue(total + 1, 0);
    countPerValue[0] = 1;
    for (Value const& availableCoin : m_availableCoins) {
        for (Value partialValue = availableCoin; partialValue <= total; partialValue++) {
            countPerValue[partialValue] += countPerValue[partialValue - availableCoin];
        }
    }
    return countPerValue.back();
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingMemoizationDP(Value const total) const {
    CoinCombinationsPerValue coinCombinationsPerValue(getMaxOfTotalAndMaxCoinPlusOne(total));
    return getCoinCombinationsUsingMemoizationDPInternal(coinCombinationsPerValue, total);
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingIterativeDP(Value const total) const {
    CoinCombinationsPerValue coinCombinationsPerValue(getMaxOfTotalAndMaxCoinPlusOne(total));

    for (Value const availableCoin : m_availableCoins) {
        if (coinCombinationsPerValue[availableCoin].empty()) {
            coinCombinationsPerValue[availableCoin].emplace(CoinCombination{availableCoin});
        }
    }
    for (Value partialValue = 1; partialValue < static_cast<Value>(coinCombinationsPerValue.size()); partialValue++) {
        CoinCombinations& combinations(coinCombinationsPerValue[partialValue]);
        for (Value const availableCoin : m_availableCoins) {
            if (partialValue > availableCoin) {
                for (CoinCombination const& combinationWithoutCoin :
                     coinCombinationsPerValue[partialValue - availableCoin]) {
                    CoinCombination combinationWithCoin(combinationWithoutCoin);
                    combinationWithCoin.emplace(availableCoin);
                    combinations.emplace(combinationWithCoin);
                }
            }
        }
    }
    return coinCombinationsPerValue[total];
}

CoinProblem::Value CoinProblem::getMaxAvailableCoin() const {
    Value result{};
    if (!m_availableCoins.empty()) {
        result = *max_element(m_availableCoins.cbegin(), m_availableCoins.cend());
    }
    return result;
}

CoinProblem::Value CoinProblem::getMaxOfTotalAndMaxCoinPlusOne(Value const total) const {
    return max(total, getMaxAvailableCoin()) + 1;
}

int CoinProblem::getNumberOfFewestCoinsUsingMemoizationDPInternal(
    CountPerValue& countPerValue, Value const total) const {
    int result(countPerValue[total]);
    if (UNUSED_COUNT == result) {
        // result is already set to max value so we can use min
        for (Value const availableCoin : m_availableCoins) {
            if (total > availableCoin) {
                int subCount(getNumberOfFewestCoinsUsingMemoizationDPInternal(countPerValue, total - availableCoin));
                if (UNUSED_COUNT != subCount) {
                    result = min(result, subCount + 1);
                }
            }
        }
        countPerValue[total] = result;
    }
    return result;
}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingMemoizationDPInternal(
    VectorOfCoins& fewestCoins, Value const total) const {
    Coins result(fewestCoins[total]);
    if (total != 0 && result.empty())  // not zero value and no solution yet
    {
        int fewestSize(UNUSED_COUNT);
        for (Value const availableCoin : m_availableCoins) {
            if (total > availableCoin) {
                Coins subSolution(getFewestCoinsUsingMemoizationDPInternal(fewestCoins, total - availableCoin));
                if (static_cast<int>(subSolution.size()) + 1 < fewestSize) {
                    subSolution.emplace_back(availableCoin);
                    fewestSize = subSolution.size();
                    result = subSolution;
                }
            } else if (total == availableCoin) {
                result = {availableCoin};
                break;
            }
        }
        fewestCoins[total] = result;
    }
    return result;
}

int CoinProblem::getNumberOfCoinPermutationsMemoizationDPInternal(
    CountPerValue& countPerValue, Value const total) const {
    int result(countPerValue[total]);
    if (UNUSED_COUNT == result) {
        result = 0;
        for (Value const availableCoin : m_availableCoins) {
            if (total >= availableCoin) {
                result += getNumberOfCoinPermutationsMemoizationDPInternal(countPerValue, total - availableCoin);
            }
        }
        countPerValue[total] = result;
    }
    return result;
}

CoinProblem::CoinPermutations CoinProblem::getCoinPermutationsUsingMemoizationDPInternal(
    CoinPermutationsPerValue& coinPermutationsPerValue, Value const total) const {
    CoinPermutations result(coinPermutationsPerValue[total]);
    if (total != 0 && result.empty())  // not zero value and no solution yet
    {
        for (Value const availableCoin : m_availableCoins) {
            if (total > availableCoin) {
                for (CoinPermutation const& subPermutation :
                     getCoinPermutationsUsingMemoizationDPInternal(coinPermutationsPerValue, total - availableCoin)) {
                    CoinPermutation permutation(subPermutation);
                    permutation.emplace_back(availableCoin);
                    coinPermutationsPerValue[total].emplace(permutation);
                }
            } else if (total == availableCoin) {
                coinPermutationsPerValue[availableCoin].emplace(CoinPermutation{availableCoin});
            }
        }
        result = coinPermutationsPerValue[total];
    }
    return result;
}

int CoinProblem::getNumberOfCoinCombinationsUsingMemoizationDPInternal(
    CountMatrix& countByValueByCoin, Value const total, int const coinIndex) const {
    int result(countByValueByCoin.getEntry(total, coinIndex));
    if (UNUSED_COUNT == result) {
        if (coinIndex > 0) {
            Value countWithCoin(0);
            Value countWithoutCoin = getNumberOfCoinCombinationsUsingMemoizationDPInternal(
                countByValueByCoin, total, coinIndex - 1);  // possibilities before this coin entry
            if (total >= m_availableCoins[coinIndex])    // if coin can be subtracted to value
            {
                countWithCoin = getNumberOfCoinCombinationsUsingMemoizationDPInternal(
                    countByValueByCoin, total - m_availableCoins[coinIndex],
                    coinIndex);  // possibilities with the subtracted value
            }
            result = countWithCoin + countWithoutCoin;
        } else {
            result = 1;  // the first coinIndex has one
        }
        countByValueByCoin.setEntry(total, coinIndex, result);
    }
    return result;
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingMemoizationDPInternal(
    CoinCombinationsPerValue& coinCombinationsPerValue, Value const total) const {
    CoinCombinations result(coinCombinationsPerValue[total]);
    if (total != 0 && result.empty())  // not zero value and no solution yet
    {
        for (Value const availableCoin : m_availableCoins) {
            if (total > availableCoin) {
                for (CoinCombination const& subCombination :
                     getCoinCombinationsUsingMemoizationDPInternal(coinCombinationsPerValue, total - availableCoin)) {
                    CoinCombination combination(subCombination);
                    combination.emplace(availableCoin);
                    coinCombinationsPerValue[total].emplace(combination);
                }
            } else if (total == availableCoin) {
                coinCombinationsPerValue[availableCoin].emplace(CoinCombination{availableCoin});
            }
        }
        result = coinCombinationsPerValue[total];
    }
    return result;
}

}  // namespace alba
