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

template <typename Vertex>
class UndirectedGraphWithVertexToAdjacencyListsMap : public BaseUndirectedGraph<Vertex>
{
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using AdjacencyList = typename GraphTypes<Vertex>::SetOfVertices;
    using AdjacencyLists = std::map<Vertex, AdjacencyList>;

    UndirectedGraphWithVertexToAdjacencyListsMap()
        : m_numberOfEdges(0U)
    {}

    bool isEmpty() const
    {
        return m_adjacencyLists.empty();
    }

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

    bool isDirectlyConnected(Vertex const& vertex1, Vertex const& vertex2) const override
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
        unsigned int result(0);
        for(auto const& vertexAndAdjacencyListPair : m_adjacencyLists)
        {
            AdjacencyList const& adjacencyList(vertexAndAdjacencyListPair.second);
            if(!adjacencyList.empty())
            {
                result++;
            }
        }
        return result;
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
        if(!isDirectlyConnected(vertex1, vertex2))
        {
            m_numberOfEdges++;
            m_adjacencyLists[vertex1].emplace(vertex2);
            m_adjacencyLists[vertex2].emplace(vertex1);
        }
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(isDirectlyConnected(vertex1, vertex2))
        {
            m_numberOfEdges--;
            m_adjacencyLists[vertex1].erase(vertex2);
            m_adjacencyLists[vertex2].erase(vertex1);
        }
    }

    void clear()
    {
        m_numberOfEdges = 0;
        m_adjacencyLists.clear();
    }

protected:
    unsigned int m_numberOfEdges;
    AdjacencyLists m_adjacencyLists;
};

}

}
