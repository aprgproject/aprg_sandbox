#pragma once

#include <algorithm>
#include <array>
#include <numeric>

namespace alba
{

template <unsigned int SIZE>
class WeightedUnionFind
{
public:
    WeightedUnionFind()
        : m_ids()
        , m_sizesOfRoots()
        , m_count(SIZE)
    {
        std::iota(m_ids.begin(), m_ids.end(), 0U);
        std::fill(m_sizesOfRoots.begin(), m_sizesOfRoots.end(), 1U);
    }

    unsigned int getCount() const
    {
        return m_count;
    }

    bool isConnected(unsigned int const id1, unsigned int const id2) const
    {
        return getRoot(id1) == getRoot(id2);
    }

    unsigned int getRoot(unsigned int const id) const
    {
        unsigned int root(id);
        unsigned int currentRoot(m_ids.at(id));
        while(root != currentRoot)
        {
            currentRoot = m_ids.at(id);
            root = currentRoot;
        }
        return root;
    }

    void connect(unsigned int const id1, unsigned int const id2)
    {
        unsigned int root1(getRoot(id1));
        unsigned int root2(getRoot(id2));
        if(root1 != root2)
        {
            // make smaller root point to larger one
            if(m_sizesOfRoots.at(root1) < m_sizesOfRoots.at(root2))
            {
                m_ids[root1] = root2;
                m_sizesOfRoots[root2] += m_sizesOfRoots.at(root1);
            }
            else
            {
                m_ids[root2] = root1;
                m_sizesOfRoots[root1] += m_sizesOfRoots.at(root2);
            }
            m_count--;
        }
    }

private:
    std::array<unsigned int, SIZE> m_ids;
    std::array<unsigned int, SIZE> m_sizesOfRoots;
    unsigned int m_count;
};

}
