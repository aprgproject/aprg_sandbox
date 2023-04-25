#pragma once

#include <Algorithm/Graph/PathSearch/EulerPaths/Common/BaseHierholzerAlgorithm.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/DirectedGraph/BaseEulerPathSearchForDirectedGraph.hpp>

#include <algorithm>
#include <stack>

namespace alba {

namespace algorithm {

template <typename Vertex>
class HierholzerAlgorithmForDirectedGraph
    : public BaseHierholzerAlgorithm<Vertex, BaseDirectedGraph<Vertex>, BaseEulerPathSearchForDirectedGraph<Vertex>> {
public:
    using BaseClass =
        BaseHierholzerAlgorithm<Vertex, BaseDirectedGraph<Vertex>, BaseEulerPathSearchForDirectedGraph<Vertex>>;
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToAdjacencyVerticesMap = std::map<Vertex, Vertices>;

    HierholzerAlgorithmForDirectedGraph(BaseDirectedGraphWithVertex const& graph)
        : BaseClass(graph), b_graph(BaseClass::b_graph) {}

private:
    void searchForEulerPath(Path& result, Vertex const& startingVertex) const override {
        VertexToAdjacencyVerticesMap vertexToAdjacentVerticesMap(createVertexToAdjacentVerticesMap());

        std::stack<Vertex> nonDeadEndPath;
        Vertex currentVertex(startingVertex);
        nonDeadEndPath.push(startingVertex);

        while (!nonDeadEndPath.empty()) {
            Vertices& adjacentVertices(vertexToAdjacentVerticesMap[currentVertex]);
            if (!adjacentVertices.empty())  // if not dead end
            {
                nonDeadEndPath.push(currentVertex);
                currentVertex = adjacentVertices.back();
                adjacentVertices.pop_back();
            } else  // if dead end
            {
                result.emplace_back(currentVertex);    // add dead end vertex
                currentVertex = nonDeadEndPath.top();  // check last vertex on "non dead end path"
                nonDeadEndPath.pop();
            }
        }
        std::reverse(result.begin(), result.end());
    }

    VertexToAdjacencyVerticesMap createVertexToAdjacentVerticesMap() const {
        VertexToAdjacencyVerticesMap result;
        Vertices allVertices(b_graph.getVertices());
        for (Vertex const& vertex : allVertices) {
            result.emplace(vertex, b_graph.getAdjacentVerticesAt(vertex));
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& b_graph;
};

}  // namespace algorithm

}  // namespace alba
