#pragma once

#include <Algorithm/Graph/PathSearch/EulerPaths/Common/BaseHierholzerAlgorithm.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/UndirectedGraph/BaseEulerPathSearchForUndirectedGraph.hpp>

#include <algorithm>
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
    using VertexToSetOfAdjacencyVerticesMap = std::map<Vertex, SetOfVertices>;

    HierholzerAlgorithmForUndirectedGraph(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph)
        , b_graph(BaseClass::b_graph)
    {}

private:

    void searchForEulerPath(Path & result, Vertex const& startingVertex) const override
    {
        VertexToSetOfAdjacencyVerticesMap vertexToSetOfAdjacencyVerticesMap(createVertexToSetOfAdjacencyVerticesMap());

        std::stack<Vertex> nonDeadEndPath;
        Vertex currentVertex(startingVertex);
        nonDeadEndPath.push(startingVertex);

        while(!nonDeadEndPath.empty())
        {
            SetOfVertices & adjacentVertices(vertexToSetOfAdjacencyVerticesMap[currentVertex]);
            if(!adjacentVertices.empty()) // if not dead end
            {
                nonDeadEndPath.push(currentVertex);
                auto firstIt = adjacentVertices.cbegin();
                Vertex nextVertex(*firstIt);
                adjacentVertices.erase(firstIt);
                vertexToSetOfAdjacencyVerticesMap[nextVertex].erase(currentVertex);
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

    VertexToSetOfAdjacencyVerticesMap createVertexToSetOfAdjacencyVerticesMap() const
    {
        VertexToSetOfAdjacencyVerticesMap result;
        Vertices allVertices(b_graph.getVertices());
        for(Vertex const& vertex : allVertices)
        {
            Vertices const& adjacentVertices(b_graph.getAdjacentVerticesAt(vertex));
            result.emplace(vertex, SetOfVertices(adjacentVertices.cbegin(), adjacentVertices.cend()));
        }
        return result;
    }

    BaseUndirectedGraphWithVertex const& b_graph;
};

}

}
