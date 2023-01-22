#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Object>
class UnionFindForFreeIndex : public BaseUnionFind<Object>
{
public:
    using RootVector = std::vector<Object>;

    UnionFindForFreeIndex(unsigned int const maximumSize)
        : m_relativeRoots()
    {
        initialize(maximumSize);    }

    bool isConnected(Object const& object1, Object const& object2) const override
    {        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override
    {
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots.at(object));
        while(currentRoot != nextRoot)        {
            currentRoot = nextRoot;
            nextRoot = m_relativeRoots.at(currentRoot);
        }
        return currentRoot;
    }

    Object getRootWithPathCompression(Object const& object)
    {
        RootVector relativeRoots;
        Object mainRoot = getRootAndRelativeRoots(object, relativeRoots);
        saveNewRootOnRelativeRoots(mainRoot, relativeRoots);
        return mainRoot;
    }

    void connect(Object const& source, Object const& destination) override
    {
        // Path compression

        RootVector relativeRoots;
        getRootAndRelativeRoots(source, relativeRoots);
        Object mainRoot = getRootAndRelativeRoots(destination, relativeRoots);
        saveNewRootOnRelativeRoots(mainRoot, relativeRoots);
    }

    RootVector const& getRelativeRootVector() const    {
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

    Object getRootAndRelativeRoots(Object const& object, RootVector & relativeRoots) const
    {
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots.at(object));
        relativeRoots.emplace_back(currentRoot);
        while(currentRoot != nextRoot)
        {
            currentRoot = nextRoot;
            relativeRoots.emplace_back(nextRoot);
            nextRoot = m_relativeRoots.at(currentRoot);
        }
        return currentRoot;
    }

    void  saveNewRootOnRelativeRoots(Object const& newRoot, RootVector const& relativeRoots)
    {
        for(Object const& relativeRoot : relativeRoots)
        {
            m_relativeRoots[relativeRoot] = newRoot;
        }
    }

    RootVector m_relativeRoots;
};
}

}