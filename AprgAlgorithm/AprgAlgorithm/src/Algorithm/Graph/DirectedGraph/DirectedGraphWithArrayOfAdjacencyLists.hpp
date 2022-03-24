#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <array>
#include <set>

namespace alba
{

namespace algorithm
{

template <typename Vertex, unsigned int MAX_VERTEX_VALUE>
class DirectedGraphWithArrayOfAdjacencyLists : public BaseDirectedGraph<Vertex>
{
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using AdjacencyList = SetOfVertices;
    using AdjacencyLists = std::array<AdjacencyList, MAX_VERTEX_VALUE>;

    DirectedGraphWithArrayOfAdjacencyLists()
        : m_numberOfEdges(0U)
        , m_adjacencyLists{}
    {}

    bool isConnected(Vertex const& sourceVertex, Vertex const& destinationVertex) const override
    {
        AdjacencyList const& adjacencyList(m_adjacencyLists.at(sourceVertex));
        return adjacencyList.find(destinationVertex) != adjacencyList.cend();
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
        AdjacencyList const& adjacencyList(m_adjacencyLists.at(vertex));
        return Vertices(adjacencyList.cbegin(), adjacencyList.cend());
    }

    Vertices getVertices() const override
    {
        SetOfVertices uniqueVertices(getUniqueVertices());
        return Vertices(uniqueVertices.cbegin(), uniqueVertices.cend());
    }

    Edges getEdges() const override
    {
        Edges result;
        for(Vertex vertex1=0; vertex1<m_adjacencyLists.size(); vertex1++)
        {
            AdjacencyList const& adjacencyList(m_adjacencyLists.at(vertex1));
            for(Vertex const& vertex2 : adjacencyList)
            {
                result.emplace_back(vertex1, vertex2);
            }
        }
        return result;
    }

    std::string getDisplayableString() const override
    {
        std::stringstream ss;
        ss << "Adjacency Lists: \n";
        for(Vertex vertex=0; vertex<m_adjacencyLists.size(); vertex++)
        {
            AdjacencyList const& adjacencyList(m_adjacencyLists.at(vertex));
            if(!adjacencyList.empty())
            {
                ss << "Adjacent with vertex " << vertex << ": {";
                containerHelper::saveContentsToStream(ss, adjacencyList, containerHelper::StreamFormat::String);
                ss << "} \n";
            }
        }
        return ss.str();
    }

    void connect(Vertex const& sourceVertex, Vertex const& destinationVertex) override
    {
        if(!isConnected(sourceVertex, destinationVertex))
        {
            m_numberOfEdges++;
            m_adjacencyLists[sourceVertex].emplace(destinationVertex);
        }
    }

    void disconnect(Vertex const& sourceVertex, Vertex const& destinationVertex) override
    {
        if(isConnected(sourceVertex, destinationVertex))
        {
            m_numberOfEdges--;
            m_adjacencyLists[sourceVertex].erase(destinationVertex);
        }
    }

    void clear()
    {
        m_numberOfEdges = 0;
        for(Vertex sourceVertex=0; sourceVertex<m_adjacencyLists.size(); sourceVertex++)
        {
            m_adjacencyLists[sourceVertex].clear();
        }
    }

protected:
    SetOfVertices getUniqueVertices() const
    {
        SetOfVertices uniqueVertices;        for(Vertex sourceVertex=0; sourceVertex<m_adjacencyLists.size(); sourceVertex++)
        {
            AdjacencyList const& adjacencyList(m_adjacencyLists.at(sourceVertex));
            if(!adjacencyList.empty())
            {
                uniqueVertices.emplace(sourceVertex);
                std::copy(adjacencyList.cbegin(), adjacencyList.cend(), std::inserter(uniqueVertices, uniqueVertices.cbegin()));
            }
        }
        return uniqueVertices;
    }

    unsigned int m_numberOfEdges;
    AdjacencyLists m_adjacencyLists;
};

}

}
