#pragma once

#include <set>
#include <sstream>
#include <string>

namespace alba
{

namespace algorithm
{

template <typename Minterm>
class Implicant
{
public:
    using Minterms = std::set<Minterm>;

    bool operator==(Implicant const& implicant) const
    {
        return m_minterms == implicant.m_minterms;
    }

    bool operator<(Implicant const& implicant) const
    {
        return  m_minterms < implicant.m_minterms;
    }

    Implicant operator+(Implicant const& implicant) const
    {
        Implicant result;
        for(Minterm const& minterm : m_minterms)
        {
            result.addMinterm(minterm);
        }
        for(Minterm const& minterm : implicant.m_minterms)
        {
            result.addMinterm(minterm);
        }
        return result;
    }

    bool isCompatible(Implicant const& implicant) const
    {
        unsigned int length(std::max(getLengthOfEquivalentString(), implicant.getLengthOfEquivalentString()));
        std::string string1(getEquivalentString(length));
        std::string string2(implicant.getEquivalentString(length));
        bool result(true);
        unsigned int difference=0;
        for(unsigned int i=0; i<length; i++)
        {
            if(string1[i] != string2[i])
            {
                if(string1[i] == '-' || string2[i] == '-')
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
        }
        return result;
    }

    bool isSubset(Implicant const& implicant) const
    {
        bool result(false);
        if(m_minterms.size() <= implicant.m_minterms.size())
        {
            result = true;
            for(Minterm const& minterm : m_minterms)
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

    bool isSuperset(Minterm const& minterm) const
    {
        bool result(false);
        if(!m_minterms.empty())
        {
            auto it = m_minterms.find(minterm);
            result = it != m_minterms.end();
        }
        return result;
    }

    unsigned int getLengthOfEquivalentString() const
    {
        unsigned int orResult(getOrResultOfMinterms());
        unsigned int length=0;
        for(; orResult > 0; orResult >>= 1)
        {
            length++;
        }
        return length;
    }

    std::string getEquivalentString() const
    {
        return getEquivalentString(getLengthOfEquivalentString());
    }

    std::string getEquivalentString(unsigned int const length) const
    {
        std::string booleanEquivalent;
        if(!m_minterms.empty() && length>0)
        {
            Minterm xorResult(getAndResultOfMinterms() ^ getOrResultOfMinterms());
            Minterm displayBits(getFirstMinterm());
            Minterm mask = 0x01 << (length-1);
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

    std::string getMintermString() const
    {
        std::stringstream mintermString;
        for(Minterm const& minterm : m_minterms)
        {
            mintermString<<minterm<<"|";
        }
        return mintermString.str();
    }

    Minterm getFirstMinterm() const
    {
        Minterm result(0);
        if(!m_minterms.empty())
        {
            result = *(m_minterms.begin());
        }
        return result;
    }

    Minterm getAndResultOfMinterms() const
    {
        Minterm andResult(getFirstMinterm());
        for(Minterm const& minterm : m_minterms)
        {
            andResult = andResult & minterm;
        }
        return andResult;
    }

    Minterm getOrResultOfMinterms() const
    {
        Minterm orResult(getFirstMinterm());
        for(Minterm const& minterm : m_minterms)
        {
            orResult = orResult | minterm;
        }
        return orResult;
    }

    void addMinterm(Minterm const& minterm)
    {
        m_minterms.emplace(minterm);
    }

private:
    Minterms m_minterms;
};

}

}
