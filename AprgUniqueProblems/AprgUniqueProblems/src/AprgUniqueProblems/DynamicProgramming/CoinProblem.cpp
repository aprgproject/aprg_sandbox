#include "CoinProblem.hpp"

#include <algorithm>
#include <limits>

using namespace std;

namespace alba
{

CoinProblem::CoinProblem(Coins const& availableCoins)
    : m_availableCoins(availableCoins)
    , m_fewestCoins{}
    , m_countPerValue{}
{}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingRecursion(Coin const total)
{
    // this recursion method is exponential
    Coins result;
    if(total < m_fewestCoins.size() && !m_fewestCoins.at(total).empty())
    {
        result = m_fewestCoins.at(total);
    }
    else if(total == 0)
    {
        // do nothing, because zero should contains null set
    }
    else
    {
        unsigned int fewestSize = numeric_limits<unsigned int>::max();
        for(Coin const availableCoin : m_availableCoins)
        {
            if(total > availableCoin)
            {
                Coins subSolution(getFewestCoinsUsingRecursion(total-availableCoin));
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
        addSolutionWithFewestCoins(total, result);
    }
    return result;
}

CoinProblem::Coins CoinProblem::getFewestCoinsUsingLoops(Coin const total)
{
    // using loops is better because its quadratic
    if(total>=m_fewestCoins.size())
    {
        Coin previousSize=m_fewestCoins.size();
        m_fewestCoins.resize(total+1);
        for(Coin partialValue=previousSize; partialValue<=total; partialValue++)
        {
            Coins & fewestCoinsForValue(m_fewestCoins[partialValue]);
            for(Coin const availableCoin : m_availableCoins)
            {
                if(partialValue >= availableCoin
                        && (m_fewestCoins.at(partialValue).empty() // has no solution
                            || m_fewestCoins.at(partialValue).size() > m_fewestCoins.at(partialValue-availableCoin).size()+1)) // is solution better
                {
                    fewestCoinsForValue = m_fewestCoins.at(partialValue-availableCoin);
                    fewestCoinsForValue.emplace_back(availableCoin);
                }
            }
        }    }
    return m_fewestCoins.at(total);
}
unsigned int CoinProblem::getNumberOfCoinPermutations(Coin const total)
{
    // using loops
    if(total>=m_countPerValue.size())
    {
        Coin previousSize=m_countPerValue.size();
        unsigned int newSize = max(total+1, *(minmax_element(m_availableCoins.cbegin(), m_availableCoins.cend()).second));
        m_countPerValue.resize(newSize, 0U);
        for(Coin const availableCoin : m_availableCoins)        {
            m_countPerValue[availableCoin] = 1;
        }
        for(Coin partialValue=previousSize; partialValue<newSize; partialValue++)
        {
            for(Coin const availableCoin : m_availableCoins)
            {                if(partialValue > availableCoin)
                {
                    m_countPerValue[partialValue] += m_countPerValue.at(partialValue-availableCoin);
                }            }
        }
    }
    return m_countPerValue.at(total);
}

CoinProblem::CoinPermutations CoinProblem::getCoinPermutationsUsingLoops(Coin const total)
{
    // using loops
    if(total>=m_coinPermutations.size())
    {
        Coin previousSize=m_coinPermutations.size();
        unsigned int newSize = max(total+1, *(minmax_element(m_availableCoins.cbegin(), m_availableCoins.cend()).second));
        m_coinPermutations.resize(newSize);
        for(Coin const availableCoin : m_availableCoins)
        {
            if(m_coinPermutations.at(availableCoin).empty())            {
                m_coinPermutations[availableCoin].emplace(CoinPermutation{availableCoin});
            }
        }

        for(Coin partialValue=previousSize; partialValue<newSize; partialValue++)
        {
            CoinPermutations & coinPermutations(m_coinPermutations[partialValue]);
            for(Coin const availableCoin : m_availableCoins)            {
                if(partialValue > availableCoin)
                {
                    for(CoinPermutation const& permutationWithoutCoin : m_coinPermutations.at(partialValue-availableCoin))                    {
                        CoinPermutation permutationWithCoin(permutationWithoutCoin);
                        permutationWithCoin.emplace_back(availableCoin);
                        coinPermutations.emplace(permutationWithCoin);
                    }
                }
            }
        }
    }
    return m_coinPermutations.at(total);
}

unsigned int CoinProblem::getNumberOfCoinCombinations(Coin const total)
{
    // using loops
    unsigned int result=0;
    if(!m_availableCoins.empty())
    {
        if(total>=m_countPerValuePerCoin.size())
        {
            Coin previousSize=m_countPerValuePerCoin.size();
            unsigned int newSize = max(total+1, *(minmax_element(m_availableCoins.cbegin(), m_availableCoins.cend()).second));
            CountPerValue countPerValue(m_availableCoins.size(), 0U);
            countPerValue.shrink_to_fit();            m_countPerValuePerCoin.resize(newSize, countPerValue);

            for(Coin coinIndex=0; coinIndex<m_availableCoins.size(); coinIndex++)
            {
                for(Coin partialValue=previousSize; partialValue<newSize; partialValue++)
                {
                    if(partialValue == 0)
                    {                        m_countPerValuePerCoin[partialValue][coinIndex] = 1; // null set when partial value is zero
                        continue;
                    }
                    if(coinIndex == 0)                    {
                        m_countPerValuePerCoin[partialValue][coinIndex] = (partialValue % m_availableCoins.at(coinIndex) == 0) ? 1 : 0; // one if divisible?
                        continue;
                    }
                    if(partialValue >= m_availableCoins.at(coinIndex)) // if coin can be subtracted to value
                    {
                        m_countPerValuePerCoin[partialValue][coinIndex]
                                = m_countPerValuePerCoin.at(partialValue).at(coinIndex-1) // possibilities before this coin entry
                                + m_countPerValuePerCoin.at(partialValue-m_availableCoins[coinIndex]).at(coinIndex); // possibilities with the subtracted value
                    }
                    else
                    {
                        m_countPerValuePerCoin[partialValue][coinIndex] =  m_countPerValuePerCoin.at(partialValue).at(coinIndex-1); // possibilities before this coin entry
                    }
                }
            }
        }
        result = m_countPerValuePerCoin.at(total).back(); // last coin entry should contain all the possibilities
    }
    return result;
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingRecursion(Coin const total)
{
    // this recursion method is exponential
    if(total >= m_coinCombinations.size())
    {
        unsigned int newSize = max(total+1, *(minmax_element(m_availableCoins.cbegin(), m_availableCoins.cend()).second));
        m_coinCombinations.resize(newSize);
    }
    if(m_coinCombinations.at(total).empty())
    {
        for(Coin const availableCoin : m_availableCoins)
        {
            if(total > availableCoin)
            {
                CoinCombinations subCombinations(getCoinCombinationsUsingRecursion(total-availableCoin));
                for(CoinCombination const& subcombination : subCombinations)
                {
                    CoinCombination combination(subcombination);
                    combination.emplace(availableCoin);
                    m_coinCombinations[total].emplace(combination);
                }
            }
            else if(total == availableCoin)
            {
                m_coinCombinations[availableCoin].emplace(CoinCombination{{availableCoin}});
            }
        }
    }
    return m_coinCombinations.at(total);
}

CoinProblem::CoinCombinations CoinProblem::getCoinCombinationsUsingLoops(Coin const total)
{
    // using loops
    if(total>=m_coinCombinations.size())
    {
        Coin previousSize=m_coinCombinations.size();
        unsigned int newSize = max(total+1, *(minmax_element(m_availableCoins.cbegin(), m_availableCoins.cend()).second));
        m_coinCombinations.resize(newSize);
        for(Coin const availableCoin : m_availableCoins)
        {
            if(m_coinCombinations.at(availableCoin).empty())            {
                m_coinCombinations[availableCoin].emplace(CoinCombination{availableCoin});
            }
        }

        for(Coin partialValue=previousSize; partialValue<newSize; partialValue++)
        {
            CoinCombinations & coinCombinations(m_coinCombinations[partialValue]);
            for(Coin const availableCoin : m_availableCoins)            {
                if(partialValue > availableCoin)
                {
                    for(CoinCombination const& combinationWithoutCoin : m_coinCombinations.at(partialValue-availableCoin))                    {
                        CoinCombination combinationWithCoin(combinationWithoutCoin);
                        combinationWithCoin.emplace(availableCoin);
                        coinCombinations.emplace(combinationWithCoin);
                    }
                }
            }
        }
    }
    return m_coinCombinations.at(total);
}

void CoinProblem::addSolutionWithFewestCoins(Coin const total, Coins const& fewestCoinSolution)
{
    if(total>=m_fewestCoins.size())
    {
        m_fewestCoins.resize(total+1);
    }
    if(m_fewestCoins.at(total).empty())
    {
        m_fewestCoins[total] = fewestCoinSolution;
    }
}

}
