#include "AlbaSackReaderParameter.hpp"

using namespace std;

namespace alba
{

AlbaSackReaderParameter::AlbaSackReaderParameter(string const& typeName, string const& parameterName)
    : m_typeName(typeName)
    , m_parameterName(parameterName)
{}

string AlbaSackReaderParameter::getTypeName() const
{
    return m_typeName;
}

string AlbaSackReaderParameter::getParameterName() const
{
    return m_parameterName;
}
}
