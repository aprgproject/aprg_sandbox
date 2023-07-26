#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class BaseDirectedGraph : public BaseGraph<Vertex> {
public:
    using Edges = typename GraphTypes<Vertex>::Edges;

    ~BaseDirectedGraph() override = default;  // no need for virtual destructor because base destructor is virtual
                                              // (similar to other virtual functions)

    GraphDirectionType getGraphDirectionType() const override { return DIRECTION_TYPE; }

    void reverseDirections() {
        Edges originalEdges(this->getEdges());
        this->clear();
        for (auto const& [startVertexOfEdge, endVertexOfEdge] : originalEdges) {
            this->connect(endVertexOfEdge, startVertexOfEdge);
        }
    }

    static constexpr GraphDirectionType DIRECTION_TYPE = GraphDirectionType::Directed;
};

}  // namespace algorithm

}  // namespace alba
