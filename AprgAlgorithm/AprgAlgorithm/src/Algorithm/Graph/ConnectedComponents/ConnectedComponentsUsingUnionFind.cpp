#include "ConnectedComponentsUsingUnionFind.hpp"

using namespace std;

namespace alba
{

namespace algorithm
{

ConnectedComponentsUsingUnionFind::ConnectedComponentsUsingUnionFind(
        BaseUndirectedGraph const& graph)
    : m_graph(graph)
    , m_unionFind()
{
    initialize();
}

bool ConnectedComponentsUsingUnionFind::isConnected(
        Vertex const vertex1,
        Vertex const vertex2) const
{
    return m_unionFind.isConnected(vertex1, vertex2);
}

void ConnectedComponentsUsingUnionFind::initialize()
{
    for(Edge const& edge : m_graph.getEdges())
    {
        m_unionFind.connect(edge.first, edge.second);
    }
}

}

}
