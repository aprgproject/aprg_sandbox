#include "DeBruijnSequences.hpp"

#include <Algorithm/Graph/PathSearch/EulerPath/DirectedGraph/HierholzerAlgorithmForDirectedGraph.hpp>



#include <Common/Debug/AlbaDebug.hpp>

using namespace alba::algorithm;
using namespace std;
namespace alba
{
DeBruijnSequences::DeBruijnSequences(
        unsigned int const substringSize,
        std::string const& alphabet)
    : m_substringSize(substringSize)
    , m_alphabet(alphabet)
{
    ALBA_PRINT2(m_substringSize, m_alphabet);
    initialize();
}
string DeBruijnSequences::getDeBruijnString() const
{
    string result;
    ALBA_PRINT1(m_graph.getDisplayableString());
    if(m_substringSize==1)
    {
        result = m_alphabet;    }
    else
    {
        HierholzerAlgorithmForDirectedGraph<string> eulerPathSearch(m_graph);
        auto eulerPath(eulerPathSearch.getEulerPath());
        ALBA_PRINT1(eulerPath);
        if(!eulerPath.empty())
        {
            result = eulerPath.at(0);            for(unsigned int i=1; i<eulerPath.size(); i++)
            {
                result += eulerPath.at(i).back();
            }        }
    }
    return result;
}

void DeBruijnSequences::initialize()
{
    ALBA_PRINT2(m_substringSize, m_alphabet);
    if(m_substringSize>1 && !m_alphabet.empty())
    {
        addAllSubstringsAsVertex();    }
}

void DeBruijnSequences::addAllSubstringsAsVertex(){
    string substring(m_substringSize-1, m_alphabet.front());
    addSubstringAsVertex(0U, substring);
}

void DeBruijnSequences::addSubstringAsVertex(
        unsigned int const depth,
        string const& substring)
{
    if(depth < m_substringSize)
    {
        for(char const c : m_alphabet)
        {
            string newSubstring = substring.substr(1, substring.length()) + c;
            addSubstringAsVertex(depth+1, newSubstring);
            m_graph.connect(substring, newSubstring);
        }
    }
}

}
