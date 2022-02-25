#include "UndirectedGraphWithListOfEdges.hpp"

#include <algorithm>
#include <sstream>

namespace alba
{

namespace algorithm
{

UndirectedGraphWithListOfEdges::EdgeInSet::EdgeInSet(Vertex const vertex1, Vertex const vertex2)
    : Edge{vertex1, vertex2}
{}

bool UndirectedGraphWithListOfEdges::EdgeInSet::operator<(EdgeInSet const& otherEdge) const
{
    bool result(false);
    if(first != otherEdge.first)
    {
        result = first < otherEdge.first;
    }
    else
    {
        result = second < otherEdge.second;
    }
    return result;
}

UndirectedGraphWithListOfEdges::UndirectedGraphWithListOfEdges()
    : m_numberOfVertices(0U)
    , m_numberOfEdges(0U)
    , m_edges{}
{}

bool UndirectedGraphWithListOfEdges::isConnected(Vertex const vertex1, Vertex const vertex2) const
{
    return m_edges.find(EdgeInSet(vertex1, vertex2)) != m_edges.cend();
}

unsigned int UndirectedGraphWithListOfEdges::getNumberOfVertices() const
{
    return m_numberOfVertices;
}

unsigned int UndirectedGraphWithListOfEdges::getNumberOfEdges() const
{
    return m_numberOfEdges;
}

Vertices UndirectedGraphWithListOfEdges::getAdjacentVerticesAt(Vertex const vertex) const
{
    Vertices result;
    auto itLower = m_edges.lower_bound(EdgeInSet(vertex, 0));
    auto itUpper = m_edges.lower_bound(EdgeInSet(vertex+1, 0));
    std::for_each(itLower, itUpper, [&](EdgeInSet const& edgeInSet)
    {
        result.emplace_back(edgeInSet.second);
    });
    return result;
}

Vertices UndirectedGraphWithListOfEdges::getVertices() const
{
    Vertices result;
    for(auto const& edge : m_edges)
    {
        Vertex vertex(edge.first);
        if(result.empty())
        {
            result.emplace_back(vertex);
        }
        else if(result.back() != vertex)
        {
            result.emplace_back(vertex);
        }
    }
    return result;
}

Edges UndirectedGraphWithListOfEdges::getEdges() const
{
    Edges result;
    for(auto const& edgeInSet : m_edges)
    {
        if(edgeInSet.first <= edgeInSet.second)
        {
            result.emplace_back(static_cast<Edge>(edgeInSet));
        }
    }
    return result;
}

std::string UndirectedGraphWithListOfEdges::getDisplayableString() const
{
    std::stringstream ss;
    ss << "Edges: {";
    for(auto const& edge : m_edges)
    {
        ss << edge.first << "<->" << edge.second << ", ";
    }
    ss << "}";
    return ss.str();
}

void UndirectedGraphWithListOfEdges::connect(Vertex const vertex1, Vertex const vertex2)
{
    if(!isConnected(vertex1, vertex2))
    {
        if(!isAnyVertexConnectedAtThisVertex(vertex1))
        {
            m_numberOfVertices++;
        }
        if(!isAnyVertexConnectedAtThisVertex(vertex2))
        {
            m_numberOfVertices++;
        }
        m_numberOfEdges++;
        m_edges.emplace(vertex1, vertex2);
        m_edges.emplace(vertex2, vertex1);
    }
}

void UndirectedGraphWithListOfEdges::disconnect(Vertex const vertex1, Vertex const vertex2)
{
    if(isConnected(vertex1, vertex2))
    {
        m_numberOfEdges--;
        m_edges.erase({vertex1, vertex2});
        m_edges.erase({vertex2, vertex1});
        if(!isAnyVertexConnectedAtThisVertex(vertex1))
        {
            m_numberOfVertices--;
        }
        if(!isAnyVertexConnectedAtThisVertex(vertex2))
        {
            m_numberOfVertices--;
        }
    }
}

bool UndirectedGraphWithListOfEdges::isAnyVertexConnectedAtThisVertex(Vertex const vertex) const
{
    bool result(false);
    auto itLower = m_edges.lower_bound({vertex, 0});
    if(itLower != m_edges.cend())
    {
        result = itLower->first == vertex;
    }
    return result;
}

}

}
