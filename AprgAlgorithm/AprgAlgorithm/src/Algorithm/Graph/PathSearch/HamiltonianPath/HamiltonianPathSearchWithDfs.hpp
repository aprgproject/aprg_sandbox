#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class HamiltonianPathSearchWithDfs // The Traveling Salesman Problem. // This is an intractable problem (classical NP-complete problem)
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;    using Path = typename GraphTypes<Vertex>::Path;
    using Paths = typename GraphTypes<Vertex>::Paths;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    enum class SearchType
    {
        Unknown,
        AllHamiltonianPaths,
        OneHamiltonianPath,
        AllHamiltonianCycles,
        OneHamiltonianCycle,
    };

    HamiltonianPathSearchWithDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
        , m_numberOfVertices(m_graph.getNumberOfVertices())
        , m_searchType(SearchType::Unknown)    {}

    Paths getAllHamiltonianPaths()
    {
        // A Hamiltonian path also visits every vertex once with no repeats
        clear();
        m_searchType = SearchType::AllHamiltonianPaths;
        searchForHamiltonianPaths();
        return m_savedPaths;
    }

    Path getOneHamiltonianPath()
    {
        Path result;
        clear();
        m_searchType = SearchType::OneHamiltonianPath;
        searchForHamiltonianPaths();
        if(!m_savedPaths.empty())
        {
            result = m_savedPaths.front();
        }
        return result;
    }

    Paths getAllHamiltonianCycles()
    {
        // A Hamiltonian path also visits every vertex once with no repeats
        clear();
        m_searchType = SearchType::AllHamiltonianCycles;
        searchForHamiltonianPaths();
        return m_savedPaths;
    }

    Path getOneHamiltonianCycle()
    {
        Path result;
        clear();
        m_searchType = SearchType::OneHamiltonianCycle;
        searchForHamiltonianPaths();
        if(!m_savedPaths.empty())
        {
            result = m_savedPaths.front();
        }
        return result;
    }

protected:

    bool shouldStop() const
    {
        return (SearchType::OneHamiltonianPath == m_searchType || SearchType::OneHamiltonianCycle == m_searchType)
                && 1U <= m_savedPaths.size();
    }

    void clear()
    {
        m_searchType = SearchType::Unknown;
        m_savedPaths.clear();
    }

    void searchForHamiltonianPaths()
    {
        for(Vertex const& startVertex : m_graph.getVertices())
        {
            Path currentPath;
            traverseUsingDfs(currentPath, startVertex);
            if(shouldStop())
            {
                break;
            }
        }
    }

    void traverseUsingDfs(Path & currentPath, Vertex const& vertex)
    {
        currentPath.emplace_back(vertex);
        checkPathAndSaveIfNeeded(currentPath);
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            checkCycleAndSaveIfNeeded(currentPath, adjacentVertex);
            if(shouldStop()) // needs to stop here to prune all dfs recursion instances
            {
                break;
            }
            else if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traverseUsingDfs(currentPath, adjacentVertex);
            }
        }
        m_processedVertices.removeVertex(vertex);
        currentPath.pop_back();
    }

    void checkPathAndSaveIfNeeded(Path const& currentPath)
    {
        if((SearchType::AllHamiltonianPaths == m_searchType || SearchType::OneHamiltonianPath == m_searchType)
                && currentPath.size() == m_numberOfVertices)
        {
            m_savedPaths.emplace_back(currentPath);
        }
    }

    void checkCycleAndSaveIfNeeded(Path const& currentPath, Vertex const& nextVertex)
    {
        if((SearchType::AllHamiltonianCycles == m_searchType || SearchType::OneHamiltonianCycle == m_searchType)
                && currentPath.size() == m_numberOfVertices && currentPath.size() > 0)
        {
            if(currentPath.front() == nextVertex)
            {
                Path cycle(currentPath);
                cycle.emplace_back(currentPath.front());
                m_savedPaths.emplace_back(cycle);
            }
        }
    }

    BaseGraphWithVertex const& m_graph;
    unsigned int m_numberOfVertices;
    SearchType m_searchType;
    CheckableVerticesWithVertex m_processedVertices;
    Paths m_savedPaths;
};

// No efficient method is known for testing if a graph contains a Hamiltonian path, and the problem is NP-hard.
// Still, in some special cases, we can be certain that a graph contains a Hamiltonian path.
// A simple observation is that if the graph is complete, i.e., there is an edge between all pairs of nodes, it also contains a Hamiltonian path.

// A simple way to search for a Hamiltonian path is to use a backtracking algorithm that goes through all possible ways to construct the path (implemented above).
// The time complexity of such an algorithm is at least O(n!), because there are n! different ways to choose the order of n nodes.
// A more efficient solution is based on dynamic programming.
// The idea is to calculate values of a function possible(S, x), where S is a subset of nodes and x is one of the nodes.
// The function indicates whether there is a Hamiltonian path that visits the nodes of S and ends at node x.
// It is possible to implement this solution in O(2^n * n^2) time.

}

}
