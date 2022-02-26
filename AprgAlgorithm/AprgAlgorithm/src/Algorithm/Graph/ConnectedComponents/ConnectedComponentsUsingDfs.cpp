#include "ConnectedComponentsUsingDfs.hpp"

#include <Algorithm/Graph/PathSearch/DepthFirstSearch/DepthFirstSearch.hpp>

using namespace std;

namespace alba
{

namespace algorithm
{

ConnectedComponentsUsingDfs::ConnectedComponentsUsingDfs(
        BaseUndirectedGraph const& graph)
    : m_graph(graph)
{
    initialize();
}

bool ConnectedComponentsUsingDfs::isConnected(
        Vertex const vertex1,
        Vertex const vertex2) const
{
    auto it1 = m_vertexToComponentIdMap.find(vertex1);
    auto it2 = m_vertexToComponentIdMap.find(vertex2);
    bool result(false);
    if(it1 != m_vertexToComponentIdMap.cend()
            && it2 != m_vertexToComponentIdMap.cend())
    {
        result = it1->second == it2->second;
    }
    return result;
}

void ConnectedComponentsUsingDfs::initialize()
{
    Vertices vertices(m_graph.getVertices());
    for(Vertex const vertex : vertices)
    {
        m_isProcessed[vertex] = false;
    }
    unsigned int componentId(0U);
    for(Vertex const vertex : vertices)
    {
        if(!m_isProcessed.at(vertex))
        {
            DepthFirstSearch dfs(m_graph, vertex);
            DepthFirstSearch::IsProcessedMap const& isProcessedMap(dfs.getIsProcessedMap());
            for(auto const& vertexAndIsProcessedPair : isProcessedMap)
            {
                if(vertexAndIsProcessedPair.second)
                {
                    m_vertexToComponentIdMap[vertexAndIsProcessedPair.first] = componentId;
                    m_isProcessed[vertexAndIsProcessedPair.first] = true;
                }
            }
            componentId++;
        }
    }
}

}

}
