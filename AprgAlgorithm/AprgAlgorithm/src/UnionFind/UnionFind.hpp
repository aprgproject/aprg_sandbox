#pragma once

#include <array>
#include <numeric>

namespace alba
{
template <unsigned int SIZE>
class UnionFind
{public:
    UnionFind()
        : m_ids()
        , m_count(SIZE)
    {
        std::iota(m_ids.begin(), m_ids.end(), 0);
    }
    unsigned int getCount() const
    {
        return m_count;
    }
    bool isConnected(unsigned int const id1, unsigned int const id2) const
    {
        return getIdEquivalent(id1) == getIdEquivalent(id2);
    }
    unsigned int getIdEquivalent(unsigned int const id) const
    {
        return m_ids.at(id);
    }

    void connect(unsigned int const id1, unsigned int const id2)
    {
        unsigned int id1Equivalent(getIdEquivalent(id1));
        unsigned int id2Equivalent(getIdEquivalent(id2));
        if(id1Equivalent != id2Equivalent)
        {
            for(unsigned int i=0; i<SIZE; i++)
            {
                if(m_ids[i] == id2Equivalent)
                {
                    m_ids[i] = id1Equivalent;
                }
            }
            m_count--;
        }
    }

private:
    std::array<unsigned int, SIZE> m_ids;
    unsigned int m_count;
};

}