#pragma once

#include <Algorithm/QuineMcCluskey/Implicant.hpp>
#include <Algorithm/QuineMcCluskey/Implicants.hpp>
#include <Algorithm/QuineMcCluskey/LogicalValue.hpp>
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
    using FunctionsMap = std::map<Minterm, LogicalValue>;
    using ComputationalTable = std::map<Minterm, ImplicantsMap>;

    QuineMcCluskey()
        : m_cubeSize(0)
    {}

    LogicalValue getOutput(Minterm const input) const
    {
        LogicalValue result(LogicalValue::False);
        auto it = m_functionMap.find(input);
        if (it != m_functionMap.end())
        {
            result = it->second;
        }
        return result;
    }

    unsigned int getNumberOfOnes(Minterm const value) const
    {
        unsigned int count=0;
        for(Minterm temp = value; temp > 0; temp >>= 1)
        {
            if(temp & 0x01)
            {
                count++;
            }
        }
        return count;
    }

    Implicants getImplicants(unsigned int degree, unsigned int cubeSize) const
    {
        Implicants result;
        auto it = m_computationalTable.find(degree);
        if (it != m_computationalTable.end())
        {
            ImplicantsMap const& implicantsMap(it->second);
            auto it2 = implicantsMap.find(cubeSize);
            if (it2 != implicantsMap.end())
            {
                Implicants const& implicants(it2->second);
                implicants.loopAllImplicants([&](Implicant const& implicant)
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
        auto itFinal=m_computationalTable.end();
        itFinal--;
        for(auto it=m_computationalTable.begin(); it!=itFinal; it++)
        {
            ImplicantsMap const& implicantsMap(it->second);
            for(auto it2=implicantsMap.rbegin(); it2!=implicantsMap.rend(); it2++)
            {
                Implicants const& currentImplicants(it2->second);
                currentImplicants.loopAllImplicants([&](Implicant const& implicant)
                {
                    result.addFinalImplicant(implicant);
                });
            }
        }
        return result;
    }

    bool doImplicantsExistAt(unsigned int degree, unsigned int cubeSize) const
    {
        bool result(false);
        auto it = m_computationalTable.find(degree);
        if(it != m_computationalTable.end())
        {
            ImplicantsMap const& implicantsMap(it->second);
            result = implicantsMap.find(cubeSize) != implicantsMap.end();
        }
        return result;
    }

    void setInputOutput(Minterm const input, LogicalValue const output)
    {
        if(output == LogicalValue::True || output == LogicalValue::DontCare)
        {
            m_functionMap.emplace(input, output);
        }
    }
    void fillComputationalTableWithMintermsForZeroCube()
    {
        for(auto const & mintermOutputPair : m_functionMap)
        {
            addMintermForZeroCube(mintermOutputPair.first);
        }
    }

    void findCombinationOfImplicants(unsigned int degree, unsigned int cubeSize)
    {
        if(degree+1<m_computationalTable.size())
        {
            Implicants const& implicants1(m_computationalTable[degree][cubeSize]);
            Implicants const& implicants2(m_computationalTable[degree+1][cubeSize]);
            implicants1.loopAllImplicants([&](Implicant const& implicant1)
            {
                implicants2.loopAllImplicants([&](Implicant const& implicant2)
                {
                    if(implicant1.isCompatible(implicant2))
                    {
                        m_computationalTable[degree][cubeSize+1].addImplicant(implicant1+implicant2);
                    }
                });
            });
        }
    }

    void findAllCombinations()
    {
        unsigned int cubeSize=0;
        bool areAllCombinationsFound(false);
        while(!areAllCombinationsFound)
        {
            bool isCombinationFound(false);
            for(unsigned int degree=0; degree+1<m_computationalTable.size(); degree++)
            {
                findCombinationOfImplicants(degree, cubeSize);
                isCombinationFound = isCombinationFound | doImplicantsExistAt(degree, cubeSize+1);
            }
            areAllCombinationsFound = !isCombinationFound;
            cubeSize++;
        }
        m_cubeSize = (cubeSize>0) ? cubeSize-1 : 0;
    }

    std::string getOutputTable(Implicants const& finalImplicants)
    {
        std::vector<Minterm> inputsWithTrue;
        for(auto inputOutputPair : m_functionMap)
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
            ss<<"0x"<<input;
            displayTable.getLastRow().addCell(ss.str());
        }
        finalImplicants.loopAllImplicants([&](Implicant const& implicant)
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

    void addMintermForZeroCube(Minterm const& minterm)
    {
        unsigned int numberOfOnes = getNumberOfOnes(minterm);
        Implicant implicant;
        implicant.addMinterm(minterm);
        m_computationalTable[numberOfOnes][0].addImplicant(implicant);
    }

    unsigned int m_cubeSize;
    FunctionsMap m_functionMap;
    ComputationalTable m_computationalTable; // https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm};

}
}
