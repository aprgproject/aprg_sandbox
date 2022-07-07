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
    using Paths = typename GraphTypes<Vertex>::Paths;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    enum class SearchType
    {
        Unknown,
        AllCycles,
        OneCycle
    };

    CycleDetectionUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
        , m_searchType(SearchType::Unknown)
    {}

    Paths getAllCycles()
    {
        clear();
        m_searchType = SearchType::AllCycles;
        search();
        return m_pathsWithCycle;
    }

    Path getOneCycle()
    {
        clear();
        m_searchType = SearchType::OneCycle;
        search();
        Path result;
        if(!m_pathsWithCycle.empty())
        {
            result = m_pathsWithCycle.front();
        }
        return result;
    }

private:

    bool hasACycle() const
    {
        return !m_pathsWithCycle.empty();
    }

    bool isThisVertexOnThePossibleCycle(Vertex const& vertex) const
    {
        return m_verticesInPossibleCycle.find(vertex) != m_verticesInPossibleCycle.cend();
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

    void clear()
    {
        m_searchType = SearchType::Unknown;
        m_processedVertices.clear();
        m_vertexToPreviousVertexMap.clear();
        m_verticesInPossibleCycle.clear();
        m_pathsWithCycle.clear();
    }

    void search()
    {
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(m_processedVertices.isNotFound(vertex))
            {
                searchUsingDfs(vertex);
            }
        }
    }

    void searchUsingDfs(Vertex const& startVertex)
    {
        switch(m_graph.getGraphDirectionType())
        {
        case GraphDirectionType::Directed:
        {
            searchUsingDfsWithDirectedGraph(startVertex);
            break;
        }
        case GraphDirectionType::Undirected:
        {
            searchUsingDfsWithUndirectedGraph(startVertex, startVertex);
            break;
        }
        }
    }

    void searchUsingDfsWithDirectedGraph(Vertex const& startVertex)
    {
        m_verticesInPossibleCycle.emplace(startVertex);
        m_processedVertices.putVertex(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(SearchType::OneCycle == m_searchType && hasACycle()) // this check is needed to end all recursion instances once cycle has been detected
            {
                break;
            }
            else if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;
                searchUsingDfsWithDirectedGraph(adjacentVertex);
            }
            else if(isThisVertexOnThePossibleCycle(adjacentVertex)) // check processed vertices if part of a cycle
            {
                m_pathsWithCycle.emplace_back(getPathWithCycle(startVertex, adjacentVertex));
            }
        }
        m_verticesInPossibleCycle.erase(startVertex);
    }

    void searchUsingDfsWithUndirectedGraph(Vertex const& startVertex, Vertex const& previousVertex)
    {
        m_verticesInPossibleCycle.emplace(startVertex);
        m_processedVertices.putVertex(startVertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex))
        {
            if(SearchType::OneCycle == m_searchType && hasACycle()) // this check is needed to end all recursion instances once cycle has been detected
            {
                break;
            }
            else if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;
                searchUsingDfsWithUndirectedGraph(adjacentVertex, startVertex);
            }
            else if(previousVertex != adjacentVertex && isThisVertexOnThePossibleCycle(adjacentVertex)) // check processed vertices if part of a cycle
            {
                // if previous and adjacent are equal then its the same edge (and not technically a cycle)
                m_pathsWithCycle.emplace_back(getPathWithCycle(startVertex, adjacentVertex));
            }
        }
        m_verticesInPossibleCycle.erase(startVertex);
    }

    BaseGraphWithVertex const& m_graph;
    SearchType m_searchType;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToVertexMap m_vertexToPreviousVertexMap;
    SetOfVertices m_verticesInPossibleCycle;
    Paths m_pathsWithCycle;
};

// Other analysis:
// Another way to find out whether a graph contains a cycle is to simply calculate the number of nodes and edges in every component.
// If a component contains c nodes and no cycle, it must contain exactly c-1 edges (so it has to be a tree).
// If there are c or more edges, the component surely contains a cycle.
// This is only for undirected graph?

}

}
