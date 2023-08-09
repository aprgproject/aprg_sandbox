#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>
#include <map>
#include <set>
#include <sstream>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class UndirectedGraphWithVertexToAdjacencyListsMap : public BaseUndirectedGraph<Vertex>
{
public:
    using AdjacencyList = std::set<Vertex>;
    using AdjacencyLists = std::map<Vertex, AdjacencyList>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;

    UndirectedGraphWithVertexToAdjacencyListsMap()
        : m_numberOfVertices(0U)
        , m_numberOfEdges(0U)
        , m_adjacencyLists{}
    {}

    bool hasAnyConnection(Vertex const& vertex) const override
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

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override
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

    Vertices getVertices() const override
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

    Edges getEdges() const override
    {
        Edges result;
        for(auto const& vertexAndAdjacencyListPair : m_adjacencyLists)
        {
            Vertex const& vertex1(vertexAndAdjacencyListPair.first);
            AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);
            if(!adjacencyList.empty())
            {
                for_each(adjacencyList.lower_bound(vertex1), adjacencyList.cend(), [&](Vertex const& vertex2)
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

private:
    unsigned int m_numberOfVertices;
    unsigned int m_numberOfEdges;
    AdjacencyLists m_adjacencyLists;
};

}

}
