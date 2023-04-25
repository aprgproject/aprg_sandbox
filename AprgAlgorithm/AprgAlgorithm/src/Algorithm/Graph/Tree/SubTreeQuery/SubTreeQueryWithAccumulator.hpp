#pragma once

#include <Algorithm/Graph/Tree/SubTreeQuery/SubTreeQuery.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>
#include <Algorithm/Search/RangeQuery/RangeQueryWithAccumulator.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class SubTreeQueryWithAccumulator : public SubTreeQuery<Vertex> {
public:
    using BaseClass = SubTreeQuery<Vertex>;
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using RangeQuery = RangeQueryWithAccumulator<Vertices>;
    using AccumulatorFunction = typename RangeQuery::AccumulatorFunction;
    using Counts = std::vector<unsigned int>;
    using VertexToIndexMap = std::map<Vertex, unsigned int>;

    SubTreeQueryWithAccumulator(
        BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree, AccumulatorFunction const& accumulator,
        AccumulatorFunction const& inverseAccumulator)
        : BaseClass(graph, rootOfTree),
          b_verticesInDfsPreOrder(BaseClass::m_verticesInDfsPreOrder),
          b_subTreeSize(BaseClass::m_subTreeSize),
          b_vertexToIndexMap(BaseClass::m_vertexToIndexMap),
          m_rangeQuery(b_verticesInDfsPreOrder, accumulator, inverseAccumulator) {}

    Vertex getAccumulatedValueOfSubTreeAt(Vertex const& subRoot) {
        Vertex result{};
        auto it = b_vertexToIndexMap.find(subRoot);
        if (it != b_vertexToIndexMap.cend()) {
            unsigned int indexOfSubRoot = it->second;
            result = m_rangeQuery.getAccumulatedValueOnInterval(
                indexOfSubRoot, indexOfSubRoot + b_subTreeSize.at(indexOfSubRoot) - 1);
        }
        return result;
    }

private:
    Vertices const& b_verticesInDfsPreOrder;
    Counts const& b_subTreeSize;
    VertexToIndexMap const& b_vertexToIndexMap;
    RangeQuery m_rangeQuery;
};

}  // namespace algorithm

}  // namespace alba
