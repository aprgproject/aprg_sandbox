#pragma once

#include <functional>
#include <PathHandlers/AlbaPathHandler.hpp>
#include <string>

using std::string;
using std::function;

namespace alba{

class AlbaWebPathHandler: public AlbaPathHandler
{
public:
    AlbaWebPathHandler(string const& path);
    void clear() override;
    string getFullPath() const override;
    bool hasProtocol() const;
    string getProtocol() const;
    void gotoLink(string const& newPath);

private:
    void save(string const& path) override;
    void setProtocolAndSplitPath(string const& path, string & protocolWithSymbols, string & pathAfterProtocol);
    void setProtocol(string const& protocol);
    void setUrlParameters(string const& urlParameters);
    string m_protocol;
    string m_urlParameters;
    bool m_hasProtocol;
};

}//namespace alba
