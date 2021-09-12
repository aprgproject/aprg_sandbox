#include "AlbaWebPathHandler.hpp"

#include <String/AlbaStringHelper.hpp>

#include <functional>
#include <string>

using namespace alba::stringHelper;
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
    int index = static_cast<int>(m_protocolWithSymbols.find_first_of(R"(:/\)"));
    if (isNotNpos(index) && m_protocolWithSymbols[static_cast<string::size_type>(index)]==':')
    {
        protocol = getStringWithLowerCaseLetters(m_protocolWithSymbols.substr(0,static_cast<string::size_type>(index)));
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
    int index = static_cast<int>(protocolWithSymbols.find_first_of(R"(:/\)"));
    if (isNotNpos(index) && protocolWithSymbols[static_cast<string::size_type>(index)]==':')
    {
        m_hasProtocol = true;
    }
}

void AlbaWebPathHandler::save(string const& path)
{
    string protocolWithSymbols;
    string pathAfterProtocol;
    splitPathToBeforeAndAfterProtocol(path, protocolWithSymbols, pathAfterProtocol);
    string correctPathAfterProtocol(getCorrectPathWithReplacedSlashCharacters(pathAfterProtocol, m_slashCharacterString));
    string correctPathAfterProtocolWithoutUrlParameters(getCorrectPathWithoutUrlParameters(correctPathAfterProtocol));
    setProtocolWithSymbols(protocolWithSymbols);
    setExtensionFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setDirectoryAndFileFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setFileType();
    setUrlParameters(getUrlParameters(correctPathAfterProtocol));
}

void AlbaWebPathHandler::splitPathToBeforeAndAfterProtocol(string const& path, string & protocolWithSymbols, string & pathAfterProtocol)
{
    int indexBeforeProtocol = static_cast<int>(path.find("://"));
    int indexBeforeSlash = static_cast<int>(path.find_first_of(m_slashCharacterString));
    if(isNotNpos(indexBeforeProtocol) && isNotNpos(indexBeforeSlash) && indexBeforeProtocol < indexBeforeSlash)
    {
        protocolWithSymbols = path.substr(0, static_cast<string::size_type>(indexBeforeProtocol)+3);
        pathAfterProtocol = path.substr(static_cast<string::size_type>(indexBeforeProtocol)+3);
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
