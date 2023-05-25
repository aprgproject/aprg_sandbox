#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class CountPathsInDirectedGraph {
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using VertexToSetOfVerticesMap = std::map<Vertex, SetOfVertices>;
    using VertexToIndexMap = std::map<Vertex, int>;
    using VertexPair = std::pair<Vertex, Vertex>;
    using VertexPairToCountMap = std::map<VertexPair, int>;

    CountPathsInDirectedGraph(BaseDirectedGraphWithVertex const& graph) : m_graph(graph) { initialize(); }

    int getCount(Vertex const& start, Vertex const& end) { return getCountInternal(start, end); }

private:
    void initialize() {
        Vertices verticesInOrder(VertexOrderingUsingDfs<Vertex>(m_graph).getVerticesInTopologicalOrder());
        int index(0);
        for (Vertex const& vertexInOrder : verticesInOrder) {
            m_vertexToTopologicalIndex[vertexInOrder] = index++;
        }

        for (Edge const& edge : m_graph.getEdges()) {
            m_vertexToDependentVertices[edge.second].emplace(edge.first);
        }
    }

    int getCountInternal(Vertex const& start, Vertex const& end) {
        int result(1);  // if start and end are equal, then return one count
        if (start != end) {
            auto it = m_pathCounts.find({start, end});
            if (it != m_pathCounts.cend()) {
                result = it->second;
            } else {
                result = sumCounts(start, end);
                m_pathCounts.emplace(VertexPair{start, end}, result);
            }
        }
        return result;
    }

    int sumCounts(Vertex const& start, Vertex const& end) {
        int result(0);
        auto itStart = m_vertexToTopologicalIndex.find(start);
        auto itEnd = m_vertexToTopologicalIndex.find(end);
        if (itStart != m_vertexToTopologicalIndex.cend() && itEnd != m_vertexToTopologicalIndex.cend()) {
            int startIndex = itStart->second;
            int endIndex = itEnd->second;
            int distanceInTopologicalOrder = endIndex - startIndex;
            // if distanceInTopologicalOrder is positive: sum counts of dependent vertices at the end
            // if distanceInTopologicalOrder is zero: count is 1
            // if distanceInTopologicalOrder is negative: count is 0
            if (distanceInTopologicalOrder > 0) {
                for (Vertex const& dependentVertexAtEnd : m_vertexToDependentVertices.at(end)) {
                    result += getCountInternal(start, dependentVertexAtEnd);
                }
            } else if (distanceInTopologicalOrder == 0) {
                result = 1;
            }
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& m_graph;
    VertexToSetOfVerticesMap m_vertexToDependentVertices;
    VertexToIndexMap m_vertexToTopologicalIndex;
    VertexPairToCountMap m_pathCounts;  // dynamic programming
};

}  // namespace algorithm

}  // namespace alba
