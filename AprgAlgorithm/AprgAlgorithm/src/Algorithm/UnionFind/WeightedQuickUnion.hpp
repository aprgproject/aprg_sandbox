#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Object, unsigned int SIZE>
class WeightedQuickUnion : public BaseUnionFind<Object>
{
public:
    WeightedQuickUnion()
        : m_relativeRoots()
        , m_sizesOfRoots()
        , m_numberOfUnconnected(SIZE)
    {
        initialize();
    }

    bool isConnected(Object const& object1, Object const& object2) const override
    {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override // worst case runs in logarithmic time (base 2 log) -> acceptable
    {
        // Continuously find relative root until its equal to the previous root
        Object result(object);
        Object currentRoot(m_relativeRoots.at(object));
        while(result != currentRoot)
        {
            result = currentRoot;
            currentRoot = m_relativeRoots.at(result);
        }
        return result;
    }

    Object getRootWithPassCompressionOnePass(Object const& object) // no longer const
    {
        Object result(object);
        while(result != m_relativeRoots.at(object))
        {
            m_relativeRoots[object] = m_relativeRoots.at(m_relativeRoots.at(object)); // make every relative root point to its grandparent
            result = m_relativeRoots.at(object);
        }
        return result;
    }

    Object getRootWithPassCompressionTwoPass(Object const& object) // no longer const
    {
        std::vector<Object> relativeRoots;
        Object mainRoot(object);
        Object currentRoot(m_relativeRoots.at(object));
        while(mainRoot != currentRoot)
        {
            mainRoot = currentRoot;
            relativeRoots.emplace_back(currentRoot);
            currentRoot = m_relativeRoots.at(mainRoot);
        }
        for(Object const& relativeRoot : relativeRoots) // set found root to all examined relative roots -> makes the tree really flat (Hopcroft Ulman Tarjan proof -> almost linear)
        {
            m_relativeRoots[relativeRoot] = mainRoot;
        }
        return mainRoot;
    }

    void connect(Object const& object1, Object const& object2) override // worst case runs in logarithmic time because of getRoot() -> acceptable
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

    void initialize() // runs in linear time
    {
        std::iota(m_relativeRoots.begin(), m_relativeRoots.end(), 0);
        std::fill(m_sizesOfRoots.begin(), m_sizesOfRoots.end(), 1U);
    }

    void connectRootsBasedOnSize(Object const root2, Object const root1)
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

// Proof
// Depth of any node x is at most log2 (SIZE)
// When does the depth of x increase? Increase by 1 when tree T1 containing x is merged into another tree T2.
// -> The size of the tree containing x [at least doubles] since size of T2 >= size of T1
// -> Size of the tree containing x [can double] at most log2 times.

// Other discussions:
// The efficiency of the union-find structure depends on how the sets are joined.
// It turns out that we can follow a simple strategy:
// always connect the representative of the smaller set to the representative of the larger set (if equal, we can make an arbitrary choice).
// Using this strategy, the length of any chain will be O(logn).

}

}
