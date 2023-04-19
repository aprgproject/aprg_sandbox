#include "LargestIndependentSetProblem.hpp"

#include <algorithm>

using namespace alba::algorithm;
using namespace std;

namespace alba
{

LargestIndependentSetProblem::LargestIndependentSetProblem(Graph const& nAryTreeGraph, Vertex const rootOfTree)
    : m_nAryTreeGraph(nAryTreeGraph)
    , m_rootOfTree(rootOfTree)
    , m_childrenInTree(m_nAryTreeGraph, m_rootOfTree)
{}

LargestIndependentSetProblem::Count LargestIndependentSetProblem::getMaximumCountUsingNaiveRecursion() const
{
    // Time Complexity: Exponential
    // Auxiliary Space: Constant
    Count result(0);
    if(!m_nAryTreeGraph.isEmpty())
    {
        result = getMaximumCountUsingNaiveRecursion(m_rootOfTree);
    }
    return result;
}

LargestIndependentSetProblem::Count LargestIndependentSetProblem::getMaximumCountUsingMemoizationDP() const{
    // Time Complexity: O(n) where n is the number of nodes in given Binary tree.
    // Auxiliary Space: O(n)

    Count result(0);
    if(!m_nAryTreeGraph.isEmpty())
    {
        VertexToCountMap vertexToCountMap;
        result = getMaximumCountUsingMemoizationDP(vertexToCountMap, m_rootOfTree);
    }
    return result;
}
LargestIndependentSetProblem::SetOfVertices LargestIndependentSetProblem::getMaximumSetUsingMemoizationDP() const
{
    // Time Complexity: O(n) where n is the number of nodes in given Binary tree.
    // Auxiliary Space: O(n)

    SetOfVertices result;
    if(!m_nAryTreeGraph.isEmpty())
    {
        VertexToSetOfVerticesMap vertexToMaximumSetMap;
        result = getMaximumSetUsingMemoizationDP(vertexToMaximumSetMap, m_rootOfTree);
    }
    return result;
}
LargestIndependentSetProblem::Count LargestIndependentSetProblem::getMaximumCountUsingNaiveRecursion(
        Vertex const vertex) const
{
    Count countIfVertexIsIncluded(1);
    Count countIfVertexIsNotIncluded(0);
    for(Vertex const child : m_childrenInTree.getChildren(vertex))
    {
        countIfVertexIsNotIncluded += getMaximumCountUsingNaiveRecursion(child);
        for(Vertex const grandChild : m_childrenInTree.getChildren(child))
        {
            countIfVertexIsIncluded += getMaximumCountUsingNaiveRecursion(grandChild);
        }
    }
    return max(countIfVertexIsIncluded, countIfVertexIsNotIncluded);
}

LargestIndependentSetProblem::Count LargestIndependentSetProblem::getMaximumCountUsingMemoizationDP(
        VertexToCountMap & vertexToCountMap,
        Vertex const vertex) const
{
    auto it = vertexToCountMap.find(vertex);
    if(it==vertexToCountMap.cend())
    {
        Count countIfVertexIsIncluded(1);
        Count countIfVertexIsNotIncluded(0);
        for(Vertex const child : m_childrenInTree.getChildren(vertex))
        {
            countIfVertexIsNotIncluded += getMaximumCountUsingMemoizationDP(vertexToCountMap, child);
            for(Vertex const grandChild : m_childrenInTree.getChildren(child))
            {
                countIfVertexIsIncluded += getMaximumCountUsingMemoizationDP(vertexToCountMap, grandChild);
            }
        }
        Count result = max(countIfVertexIsIncluded, countIfVertexIsNotIncluded);
        vertexToCountMap.emplace(vertex, result);
        return result;
    }
    else
    {
        return it->second;
    }
}

LargestIndependentSetProblem::SetOfVertices LargestIndependentSetProblem::getMaximumSetUsingMemoizationDP(
        VertexToSetOfVerticesMap & vertexToMaximumSetMap,
        Vertex const vertex) const
{
    auto it = vertexToMaximumSetMap.find(vertex);
    if(it==vertexToMaximumSetMap.cend())
    {
        SetOfVertices setIfVertexIsIncluded{vertex};
        SetOfVertices setIfVertexIsNotIncluded;
        for(Vertex const child : m_childrenInTree.getChildren(vertex))
        {
            SetOfVertices childSet(getMaximumSetUsingMemoizationDP(vertexToMaximumSetMap, child));
            copy(childSet.cbegin(), childSet.cend(), inserter(setIfVertexIsNotIncluded, setIfVertexIsNotIncluded.begin()));
            for(Vertex const grandChild : m_childrenInTree.getChildren(child))
            {
                SetOfVertices grandChildSet(getMaximumSetUsingMemoizationDP(vertexToMaximumSetMap, grandChild));
                copy(grandChildSet.cbegin(), grandChildSet.cend(), inserter(setIfVertexIsIncluded, setIfVertexIsIncluded.begin()));
            }
        }
        if(setIfVertexIsIncluded.size() >= setIfVertexIsNotIncluded.size())
        {
            vertexToMaximumSetMap.emplace(vertex, setIfVertexIsIncluded);
            return setIfVertexIsIncluded;
        }        else
        {
            vertexToMaximumSetMap.emplace(vertex, setIfVertexIsNotIncluded);
            return setIfVertexIsNotIncluded;
        }
    }
    else
    {
        return it->second;
    }
}

}


