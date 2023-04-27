#pragma once

#include <istream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace alba {

class AlbaStreamParameterReader {
public:
    explicit AlbaStreamParameterReader(std::istream& stream);
    template <typename TypeToRetrieve>
    TypeToRetrieve readData() const;
    template <typename TypeToRetrieve>
    void readVectorData(std::vector<TypeToRetrieve>& vectorOfData) const;
    template <typename TypeToRetrieve>
    void readSetData(std::set<TypeToRetrieve>& setOfData) const;
    template <typename TypeToRetrieve1, typename TypeToRetrieve2>
    void readMapData(std::map<TypeToRetrieve1, TypeToRetrieve2>& mapOfData) const;

private:
    std::istream& m_stream;
};

template <typename TypeToRetrieve>
TypeToRetrieve AlbaStreamParameterReader::readData() const {
    TypeToRetrieve data{};
    m_stream >> data;
    return data;
}

template <>
std::string AlbaStreamParameterReader::readData<std::string>() const;

template <typename TypeToRetrieve>
void AlbaStreamParameterReader::readVectorData(std::vector<TypeToRetrieve>& vectorOfData) const {
    size_t size;
    m_stream >> size;
    for (size_t i = 0; i < size; i++) {
        vectorOfData.emplace_back(readData<TypeToRetrieve>());
    }
}

template <typename TypeToRetrieve>
void AlbaStreamParameterReader::readSetData(std::set<TypeToRetrieve>& setOfData) const  // test
{
    size_t size;
    m_stream >> size;
    for (size_t i = 0; i < size; i++) {
        setOfData.emplace(readData<TypeToRetrieve>());
    }
}

template <typename TypeToRetrieve1, typename TypeToRetrieve2>
void AlbaStreamParameterReader::readMapData(std::map<TypeToRetrieve1, TypeToRetrieve2>& mapOfData) const {
    size_t size;
    m_stream >> size;
    for (size_t i = 0; i < size; i++) {
        TypeToRetrieve1 data1(readData<TypeToRetrieve1>());
        TypeToRetrieve2 data2(readData<TypeToRetrieve2>());
        mapOfData.try_emplace(data1, data2);
    }
}

}  // namespace alba
