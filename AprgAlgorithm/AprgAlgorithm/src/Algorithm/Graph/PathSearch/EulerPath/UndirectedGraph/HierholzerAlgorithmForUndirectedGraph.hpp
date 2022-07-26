#pragma once

#include <Algorithm/Graph/PathSearch/EulerPath/Common/BaseHierholzerAlgorithm.hpp>
#include <Algorithm/Graph/PathSearch/EulerPath/UndirectedGraph/BaseEulerPathSearchForUndirectedGraph.hpp>

#include <stack>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class HierholzerAlgorithmForUndirectedGraph : public BaseHierholzerAlgorithm<Vertex, BaseUndirectedGraph<Vertex>, BaseEulerPathSearchForUndirectedGraph<Vertex>>
{
public:
    using BaseClass = BaseHierholzerAlgorithm<Vertex, BaseUndirectedGraph<Vertex>, BaseEulerPathSearchForUndirectedGraph<Vertex>>;
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using VertexToAdjacencyVerticesMap = std::map<Vertex, SetOfVertices>;

    HierholzerAlgorithmForUndirectedGraph(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph)
        , b_graph(BaseClass::b_graph)
    {}

private:

    void searchForEulerPath(Path & result, Vertex const& startingVertex) const override
    {
        VertexToAdjacencyVerticesMap vertexToAdjacentVerticesMap;
        Vertices allVertices(b_graph.getVertices());
        for(Vertex const& vertex : allVertices)
        {
            Vertices const& adjacentVertices(b_graph.getAdjacentVerticesAt(vertex));
            vertexToAdjacentVerticesMap.emplace(vertex, SetOfVertices(adjacentVertices.cbegin(), adjacentVertices.cend()));
        }

        std::stack<Vertex> nonDeadEndPath;
        Vertex currentVertex(startingVertex);
        nonDeadEndPath.push(startingVertex);

        while(!nonDeadEndPath.empty())
        {
            SetOfVertices & adjacentVertices(vertexToAdjacentVerticesMap[currentVertex]);
            if(!isDeadEnd(adjacentVertices)) // if not dead end
            {
                nonDeadEndPath.push(currentVertex);
                auto lastIt = adjacentVertices.cbegin();
                Vertex nextVertex(*lastIt);
                adjacentVertices.erase(lastIt);
                vertexToAdjacentVerticesMap[nextVertex].erase(currentVertex);
                currentVertex = nextVertex;
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

    bool isDeadEnd(SetOfVertices const& adjacentVertices) const
    {
        return adjacentVertices.empty();
    }

    BaseUndirectedGraphWithVertex const& b_graph;
};

}

}
