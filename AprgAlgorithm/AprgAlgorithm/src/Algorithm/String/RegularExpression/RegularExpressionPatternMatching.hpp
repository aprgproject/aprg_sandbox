#pragma once

#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

#include <stack>
#include <string>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Index>
class RegularExpressionPatternMatching
{
public:
    using Indexes = std::vector<Index>;

    RegularExpressionPatternMatching(std::string const& regularExpression)
        : m_regularExpression(regularExpression)
    {
        initialize();
    }

    bool isAMatch(std::string const& stringToCheck) const
    {
        bool result(false);
        Indexes pc;
        PathSearchUsingDfs<Index> pathSearch(m_nfaGraph, Index(0));
        for(Index const index : m_nfaGraph.getVertices())
        {
            if(pathSearch.hasPathTo(index))
            {
                pc.emplace_back(index);
            }
        }
        Index stringToCheckLength(stringToCheck.size());
        Index regularExpressionLength(m_regularExpression.size());
        for(Index i=0; i<stringToCheckLength; i++)
        {
            Indexes match;
            for(Index const index : pc)
            {
                if(index < regularExpressionLength)
                {
                    char charInRegularExpression(m_regularExpression.at(index));
                    if(charInRegularExpression == stringToCheck.at(i) || charInRegularExpression == '.')
                    {
                        match.emplace_back(index+1);
                    }
                }
            }
            pc.clear();
            if(!match.empty())
            {
                PathSearchUsingDfs<Index> pathSearch(m_nfaGraph, match.front());
                for(Index const index : m_nfaGraph.getVertices())
                {
                    if(pathSearch.hasPathTo(index))
                    {
                        pc.emplace_back(index);
                    }
                }
            }
        }
        for(Index const index : pc)
        {
            if(index == regularExpressionLength)
            {
                result = true;
                break;
            }
        }
        return result;
    }

private:

    void initialize()
    {
        std::stack<Index> operatorIndexes;
        Index regularExpressionLength(m_regularExpression.length());
        for(Index i=0; i<regularExpressionLength; i++)
        {
            Index lp = i;
            if(m_regularExpression.at(i) == '(' || m_regularExpression.at(i) == '|')
            {
                operatorIndexes.push(i);
            }
            else if(m_regularExpression.at(i) == ')')
            {
                Index operatorIndex(operatorIndexes.top());
                operatorIndexes.pop();
                if(m_regularExpression.at(operatorIndex) == '|')
                {
                    lp = operatorIndexes.top();
                    operatorIndexes.pop();
                    m_nfaGraph.connect(lp, operatorIndex+1);
                    m_nfaGraph.connect(operatorIndex, i);
                }
                else
                {
                    lp = operatorIndex;
                }
            }
            if(i < regularExpressionLength-1 && m_regularExpression.at(i+1) == '*')
            {
                m_nfaGraph.connect(lp, i+1);
                m_nfaGraph.connect(i+1, lp);
            }
            if(m_regularExpression.at(i) == '(' || m_regularExpression.at(i) == '*' || m_regularExpression.at(i) == ')')
            {
                m_nfaGraph.connect(i, i+1);
            }
        }
    }

    std::string m_regularExpression;
    DirectedGraphWithListOfEdges<Index> m_nfaGraph;
};

}

}
