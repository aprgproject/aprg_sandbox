#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Object>
class QuickUnionWithPathCompressionWithVector : public BaseUnionFind<Object>
{
public:
    using RootVector = std::vector<Object>;

    QuickUnionWithPathCompressionWithVector(unsigned int const maximumSize)
        : m_relativeRoots()
    {
        initialize(maximumSize);
    }

    bool isConnected(Object const& object1, Object const& object2) const override
    {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override
    {
        // worst case (tall tree) runs in linear time (too expensive it should take constant/logarithmic time)
        // this is a lazy approach (every getRoot() -> check relative roots until main root is found)
        // Continuously find relative root until main root is found (it needs to be equal to the previous root)
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots.at(object));
        while(currentRoot != nextRoot)
        {
            currentRoot = nextRoot;
            nextRoot = m_relativeRoots.at(currentRoot);
        }
        return currentRoot;
    }

    Object getRootWithPathCompressionTwoPass(Object const& object) // no longer const
    {
        std::vector<Object> relativeRoots;
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots.at(object));

        while(currentRoot != nextRoot)
        {
            currentRoot = nextRoot;
            relativeRoots.emplace_back(nextRoot);
            nextRoot = m_relativeRoots.at(currentRoot);
        }
        for(Object const& relativeRoot : relativeRoots) // set found root to all examined relative roots -> makes the tree really flat (Hopcroft Ulman Tarjan proof -> almost linear)
        {
            m_relativeRoots[relativeRoot] = currentRoot;
        }
        return currentRoot;
    }

    void connect(Object const& object1, Object const& object2) override
    {
        Object root1(getRootWithPathCompressionTwoPass(object1));
        Object root2(getRootWithPathCompressionTwoPass(object2));
        if(root1 != root2)
        {
            m_relativeRoots[root1] = root2; // the relative root tree might take too tall (check weighted union find for implementation that consider sizes)
        }
    }

    RootVector const& getRelativeRootVector() const
    {
        return m_relativeRoots;
    }

    RootVector & getRelativeRootVectorReference()
    {
        return m_relativeRoots;
    }

private:

    void initialize(unsigned int const maximumSize) // runs in linear time
    {
        m_relativeRoots.reserve(maximumSize);
        for(unsigned int i=0; i<maximumSize; i++)
        {
            m_relativeRoots.emplace_back(i);
        }
        m_relativeRoots.shrink_to_fit();
    }

    RootVector m_relativeRoots;
};

}

}
