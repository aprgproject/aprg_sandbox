#pragma once

#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>
#include <Common/Container/AlbaFakeCopyable.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class LongestPathsInTree
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using EndPointPair = std::pair<Vertex, Vertex>;
    using EndPointPairs = std::vector<EndPointPair>;
    using Dfs = PathSearchUsingDfs<Vertex>;
    using DfsEntry = AlbaFakeCopyable<Dfs>;
    using VertexToDfsEntry = std::map<Vertex, DfsEntry>;

    LongestPathsInTree(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {
        initialize();
    }

    EndPointPairs const& getEndPointPairsOfLongestPaths() const
    {
        return m_endPointPairsOfLongestPaths;
    }

    unsigned int getLongestDistance()
    {
        unsigned int result(0);
        if(!m_endPointPairsOfLongestPaths.empty())
        {
            Vertex start = m_endPointPairsOfLongestPaths.front().first;
            Vertex end = m_endPointPairsOfLongestPaths.front().second;
            result = getDfs(start).getDistanceTo(end);
        }
        return result;
    }

    void searchForAtLeastOneEndPointPair()
    {
        if(!m_startVertices.empty() && m_endPointPairsOfLongestPaths.empty())
        {
            Vertex const& startVertex(m_startVertices.front());
            searchForEndPointPairsAt(startVertex);
        }
    }

    void searchForAllEndPointPairs()
    {
        m_endPointPairsOfLongestPaths.clear();
        for(Vertex const& startVertex : m_startVertices)
        {
            searchForEndPointPairsAt(startVertex);
        }
    }

private:
    void initialize()
    {
        if(GraphUtilities::isATree(m_graph))
        {
            m_allVertices = m_graph.getVertices();
            m_startVertices = getStartVerticesOfLongestPath(m_allVertices);
        }
    }

    Vertices getStartVerticesOfLongestPath(Vertices const& allVertices)
    {
        Vertices startVertices;
        if(!allVertices.empty())
        {
            Dfs const& dfs(getDfs(allVertices.front())); // start at some arbitiary node
            unsigned int maxDistance(0);
            for(auto it=allVertices.cbegin()+1; it!=allVertices.cend(); it++)
            {
                updateIfMaxDistance(startVertices, maxDistance, dfs, *it);
            }
        }
        return startVertices; // start vertices are the ones with max distance from arbitiary node
    }

    void searchForEndPointPairsAt(Vertex const& startVertex)
    {
        Dfs const& dfs(getDfs(startVertex));
        unsigned int maxDistance(0);
        Vertices endVerticesWithMaxDistance;
        for(Vertex const& possibleEndVertex : m_allVertices)
        {
            updateIfMaxDistance(endVerticesWithMaxDistance, maxDistance, dfs, possibleEndVertex); // get end vertices with max distance
        }
        for(Vertex const& endVertex : endVerticesWithMaxDistance)
        {
            m_endPointPairsOfLongestPaths.emplace_back(startVertex, endVertex);
        }
    }

    void updateIfMaxDistance(
            Vertices & verticesWithMaxDistance,
            unsigned int & maxDistance,
            Dfs const& dfs,
            Vertex const& currentVertex)
    {
        unsigned int currentDistance(dfs.getDistanceTo(currentVertex));
        if(maxDistance < currentDistance)
        {
            verticesWithMaxDistance.clear();
            maxDistance = currentDistance;
            verticesWithMaxDistance.emplace_back(currentVertex);
        }
        else if(maxDistance == currentDistance)
        {
            verticesWithMaxDistance.emplace_back(currentVertex);
        }
    }

    Dfs const& getDfs(Vertex const& vertex) // uses dynamic programming
    {
        auto it = m_vertexToDfs.find(vertex);
        if(it != m_vertexToDfs.cend())
        {
            return it->second.getObject();
        }
        else
        {
            m_vertexToDfs.emplace(vertex, Dfs(m_graph, vertex));
            return m_vertexToDfs.at(vertex).getObject();
        }
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertices m_allVertices;
    Vertices m_startVertices;
    EndPointPairs m_endPointPairsOfLongestPaths;
    VertexToDfsEntry m_vertexToDfs;
};

}

}
