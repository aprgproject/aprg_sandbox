#pragma once

#include <string>

namespace alba {

class AlbaSackReaderParameter {
public:
    AlbaSackReaderParameter(std::string const& typeName, std::string const& parameterName);
    std::string getTypeName() const;
    std::string getParameterName() const;

private:
    std::string m_typeName;
    std::string m_parameterName;
};

}  // namespace alba
