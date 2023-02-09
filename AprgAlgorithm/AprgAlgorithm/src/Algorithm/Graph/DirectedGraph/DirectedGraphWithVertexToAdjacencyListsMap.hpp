#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>
#include <map>

namespace alba
{
namespace algorithm
{
template <typename Vertex>
class DirectedGraphWithVertexToAdjacencyListsMap : public BaseDirectedGraph<Vertex>
{
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using AdjacencyList = SetOfVertices;
    using AdjacencyLists = std::map<Vertex, AdjacencyList>;

    DirectedGraphWithVertexToAdjacencyListsMap()
        : m_numberOfEdges(0U)
        , m_adjacencyLists{}
    {}

    bool isEmpty() const
    {
        return m_adjacencyLists.empty();
    }

    bool isDirectlyConnected(Vertex const& sourceVertex, Vertex const& destinationVertex) const override
    {
        bool result(false);
        auto it = m_adjacencyLists.find(sourceVertex);
        if(it != m_adjacencyLists.cend())
        {
            AdjacencyList const& adjacencyList(it->second);
            result = adjacencyList.find(destinationVertex) != adjacencyList.cend();
        }
        return result;
    }

    unsigned int getNumberOfVertices() const override
    {
        return getUniqueVertices().size();
    }

    unsigned int getNumberOfEdges() const override
    {
        return m_numberOfEdges;
    }

    Vertices getAdjacentVerticesAt(Vertex const& vertex) const override
    {
        Vertices result(false);
        auto it = m_adjacencyLists.find(vertex);
        if(it != m_adjacencyLists.cend())
        {
            AdjacencyList const& adjacencyList(it->second);
            result.reserve(adjacencyList.size());
            std::copy(adjacencyList.cbegin(), adjacencyList.cend(), std::back_inserter(result));
        }
        return result;
    }

    Vertices getVertices() const override
    {
        SetOfVertices uniqueVertices(getUniqueVertices());
        return Vertices(uniqueVertices.cbegin(), uniqueVertices.cend());
    }

    Edges getEdges() const override
    {
        Edges result;
        for(auto const& vertexAndAdjacencyListPair : m_adjacencyLists)
        {
            Vertex const& sourceVertex(vertexAndAdjacencyListPair.first);
            AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);
            for(Vertex const& destinationVertex : adjacencyList)
            {
                result.emplace_back(sourceVertex, destinationVertex);
            }
        }
        return result;
    }

    void connect(Vertex const& sourceVertex, Vertex const& destinationVertex) override
    {
        if(!isDirectlyConnected(sourceVertex, destinationVertex))        {
            m_numberOfEdges++;
            m_adjacencyLists[sourceVertex].emplace(destinationVertex);
        }    }

    void disconnect(Vertex const& sourceVertex, Vertex const& destinationVertex) override
    {
        if(isDirectlyConnected(sourceVertex, destinationVertex))
        {
            m_numberOfEdges--;
            m_adjacencyLists[sourceVertex].erase(destinationVertex);
        }
    }

    void clear()
    {
        m_numberOfEdges = 0;
        m_adjacencyLists.clear();
    }

protected:

    SetOfVertices getUniqueVertices() const
    {
        SetOfVertices uniqueVertices;        for(auto const& vertexAndAdjacencyListPair : m_adjacencyLists)
        {
            Vertex const& sourceVertex(vertexAndAdjacencyListPair.first);
            AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);            uniqueVertices.emplace(sourceVertex);
            std::copy(adjacencyList.cbegin(), adjacencyList.cend(), std::inserter(uniqueVertices, uniqueVertices.cbegin()));
        }
        return uniqueVertices;
    }

    friend std::ostream & operator<<(std::ostream & out, DirectedGraphWithVertexToAdjacencyListsMap const& graph)
    {
        out << "Adjacency Lists: \n";
        for(auto const& vertexAndAdjacencyListPair : graph.m_adjacencyLists)
        {
            Vertex const& vertex(vertexAndAdjacencyListPair.first);
            AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);
            if(!adjacencyList.empty())
            {
                out << "Adjacent with vertex " << vertex << ": {";
                containerHelper::saveContentsToStream(out, adjacencyList, containerHelper::StreamFormat::String);
                out << "} \n";
            }
        }
        return out;
    }

    unsigned int m_numberOfEdges;
    AdjacencyLists m_adjacencyLists;
};
}

}