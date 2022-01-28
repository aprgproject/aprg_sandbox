#pragma once

#include <UnionFind/BaseUnionFind.hpp>

#include <algorithm>
#include <array>
#include <numeric>

namespace alba
{

template <typename Object, unsigned int SIZE>
class WeightedUnionFind : public BaseUnionFind<Object>
{
public:
    WeightedUnionFind()
        : m_relativeRoots()
        , m_sizesOfRoots()
        , m_numberOfUnconnected(SIZE)
    {
        std::iota(m_relativeRoots.begin(), m_relativeRoots.end(), 0);
        std::fill(m_sizesOfRoots.begin(), m_sizesOfRoots.end(), 1U);
    }

    bool isConnected(Object const& object1, Object const& object2) const override
    {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override
    {
        //Continuously find relative root until its equal to the previous root
        Object result(object);
        Object currentRoot(m_relativeRoots.at(object));
        while(result != currentRoot)
        {
            result = currentRoot;
            currentRoot = m_relativeRoots.at(result);
        }        return result;
    }

    void connect(Object const& object1, Object const& object2) override
    {
        Object root1(getRoot(object1));
        Object root2(getRoot(object2));
        if(root1 != root2)
        {
            connectRootsBasedOnSize(root2, root1);
            m_numberOfUnconnected--;
        }
    }

    unsigned int getNumberOfUnconnected() const
    {
        return m_numberOfUnconnected;
    }

private:

    void connectRootsBasedOnSize(Object root2, Object root1)
    {
        // assign the root of the smaller root to the larger root (to make it flatter)
        if(m_sizesOfRoots.at(root1) < m_sizesOfRoots.at(root2))
        {
            m_relativeRoots[root1] = root2;
            m_sizesOfRoots[root2] += m_sizesOfRoots.at(root1);
        }
        else
        {
            m_relativeRoots[root2] = root1;
            m_sizesOfRoots[root1] += m_sizesOfRoots.at(root2);
        }
    }

    std::array<Object, SIZE> m_relativeRoots;
    std::array<unsigned int, SIZE> m_sizesOfRoots;
    unsigned int m_numberOfUnconnected;
};

}
