#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>
#include <array>
#include <set>

namespace alba
{

namespace algorithm
{

template <typename Vertex, unsigned int MAX_VERTEX_VALUE>
class UndirectedGraphWithArrayOfAdjacencyLists : public BaseUndirectedGraph<Vertex>
{
public:
    using AdjacencyList = std::set<Vertex>;
    using AdjacencyLists = std::array<AdjacencyList, MAX_VERTEX_VALUE>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;

    UndirectedGraphWithArrayOfAdjacencyLists()
        : m_numberOfVertices(0U)
        , m_numberOfEdges(0U)
        , m_adjacencyLists{}
    {}

    bool hasAnyConnection(Vertex const& vertex) const override
    {
        return !m_adjacencyLists.at(vertex).empty();
    }

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        AdjacencyList const& adjacencyList(m_adjacencyLists.at(vertex1));
        return adjacencyList.find(vertex2) != adjacencyList.cend();
    }

    unsigned int getNumberOfVertices() const override
    {
        return m_numberOfVertices;
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
        Vertices result;
        for(Vertex vertex=0; vertex<m_adjacencyLists.size(); vertex++)
        {
            if(!m_adjacencyLists.at(vertex).empty())
            {
                result.emplace_back(vertex);
            }
        }
        return result;
    }

    Edges getEdges() const override
    {
        Edges result;
        for(Vertex vertex1=0; vertex1<m_adjacencyLists.size(); vertex1++)
        {
            AdjacencyList const& adjacencyList(m_adjacencyLists.at(vertex1));
            if(!adjacencyList.empty())
            {
                std::for_each(adjacencyList.lower_bound(vertex1), adjacencyList.cend(), [&](Vertex const& vertex2)
                {
                    result.emplace_back(vertex1, vertex2);
                });
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

    void connect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(!isConnected(vertex1, vertex2))
        {
            if(!hasAnyConnection(vertex1))
            {
                m_numberOfVertices++;
            }
            if(!hasAnyConnection(vertex2))
            {
                m_numberOfVertices++;
            }
            m_numberOfEdges++;
            m_adjacencyLists[vertex1].emplace(vertex2);
            m_adjacencyLists[vertex2].emplace(vertex1);
        }
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(isConnected(vertex1, vertex2))
        {
            m_numberOfEdges--;
            m_adjacencyLists[vertex1].erase(vertex2);
            m_adjacencyLists[vertex2].erase(vertex1);
            if(!hasAnyConnection(vertex1))
            {
                m_numberOfVertices--;
            }
            if(!hasAnyConnection(vertex2))
            {
                m_numberOfVertices--;
            }
        }
    }

    void clear()
    {
        m_numberOfVertices = 0;
        m_numberOfEdges = 0;
        for(Vertex vertex=0; vertex<m_adjacencyLists.size(); vertex++)
        {
            m_adjacencyLists[vertex].clear();
        }
    }

private:
    unsigned int m_numberOfVertices;
    unsigned int m_numberOfEdges;
    AdjacencyLists m_adjacencyLists;
};

}

}
