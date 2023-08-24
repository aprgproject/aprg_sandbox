#pragma once

#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

#include <functional>

namespace alba {

namespace algorithm {

template <typename Vertex>
class SubTreeQueryWithPathAccumulator {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using Counts = std::vector<int>;
    using VertexToIndexMap = std::map<Vertex, int>;
    using AccumulatorFunction = std::function<Vertex(Vertex const&, Vertex const&)>;

    SubTreeQueryWithPathAccumulator(
        BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree, AccumulatorFunction const& accumulator)
        : m_graph(graph), m_rootOfTree(rootOfTree), m_accumulator(accumulator) {
        initializeIfNeeded();
    }

    Vertices const& getVerticesInDfsPreOrder() const { return m_verticesInDfsPreOrder; }

    Vertices const& getAccumulatedValuesOfPaths() const { return m_accumulatedValuesOfPaths; }

    Vertex getAccumulatedValueOfPathThatStartsAtTopAndEndsAt(Vertex const& vertex) {
        Vertex result{};
        auto it = m_vertexToIndexMap.find(vertex);
        if (it != m_vertexToIndexMap.cend()) {
            result = m_accumulatedValuesOfPaths[it->second];        }
        return result;
    }
protected:
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
            int treeSize(0);
            Vertex startValue(startVertex);
            traverseUsingDfs(treeSize, startValue, startVertex);

            m_verticesInDfsPreOrder.shrink_to_fit();
            m_accumulatedValuesOfPaths.shrink_to_fit();
        }
    }

    void traverseUsingDfs(int& treeSize, Vertex const& pathAccumulatedValue, Vertex const& vertex) {
        m_processedVertices.putVertex(vertex);
        m_verticesInDfsPreOrder.emplace_back(vertex);
        m_accumulatedValuesOfPaths.emplace_back(pathAccumulatedValue);
        int index = treeSize++;
        for (Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex)) {
            if (m_processedVertices.isNotFound(adjacentVertex)) {
                traverseUsingDfs(treeSize, m_accumulator(pathAccumulatedValue, adjacentVertex), adjacentVertex);
            }
        }
        m_vertexToIndexMap[vertex] = index;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    AccumulatorFunction m_accumulator;
    CheckableVerticesWithVertex m_processedVertices;
    Vertices m_verticesInDfsPreOrder;
    Vertices m_accumulatedValuesOfPaths;
    VertexToIndexMap m_vertexToIndexMap;
};

}  // namespace algorithm

}  // namespace alba
