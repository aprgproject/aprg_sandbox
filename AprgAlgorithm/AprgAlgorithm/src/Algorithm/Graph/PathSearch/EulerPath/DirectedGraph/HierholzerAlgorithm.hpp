#pragma once

#include <Algorithm/Graph/PathSearch/EulerPath/DirectedGraph/BaseEulerPathSearchForDirectedGraph.hpp>

#include <algorithm>
#include <stack>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class HierholzerAlgorithm : public BaseEulerPathSearchForDirectedGraph<Vertex>
{
public:
    using BaseClass = BaseEulerPathSearchForDirectedGraph<Vertex>;
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToAdjacencyVerticesMap = std::map<Vertex, Vertices>;

    HierholzerAlgorithm(BaseDirectedGraphWithVertex const& graph)
        : BaseClass(graph)
        , b_graph(BaseClass::m_graph)
    {}

    Path getEulerCycle() const override
    {
        Path result;
        if(this->hasEulerCycle()) // this is check is needed because Hierholzer algorithm does not check this
        {
            searchForEulerPath(result, this->getStartingVertexForEulerCycle());
        }
        return result;
    }

    Path getEulerPath() const override
    {
        Path result;
        if(this->hasEulerPath()) // this is check is needed because Hierholzer algorithm does not check this
        {
            searchForEulerPath(result, this->getStartingVertexForEulerPath());
        }
        return result;
    }

private:

    void searchForEulerPath(Path & result, Vertex const& startingVertex) const
    {
        VertexToAdjacencyVerticesMap vertexToAdjacentVerticesMap;
        Vertices allVertices(b_graph.getVertices());
        for(Vertex const& vertex : allVertices)
        {
            vertexToAdjacentVerticesMap.emplace(vertex, b_graph.getAdjacentVerticesAt(vertex));
        }

        std::stack<Vertex> nonDeadEndPath;
        Vertex currentVertex(startingVertex);
        nonDeadEndPath.push(startingVertex);

        while(!nonDeadEndPath.empty())
        {
            Vertices & adjacentVertices(vertexToAdjacentVerticesMap.at(currentVertex));
            if(!isDeadEnd(currentVertex, adjacentVertices)) // if not dead end
            {
                nonDeadEndPath.push(currentVertex);
                currentVertex = adjacentVertices.back();
                adjacentVertices.pop_back();
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

    bool isDeadEnd(Vertex const&, Vertices const& adjacentVertices) const
    {
        return adjacentVertices.empty();
    }

    BaseDirectedGraphWithVertex const& b_graph;
};

}

}
