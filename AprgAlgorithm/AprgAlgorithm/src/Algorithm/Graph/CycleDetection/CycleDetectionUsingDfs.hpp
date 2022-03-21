#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class CycleDetectionUsingDfs
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;

    CycleDetectionUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
        , m_isProcessedMap()
        , m_vertexToPreviousVertexMap()
    {}

    bool hasCycle() const
    {
        return !m_pathWithCycle.empty();
    }

    Path getPathWithCycle()
    {
        return m_pathWithCycle;
    }

    void checkForCycles()
    {
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(isNotProcessed(vertex))
            {
                checkForCyclesUsingDfs(vertex);
            }
        }
    }

private:

    bool isNotProcessed(Vertex const& vertex) const
    {
        auto it = m_isProcessedMap.find(vertex);
        return it == m_isProcessedMap.cend() || !it->second;
    }

    bool isPartOfCycle(Vertex const& vertex) const
    {
        bool result(false);
        auto it = m_isPartOfCycle.find(vertex);
        if(it != m_isPartOfCycle.cend())
        {
            result = it->second;
        }
        return result;
    }

    Path getPathWithCycle(Vertex const& secondToTheLastVertex, Vertex const& lastVertex) const
    {
        bool isSuccessful(true);
        Path reversedPath{lastVertex};
        Vertex currentVertex = secondToTheLastVertex;
        while(currentVertex != lastVertex)
        {
            reversedPath.emplace_back(currentVertex);
            auto it = m_vertexToPreviousVertexMap.find(currentVertex);
            if(it != m_vertexToPreviousVertexMap.cend())
            {
                currentVertex = it->second;
            }
            else
            {
                isSuccessful = false;
                break;
            }
        }
        Path result;
        if(isSuccessful)
        {
            reversedPath.emplace_back(lastVertex);
            result.reserve(reversedPath.size());
            std::copy(reversedPath.crbegin(), reversedPath.crend(), std::back_inserter(result));
        }
        return result;
    }

    void checkForCyclesUsingDfs(Vertex const& startVertex)
    {
        switch(m_graph.getGraphDirectionType())
        {
        case GraphDirectionType::Directed:
        {
            checkForCyclesUsingDfsWithDirectedGraph(startVertex);
            break;
        }
        case GraphDirectionType::Undirected:
        {
            checkForCyclesUsingDfsWithUndirectedGraph(startVertex, startVertex);
            break;
        }
        }
    }

    void checkForCyclesUsingDfsWithDirectedGraph(Vertex const& startVertex)
    {
        m_isPartOfCycle[startVertex] = true;
        m_isProcessedMap[startVertex] = true;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(hasCycle())
            {
                break;
            }
            else if(isNotProcessed(adjacentVertex))
            {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;
                checkForCyclesUsingDfsWithDirectedGraph(adjacentVertex);
            }
            else if(isPartOfCycle(adjacentVertex))
            {
                m_pathWithCycle = getPathWithCycle(startVertex, adjacentVertex);
            }
        }
        m_isPartOfCycle.erase(startVertex);
    }

    void checkForCyclesUsingDfsWithUndirectedGraph(Vertex const& startVertex, Vertex const& previousVertex)
    {
        m_isPartOfCycle[startVertex] = true;
        m_isProcessedMap[startVertex] = true;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(hasCycle())
            {
                break;
            }
            else if(isNotProcessed(adjacentVertex))
            {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;
                checkForCyclesUsingDfsWithUndirectedGraph(adjacentVertex, startVertex);
            }
            else if(previousVertex != adjacentVertex && isPartOfCycle(adjacentVertex))
            {
                m_pathWithCycle = getPathWithCycle(startVertex, adjacentVertex);
            }
        }
        m_isPartOfCycle.erase(startVertex);
    }

    BaseGraphWithVertex const& m_graph;
    VertexToBoolMap m_isProcessedMap;
    VertexToVertexMap m_vertexToPreviousVertexMap;
    VertexToBoolMap m_isPartOfCycle;
    Path m_pathWithCycle;
};

}

}
