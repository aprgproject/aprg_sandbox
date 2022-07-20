#pragma once

#include <BooleanAlgebra/Algorithm/QuineMcCluskey/Implicant.hpp>
#include <BooleanAlgebra/Algorithm/QuineMcCluskey/Implicants.hpp>
#include <BooleanAlgebra/Algorithm/QuineMcCluskey/LogicalValue.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/User/DisplayTable.hpp>

#include <map>
#include <queue>
#include <sstream>
#include <vector>
namespace alba
{
namespace booleanAlgebra
{

template <typename Minterm>
class QuineMcCluskey
{
public:
    using Minterms = std::vector<Minterm>;
    using SetOfMinterms = std::set<Minterm>;
    using Implicant = Implicant<Minterm>;
    using Implicants = Implicants<Minterm>;
    using ImplicantsMap = std::map<Minterm, Implicants>;    using InputToOutputMap = std::map<Minterm, LogicalValue>;
    using ComputationalTable = std::map<Minterm, ImplicantsMap>;

    QuineMcCluskey()        : m_maxCommonalityCount(0)
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
                for(Implicant const& implicant : implicants.getImplicantsData())
                {
                    result.addImplicant(implicant);
                }
            }
        }
        return result;    }

    Implicants getAllFinalImplicants() const
    {        Implicants result;
        for(auto it=m_computationalTable.begin(); it!=m_computationalTable.end(); it++)
        {
            ImplicantsMap const& implicantsMap(it->second);
            for(auto reverseIt=implicantsMap.rbegin(); reverseIt!=implicantsMap.rend(); reverseIt++)
            {
                Implicants const& currentImplicants(reverseIt->second);
                for(Implicant const& implicant : currentImplicants.getImplicantsData())
                {
                    result.addFinalImplicant(implicant);
                }
            }
        }
        return result;    }

    bool doImplicantsExistAt(unsigned int numberOfOnes, unsigned int commonalityCount) const
    {        bool result(false);
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
            for(Implicant const& implicant1 : implicants1.getImplicantsData())
            {
                for(Implicant const& implicant2 : implicants2.getImplicantsData())
                {
                    if(implicant1.isCompatible(implicant2))
                    {
                        m_computationalTable[numberOfOnes][commonalityCount+1].addImplicant(implicant1+implicant2);
                    }
                }
            }
        }
    }
    std::string getComputationTableString() const
    {
        std::stringstream ss;        for(auto const& numberOfOnesAndCommonalityCountImplicantsPair : m_computationalTable)
        {
            ss << "Number of ones = " << numberOfOnesAndCommonalityCountImplicantsPair.first << std::endl;
            for(auto const& commonalityCountAndImplicantsPair : numberOfOnesAndCommonalityCountImplicantsPair.second)
            {
                ss << "Commonality count = " << commonalityCountAndImplicantsPair.first << " with " << commonalityCountAndImplicantsPair.second << std::endl;
            }
        }
        return ss.str();
    }

    Implicants getBestImplicants(Implicants const& finalImplicants) const
    {
        // Specialized selection
        Implicants result;
        SetOfMinterms inputMintermsWithTrue(getSetOfInputMintermsWithTrue());

        while(!inputMintermsWithTrue.empty())
        {
            std::map<Minterm, unsigned int> inputMintermToCountMap;
            std::map<Minterm, Implicant> inputMintermToImplicantMap;
            std::map<unsigned int, Implicant> countToImplicantMap;
            for(Implicant const& implicant : finalImplicants.getImplicantsData())
            {
                unsigned int implicantCount(0U);
                for(auto const& inputMinterm : inputMintermsWithTrue)
                {
                    if(implicant.isSuperset(inputMinterm))
                    {
                        inputMintermToCountMap[inputMinterm]++;
                        inputMintermToImplicantMap.emplace(inputMinterm, implicant);
                        implicantCount++;
                    }
                }
                countToImplicantMap.emplace(implicantCount, implicant);
            }
            unsigned int minCount = std::numeric_limits<unsigned int>::max();
            Minterm mintermWithMinCount;
            for(auto const& inputMintermAndCountPair : inputMintermToCountMap)
            {
                if(minCount > inputMintermAndCountPair.second)
                {
                    mintermWithMinCount = inputMintermAndCountPair.first;
                    minCount = inputMintermAndCountPair.second;
                }
            }
            Implicant bestImplicant;
            if(minCount == 1U)
            {
                bestImplicant = inputMintermToImplicantMap.at(mintermWithMinCount);
            }
            else
            {
                auto it = countToImplicantMap.cend();
                it--;
                bestImplicant = it->second;
            }
            SetOfMinterms bestImplicantMinterms(bestImplicant.getMinterms());
            if(!bestImplicantMinterms.empty())
            {
                for(Minterm const& bestImplicantMinterm : bestImplicantMinterms)
                {
                    inputMintermsWithTrue.erase(bestImplicantMinterm);
                }
                result.addImplicant(bestImplicant);
            }
        }
        return result;
    }

    std::string getOutputTable(Implicants const& finalImplicants) const
    {
        Minterms inputsWithTrue(getInputMintermsWithTrue());
        DisplayTable displayTable;
        displayTable.setBorders("", "|");
        displayTable.addRow();        displayTable.getLastRow().addCell(" ");
        for(auto const& input : inputsWithTrue)
        {
            std::stringstream ss;
            ss << input;
            displayTable.getLastRow().addCell(ss.str());
        }
        for(Implicant const& implicant : finalImplicants.getImplicantsData())
        {
            displayTable.addRow();
            displayTable.getLastRow().addCell(implicant.getEquivalentString(8));
            for(auto const& input : inputsWithTrue)
            {
                std::string cell = implicant.isSuperset(input) ? "X" : " ";
                displayTable.getLastRow().addCell(cell);
            }
        }
        return displayTable.drawOutput();
    }

private:

    Minterms getInputMintermsWithTrue() const
    {
        Minterms result;
        for(auto inputOutputPair : m_inputToOutputMap)
        {
            if(inputOutputPair.second == LogicalValue::True)
            {
                result.emplace_back(inputOutputPair.first);
            }
        }
        return result;
    }

    SetOfMinterms getSetOfInputMintermsWithTrue() const
    {
        SetOfMinterms result;
        for(auto inputOutputPair : m_inputToOutputMap)
        {
            if(inputOutputPair.second == LogicalValue::True)
            {
                result.emplace(inputOutputPair.first);
            }
        }
        return result;
    }

    void addMintermForZeroCommonalityCount(Minterm const& minterm)
    {
        unsigned int numberOfOnes(getNumberOfOnes(minterm));        Implicant implicant;
        implicant.addMinterm(minterm);
        m_computationalTable[numberOfOnes][0].addImplicant(implicant);
    }
    unsigned int m_maxCommonalityCount;
    InputToOutputMap m_inputToOutputMap;
    ComputationalTable m_computationalTable; // https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm
};

}

}
