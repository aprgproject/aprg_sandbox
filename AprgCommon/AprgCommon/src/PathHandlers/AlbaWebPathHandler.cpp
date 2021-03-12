#include "AlbaWebPathHandler.hpp"

#include <String/AlbaStringHelper.hpp>

#include <functional>
#include <string>

using namespace std;

namespace alba
{

AlbaWebPathHandler::AlbaWebPathHandler(string const& path)
    : AlbaPathHandler("/")
    , m_hasProtocol(false)
{
    save(path);
}

AlbaWebPathHandler::~AlbaWebPathHandler()
{}

void AlbaWebPathHandler::clear()
{
    AlbaPathHandler::clear();
    m_protocolWithSymbols.clear();
    m_urlParameters.clear();
    m_hasProtocol = false;
}

string AlbaWebPathHandler::getFullPath() const
{
    return m_protocolWithSymbols+m_directory+m_file+m_urlParameters;
}

string AlbaWebPathHandler::getDirectory() const
{
    return m_protocolWithSymbols+m_directory;
}

bool AlbaWebPathHandler::hasProtocol() const
{
    return m_hasProtocol;
}

string AlbaWebPathHandler::getProtocol() const
{
    string protocol;
    int index = m_protocolWithSymbols.find_first_of(R"(:/\)");
    if (stringHelper::isNotNpos(index) && m_protocolWithSymbols[index]==':')
    {
        protocol = stringHelper::getStringWithLowerCaseLetters(m_protocolWithSymbols.substr(0,index));
    }
    return protocol;
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

void AlbaWebPathHandler::setProtocolWithSymbols(string const& protocolWithSymbols)
{
    m_protocolWithSymbols = protocolWithSymbols;
    int index = protocolWithSymbols.find_first_of(R"(:/\)");
    if (stringHelper::isNotNpos(index) && protocolWithSymbols[index]==':')
    {
        m_hasProtocol = true;
    }
}

void AlbaWebPathHandler::save(string const& path)
{
    string protocolWithSymbols;
    string pathAfterProtocol;
    splitPathToBeforeAndAfterProtocol(path, protocolWithSymbols, pathAfterProtocol);
    string correctPathAfterProtocol(stringHelper::getCorrectPathWithReplacedSlashCharacters(pathAfterProtocol, m_slashCharacterString));
    string correctPathAfterProtocolWithoutUrlParameters(stringHelper::getCorrectPathWithoutUrlParameters(correctPathAfterProtocol));
    setProtocolWithSymbols(protocolWithSymbols);
    setExtensionFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setDirectoryAndFileFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setFileType();
    setUrlParameters(stringHelper::getUrlParameters(correctPathAfterProtocol));
}

void AlbaWebPathHandler::splitPathToBeforeAndAfterProtocol(string const& path, string & protocolWithSymbols, string & pathAfterProtocol)
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

void AlbaWebPathHandler::setUrlParameters(string const& urlParameters)
{
    m_urlParameters = urlParameters;
}


}
