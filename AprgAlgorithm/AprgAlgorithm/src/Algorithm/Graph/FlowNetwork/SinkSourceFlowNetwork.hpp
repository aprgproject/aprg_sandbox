#pragma once

#include <Algorithm/Graph/FlowNetwork/FlowNetwork.hpp>

#include <algorithm>
#include <sstream>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename FlowDataType, typename DirectedGraph>
class SinkSourceFlowNetwork : public FlowNetwork<Vertex, FlowDataType, DirectedGraph>
{
public:
    using BaseClass = FlowNetwork<Vertex, FlowDataType, DirectedGraph>;

    // An ST-flow network has two identified vertices, a source "s" and a sink "t";

    SinkSourceFlowNetwork(Vertex const& source, Vertex const& sink)
        : BaseClass()
        , m_source(source)
        , m_sink(sink)
    {}

    Vertex getSourceVertex() const
    {
        return m_source;
    }

    Vertex getSinkVertex() const
    {
        return m_sink;
    }

private:
    Vertex m_source;
    Vertex m_sink;
};

}

}
