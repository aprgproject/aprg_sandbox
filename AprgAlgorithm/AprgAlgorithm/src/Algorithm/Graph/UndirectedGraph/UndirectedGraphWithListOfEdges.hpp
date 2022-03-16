#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <algorithm>
#include <sstream>
#include <set>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class UndirectedGraphWithListOfEdges : public BaseUndirectedGraph<Vertex>
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeInSet = typename GraphTypes<Vertex>::EdgeInSet;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;

    UndirectedGraphWithListOfEdges()
        : m_numberOfEdges(0U)
        , m_edges{}
    {}

    bool hasAnyConnection(Vertex const& vertex) const override
    {
        bool result(false);
        auto itLower = m_edges.lower_bound({vertex, 0});
        if(itLower != m_edges.cend())
        {
            result = itLower->first == vertex;
        }
        return result;
    }

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        return m_edges.find(EdgeInSet(vertex1, vertex2)) != m_edges.cend();
    }

    unsigned int getNumberOfVertices() const override
    {
        return getVertices().size();
    }

    unsigned int getNumberOfEdges() const override
    {
        return m_numberOfEdges;
    }

    Vertices getAdjacentVerticesAt(Vertex const& vertex) const override
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

    Vertices getVertices() const override
    {
        Vertices result;
        for(auto const& edge : m_edges)
        {
            Vertex const& vertex(edge.first);
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

    Edges getEdges() const override
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

    std::string getDisplayableString() const override
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

    void connect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(!isConnected(vertex1, vertex2))
        {
            m_numberOfEdges++;
            m_edges.emplace(vertex1, vertex2);
            m_edges.emplace(vertex2, vertex1);
        }
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(isConnected(vertex1, vertex2))
        {
            m_numberOfEdges--;
            m_edges.erase({vertex1, vertex2});
            m_edges.erase({vertex2, vertex1});
        }
    }

private:

    unsigned int m_numberOfEdges;
    SetOfEdges m_edges;
};

}

}
