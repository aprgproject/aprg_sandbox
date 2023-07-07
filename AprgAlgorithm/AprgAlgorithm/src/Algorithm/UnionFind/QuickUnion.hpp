#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <array>
#include <numeric>

namespace alba {

namespace algorithm {

template <typename Object, int SIZE>
class QuickUnion : public BaseUnionFind<Object> {
public:
    using RootArray = std::array<Object, SIZE>;

    QuickUnion() : m_relativeRoots() { initialize(); }

    bool isConnected(Object const& object1, Object const& object2) const override {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override {
        // worst case (tall tree) runs in linear time (too expensive it should take constant/logarithmic time)
        // this is a lazy approach (every getRoot() -> check relative roots until main root is found)
        // Continuously find relative root until main root is found (it needs to be equal to the previous root)
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots[object]);
        while (currentRoot != nextRoot) {
            currentRoot = nextRoot;
            nextRoot = m_relativeRoots[currentRoot];
        }
        return currentRoot;
    }

    void connect(Object const& object1, Object const& object2) override {
        Object root1(getRoot(object1));
        Object root2(getRoot(object2));
        if (root1 != root2) {
            m_relativeRoots[root1] = root2;
            // the relative root tree might take too tall
            //(check weighted union find for implementation that consider sizes)
        }
    }

    RootArray const& getRelativeRootArray() const { return m_relativeRoots; }

private:
    void initialize() {
        // runs in linear time
        std::iota(m_relativeRoots.begin(), m_relativeRoots.end(), 0);
    }
    RootArray m_relativeRoots;
};
}  // namespace algorithm

}  // namespace alba
