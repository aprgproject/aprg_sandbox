#pragma once

#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace alba
{

class AlbaFileParameterReader
{
public:
    explicit AlbaFileParameterReader(std::istream& stream);
    template<typename TypeToRetrieve> TypeToRetrieve readData() const;
    template<typename TypeToRetrieve> void readVectorData(std::vector<TypeToRetrieve> & vectorOfData) const;
    template<typename TypeToRetrieve> void readSetData(std::set<TypeToRetrieve> & setOfData) const;
    template<typename TypeToRetrieve1, typename TypeToRetrieve2> void readMapData(std::map<TypeToRetrieve1, TypeToRetrieve2> & mapOfData) const
;
private:
    std::istream& m_stream;
};

template<typename TypeToRetrieve>
TypeToRetrieve AlbaFileParameterReader::readData() const
{
    TypeToRetrieve data{};
    m_stream >> data;
    return data;
}

template <>
std::string AlbaFileParameterReader::readData<std::string>() const;

template<typename TypeToRetrieve>
void AlbaFileParameterReader::readVectorData(std::vector<TypeToRetrieve> & vectorOfData) const
{
    unsigned int size;
    m_stream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        vectorOfData.emplace_back(readData<TypeToRetrieve>());
    }
}

template<typename TypeToRetrieve>
void AlbaFileParameterReader::readSetData(std::set<TypeToRetrieve> & setOfData) const //test
{
    unsigned int size;
    m_stream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        setOfData.emplace(readData<TypeToRetrieve>());
    }
}

template<typename TypeToRetrieve1, typename TypeToRetrieve2>
void AlbaFileParameterReader::readMapData(std::map<TypeToRetrieve1, TypeToRetrieve2> & mapOfData) const
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
