#pragma once

#include <Algorithm/QuineMcCluskey/Implicant.hpp>
#include <Algorithm/QuineMcCluskey/Implicants.hpp>
#include <Algorithm/QuineMcCluskey/LogicalValue.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/User/DisplayTable.hpp>

#include <map>
#include <sstream>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Minterm>
class QuineMcCluskey
{
public:
    using Implicant = Implicant<Minterm>;
    using Implicants = Implicants<Minterm>;
    using ImplicantsMap = std::map<Minterm, Implicants>;
    using InputToOutputMap = std::map<Minterm, LogicalValue>;
    using ComputationalTable = std::map<Minterm, ImplicantsMap>;

    QuineMcCluskey()
        : m_maxCommonalityCount(0)
    {}

    LogicalValue getOutput(Minterm const input) const
    {
        LogicalValue result(LogicalValue::False);
        auto it = m_inputToOutputMap.find(input);
        if (it != m_inputToOutputMap.end())
        {
            result = it->second;
        }
        return result;
    }

    unsigned int getNumberOfOnes(Minterm const value) const
    {
        return AlbaBitValueUtilities<Minterm>::getNumberOfOnes(value);
    }

    Implicants getImplicants(unsigned int numberOfOnes, unsigned int commonalityCount) const
    {
        Implicants result;
        auto numberOfOnesIt = m_computationalTable.find(numberOfOnes);
        if (numberOfOnesIt != m_computationalTable.end())
        {
            ImplicantsMap const& implicantsMap(numberOfOnesIt->second);
            auto commonalityCountIt = implicantsMap.find(commonalityCount);
            if (commonalityCountIt != implicantsMap.end())
            {
                Implicants const& implicants(commonalityCountIt->second);
                implicants.traverseAllImplicants([&](Implicant const& implicant)
                {
                    result.addImplicant(implicant);
                });
            }
        }
        return result;
    }

    Implicants getAllFinalImplicants() const
    {
        Implicants result;
        for(auto it=m_computationalTable.begin(); it!=m_computationalTable.end(); it++)
        {
            ImplicantsMap const& implicantsMap(it->second);
            for(auto reverseIt=implicantsMap.rbegin(); reverseIt!=implicantsMap.rend(); reverseIt++)
            {
                Implicants const& currentImplicants(reverseIt->second);
                currentImplicants.traverseAllImplicants([&](Implicant const& implicant)
                {
                    result.addFinalImplicant(implicant);
                });
            }
        }
        return result;
    }

    bool doImplicantsExistAt(unsigned int numberOfOnes, unsigned int commonalityCount) const
    {
        bool result(false);
        auto numberOfOnesIt = m_computationalTable.find(numberOfOnes);
        if(numberOfOnesIt != m_computationalTable.end())
        {
            ImplicantsMap const& implicantsMap(numberOfOnesIt->second);
            result = implicantsMap.find(commonalityCount) != implicantsMap.end();
        }
        return result;
    }

    void setInputOutput(Minterm const input, LogicalValue const output)
    {
        if(output == LogicalValue::True || output == LogicalValue::DontCare)
        {
            m_inputToOutputMap.emplace(input, output);
        }
    }

    void findAllCombinations()
    {
        unsigned int commonalityCount=0;
        bool areAllCombinationsFound(false);
        while(!areAllCombinationsFound)
        {
            bool isCombinationFound(false);
            for(unsigned int numberOfOnes=0; numberOfOnes+1 < m_computationalTable.size(); numberOfOnes++)
            {
                findCombinationOfImplicants(numberOfOnes, commonalityCount);
                isCombinationFound = isCombinationFound | doImplicantsExistAt(numberOfOnes, commonalityCount+1);
            }
            areAllCombinationsFound = !isCombinationFound;
            commonalityCount++;
        }
        m_maxCommonalityCount = (commonalityCount>0) ? commonalityCount-1 : 0;
    }

    void fillComputationalTableWithMintermsWithZeroCommonalityCount()
    {
        for(auto const & inputAndOutputPair : m_inputToOutputMap)
        {
            addMintermForZeroCommonalityCount(inputAndOutputPair.first);
        }
    }

    void findCombinationOfImplicants(unsigned int numberOfOnes, unsigned int commonalityCount)
    {
        if(numberOfOnes+1 < m_computationalTable.size())
        {
            Implicants const& implicants1(m_computationalTable[numberOfOnes][commonalityCount]);
            Implicants const& implicants2(m_computationalTable[numberOfOnes+1][commonalityCount]);
            implicants1.traverseAllImplicants([&](Implicant const& implicant1)
            {
                implicants2.traverseAllImplicants([&](Implicant const& implicant2)
                {
                    if(implicant1.isCompatible(implicant2))
                    {
                        m_computationalTable[numberOfOnes][commonalityCount+1].addImplicant(implicant1+implicant2);
                    }
                });
            });
        }
    }

    std::string getComputationTableString() const
    {
        std::stringstream ss;
        for(auto const& numberOfOnesAndCommonalityCountImplicantsPair : m_computationalTable)
        {
            ss << "Number of ones = " << numberOfOnesAndCommonalityCountImplicantsPair.first << std::endl;
            for(auto const& commonalityCountAndImplicantsPair : numberOfOnesAndCommonalityCountImplicantsPair.second)
            {
                ss << "Commonality count = " << commonalityCountAndImplicantsPair.first << " with " << commonalityCountAndImplicantsPair.second << std::endl;
            }
        }
        return ss.str();
    }

    std::string getOutputTable(Implicants const& finalImplicants) const
    {
        std::vector<Minterm> inputsWithTrue;
        for(auto inputOutputPair : m_inputToOutputMap)
        {
            if(inputOutputPair.second == LogicalValue::True)
            {
                inputsWithTrue.emplace_back(inputOutputPair.first);
            }
        }
        DisplayTable displayTable;
        displayTable.setBorders("", "|");
        displayTable.addRow();
        displayTable.getLastRow().addCell(" ");
        for(auto const& input : inputsWithTrue)
        {
            std::stringstream ss;
            ss << input;
            displayTable.getLastRow().addCell(ss.str());
        }
        finalImplicants.traverseAllImplicants([&](Implicant const& implicant)
        {
            displayTable.addRow();
            displayTable.getLastRow().addCell(implicant.getEquivalentString(8));
            for(auto const& input : inputsWithTrue)
            {
                if(implicant.isSuperset(input))
                {
                    displayTable.getLastRow().addCell("X");
                }
                else
                {
                    displayTable.getLastRow().addCell(" ");
                }
            }
        });
        return displayTable.drawOutput();
    }

private:

    void addMintermForZeroCommonalityCount(Minterm const& minterm)
    {
        unsigned int numberOfOnes(getNumberOfOnes(minterm));
        Implicant implicant;
        implicant.addMinterm(minterm);
        m_computationalTable[numberOfOnes][0].addImplicant(implicant);
    }

    unsigned int m_maxCommonalityCount;
    InputToOutputMap m_inputToOutputMap;
    ComputationalTable m_computationalTable; // https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm
};

}

}
