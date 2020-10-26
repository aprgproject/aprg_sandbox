#include "AlbaSackReaderType.hpp"

#include <iostream>
#include <iterator>

using namespace std;

namespace alba
{

AlbaSackReaderType::AlbaSackReaderType()
    : m_isUnion(false)
{}

bool AlbaSackReaderType::isUnion() const
{
    return m_isUnion;
}

AlbaSackReaderType::Parameters AlbaSackReaderType::getParameters() const
{
    return m_parameters;
}

AlbaSackReaderType::TypeNames AlbaSackReaderType::getOtherTypes() const
{
    return m_otherTypes;
}

void AlbaSackReaderType::clear()
{
    *this = AlbaSackReaderType();
}

void AlbaSackReaderType::copyContents(AlbaSackReaderType const& type)
{
    if(type.m_isUnion)
    {
        m_isUnion=true;
    }
    copy(type.m_parameters.begin(), type.m_parameters.end(), back_inserter(m_parameters));
    copy(type.m_otherTypes.begin(), type.m_otherTypes.end(), inserter(m_otherTypes, m_otherTypes.begin()));
}

void AlbaSackReaderType::addParameter(AlbaSackReaderParameter const& parameter)
{
    m_parameters.emplace_back(parameter);
}

void AlbaSackReaderType::addOtherTypeName(std::string const& otherTypeName)
{
    m_otherTypes.emplace(otherTypeName);
}

void AlbaSackReaderType::setAsUnion()
{
    m_isUnion = true;
}

void AlbaSackReaderType::printAll() const
{
    for(AlbaSackReaderParameter parameter:m_parameters)
    {
        cout<<"Parameter: "<<parameter.getTypeName()<<" "<<parameter.getParameterName()<<endl;
    }
    for(string otherType:m_otherTypes)
    {
        cout<<"OtherType: "<<otherType<<endl;
    }
}

}



