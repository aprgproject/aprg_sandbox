#pragma once

#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class LowestCommonAncestors {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using Depths = std::vector<int>;
    using VertexToIndexMap = std::map<Vertex, int>;

    LowestCommonAncestors(BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree)
        : m_graph(graph), m_rootOfTree(rootOfTree) {
        initializeIfNeeded();
    }

    Vertices const& getVerticesInTreeOrder() const { return m_verticesInTreeOrder; }

    Depths const& getDepths() const { return m_depths; }

    Vertex getLowestCommonAncestor(Vertex const& vertex1, Vertex const& vertex2) const {
        Vertex result{};
        auto it1 = m_vertexToFirstIndexMap.find(vertex1);
        auto it2 = m_vertexToFirstIndexMap.find(vertex2);
        if (it1 != m_vertexToFirstIndexMap.cend() && it2 != m_vertexToFirstIndexMap.cend()) {
            int vertexIndex1 = it1->second;
            int vertexIndex2 = it2->second;
            int lowestCommonAncestorIndex(getLowestCommonAncestorIndex(vertexIndex1, vertexIndex2));
            result = m_verticesInTreeOrder[lowestCommonAncestorIndex];
        }
        return result;
    }

    int getDistanceBetweenVertices(Vertex const& vertex1, Vertex const& vertex2) const {
        int result{};
        auto it1 = m_vertexToFirstIndexMap.find(vertex1);
        auto it2 = m_vertexToFirstIndexMap.find(vertex2);
        if (it1 != m_vertexToFirstIndexMap.cend() && it2 != m_vertexToFirstIndexMap.cend()) {
            int vertexIndex1 = it1->second;
            int vertexIndex2 = it2->second;
            int lowestCommonAncestorIndex(getLowestCommonAncestorIndex(vertexIndex1, vertexIndex2));
            result = m_depths[vertexIndex1] + m_depths[vertexIndex2] - 2 * m_depths[lowestCommonAncestorIndex];
        }
        return result;
    }

private:
    int getLowestCommonAncestorIndex(int const vertexIndex1, int const vertexIndex2) const {
        int result = vertexIndex1;
        int minimumDepth(m_depths[vertexIndex1]);
        for (int i = vertexIndex1 + 1; i <= vertexIndex2; i++) {
            int currentDepth(m_depths[i]);
            if (minimumDepth > currentDepth) {
                minimumDepth = currentDepth;
                result = i;
            }
        }
        return result;
    }

    void initializeIfNeeded() {
        if (GraphUtilities::isATree(m_graph)) {
            initialize();
        }
    }

    void initialize() { traverseStartingFromAVertex(m_rootOfTree); }

    void traverseStartingFromAVertex(Vertex const& startVertex) {
        if (m_processedVertices.isNotFound(startVertex) &&
            !m_graph.getAdjacentVerticesAt(startVertex).empty())  // dont include invalid vertex
        {
            int index(0);
            int depth(0);

            traverseUsingDfs(index, depth, startVertex);

            m_verticesInTreeOrder.shrink_to_fit();
            m_depths.shrink_to_fit();
        }
    }

    void traverseUsingDfs(int& index, int& depth, Vertex const& vertex) {
        // However, we use a different tree traversal array than before:
        // we add each node to the array always when the depth-first search walks through the node, and not only at the
        // first visit. Hence, a node that has k children appears k+1 times in the array and there are a total of 2n-1
        // nodes in the array. Tree order: parent1, child1, grandchild1, child1, parent1,

        depth++;
        m_processedVertices.putVertex(vertex);
        m_vertexToFirstIndexMap[vertex] = index;
        addVertex(index, depth, vertex);  // add vertex for tree traversal
        for (Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex)) {
            if (m_processedVertices.isNotFound(adjacentVertex)) {
                traverseUsingDfs(index, depth, adjacentVertex);
                addVertex(index, depth, vertex);  // add vertex for tree traversal
            }
        }
        depth--;
    }

    void addVertex(int& index, int const depth, Vertex const& vertex) {
        m_verticesInTreeOrder.emplace_back(vertex);
        m_depths.emplace_back(depth);
        index++;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    CheckableVerticesWithVertex m_processedVertices;
    Vertices m_verticesInTreeOrder;
    Depths m_depths;
    VertexToIndexMap m_vertexToFirstIndexMap;
};

}  // namespace algorithm

}  // namespace alba
