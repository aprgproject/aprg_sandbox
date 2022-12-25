#include "CoinProblem.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

CoinProblem::CoinProblem(Coins const& availableCoins)
    : m_availableCoins(availableCoins)
{}

unsigned int CoinProblem::getNumberOfFewestCoinsUsingMemoizationDP(Value const total) const
{
    CountPerValue countPerValue(total+1, static_cast<unsigned int>(UNUSED_COUNT));
    return getNumberOfFewestCoinsUsingMemoizationDPInternal(countPerValue, total);
}

unsigned int CoinProblem::getNumberOfFewestCoinsTabularDP(Value const total) const
{
    CountPerValue countPerValue(getMaxOfTotalAndMaxCoin(total), static_cast<unsigned int>(UNUSED_COUNT));
    countPerValue[0] = 1; // null set
    for(Value const availableCoin : m_availableCoins)
    {
        countPerValue[availableCoin] = 1;
    }
    for(Value partialValue=1; partialValue<=total; partialValue++)
    {
        for(Value const availableCoin : m_availableCoins)
        {
            if(partialValue > availableCoin)
            {
                unsigned int subCount(countPerValue.at(partialValue-availableCoin));
                if(UNUSED_COUNT!=subCount)
                {
                    countPerValue[partialValue] = min(countPerValue.at(partialValue), subCount+1);
                }
            }
        }
    }
    return countPerValue.at(total);
}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingMemoizationDP(Value const total) const
{
    VectorOfCoins fewestCoins(total+1);
    return getFewestCoinsUsingMemoizationDPInternal(fewestCoins, total);
}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingTabularDP(Value const total) const
{
    VectorOfCoins fewestCoins(total+1);
    for(Value partialValue=1; partialValue<=total; partialValue++)
    {
        Coins & fewestCoinsForValue(fewestCoins[partialValue]);
        for(Value const availableCoin : m_availableCoins)
        {
            if(partialValue >= availableCoin
                    && (fewestCoins.at(partialValue).empty() // has no solution
                        || fewestCoins.at(partialValue).size() > fewestCoins.at(partialValue-availableCoin).size()+1)) // is this solution better
            {
                fewestCoinsForValue = fewestCoins.at(partialValue-availableCoin);
                fewestCoinsForValue.emplace_back(availableCoin);
                // if only count is required, we can use a counter here here instead of list of coins(fewestCoinsForValue)
            }
        }
    }
    return fewestCoins.at(total);
}

unsigned int CoinProblem::getNumberOfCoinPermutationsMemoizationDP(Value const total) const
{
    CountPerValue countPerValue(getMaxOfTotalAndMaxCoin(total), static_cast<unsigned int>(UNUSED_COUNT));
    countPerValue[0] = 1; // null set
    return getNumberOfCoinPermutationsMemoizationDPInternal(countPerValue, total);
}

unsigned int CoinProblem::getNumberOfCoinPermutationsTabularDP(Value const total) const
{
    CountPerValue countPerValue(getMaxOfTotalAndMaxCoin(total), 0);
    countPerValue[0] = 1; // null set
    for(Value const availableCoin : m_availableCoins)
    {
        countPerValue[availableCoin] = 1;
    }
    for(Value partialValue=1; partialValue<=total; partialValue++)
    {
        for(Value const availableCoin : m_availableCoins)
        {
            if(partialValue > availableCoin)
            {
                countPerValue[partialValue] += countPerValue.at(partialValue-availableCoin);
            }
        }
    }
    return countPerValue.at(total);
}

CoinProblem::CoinPermutations CoinProblem::getCoinPermutationsUsingMemoizationDP(Value const total) const
{
    CoinPermutationsPerValue coinPermutationsPerValue(getMaxOfTotalAndMaxCoin(total));
    return getCoinPermutationsUsingMemoizationDPInternal(coinPermutationsPerValue, total);
}

CoinProblem::CoinPermutations CoinProblem::getCoinPermutationsUsingTabularDP(Value const total) const
{
    CoinPermutationsPerValue coinPermutationsPerValue(getMaxOfTotalAndMaxCoin(total));

    for(Value const availableCoin : m_availableCoins)
    {
        if(coinPermutationsPerValue.at(availableCoin).empty())
        {
            coinPermutationsPerValue[availableCoin].emplace(CoinPermutation{availableCoin});
        }
    }

    for(Value partialValue=0; partialValue<coinPermutationsPerValue.size(); partialValue++)
    {
        CoinPermutations & coinPermutations(coinPermutationsPerValue[partialValue]);
        for(Value const availableCoin : m_availableCoins)
        {
            if(partialValue > availableCoin)
            {
                for(CoinPermutation const& permutationWithoutCoin : coinPermutationsPerValue.at(partialValue-availableCoin))
                {
                    CoinPermutation permutationWithCoin(permutationWithoutCoin);
                    permutationWithCoin.emplace_back(availableCoin);
                    coinPermutations.emplace(permutationWithCoin);
                }
            }
        }
    }
    return coinPermutationsPerValue.at(total);
}

unsigned int CoinProblem::getNumberOfCoinCombinationsUsingMemoizationDP(Value const total) const
{
    CountPerValue countPerValue(m_availableCoins.size(), static_cast<unsigned int>(UNUSED_COUNT));
    countPerValue.shrink_to_fit();
    CountPerValueAndPerCoin countPerValuePerCoin(total+1, countPerValue);

    unsigned int result(0);
    if(!m_availableCoins.empty())
    {
        result = getNumberOfCoinCombinationsUsingMemoizationDPInternal(countPerValuePerCoin, total, m_availableCoins.size()-1);
    }
    return result;
}

unsigned int CoinProblem::getNumberOfCoinCombinationsUsingTabularDP(Value const total) const
{
    CountPerValue countPerValue(m_availableCoins.size(), 0);
    countPerValue.shrink_to_fit();
    CountPerValueAndPerCoin countPerValuePerCoin(total+1, countPerValue);

    for(unsigned int coinIndex=0; coinIndex<m_availableCoins.size(); coinIndex++)
    {
        countPerValuePerCoin[0][coinIndex] = 1; // null set when partial value is zero
    }
    for(Value partialValue=1; partialValue<=total; partialValue++)
    {
        for(unsigned int coinIndex=0; coinIndex<m_availableCoins.size(); coinIndex++)
        {
            Value countWithoutCoin(0), countWithCoin(0);
            if(coinIndex > 0)
            {
                countWithoutCoin = countPerValuePerCoin.at(partialValue).at(coinIndex-1); // possibilities before this coin entry
            }
            if(partialValue >= m_availableCoins.at(coinIndex)) // if coin can be subtracted to value
            {
                countWithCoin = countPerValuePerCoin.at(partialValue-m_availableCoins.at(coinIndex)).at(coinIndex); // possibilities with the subtracted value
            }
            countPerValuePerCoin[partialValue][coinIndex] = countWithCoin + countWithoutCoin;
        }
    }
    return countPerValuePerCoin.at(total).back(); // last coin entry should contain all the possibilities
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingMemoizationDP(Value const total) const
{
    CoinCombinationsPerValue coinCombinationsPerValue(getMaxOfTotalAndMaxCoin(total));
    return getCoinCombinationsUsingMemoizationDPInternal(coinCombinationsPerValue, total);
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingTabularDP(Value const total) const
{
    CoinCombinationsPerValue coinCombinationsPerValue(getMaxOfTotalAndMaxCoin(total));

    for(Value const availableCoin : m_availableCoins)
    {
        if(coinCombinationsPerValue.at(availableCoin).empty())
        {
            coinCombinationsPerValue[availableCoin].emplace(CoinCombination{availableCoin});
        }
    }
    for(Value partialValue=1; partialValue<coinCombinationsPerValue.size(); partialValue++)
    {
        CoinCombinations & combinations(coinCombinationsPerValue[partialValue]);
        for(Value const availableCoin : m_availableCoins)
        {
            if(partialValue > availableCoin)
            {
                for(CoinCombination const& combinationWithoutCoin : coinCombinationsPerValue.at(partialValue-availableCoin))
                {
                    CoinCombination combinationWithCoin(combinationWithoutCoin);
                    combinationWithCoin.emplace(availableCoin);
                    combinations.emplace(combinationWithCoin);
                }
            }
        }
    }
    return coinCombinationsPerValue.at(total);
}

CoinProblem::Value CoinProblem::getMaxAvailableCoin() const
{
    Value result{};
    if(!m_availableCoins.empty())
    {
        result = *max_element(m_availableCoins.cbegin(), m_availableCoins.cend());
    }
    return result;
}

CoinProblem::Value CoinProblem::getMaxOfTotalAndMaxCoin(Value const total) const
{
    return max(total+1, getMaxAvailableCoin());
}

unsigned int CoinProblem::getNumberOfFewestCoinsUsingMemoizationDPInternal(
        CountPerValue & countPerValue,
        Value const total) const
{
    unsigned int result(countPerValue.at(total));
    if(UNUSED_COUNT == result)
    {
        result = MAX_COUNT;
        for(Value const availableCoin : m_availableCoins)
        {
            if(total > availableCoin)
            {
                unsigned int subCount(getNumberOfFewestCoinsUsingMemoizationDPInternal(countPerValue, total-availableCoin));
                if(UNUSED_COUNT!=subCount && MAX_COUNT!=subCount)
                {
                    result = min(result, subCount+1);
                }
            }
            else if(total == availableCoin)
            {
                result = 1;
                break;
            }
        }
        countPerValue[total] = result;
    }
    return result;
}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingMemoizationDPInternal(
        VectorOfCoins & fewestCoins,
        Value const total) const
{
    Coins result(fewestCoins.at(total));
    if(total != 0 && result.empty()) // not zero value and no solution yet
    {
        unsigned int fewestSize(MAX_COUNT);
        for(Value const availableCoin : m_availableCoins)
        {
            if(total > availableCoin)
            {
                Coins subSolution(getFewestCoinsUsingMemoizationDPInternal(fewestCoins, total-availableCoin));
                if(fewestSize > subSolution.size()+1)
                {
                    subSolution.emplace_back(availableCoin);
                    fewestSize = subSolution.size();
                    result = subSolution;
                }
            }
            else if(total == availableCoin)
            {
                result = {availableCoin};
                break;
            }
        }
        fewestCoins[total] = result;
    }
    return result;
}

unsigned int CoinProblem::getNumberOfCoinPermutationsMemoizationDPInternal(
        CountPerValue & countPerValue,
        Value const total) const
{
    unsigned int result(countPerValue.at(total));
    if(UNUSED_COUNT == result)
    {
        result = 0;
        for(Value const availableCoin : m_availableCoins)
        {
            if(total >= availableCoin)
            {
                result += getNumberOfCoinPermutationsMemoizationDPInternal(countPerValue, total-availableCoin);
            }
        }
        countPerValue[total] = result;
    }
    return result;
}

CoinProblem::CoinPermutations CoinProblem::getCoinPermutationsUsingMemoizationDPInternal(
        CoinPermutationsPerValue & coinPermutationsPerValue,
        Value const total) const
{
    CoinPermutations result(coinPermutationsPerValue.at(total));
    if(total != 0 && result.empty()) // not zero value and no solution yet
    {
        for(Value const availableCoin : m_availableCoins)
        {
            if(total > availableCoin)
            {
                CoinPermutations subPermutations(getCoinPermutationsUsingMemoizationDPInternal(coinPermutationsPerValue, total-availableCoin));
                for(CoinPermutation const& subPermutation : subPermutations)
                {
                    CoinPermutation permutation(subPermutation);
                    permutation.emplace_back(availableCoin);
                    coinPermutationsPerValue[total].emplace(permutation);
                }
            }
            else if(total == availableCoin)
            {
                coinPermutationsPerValue[availableCoin].emplace(CoinPermutation{availableCoin});
            }
        }
        result = coinPermutationsPerValue.at(total);
    }
    return result;
}

unsigned int CoinProblem::getNumberOfCoinCombinationsUsingMemoizationDPInternal(
        CountPerValueAndPerCoin & countPerValuePerCoin,
        Value const total,
        unsigned int const coinIndex) const
{
    unsigned int result(countPerValuePerCoin.at(total).at(coinIndex));
    if(UNUSED_COUNT == result)
    {
        if(coinIndex > 0)
        {
            Value countWithCoin(0);
            Value countWithoutCoin = getNumberOfCoinCombinationsUsingMemoizationDPInternal(countPerValuePerCoin, total, coinIndex-1); // possibilities before this coin entry
            if(total >= m_availableCoins.at(coinIndex)) // if coin can be subtracted to value
            {
                countWithCoin = getNumberOfCoinCombinationsUsingMemoizationDPInternal(countPerValuePerCoin, total-m_availableCoins.at(coinIndex), coinIndex); // possibilities with the subtracted value
            }
            result = countWithCoin + countWithoutCoin;
        }
        else
        {
            result = 1;
        }
        countPerValuePerCoin[total][coinIndex] = result;
    }
    return result;
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingMemoizationDPInternal(
        CoinCombinationsPerValue & coinCombinationsPerValue,
        Value const total) const
{
    CoinCombinations result(coinCombinationsPerValue.at(total));
    if(total != 0 && result.empty()) // not zero value and no solution yet
    {
        for(Value const availableCoin : m_availableCoins)
        {
            if(total > availableCoin)
            {
                CoinCombinations subCombinations(getCoinCombinationsUsingMemoizationDPInternal(coinCombinationsPerValue, total-availableCoin));
                for(CoinCombination const& subCombination : subCombinations)
                {
                    CoinCombination combination(subCombination);
                    combination.emplace(availableCoin);
                    coinCombinationsPerValue[total].emplace(combination);
                }
            }
            else if(total == availableCoin)
            {
                coinCombinationsPerValue[availableCoin].emplace(CoinCombination{availableCoin});
            }
        }
        result = coinCombinationsPerValue.at(total);
    }
    return result;
}

}
