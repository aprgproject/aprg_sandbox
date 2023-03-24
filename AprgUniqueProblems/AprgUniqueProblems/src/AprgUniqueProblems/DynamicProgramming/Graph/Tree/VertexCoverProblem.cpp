#include "VertexCoverProblem.hpp"

#include <algorithm>

using namespace alba::algorithm;
using namespace std;

namespace alba
{

VertexCoverProblem::VertexCoverProblem(Graph const& binaryTreeGraph, Vertex const rootOfTree)
    : m_nAryTreeGraph(binaryTreeGraph)
    , m_rootOfTree(rootOfTree)
    , m_childrenInTree(m_nAryTreeGraph, m_rootOfTree)
{}

VertexCoverProblem::Count VertexCoverProblem::getMinimumCountUsingNaiveRecursion() const
{
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Count result(0);
    if(!m_nAryTreeGraph.isEmpty())
    {
        result = getMinimumCountUsingNaiveRecursion(m_rootOfTree);
    }
    return result;
}

VertexCoverProblem::Count VertexCoverProblem::getMinimumCountUsingMemoizationDP() const
{
    // Time Complexity: O(n) where n is the number of nodes in given Binary tree.
    // Auxiliary Space: O(n)

    Count result(0);
    if(!m_nAryTreeGraph.isEmpty())
    {
        VertexToCountMap vertexToCountMap;
        result = getMinimumCountUsingMemoizationDP(vertexToCountMap, m_rootOfTree);
    }
    return result;
}

VertexCoverProblem::SetOfVertices VertexCoverProblem::getMinimumSetUsingMemoizationDP() const
{
    // Time Complexity: O(n) where n is the number of nodes in given Binary tree.
    // Auxiliary Space: O(n)

    SetOfVertices result;
    if(!m_nAryTreeGraph.isEmpty())
    {
        VertexToSetOfVerticesMap vertexToMinimumSetMap;
        result = getMinimumSetUsingMemoizationDP(vertexToMinimumSetMap, m_rootOfTree);
    }
    return result;
}

VertexCoverProblem::Count VertexCoverProblem::getMinimumCountUsingNaiveRecursion(
        Vertex const vertex) const
{
    Count countIfVertexIsIncluded(1);
    Count countIfVertexIsNotIncluded(0);
    for(Vertex const child : m_childrenInTree.getChildren(vertex))
    {
        Count childrenCount = getMinimumCountUsingNaiveRecursion(child);
        Count grandChildrenCount = 1;
        for(Vertex const grandChild : m_childrenInTree.getChildren(child))
        {
            grandChildrenCount += getMinimumCountUsingNaiveRecursion(grandChild);
        }
        countIfVertexIsIncluded += childrenCount;
        countIfVertexIsNotIncluded += grandChildrenCount;
    }
    return min(countIfVertexIsIncluded, countIfVertexIsNotIncluded);
}

VertexCoverProblem::Count VertexCoverProblem::getMinimumCountUsingMemoizationDP(
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
            Count childrenCount = getMinimumCountUsingNaiveRecursion(child);
            Count grandChildrenCount = 1;
            for(Vertex const grandChild : m_childrenInTree.getChildren(child))
            {
                grandChildrenCount += getMinimumCountUsingNaiveRecursion(grandChild);
            }
            countIfVertexIsIncluded += childrenCount;
            countIfVertexIsNotIncluded += grandChildrenCount;
        }
        Count result = min(countIfVertexIsIncluded, countIfVertexIsNotIncluded);
        vertexToCountMap.emplace(vertex, result);
        return result;
    }
    else
    {
        return it->second;
    }
}

VertexCoverProblem::SetOfVertices VertexCoverProblem::getMinimumSetUsingMemoizationDP(
        VertexToSetOfVerticesMap & vertexToMinimumSetMap,
        Vertex const vertex) const
{
    auto it = vertexToMinimumSetMap.find(vertex);
    if(it==vertexToMinimumSetMap.cend())
    {
        SetOfVertices setIfVertexIsIncluded{vertex};
        SetOfVertices setIfVertexIsNotIncluded;
        for(Vertex const child : m_childrenInTree.getChildren(vertex))
        {
            SetOfVertices childSet(getMinimumSetUsingMemoizationDP(vertexToMinimumSetMap, child));
            copy(childSet.cbegin(), childSet.cend(), inserter(setIfVertexIsIncluded, setIfVertexIsIncluded.begin()));
            setIfVertexIsNotIncluded.emplace(child);
            for(Vertex const grandChild : m_childrenInTree.getChildren(child))
            {
                SetOfVertices grandChildSet(getMinimumSetUsingMemoizationDP(vertexToMinimumSetMap, grandChild));
                copy(grandChildSet.cbegin(), grandChildSet.cend(), inserter(setIfVertexIsNotIncluded, setIfVertexIsNotIncluded.begin()));
            }
        }
        if(setIfVertexIsIncluded.size() <= setIfVertexIsNotIncluded.size())
        {
            vertexToMinimumSetMap.emplace(vertex, setIfVertexIsIncluded);
            return setIfVertexIsIncluded;
        }
        else
        {
            vertexToMinimumSetMap.emplace(vertex, setIfVertexIsNotIncluded);
            return setIfVertexIsNotIncluded;
        }
    }
    else
    {
        return it->second;
    }
}

}


