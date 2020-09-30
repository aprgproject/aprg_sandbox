#include "AlbaWebPathHandler.hpp"

#include "AlbaStringHelper.hpp"
#include <functional>
#include <string>

namespace alba{

AlbaWebPathHandler::AlbaWebPathHandler()
    : AlbaPathHandler("/")
    , m_hasProtocol(false)
{}

void AlbaWebPathHandler::inputPath(string const& path)
{
    clear();

    string pathWithProtocol;
    string pathAfterProtocol;
    splitPathInProtocol(path, pathWithProtocol, pathAfterProtocol);
    string correctPathAfterProtocol(stringHelper::getCorrectPathWithReplacedSlashCharacters(pathAfterProtocol, m_slashCharacterString));
    string correctPathAfterProtocolWithoutUrlParameters(getCorrectPathWithoutUrlParameters(correctPathAfterProtocol));

    setExtensionFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setDirectoryAndFileFromPath(pathWithProtocol+correctPathAfterProtocolWithoutUrlParameters);
    setFileType();
    setProtocolAndCorrectProtocolInDirectory(pathWithProtocol);
    setUrlParameters(correctPathAfterProtocol);
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
    AlbaWebPathHandler newPathHandler;
    newPathHandler.inputPath(newPath);
    if(newPathHandler.hasProtocol())
    {
        inputPath(newPath);
    }
    else
    {
        inputPath(getDirectory()+newPath);
    }
}

void AlbaWebPathHandler::splitPathInProtocol(string const& path, string & pathWithProtocol, string & pathAfterProtocol)
{
    int indexBeforeProtocol = path.find("://");
    int indexBeforeSlash = path.find_first_of(m_slashCharacterString);
    if(stringHelper::isNotNpos(indexBeforeProtocol) && stringHelper::isNotNpos(indexBeforeSlash) && indexBeforeProtocol < indexBeforeSlash)
    {
        pathWithProtocol = path.substr(0,indexBeforeProtocol+3);
        pathAfterProtocol = path.substr(indexBeforeProtocol+3);
    }
    else
    {
        pathWithProtocol.clear();
        pathAfterProtocol = path;
    }
}

string AlbaWebPathHandler::getCorrectPathWithoutUrlParameters(string const& correctPath) const
{
    string correctPathWithoutUrlParameters(correctPath);
    int indexOfQuestionMark = correctPath.find_first_of("?");
    if(stringHelper::isNotNpos(indexOfQuestionMark))
    {
            correctPathWithoutUrlParameters = correctPath.substr(0, indexOfQuestionMark);
    }
    return correctPathWithoutUrlParameters;
}

void AlbaWebPathHandler::setProtocolAndCorrectProtocolInDirectory(string const& pathWithProtocol)
{
    int index = pathWithProtocol.find_first_of(R"(:/\)");
    if (stringHelper::isNotNpos(index) && m_directory[index]==':')
    {
        m_protocol = stringHelper::getStringWithLowerCaseLetters(m_directory.substr(0,index));
        m_hasProtocol = true;
    }
}

void AlbaWebPathHandler::setUrlParameters(string const& correctPath)
{
    int indexOfQuestionMark = correctPath.find_first_of("?");
    if(stringHelper::isNotNpos(indexOfQuestionMark))
    {
            m_urlParameters = correctPath.substr(indexOfQuestionMark);
    }
}


}
