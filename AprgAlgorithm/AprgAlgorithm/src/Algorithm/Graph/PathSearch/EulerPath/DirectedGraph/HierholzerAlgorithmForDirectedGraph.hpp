#pragma once

#include <Algorithm/Graph/PathSearch/EulerPath/Common/BaseHierholzerAlgorithm.hpp>
#include <Algorithm/Graph/PathSearch/EulerPath/DirectedGraph/BaseEulerPathSearchForDirectedGraph.hpp>

#include <stack>

namespace alba{

namespace algorithm
{

template <typename Vertex>
class HierholzerAlgorithmForDirectedGraph : public BaseHierholzerAlgorithm<Vertex, BaseDirectedGraph<Vertex>, BaseEulerPathSearchForDirectedGraph<Vertex>>
{
public:
    using BaseClass = BaseHierholzerAlgorithm<Vertex, BaseDirectedGraph<Vertex>, BaseEulerPathSearchForDirectedGraph<Vertex>>;
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToAdjacencyVerticesMap = std::map<Vertex, Vertices>;

    HierholzerAlgorithmForDirectedGraph(BaseDirectedGraphWithVertex const& graph)
        : BaseClass(graph)
        , b_graph(BaseClass::b_graph)
    {}

private:

    void searchForEulerPath(Path & result, Vertex const& startingVertex) const override
    {
        VertexToAdjacencyVerticesMap vertexToAdjacentVerticesMap;
        Vertices allVertices(b_graph.getVertices());        for(Vertex const& vertex : allVertices)
        {
            vertexToAdjacentVerticesMap.emplace(vertex, b_graph.getAdjacentVerticesAt(vertex));
        }

        std::stack<Vertex> nonDeadEndPath;
        Vertex currentVertex(startingVertex);
        nonDeadEndPath.push(startingVertex);

        while(!nonDeadEndPath.empty())
        {
            Vertices & adjacentVertices(vertexToAdjacentVerticesMap[currentVertex]);
            if(!isDeadEnd(adjacentVertices)) // if not dead end
            {
                nonDeadEndPath.push(currentVertex);
                currentVertex = adjacentVertices.back();                adjacentVertices.pop_back();
            }
            else // if dead end
            {
                result.emplace_back(currentVertex); // add dead end vertex
                currentVertex = nonDeadEndPath.top(); // check last vertex on "non dead end path"
                nonDeadEndPath.pop();
            }
        }
        std::reverse(result.begin(), result.end());
    }

    bool isDeadEnd(Vertices const& adjacentVertices) const
    {
        return adjacentVertices.empty();
    }
    BaseDirectedGraphWithVertex const& b_graph;
};

}

}
