#pragma once

#include <fstream>
#include <map>
#include <vector>

namespace alba
{

class AlbaFileParameterWriter
{
public:
    explicit AlbaFileParameterWriter(std::ostream& stream);
    template<typename TypeToWrite> void writeData(TypeToWrite const& data) const;
    template<typename TypeToWrite> void writeData(std::vector<TypeToWrite> const& vectorOfData) const;
    template<typename TypeToWrite1, typename TypeToWrite2> void writeData(std::map<TypeToWrite1, TypeToWrite2> const& mapOfData) const;

private:
    std::ostream& m_stream;
};

AlbaFileParameterWriter::AlbaFileParameterWriter(std::ostream& stream) : m_stream(stream){}

template<typename TypeToRetrieve> void AlbaFileParameterWriter::writeData(TypeToRetrieve const& data) const
{
    m_stream << data << std::endl;
}

template<> void AlbaFileParameterWriter::writeData(std::string const& data) const
{
    bool isExisting(!data.empty());
    m_stream << isExisting << std::endl;
    if(isExisting)
    {
        m_stream << data << std::endl;
    }
}

template<typename TypeToWrite> void AlbaFileParameterWriter::writeData(std::vector<TypeToWrite> const& vectorOfData) const
{
    m_stream << vectorOfData.size() << std::endl;
    for(TypeToWrite const& data : vectorOfData)
    {
        writeData(data);
    }
}

template<typename TypeToWrite1, typename TypeToWrite2> void AlbaFileParameterWriter::writeData(std::map<TypeToWrite1, TypeToWrite2> const& mapOfData) const
{
    m_stream << mapOfData.size() << std::endl;
    for(std::pair<TypeToWrite1, TypeToWrite2> const& dataPair : mapOfData)
    {
        writeData<TypeToWrite1>(dataPair.first);
        writeData<TypeToWrite2>(dataPair.second);
    }
}

}//namespace alba
