#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <array>
#include <numeric>

namespace alba
{

namespace algorithm
{

template <typename Object, unsigned int SIZE>
class QuickFind : public BaseUnionFind<Object>
{
public:
    QuickFind()
        : m_roots()
        , m_numberOfUnconnected(SIZE)
    {
        initialize();
    }

    bool isConnected(Object const& object1, Object const& object2) const override    {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override
    {
        return m_roots.at(object);
    }

    void connect(Object const& object1, Object const& object2) override // runs in linear time (too expensive it should take constant/logarithmic time)
    {
        Object root1(getRoot(object1));
        Object root2(getRoot(object2));
        if(root1 != root2)
        {
            replaceAllOldRootsWithNewRoot(root2, root1); // this is an eager approach (every connect -> update new root to all old roots)
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
        std::iota(m_roots.begin(), m_roots.end(), 0);
    }

    void replaceAllOldRootsWithNewRoot(Object const& oldRoot, Object const& newRoot)
    {
        for(unsigned int i=0; i<SIZE; i++)
        {            if(m_roots[i] == oldRoot)
            {
                m_roots[i] = newRoot;
            }
        }
    }

    std::array<Object, SIZE> m_roots;
    unsigned int m_numberOfUnconnected;
};

}

}
