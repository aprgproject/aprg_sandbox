#include "AlbaWebPathHandler.hpp"

#include <String/AlbaStringHelper.hpp>
#include <functional>
#include <string>
using namespace std;

namespace alba{
AlbaWebPathHandler::AlbaWebPathHandler(string const& path)
    : AlbaPathHandler("/")
    , m_hasProtocol(false)
{
    save(path);
}

void AlbaWebPathHandler::clear()
{
    AlbaPathHandler::clear();
    m_protocol.clear();
    m_urlParameters.clear();
    m_hasProtocol = false;
}

string AlbaWebPathHandler::getFullPath() const
{
    return m_directory+m_file+m_urlParameters;
}

bool AlbaWebPathHandler::hasProtocol() const
{
    return m_hasProtocol;
}

string AlbaWebPathHandler::getProtocol() const
{
    return m_protocol;
}

void AlbaWebPathHandler::gotoLink(string const& newPath)
{
    AlbaWebPathHandler newPathHandler(newPath);
    if(newPathHandler.hasProtocol())
    {
        input(newPath);
    }
    else
    {
        input(getDirectory()+newPath);
    }
}

void AlbaWebPathHandler::save(string const& path)
{
    string protocolWithSymbols;
    string pathAfterProtocol;
    setProtocolAndSplitPath(path, protocolWithSymbols, pathAfterProtocol);
    string correctPathAfterProtocol(stringHelper::getCorrectPathWithReplacedSlashCharacters(pathAfterProtocol, m_slashCharacterString));
    string correctPathAfterProtocolWithoutUrlParameters(stringHelper::getCorrectPathWithoutUrlParameters(correctPathAfterProtocol));
    setProtocol(stringHelper::getStringWithLowerCaseLetters(protocolWithSymbols));
    setExtensionFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setDirectoryAndFileFromPath(protocolWithSymbols+correctPathAfterProtocolWithoutUrlParameters);
    setFileType();
    setUrlParameters(stringHelper::getUrlParameters(correctPathAfterProtocol));
}

void AlbaWebPathHandler::setProtocolAndSplitPath(string const& path, string & protocolWithSymbols, string & pathAfterProtocol)
{
    int indexBeforeProtocol = path.find("://");
    int indexBeforeSlash = path.find_first_of(m_slashCharacterString);
    if(stringHelper::isNotNpos(indexBeforeProtocol) && stringHelper::isNotNpos(indexBeforeSlash) && indexBeforeProtocol < indexBeforeSlash)
    {
        protocolWithSymbols = path.substr(0,indexBeforeProtocol+3);
        pathAfterProtocol = path.substr(indexBeforeProtocol+3);
    }
    else
    {
        protocolWithSymbols.clear();
        pathAfterProtocol = path;
    }
}

void AlbaWebPathHandler::setProtocol(string const& protocolWithSymbols)
{
    int index = protocolWithSymbols.find_first_of(R"(:/\)");
    if (stringHelper::isNotNpos(index) && protocolWithSymbols[index]==':')
    {
        m_protocol = stringHelper::getStringWithLowerCaseLetters(protocolWithSymbols.substr(0,index));
        m_hasProtocol = true;
    }
}

void AlbaWebPathHandler::setUrlParameters(string const& urlParameters)
{
    m_urlParameters = urlParameters;
}


}
