#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>
#include <bitset>
#include <numeric>
#include <set>
#include <sstream>
#include <string>

namespace alba
{

namespace booleanAlgebra
{

template <typename Minterm>
class Implicant
{
public:
    using MintermsInitializerList = std::initializer_list<Minterm>;
    using Minterms = std::set<Minterm>;

    Implicant()=default;

    Implicant(MintermsInitializerList const& minterms)
        : m_minterms(minterms)
    {}

    bool operator==(Implicant const& second) const
    {
        return m_minterms == second.m_minterms;
    }

    bool operator!=(Implicant const& second) const
    {
        Implicant const& first(*this);
        return !(first==second);
    }

    bool operator<(Implicant const& second) const
    {
        return  m_minterms < second.m_minterms;
    }

    Implicant operator+(Implicant const& implicant) const
    {
        Implicant result;
        result.m_minterms = m_minterms;
        std::copy(implicant.m_minterms.cbegin(), implicant.m_minterms.cend(), std::inserter(result.m_minterms, result.m_minterms.begin()));
        return result;
    }

    bool isCompatible(Implicant const& implicant) const
    {
        unsigned int commonLength(std::max(getMaxLengthOfEquivalentString(), implicant.getMaxLengthOfEquivalentString()));
        std::string string1(getEquivalentString(commonLength));
        std::string string2(implicant.getEquivalentString(commonLength));
        bool result(true);
        unsigned int difference=0;
        for(unsigned int i=0; i<commonLength; i++)
        {
            if(string1.at(i) != string2.at(i))
            {
                if(string1.at(i) == '-' || string2.at(i) == '-')
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
                if (it == implicant.m_minterms.cend())
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

    Minterms const& getMinterms() const
    {
        return m_minterms;
    }

    std::string getEquivalentString() const
    {
        return getEquivalentString(getMaxLengthOfEquivalentString());
    }

    std::string getEquivalentString(unsigned int const length) const
    {
        std::string booleanEquivalent;
        if(!m_minterms.empty() && length>0)
        {
            constexpr unsigned int NUMBER_OF_BITS(AlbaBitValueUtilities<Minterm>::getNumberOfBits());
            std::bitset<NUMBER_OF_BITS> xorBits(performAndOperationOfAllMinterms() ^ performOrOperationOfAllMinterms());
            std::bitset<NUMBER_OF_BITS> displayBits(getFirstMinterm());
            for(unsigned int i=0; i<length; i++)
            {
                unsigned int bitIndex = length-i-1;
                if(xorBits[bitIndex])
                {
                    booleanEquivalent.push_back('-');
                }
                else if(displayBits[bitIndex])
                {
                    booleanEquivalent.push_back('1');
                }
                else
                {
                    booleanEquivalent.push_back('0');
                }
            }
        }
        return booleanEquivalent;
    }

    std::string getMintermString() const
    {
        std::stringstream result;
        for(Minterm const& minterm : m_minterms)
        {
            result << minterm << "|";
        }
        return result.str();
    }

    void addMinterm(Minterm const& minterm)
    {
        m_minterms.emplace(minterm);
    }

private:

    unsigned int getMaxLengthOfEquivalentString() const
    {
        unsigned int result=0;
        unsigned int orResult(performOrOperationOfAllMinterms());
        for(; orResult > 0; orResult >>= 1)
        {
            result++;
        }
        return result;
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

    Minterm performAndOperationOfAllMinterms() const
    {
        constexpr Minterm INITIAL_VALUE(AlbaBitValueUtilities<Minterm>::getAllOnes());
        return std::accumulate(m_minterms.cbegin(), m_minterms.cend(), INITIAL_VALUE, [](Minterm const& minterm1, Minterm const& minterm2)
        {
            return minterm1 & minterm2;
        });
    }

    Minterm performOrOperationOfAllMinterms() const
    {
        constexpr Minterm INITIAL_VALUE(0);
        return std::accumulate(m_minterms.cbegin(), m_minterms.cend(), INITIAL_VALUE, [](Minterm const& minterm1, Minterm const& minterm2)
        {
            return minterm1 | minterm2;
        });
    }

    friend std::ostream & operator<<(std::ostream & out, Implicant<Minterm> const& implicant)
    {
        Minterms const& minterms(implicant.m_minterms);
        out << "'" << implicant.getEquivalentString() << " (";
        if(minterms.size() == 1)
        {
            out << *(minterms.cbegin());
        }
        else
        {
            containerHelper::saveContentsToStream(out, minterms, containerHelper::StreamFormat::String);
        }
        out << ")'";
        return out;
    }

    Minterms m_minterms;
};

}

}
