#include "AlbaPathHandler.hpp"

#include <String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

AlbaPathHandler::AlbaPathHandler(string const& slashCharacterString)
    : m_slashCharacterString(slashCharacterString)
{}

AlbaPathHandler::AlbaPathHandler(string const& path, string const& slashCharacterString)
    : m_slashCharacterString(slashCharacterString)
{
    save(path);
}

void AlbaPathHandler::clear()
{
    m_pathType = PathType::Empty;
    m_directory.clear();
    m_file.clear();
    m_extension.clear();
}

string AlbaPathHandler::getFullPath() const
{
    return m_directory+m_file;
}

void AlbaPathHandler::input(string const& path)
{
    clear();
    save(path);
}

void AlbaPathHandler::reInput()
{
    string const previousFullPath(getFullPath());
    clear();
    save(previousFullPath);
}

void AlbaPathHandler::goUp()
{
    string directoryWithoutSlash(stringHelper::getStringWithoutCharAtTheEnd(m_directory, m_slashCharacterString[0]));
    int indexOfSlash = directoryWithoutSlash.find_last_of(m_slashCharacterString);
    if (stringHelper::isNotNpos(indexOfSlash))
    {
        input(directoryWithoutSlash.substr(0, indexOfSlash+1));
    }
}

string AlbaPathHandler::getImmediateDirectoryName() const
{
    return stringHelper::getImmediateDirectoryName(m_directory, m_slashCharacterString);
}

string AlbaPathHandler::getDirectory() const
{
    return m_directory;
}

string AlbaPathHandler::getFile() const
{
    return m_file;
}

string AlbaPathHandler::getFilenameOnly() const
{
    int indexOfSlashOrPeriod = m_file.find_last_of (".");
    if (stringHelper::isNotNpos(indexOfSlashOrPeriod))
    {
        return m_file.substr(0, indexOfSlashOrPeriod);
    }
    return m_file;
}

string AlbaPathHandler::getExtension() const
{
    return m_extension;
}

PathType AlbaPathHandler::getPathType() const
{
    return m_pathType;
}

bool AlbaPathHandler::isDirectory() const
{
    return m_pathType == PathType::Directory;
}

bool AlbaPathHandler::isFile() const
{
    return m_pathType == PathType::File;
}

bool AlbaPathHandler::isEmpty() const
{
    return m_pathType == PathType::Empty;
}

void AlbaPathHandler::save(string const& path)
{
    string correctPath(stringHelper::getCorrectPathWithReplacedSlashCharacters(path, m_slashCharacterString));
    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setFileType();
}

void AlbaPathHandler::setExtensionFromPath(string const& path)
{
    int indexOfSlashOrPeriod = path.find_last_of (m_slashCharacterString + ".");
    if (stringHelper::isNotNpos(indexOfSlashOrPeriod) && path[indexOfSlashOrPeriod]=='.')
    {
        m_extension = path.substr(indexOfSlashOrPeriod+1);
    }
}

void AlbaPathHandler::setDirectoryAndFileFromPath(string const& path)
{
    int indexOfSlash = path.find_last_of(m_slashCharacterString);
    if (stringHelper::isNotNpos(indexOfSlash))
    {
        m_directory = path.substr(0, indexOfSlash+1);
        m_file = path.substr(indexOfSlash+1);
    }
    else
    {
        m_directory = "";
        m_file = path;
    }
}

void AlbaPathHandler::setFileType()
{
    if(m_file=="")
    {
        if(m_directory=="")
        {
            m_pathType = PathType::Empty;
        }
        else
        {
            m_pathType = PathType::Directory;
        }
    }
    else
    {
        m_pathType = PathType::File;
    }
}

}//namespace alba



