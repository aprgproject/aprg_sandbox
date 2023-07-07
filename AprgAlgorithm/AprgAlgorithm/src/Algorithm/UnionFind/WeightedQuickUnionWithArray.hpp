#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <array>
#include <numeric>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Object, int SIZE>
class WeightedQuickUnionWithArray : public BaseUnionFind<Object> {
public:
    using RootArray = std::array<Object, SIZE>;
    using RootVector = std::vector<Object>;
    using SizeArray = std::array<int, SIZE>;

    WeightedQuickUnionWithArray() : m_relativeRoots(), m_sizesOfRoots() { initialize(); }

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

    RootArray const& getRelativeRootArray() const { return m_relativeRoots; }

    SizeArray const& getSizesOfRootsArray() const { return m_sizesOfRoots; }

private:
    void initialize() {
        // runs in linear time
        std::iota(m_relativeRoots.begin(), m_relativeRoots.end(), 0);
        std::fill(m_sizesOfRoots.begin(), m_sizesOfRoots.end(), 1);
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

    RootArray m_relativeRoots;
    SizeArray m_sizesOfRoots;
};

}  // namespace algorithm

}  // namespace alba

// Proof
// Depth of any node x is at most log2 (SIZE)
// When does the depth of x increase? Increase by 1 when tree T1 containing x is merged into another tree T2.
// -> The size of the tree containing x [at least doubles] since size of T2 >= size of T1
// -> Size of the tree containing x [can double] at most log2 times.

// Other discussions:
// The efficiency of the union-find structure depends on how the sets are joined.
// It turns out that we can follow a simple strategy:
// always connect the representative of the smaller set to the representative of the larger set (if equal, we can make
// an arbitrary choice). Using this strategy, the length of any chain will be O(log n).
