#include "UndirectedGraphWithVertexToAdjacencyListsMap.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algorithm
{

UndirectedGraphWithVertexToAdjacencyListsMap::UndirectedGraphWithVertexToAdjacencyListsMap()
    : m_numberOfVertices(0U)
    , m_numberOfEdges(0U)
    , m_adjacencyLists{}
{}

bool UndirectedGraphWithVertexToAdjacencyListsMap::isConnected(Vertex const vertex1, Vertex const vertex2) const
{
    bool result(false);
    auto it = m_adjacencyLists.find(vertex1);
    if(it != m_adjacencyLists.cend())
    {
        AdjacencyList const& adjacencyList(it->second);
        result = adjacencyList.find(vertex2) != adjacencyList.cend();
    }
    return result;
}

unsigned int UndirectedGraphWithVertexToAdjacencyListsMap::getNumberOfVertices() const
{
    return m_numberOfVertices;
}

unsigned int UndirectedGraphWithVertexToAdjacencyListsMap::getNumberOfEdges() const
{
    return m_numberOfEdges;
}

Vertices UndirectedGraphWithVertexToAdjacencyListsMap::getAdjacentVerticesAt(Vertex const vertex) const
{
    Vertices result(false);
    auto it = m_adjacencyLists.find(vertex);
    if(it != m_adjacencyLists.cend())
    {
        AdjacencyList const& adjacencyList(it->second);
        result.reserve(adjacencyList.size());
        copy(adjacencyList.cbegin(), adjacencyList.cend(), back_inserter(result));
    }
    return result;
}

Vertices UndirectedGraphWithVertexToAdjacencyListsMap::getVertices() const
{
    Vertices result;
    for(auto const& vertexAndAdjacencyListPair : m_adjacencyLists)
    {
        Vertex const& vertex(vertexAndAdjacencyListPair.first);
        AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);
        if(!adjacencyList.empty())
        {
            result.emplace_back(vertex);
        }
    }
    return result;
}

Edges UndirectedGraphWithVertexToAdjacencyListsMap::getEdges() const
{
    Edges result;
    for(auto const& vertexAndAdjacencyListPair : m_adjacencyLists)
    {
        Vertex const& vertex1(vertexAndAdjacencyListPair.first);
        AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);
        if(!adjacencyList.empty())
        {
            for_each(adjacencyList.lower_bound(vertex1), adjacencyList.cend(), [&](Vertex const vertex2)
            {
                result.emplace_back(vertex1, vertex2);
            });
        }
    }
    return result;
}

string UndirectedGraphWithVertexToAdjacencyListsMap::getDisplayableString() const
{
    stringstream ss;
    ss << "Adjacency Lists: \n";
    for(auto const& vertexAndAdjacencyListPair : m_adjacencyLists)
    {
        Vertex const& vertex(vertexAndAdjacencyListPair.first);
        AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);
        if(!adjacencyList.empty())
        {
            ss << "Adjacent with vertex " << vertex << ": {";
            containerHelper::saveContentsToStream(ss, adjacencyList, containerHelper::StreamFormat::String);
            ss << "} \n";
        }
    }
    return ss.str();
}

void UndirectedGraphWithVertexToAdjacencyListsMap::connect(Vertex const vertex1, Vertex const vertex2)
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
        m_adjacencyLists[vertex1].emplace(vertex2);
        m_adjacencyLists[vertex2].emplace(vertex1);
    }
}

void UndirectedGraphWithVertexToAdjacencyListsMap::disconnect(Vertex const vertex1, Vertex const vertex2)
{
    if(isConnected(vertex1, vertex2))
    {
        m_numberOfEdges--;
        m_adjacencyLists[vertex1].erase(vertex2);
        m_adjacencyLists[vertex2].erase(vertex1);
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

bool UndirectedGraphWithVertexToAdjacencyListsMap::isAnyVertexConnectedAtThisVertex(Vertex const vertex) const
{
    bool result(false);
    auto it = m_adjacencyLists.find(vertex);
    if(it != m_adjacencyLists.cend())
    {
        AdjacencyList const& adjacencyList(it->second);
        result = !adjacencyList.empty();
    }
    return result;
}

}

}

