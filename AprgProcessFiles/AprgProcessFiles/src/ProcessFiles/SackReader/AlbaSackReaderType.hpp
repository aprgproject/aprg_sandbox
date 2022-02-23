#pragma once

#include <ProcessFiles/SackReader/AlbaSackReaderParameter.hpp>

#include <set>
#include <string>
#include <vector>

namespace alba
{

class AlbaSackReaderType
{
public:
    typedef std::vector<AlbaSackReaderParameter> Parameters;
    typedef std::set<std::string> TypeNames;

    AlbaSackReaderType();
    bool isUnion() const;
    Parameters getParameters() const;
    TypeNames getOtherTypes() const;
    void clear();
    void copyContents(AlbaSackReaderType const& type);
    void addParameter(AlbaSackReaderParameter const& parameter);
    void addOtherTypeName(std::string const& otherTypeName);
    void setAsUnion();
    void printAll() const;

private:
    bool m_isUnion;
    Parameters m_parameters;
    TypeNames m_otherTypes;
};

}
