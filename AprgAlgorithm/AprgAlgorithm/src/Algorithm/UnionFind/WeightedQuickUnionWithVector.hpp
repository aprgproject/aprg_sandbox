#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <vector>

namespace alba {

namespace algorithm {

template <typename Object>
class WeightedQuickUnionWithVector : public BaseUnionFind<Object> {
public:
    using RootVector = std::vector<Object>;
    using SizeVector = std::vector<int>;

    WeightedQuickUnionWithVector(int const maximumSize) : m_relativeRoots(), m_sizesOfRoots() {
        initialize(maximumSize);
    }

    bool isConnected(Object const& object1, Object const& object2) const override {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(
        Object const& object) const override  // worst case runs in logarithmic time (base 2 log) -> acceptable
    {
        // Continuously find relative root until its equal to the previous root
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots[object]);
        while (currentRoot != nextRoot) {
            currentRoot = nextRoot;
            nextRoot = m_relativeRoots[currentRoot];
        }
        return currentRoot;
    }

    Object getRootWithPathCompressionOnePass(Object const& object)  // no longer const
    {
        Object result(object);
        while (result != m_relativeRoots[object]) {
            m_relativeRoots[object] =
                m_relativeRoots[m_relativeRoots[object]];  // make every relative root point to its grandparent
            result = m_relativeRoots[object];
        }
        return result;
    }

    Object getRootWithPathCompressionTwoPass(Object const& object)  // no longer const
    {
        RootVector relativeRoots;
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots[object]);

        while (currentRoot != nextRoot) {
            currentRoot = nextRoot;
            relativeRoots.emplace_back(nextRoot);
            nextRoot = m_relativeRoots[currentRoot];
        }
        for (Object const& relativeRoot :
             relativeRoots)  // set found root to all examined relative roots -> makes the tree really flat (Hopcroft
                             // Ulman Tarjan proof -> almost linear)
        {
            m_relativeRoots[relativeRoot] = currentRoot;
        }
        return currentRoot;
    }

    void connect(Object const& object1, Object const& object2)
        override  // worst case runs in logarithmic time because of getRoot() -> acceptable
    {
        Object root1(getRoot(object1));
        Object root2(getRoot(object2));
        if (root1 != root2) {
            connectRootsBasedOnSize(root2, root1);
        }
    }

    RootVector const& getRelativeRootVector() const { return m_relativeRoots; }

    SizeVector const& getSizesOfRootsVector() const { return m_sizesOfRoots; }

    RootVector& getRelativeRootVectorReference() { return m_relativeRoots; }

    SizeVector& getSizesOfRootsVectorReference() { return m_sizesOfRoots; }

private:
    void initialize(int const maximumSize)  // runs in linear time
    {
        m_relativeRoots.reserve(maximumSize);
        for (int i = 0; i < maximumSize; i++) {
            m_relativeRoots.emplace_back(i);
        }
        m_relativeRoots.shrink_to_fit();

        m_sizesOfRoots.resize(maximumSize, Object{1});
        m_sizesOfRoots.shrink_to_fit();
    }

    void connectRootsBasedOnSize(Object const root2, Object const root1) {
        // assign the root of the smaller root to the larger root (to make it flatter)
        if (m_sizesOfRoots[root1] < m_sizesOfRoots[root2]) {
            m_relativeRoots[root1] = root2;
            m_sizesOfRoots[root2] += m_sizesOfRoots[root1];
        } else {
            m_relativeRoots[root2] = root1;
            m_sizesOfRoots[root1] += m_sizesOfRoots[root2];
        }
    }

    RootVector m_relativeRoots;
    SizeVector m_sizesOfRoots;
};

}  // namespace algorithm

}  // namespace alba
