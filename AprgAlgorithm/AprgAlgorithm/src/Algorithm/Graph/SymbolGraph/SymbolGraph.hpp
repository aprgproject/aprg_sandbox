#pragma once

#include <Algorithm/Graph/GraphTypes.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Object>
Vertex getUniqueVertexIdentifier(Object const& object);


template <typename Vertex, typename Object, typename Graph>
class SymbolGraph : public GraphTypes<Vertex>
{
    using SymbolTable = std::map<Vertex, Object>;
public:

    bool contains(Object const& object) const
    {
        m_symbolTable.find(getUniqueVertexIdentifier(object)) != m_symbolTable.cend();
    }

    Vertex getKey(Object const& object) const
    {
        return getUniqueVertexIdentifier(object);
    }

    Object getName(Vertex const& key) const
    {
        Object result{};
        auto it = m_symbolTable.find(key);
        if(it != m_symbolTable.cend())
        {
            result = it->second;
        }
        return result;
    }

    Graph const& getGraph()
    {
        return m_graph;
    }

    void connect(Object const& object1, Object const& object2)
    {
        Vertex id1(getUniqueVertexIdentifier(object1));
        Vertex id2(getUniqueVertexIdentifier(object2));
        m_graph.connect(id1, id2);
        m_symbolTable[id1] = object1;
        m_symbolTable[id2] = object2;
    }

    void disconnect(Object const& object1, Object const& object2)
    {
        Vertex id1(getUniqueVertexIdentifier(object1));
        Vertex id2(getUniqueVertexIdentifier(object2));
        m_graph.disconnect(id1, id2);
        if(!m_graph.hasAnyConnection(id1))
        {
            m_symbolTable.erase(id1);
        }
        if(!m_graph.hasAnyConnection(id2))
        {
            m_symbolTable.erase(id2);
        }
    }

private:
    Graph m_graph;
    SymbolTable m_symbolTable;
};

}

}

}
