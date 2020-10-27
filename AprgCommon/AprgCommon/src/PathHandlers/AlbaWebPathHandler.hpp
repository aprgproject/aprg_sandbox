#pragma once

#include <PathHandlers/AlbaPathHandler.hpp>

#include <string>

namespace alba
{

class AlbaWebPathHandler: public AlbaPathHandler
{
public:
    AlbaWebPathHandler(std::string const& path);
    void clear() override;
    std::string getFullPath() const override;
    bool hasProtocol() const;
    std::string getProtocol() const;
    void gotoLink(std::string const& newPath);

private:
    void save(std::string const& path) override;
    void setProtocolAndSplitPath(std::string const& path, std::string & protocolWithSymbols, std::string & pathAfterProtocol);
    void setProtocol(std::string const& protocol);
    void setUrlParameters(std::string const& urlParameters);
    std::string m_protocol;
    std::string m_urlParameters;
    bool m_hasProtocol;
};

}//namespace alba
