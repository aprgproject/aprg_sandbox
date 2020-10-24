#include "QuineMcCluskey.hpp"

#include <User/AlbaDisplayTable.hpp>

#include <sstream>

using namespace std;

namespace alba
{

Implicant Implicant::operator+(Implicant const& implicant) const
{
    Implicant result;
    for(unsigned int minterm : m_minterms)
    {
        result.addMinterm(minterm);
    }
    for(unsigned int minterm : implicant.m_minterms)
    {
        result.addMinterm(minterm);
    }
    return result;
}

bool Implicant::operator==(Implicant const& implicant) const
{
    return m_minterms == implicant.m_minterms;
}

bool Implicant::operator<(Implicant const& implicant) const
{
    return getFirstMinterm() < implicant.getFirstMinterm();
}

bool Implicant::isCompatible(Implicant const& implicant) const
{
    unsigned int length(std::max(getLengthOfEquivalentString(), implicant.getLengthOfEquivalentString()));
    string string1(getEquivalentString(length));
    string string2(implicant.getEquivalentString(length));
    bool result(true);
    unsigned int difference=0;
    for(unsigned int i=0; i<length; i++)
    {
        if(string1[i] == string2[i])
        {

        }
        else if(string1[i] == '-' || string2[i] == '-')
        {
            result = false;
            break;
        }
        else if(difference > 1)
        {
            result = false;
            break;
        }
        else
        {
            difference++;
        }
    }
    return result;
}

bool Implicant::isSubset(Implicant const& implicant) const
{
    bool result(false);
    if(m_minterms.size() <= implicant.m_minterms.size())
    {
        result = true;
        for(unsigned int minterm : m_minterms)
        {
            auto it = implicant.m_minterms.find(minterm);
            if (it == implicant.m_minterms.end())
            {
                result=false;
                break;
            }
        }
    }
    return result;
}

bool Implicant::isSuperset(unsigned int minterm) const
{
    bool result(false);
    if(m_minterms.size()>0)
    {
        auto it = m_minterms.find(minterm);
        if (it == m_minterms.end())
        {
            result = false;
        }
        else
        {
            result = true;
        }
    }
    return result;
}

unsigned int Implicant::getLengthOfEquivalentString() const
{
    unsigned int orResult(getOrResultOfMinterms());
    unsigned int length=0;
    for(; orResult > 0; orResult >>= 1)
    {
        length++;
    }
    return length;
}

string Implicant::getEquivalentString() const
{
    return getEquivalentString(getLengthOfEquivalentString());
}

string Implicant::getEquivalentString(unsigned int length) const
{
    string booleanEquivalent;
    if(m_minterms.size()>0 && length>0)
    {
        unsigned int xorResult(getAndResultOfMinterms() ^ getOrResultOfMinterms());
        unsigned int displayBits(getFirstMinterm());
        unsigned int mask = 0x01 << (length-1);
        for(unsigned int i=0; i<length; i++)
        {
            if(xorResult & mask)
            {
                booleanEquivalent.push_back('-');
            }
            else if(displayBits & mask)
            {
                booleanEquivalent.push_back('1');
            }
            else
            {
                booleanEquivalent.push_back('0');
            }
            mask >>= 1;
        }
    }
    return booleanEquivalent;
}

string Implicant::getMintermString() const
{
    stringstream mintermString;
    for(unsigned int minterm : m_minterms)
    {
        mintermString<<minterm<<"|";
    }
    return mintermString.str();
}

unsigned int Implicant::getFirstMinterm() const
{
    unsigned int result(0);
    if(m_minterms.size()>0)
    {
        result = *m_minterms.begin();
    }
    return result;
}

unsigned int Implicant::getAndResultOfMinterms() const
{
    unsigned int andResult(getFirstMinterm());
    for(unsigned int minterm : m_minterms)
    {
        andResult = andResult & minterm;
    }
    return andResult;
}

unsigned int Implicant::getOrResultOfMinterms() const
{
    unsigned int orResult(getFirstMinterm());
    for(unsigned int minterm : m_minterms)
    {
        orResult = orResult | minterm;
    }
    return orResult;
}

void Implicant::addMinterm(unsigned int minterm)
{
    m_minterms.emplace(minterm);
}

void Implicants::loopAllImplicants(std::function<void(Implicant const&)> doFunction) const
{
    for(Implicant const& implicant : m_implicants)
    {
        doFunction(implicant);
    }
}

unsigned int Implicants::getSize() const
{
    return m_implicants.size();
}

string Implicants::getImplicantsString() const
{
    stringstream implicantString;
    int index=0;
    for(Implicant const& implicant : m_implicants)
    {
        implicantString<<"["<<index<<" : "<<implicant.getMintermString()<<"], ";
        index++;
    }
    return implicantString.str();
}

void Implicants::addImplicant(Implicant const& implicant)
{
    bool isExisting(false);
    for(Implicant const& iteratorImplicant : m_implicants)
    {
        if(iteratorImplicant == implicant)
        {
            isExisting = true;
            break;
        }
    }
    if(!isExisting)
    {
        m_implicants.emplace_back(implicant);
    }
}

void Implicants::addFinalImplicant(Implicant const& implicant)
{
    bool isAlreadyRepresented(false);
    for(Implicant const& iteratorImplicant : m_implicants)
    {
        if(implicant.isSubset(iteratorImplicant))
        {
            isAlreadyRepresented = true;
            break;
        }
    }
    if(!isAlreadyRepresented)
    {
        m_implicants.emplace_back(implicant);
    }
}


QuineMcCluskey::QuineMcCluskey()
{}

LogicalValue QuineMcCluskey::getOutput(unsigned int const input) const
{
    LogicalValue result(LogicalValue::False);
    auto it = m_functionMap.find(input);
    if (it != m_functionMap.end())
    {
        result = it->second;
    }
    return result;
}

unsigned int QuineMcCluskey::getNumberOfOnes(unsigned int const value) const
{
    int count=0;
    for(unsigned int temp = value; temp > 0; temp >>= 1)
    {
        if(temp & 0x01)
        {
            count++;
        }
    }
    return count;
}

Implicants QuineMcCluskey::getImplicants(unsigned int degree, unsigned int cubeSize) const
{
    Implicants result;
    auto it = m_computationalTable.find(degree);
    if (it != m_computationalTable.end())
    {
        ImplicantsMap const& implicantsMap(it->second);
        auto it2 = implicantsMap.implicantsMap.find(cubeSize);
        if (it2 != implicantsMap.implicantsMap.end())
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

Implicants QuineMcCluskey::getAllFinalImplicants() const
{
    Implicants result;
    for(int cubeSize=(int)m_cubeSize; cubeSize>=0; cubeSize--)
    {
        for(unsigned int degree=0; degree+1<m_computationalTable.size(); degree++)
        {
            auto it = m_computationalTable.find(degree);
            if (it != m_computationalTable.end())
            {
                ImplicantsMap const& implicantsMap(it->second);
                auto it2 = implicantsMap.implicantsMap.find(cubeSize);
                if (it2 != implicantsMap.implicantsMap.end())
                {
                    Implicants const& currentImplicants(it2->second);
                    currentImplicants.loopAllImplicants([&](Implicant const& implicant)
                    {
                        result.addFinalImplicant(implicant);
                    });
                }
            }
        }
    }
    return result;
}

void QuineMcCluskey::setInputOutput(unsigned int const input, LogicalValue const output)
{
    if(output == LogicalValue::True || output == LogicalValue::DontCare)
    {
        m_functionMap.emplace(input, output);
    }
}

void QuineMcCluskey::fillComputationalTableWithMintermsForZeroCube()
{
    for(auto const & mintermOutputPair : m_functionMap)
    {
        addMintermForZeroCube(mintermOutputPair.first);
    }
}

void QuineMcCluskey::findCombinationOfImplicants(unsigned int degree, unsigned int cubeSize)
{
    if(degree+1<m_computationalTable.size())
    {
        Implicants const& implicants1(m_computationalTable[degree].implicantsMap[cubeSize]);
        Implicants const& implicants2(m_computationalTable[degree+1].implicantsMap[cubeSize]);
        implicants1.loopAllImplicants([&](Implicant const& implicant1)
        {
            implicants2.loopAllImplicants([&](Implicant const& implicant2)
            {
                if(implicant1.isCompatible(implicant2))
                {
                    m_computationalTable[degree].implicantsMap[cubeSize+1].addImplicant(implicant1+implicant2);
                }
            });
        });
    }
}

void QuineMcCluskey::findAllCombinations()
{
    unsigned int cubeSize=0;
    bool areAllCombinationsFound(false);
    while(!areAllCombinationsFound)
    {
        unsigned int count=0;
        for(unsigned int degree=0; degree+1<m_computationalTable.size(); degree++)
        {
            findCombinationOfImplicants(degree, cubeSize);
            count += m_computationalTable[degree].implicantsMap[cubeSize].getSize();
        }
        cubeSize++;
        areAllCombinationsFound = count==0;
    }
    m_cubeSize = (cubeSize>0) ? cubeSize-1 : 0;
}

string QuineMcCluskey::getOutputTable(Implicants const& finalImplicants)
{
    vector<unsigned int> inputsWithTrue;
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
        stringstream ss;
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

void QuineMcCluskey::addMintermForZeroCube(unsigned int minterm)
{
    unsigned int numberOfOnes = getNumberOfOnes(minterm);
    Implicant implicant;
    implicant.addMinterm(minterm);
    m_computationalTable[numberOfOnes].implicantsMap[0].addImplicant(implicant);
}

}
