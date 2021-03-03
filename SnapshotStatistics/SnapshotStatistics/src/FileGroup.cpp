#include "FileGroup.hpp"

using namespace std;

namespace alba
{

FileGroup::FileGroup(string const& wildcardName, ConditionFunction const& condition)
    : m_wildcardName(wildcardName)
    , m_condition(condition)
{}

bool FileGroup::isInFileGroup(string const& fileName) const
{
    return m_condition(fileName);
}

string FileGroup::getWildcardName() const
{
    return m_wildcardName;
}



}
