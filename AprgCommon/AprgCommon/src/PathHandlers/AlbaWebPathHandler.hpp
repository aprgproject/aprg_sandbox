#pragma once

#include <AlbaPathHandler.hpp>
#include <functional>
#include <string>

using std::string;
using std::function;
namespace alba{

class AlbaWebPathHandler: public AlbaPathHandler{
public:
    AlbaWebPathHandler();
    void inputPath(string const& path) override;
    void clear() override;
    string getFullPath() const override;
    bool hasProtocol() const;
    string getProtocol() const;
    void gotoLink(string const& newPath);

private:
    void splitPathInProtocol(string const& path, string & pathWithProtocol, string & pathAfterProtocol);
    string getCorrectPathWithoutUrlParameters(string const& correctPath) const;
    void setProtocolAndCorrectProtocolInDirectory(string const& pathWithProtocol);
    void setUrlParameters(string const& correctPath);
    string m_protocol;
    string m_urlParameters;
    bool m_hasProtocol;
};

}//namespace alba
