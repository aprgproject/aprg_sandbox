#pragma once

#include <Algorithm/Graph/Tree/ChildrenInTree.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class MinimumNodeCoverForTree {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using SetOfVerticesWithVertex = typename GraphTypes<Vertex>::SetOfVertices;
    using ChildrenInTreeWithVertex = ChildrenInTree<Vertex>;
    using Count = unsigned int;
    using VertexToCountMap = std::map<Vertex, Count>;
    using VertexToSetOfVerticesMap = std::map<Vertex, SetOfVerticesWithVertex>;
    static constexpr unsigned int UNUSED_COUNT = std::numeric_limits<Count>::max();

    MinimumNodeCoverForTree(BaseUndirectedGraphWithVertex const& nAryTreeGraph, Vertex const rootOfTree)
        : m_nAryTreeGraph(nAryTreeGraph), m_rootOfTree(rootOfTree), m_childrenInTree(m_nAryTreeGraph, m_rootOfTree) {}

    Count getMinimumNodeCoverSize() const {
        Count result(0);
        if (!m_nAryTreeGraph.isEmpty()) {
            VertexToCountMap vertexToCountMap;
            result = getMinimumNodeCoverSizeUsingMemoizationDP(vertexToCountMap, m_rootOfTree);
        }
        return result;
    }

    SetOfVerticesWithVertex getMinimumNodeCover() const {
        SetOfVerticesWithVertex result;
        if (!m_nAryTreeGraph.isEmpty()) {
            VertexToSetOfVerticesMap vertexToMinimumSetMap;
            result = getMinimumNodeCoverUsingMemoizationDP(vertexToMinimumSetMap, m_rootOfTree);
        }
        return result;
    }

private:
    Count getMinimumNodeCoverSizeUsingMemoizationDP(VertexToCountMap& vertexToCountMap, Vertex const vertex) const {
        auto it = vertexToCountMap.find(vertex);
        if (it == vertexToCountMap.cend()) {
            Count countIfVertexIsIncluded(1);
            Count countIfVertexIsNotIncluded(0);
            for (Vertex const child : m_childrenInTree.getChildren(vertex)) {
                Count childrenCount = getMinimumNodeCoverSizeUsingMemoizationDP(vertexToCountMap, child);
                Count grandChildrenCount = 1;
                for (Vertex const grandChild : m_childrenInTree.getChildren(child)) {
                    grandChildrenCount += getMinimumNodeCoverSizeUsingMemoizationDP(vertexToCountMap, grandChild);
                }
                countIfVertexIsIncluded += childrenCount;
                countIfVertexIsNotIncluded += grandChildrenCount;
            }
            Count result = std::min(countIfVertexIsIncluded, countIfVertexIsNotIncluded);
            vertexToCountMap.emplace(vertex, result);
            return result;
        } else {
            return it->second;
        }
    }

    SetOfVerticesWithVertex getMinimumNodeCoverUsingMemoizationDP(
        VertexToSetOfVerticesMap& vertexToMinimumSetMap, Vertex const vertex) const {
        auto it = vertexToMinimumSetMap.find(vertex);
        if (it == vertexToMinimumSetMap.cend()) {
            SetOfVerticesWithVertex setIfVertexIsIncluded{vertex};
            SetOfVerticesWithVertex setIfVertexIsNotIncluded;
            for (Vertex const child : m_childrenInTree.getChildren(vertex)) {
                SetOfVerticesWithVertex childSet(getMinimumNodeCoverUsingMemoizationDP(vertexToMinimumSetMap, child));
                copy(
                    childSet.cbegin(), childSet.cend(), inserter(setIfVertexIsIncluded, setIfVertexIsIncluded.begin()));
                setIfVertexIsNotIncluded.emplace(child);
                for (Vertex const grandChild : m_childrenInTree.getChildren(child)) {
                    SetOfVerticesWithVertex grandChildSet(
                        getMinimumNodeCoverUsingMemoizationDP(vertexToMinimumSetMap, grandChild));
                    copy(
                        grandChildSet.cbegin(), grandChildSet.cend(),
                        inserter(setIfVertexIsNotIncluded, setIfVertexIsNotIncluded.begin()));
                }
            }
            if (setIfVertexIsIncluded.size() <= setIfVertexIsNotIncluded.size()) {
                vertexToMinimumSetMap.emplace(vertex, setIfVertexIsIncluded);
                return setIfVertexIsIncluded;
            } else {
                vertexToMinimumSetMap.emplace(vertex, setIfVertexIsNotIncluded);
                return setIfVertexIsNotIncluded;
            }
        } else {
            return it->second;
        }
    }
    BaseUndirectedGraphWithVertex const& m_nAryTreeGraph;
    Vertex m_rootOfTree;
    ChildrenInTreeWithVertex m_childrenInTree;
};

}  // namespace algorithm

}  // namespace alba

// Minimum Node Cover For Tree

// A vertex cover of an undirected graph is a subset of its vertices such that
// for every edge (u, v) of the graph, either ‘u’ or ‘v’ is in vertex cover.
// Although the name is Vertex Cover, the set covers all edges of the given graph.
// The problem to find minimum size vertex cover of a graph is NP complete.
// But it can be solved in polynomial time for trees.
