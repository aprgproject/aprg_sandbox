#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <algorithm>
#include <sstream>
#include <set>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class UndirectedGraphWithListOfEdges : public BaseUndirectedGraph<Vertex>
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;

    UndirectedGraphWithListOfEdges()
        : m_numberOfEdges(0U)
        , m_edges{}
    {}

    bool isEmpty() const
    {
        return m_edges.empty();
    }

    bool hasAnyConnection(Vertex const& vertex) const override
    {
        bool result(false);
        auto itLower = m_edges.lower_bound({vertex, Vertex{}});
        if(itLower != m_edges.cend())
        {
            result = itLower->first == vertex;        }
        return result;
    }
    bool isDirectlyConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        return m_edges.find({vertex1, vertex2}) != m_edges.cend();
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
        for(auto it = m_edges.lower_bound({vertex, Vertex{}}); it!=m_edges.cend() && it->first==vertex; it++)
        {
            result.emplace_back(it->second);
        };
        return result;
    }
    Vertices getVertices() const override
    {
        Vertices result;        for(auto const& edge : m_edges)
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
        for(auto const& edge : m_edges)
        {
            if(edge.first <= edge.second)
            {
                result.emplace_back(edge);
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
        if(!isDirectlyConnected(vertex1, vertex2))
        {
            m_numberOfEdges++;
            m_edges.emplace(vertex1, vertex2);
            m_edges.emplace(vertex2, vertex1);
        }
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(isDirectlyConnected(vertex1, vertex2))
        {
            m_numberOfEdges--;
            m_edges.erase({vertex1, vertex2});
            m_edges.erase({vertex2, vertex1});
        }
    }

    void clear()
    {
        m_numberOfEdges = 0;
        m_edges.clear();
    }

    SetOfEdges& getSetOfEdgesReference()
    {
        return m_edges;
    }

protected:

    unsigned int m_numberOfEdges;
    SetOfEdges m_edges;
};

}

}
