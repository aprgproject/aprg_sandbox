#pragma once

#include <fstream>
#include <vector>
#include <map>

namespace alba
{

class AlbaFileParameterReader
{
public:
    explicit AlbaFileParameterReader(std::istream& stream);
    template<typename TypeToRetrieve> TypeToRetrieve readData() const;
    template<typename TypeToRetrieve> void readData(std::vector<TypeToRetrieve> & vectorOfData) const;
    template<typename TypeToRetrieve1, typename TypeToRetrieve2> void readData(std::map<TypeToRetrieve1, TypeToRetrieve2> & mapOfData) const
;
private:
    std::istream& m_stream;
};

AlbaFileParameterReader::AlbaFileParameterReader(std::istream& stream) : m_stream(stream){}

template<typename TypeToRetrieve> TypeToRetrieve AlbaFileParameterReader::readData() const
{
    TypeToRetrieve data;
    m_stream >> data;
    return data;
}

template <>
std::string AlbaFileParameterReader::readData<std::string>() const
{
    std::string data;
    bool isExisting(false);
    m_stream >> isExisting;
    if(isExisting)
    {
        while(m_stream.peek()=='\r' || m_stream.peek()=='\n') { m_stream.ignore(1); }
        std::getline(m_stream, data);
    }
    return data;
}

template<typename TypeToRetrieve> void AlbaFileParameterReader::readData(std::vector<TypeToRetrieve> & vectorOfData) const
{
    unsigned int size;
    m_stream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        vectorOfData.emplace_back(readData<TypeToRetrieve>());
    }
}

template<typename TypeToRetrieve1, typename TypeToRetrieve2> void AlbaFileParameterReader::readData(std::map<TypeToRetrieve1, TypeToRetrieve2> & mapOfData) const
{
    unsigned int size;
    m_stream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        TypeToRetrieve1 data1(readData<TypeToRetrieve1>());
        TypeToRetrieve2 data2(readData<TypeToRetrieve2>());
        mapOfData.emplace(data1, data2);
    }
}

}//namespace alba
