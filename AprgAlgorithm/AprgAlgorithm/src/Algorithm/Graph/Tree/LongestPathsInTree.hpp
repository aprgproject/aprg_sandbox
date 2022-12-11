#pragma once

#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfsWithDistanceCount.hpp>
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
    using Dfs = PathSearchUsingDfsWithDistanceCount<Vertex>;
    using DfsEntry = AlbaFakeCopyable<Dfs>;
    using VertexToDfsEntry = std::map<Vertex, DfsEntry>;
    LongestPathsInTree(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {        initializeIfNeeded();
    }

    EndPointPairs const& getEndPointPairsOfLongestPaths() const
    {
        return m_endPointPairsOfLongestPaths;
    }

    unsigned int getLongestDistance() // this function is coupled with search function
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
        if(!m_startVerticesOfLongestPath.empty() && m_endPointPairsOfLongestPaths.empty())
        {
            Vertex const& startVertexForLongestPath(m_startVerticesOfLongestPath.front());
            searchForEndPointPairsAt(startVertexForLongestPath);
        }
    }

    void searchForAllEndPointPairs()
    {
        m_endPointPairsOfLongestPaths.clear();
        for(Vertex const& startVertexForLongestPath : m_startVerticesOfLongestPath)
        {
            searchForEndPointPairsAt(startVertexForLongestPath);
        }
    }

private:
    void initializeIfNeeded()
    {
        if(GraphUtilities::isATree(m_graph))
        {
            initialize();
        }
    }

    void initialize()
    {
        m_allVertices = m_graph.getVertices();
        m_startVerticesOfLongestPath = getStartVerticesOfLongestPath(m_allVertices);
    }

    Vertices getStartVerticesOfLongestPath(Vertices const& allVertices)
    {
        Vertices result;
        if(!allVertices.empty())
        {
            Dfs const& dfs(getDfs(allVertices.front())); // start at some arbitiary node
            unsigned int maxDistance(0);
            for(auto it=allVertices.cbegin()+1; it!=allVertices.cend(); it++)
            {
                updateIfMaxDistance(result, maxDistance, dfs, *it);
            }
        }
        return result; // start vertices are the ones with max distance from arbitiary node
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
            m_vertexToDfs.emplace(vertex, Dfs(m_graph, {vertex}));
            return m_vertexToDfs.at(vertex).getObject();
        }
    }
    BaseUndirectedGraphWithVertex const& m_graph;
    Vertices m_allVertices;
    Vertices m_startVerticesOfLongestPath;    EndPointPairs m_endPointPairsOfLongestPaths;
    VertexToDfsEntry m_vertexToDfs;
};

}

}
