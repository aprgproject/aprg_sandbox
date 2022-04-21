#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class CycleDetectionUsingDfs
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    CycleDetectionUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
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
            if(m_processedVertices.isNotFound(vertex))
            {
                checkForCyclesUsingDfs(vertex);
            }
        }
    }

private:

    bool isPartOfCycle(Vertex const& vertex) const
    {
        return m_verticesInCycle.find(vertex) != m_verticesInCycle.cend();
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
        m_verticesInCycle.emplace(startVertex);
        m_processedVertices.putVertex(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(hasCycle())
            {
                break;
            }
            else if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;
                checkForCyclesUsingDfsWithDirectedGraph(adjacentVertex);
            }
            else if(isPartOfCycle(adjacentVertex))
            {
                m_pathWithCycle = getPathWithCycle(startVertex, adjacentVertex);
            }
        }
        m_verticesInCycle.erase(startVertex);
    }

    void checkForCyclesUsingDfsWithUndirectedGraph(Vertex const& startVertex, Vertex const& previousVertex)
    {
        m_verticesInCycle.emplace(startVertex);
        m_processedVertices.putVertex(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(hasCycle())
            {
                break;
            }
            else if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;
                checkForCyclesUsingDfsWithUndirectedGraph(adjacentVertex, startVertex);
            }
            else if(previousVertex != adjacentVertex && isPartOfCycle(adjacentVertex))
            {
                m_pathWithCycle = getPathWithCycle(startVertex, adjacentVertex);
            }
        }
        m_verticesInCycle.erase(startVertex);
    }

    BaseGraphWithVertex const& m_graph;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToVertexMap m_vertexToPreviousVertexMap;
    SetOfVertices m_verticesInCycle;
    Path m_pathWithCycle;
};

}

}
