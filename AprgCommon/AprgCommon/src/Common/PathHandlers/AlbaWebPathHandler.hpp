#pragma once

#include <Common/PathHandlers/AlbaPathHandler.hpp>

#include <string>

namespace alba
{

class AlbaWebPathHandler: public AlbaPathHandler
{
public:
    AlbaWebPathHandler(std::string const& path);
    virtual ~AlbaWebPathHandler() override;

    void clear() override;
    std::string getFullPath() const override;
    std::string getDirectory() const override;
    bool hasProtocol() const;
    std::string getProtocol() const;
    void gotoLink(std::string const& newPath);
    void setProtocolWithSymbols(std::string const& protocolWithSymbols);

private:
    void save(std::string const& path) override;
    void splitPathToBeforeAndAfterProtocol(std::string const& path, std::string & protocolWithSymbols, std::string & pathAfterProtocol);
    void setUrlParameters(std::string const& urlParameters);
    std::string m_protocolWithSymbols;
    std::string m_urlParameters;
    bool m_hasProtocol;
};

}//namespace alba
