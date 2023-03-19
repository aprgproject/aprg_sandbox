#pragma once

#include <map>
#include <set>
#include <string>
#include <ostream>
#include <vector>

namespace alba
{

class AlbaStreamParameterWriter
{
public:
    explicit AlbaStreamParameterWriter(std::ostream& stream);

    // rule of zero

    template <typename TypeToWrite> void writeData(TypeToWrite const& data) const;
    template <typename TypeToWrite> void writeVectorData(std::vector<TypeToWrite> const& vectorOfData) const;
    template <typename TypeToWrite> void writeSetData(std::set<TypeToWrite> const& setOfData) const;    template <typename TypeToWrite1, typename TypeToWrite2> void writeMapData(std::map<TypeToWrite1, TypeToWrite2> const& mapOfData) const;
    void flush();

private:    std::ostream& m_stream;
};

template <typename TypeToWrite>
void AlbaStreamParameterWriter::writeData(TypeToWrite const& data) const
{
    m_stream << data << "\n";
}

template <>
void AlbaStreamParameterWriter::writeData(std::string const& data) const;

template <typename TypeToWrite>
void AlbaStreamParameterWriter::writeVectorData(std::vector<TypeToWrite> const& vectorOfData) const
{
    m_stream << vectorOfData.size() << "\n";
    for(TypeToWrite const& data : vectorOfData)
    {
        writeData(data);
    }
}

template <typename TypeToWrite>
void AlbaStreamParameterWriter::writeSetData(std::set<TypeToWrite> const& setOfData) const //test
{
    m_stream << setOfData.size() << "\n";
    for(TypeToWrite const& data : setOfData)
    {
        writeData(data);
    }
}

template <typename TypeToWrite1, typename TypeToWrite2>
void AlbaStreamParameterWriter::writeMapData(std::map<TypeToWrite1, TypeToWrite2> const& mapOfData) const
{
    m_stream << mapOfData.size() << "\n";
    for(std::pair<TypeToWrite1, TypeToWrite2> const& dataPair : mapOfData)
    {
        writeData<TypeToWrite1>(dataPair.first);
        writeData<TypeToWrite2>(dataPair.second);
    }
}


}//namespace alba
