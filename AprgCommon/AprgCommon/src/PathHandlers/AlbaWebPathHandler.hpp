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
    AlbaWebPathHandler();
    void inputPath(string const& path) override;
    void clear() override;
    string getFullPath() const override;
    bool hasProtocol() const;
    string getProtocol() const;
    void gotoLink(string const& newPath);

private:
    void splitPathInProtocol(string const& path, string & protocolWithSymbols, string & pathAfterProtocol);
    string getCorrectPathWithoutUrlParameters(string const& correctPath) const;
    void setProtocolAndCorrectProtocolInDirectory(string const& protocolWithSymbols);
    void setUrlParameters(string const& correctPath);
    string m_protocol;
    string m_urlParameters;
    bool m_hasProtocol;
};

}//namespace alba
