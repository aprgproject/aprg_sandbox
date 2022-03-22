#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/Reachability/Reachability/ReachabilityInDigraphWithArrayUsingDfs.hpp>
#include <Algorithm/Graph/Reachability/TransitiveClosure/BaseTransitiveClosure.hpp>

#include <array>
#include <memory>

namespace alba
{

namespace algorithm
{

template<typename Vertex, unsigned int MAX_VERTEX_VALUE>
class TransitiveClosureWithArray : public BaseTransitiveClosure<Vertex>
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Reachability = ReachabilityInDigraphWithArrayUsingDfs<Vertex, MAX_VERTEX_VALUE>;
    using ReachabilityPointer = std::unique_ptr<Reachability>;
    using ReachabilityPointerArray = typename std::array<ReachabilityPointer, MAX_VERTEX_VALUE>;
    using ReachabilityInitializerList = typename std::initializer_list<Reachability>;

    TransitiveClosureWithArray(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_reachabilityPointerArray{}
    {
        initialize();
    }

    bool isReachable(Vertex const& sourceVertex, Vertex const& destinationVertex) const override
    {
        bool result(false);
        ReachabilityPointer const& pointer(m_reachabilityPointerArray.at(sourceVertex));
        if(pointer)
        {
            result = pointer->isReachable(destinationVertex);
        }
        return result;
    }

private:

    void initialize()
    {
        for(Vertex vertex=0; vertex<MAX_VERTEX_VALUE; vertex++)
        {
            m_reachabilityPointerArray[vertex] = std::make_unique<Reachability>(m_graph, vertex);
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    ReachabilityPointerArray m_reachabilityPointerArray;
};

}

}
