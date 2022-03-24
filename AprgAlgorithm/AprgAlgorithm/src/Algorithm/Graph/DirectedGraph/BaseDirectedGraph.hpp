#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BaseDirectedGraph : public BaseGraph<Vertex>
{
public:
    using Edges = typename GraphTypes<Vertex>::Edges;

    GraphDirectionType getGraphDirectionType() const
    {
        return DIRECTION_TYPE;
    }

    void reverseDirections()    {
        Edges originalEdges(this->getEdges());
        this->clear();
        for(auto const& originalEdge : originalEdges)
        {
            this->connect(originalEdge.second, originalEdge.first);
        }
    }

    static constexpr GraphDirectionType DIRECTION_TYPE = GraphDirectionType::Directed;
};

}
}
