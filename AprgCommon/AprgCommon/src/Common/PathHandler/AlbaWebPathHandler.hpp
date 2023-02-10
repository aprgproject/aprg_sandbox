#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>

#include <string>

namespace alba
{

class AlbaWebPathHandler: public AlbaPathHandler
{
public:
    AlbaWebPathHandler(std::string const& path);
    virtual ~AlbaWebPathHandler() = default;

    void clear() override;
    std::string getFullPath() const override;
    std::string getDirectory() const override;
    bool hasProtocol() const;
    std::string getProtocol() const;
    void gotoLink(std::string const& newPath);
    void setProtocolWithSymbols(std::string const& protocolWithSymbols);

private:
    void save(std::string const& path) override;
    void setPath(std::string const& path);
    void splitPathToBeforeAndAfterProtocol(std::string const& path, std::string & protocolWithSymbols, std::string & pathAfterProtocol);
    void setUrlParameters(std::string const& urlParameters);
    std::string m_protocolWithSymbols;
    std::string m_urlParameters;
    bool m_hasProtocol;
};

}//namespace alba
