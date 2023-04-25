#include "AlbaPathHandler.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaPathHandler::AlbaPathHandler(string const& slashCharacterString)
    : m_pathType(PathType::Empty), m_slashCharacterString(slashCharacterString) {}

AlbaPathHandler::AlbaPathHandler(string const& path, string const& slashCharacterString)
    : m_pathType(PathType::Empty), m_slashCharacterString(slashCharacterString) {
    setPath(path);
}

void AlbaPathHandler::clear() {
    m_pathType = PathType::Empty;
    m_directory.clear();
    m_file.clear();
    m_extension.clear();
}

string AlbaPathHandler::getFullPath() const { return m_directory + m_file; }

string AlbaPathHandler::getDirectory() const { return m_directory; }

void AlbaPathHandler::input(string const& path) {
    clear();
    save(path);
}

void AlbaPathHandler::reInput() {
    string const previousFullPath(getFullPath());
    clear();
    save(previousFullPath);
}

void AlbaPathHandler::goUp() {
    string directoryWithoutSlash(getStringWithoutCharAtTheEnd(m_directory, m_slashCharacterString[0]));
    int indexOfSlash = static_cast<int>(directoryWithoutSlash.find_last_of(m_slashCharacterString));
    if (isNotNpos(indexOfSlash)) {
        input(directoryWithoutSlash.substr(0, static_cast<string::size_type>(indexOfSlash) + 1));
    }
}

string AlbaPathHandler::getImmediateDirectoryName() const {
    return stringHelper::getImmediateDirectoryName(m_directory, m_slashCharacterString);
}

string AlbaPathHandler::getFile() const { return m_file; }

string AlbaPathHandler::getFilenameOnly() const {
    int indexOfSlashOrPeriod = static_cast<int>(m_file.find_last_of('.'));
    if (isNotNpos(indexOfSlashOrPeriod)) {
        return m_file.substr(0, static_cast<string::size_type>(indexOfSlashOrPeriod));
    }
    return m_file;
}

string AlbaPathHandler::getExtension() const { return m_extension; }

PathType AlbaPathHandler::getPathType() const { return m_pathType; }

bool AlbaPathHandler::isDirectory() const { return m_pathType == PathType::Directory; }

bool AlbaPathHandler::isFile() const { return m_pathType == PathType::File; }

bool AlbaPathHandler::isEmpty() const { return m_pathType == PathType::Empty; }

void AlbaPathHandler::save(string const& path) { setPath(path); }

void AlbaPathHandler::setPath(string const& path) {
    string correctPath(getCorrectPathWithReplacedSlashCharacters(path, m_slashCharacterString));
    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setFileType();
}

void AlbaPathHandler::setExtensionFromPath(string const& path) {
    int indexOfSlashOrPeriod = static_cast<int>(path.find_last_of(m_slashCharacterString + "."));
    if (isNotNpos(indexOfSlashOrPeriod) && path[static_cast<string::size_type>(indexOfSlashOrPeriod)] == '.') {
        m_extension = path.substr(static_cast<string::size_type>(indexOfSlashOrPeriod) + 1);
    }
}

void AlbaPathHandler::setDirectoryAndFileFromPath(string const& path) {
    int indexOfSlash = static_cast<int>(path.find_last_of(m_slashCharacterString));
    if (isNotNpos(indexOfSlash)) {
        m_directory = path.substr(0, static_cast<string::size_type>(indexOfSlash) + 1);
        m_file = path.substr(static_cast<string::size_type>(indexOfSlash) + 1);
    } else {
        m_directory.clear();
        m_file = path;
    }
}

void AlbaPathHandler::setFileType() {
    if (m_file.empty()) {
        if (m_directory.empty()) {
            m_pathType = PathType::Empty;
        } else {
            m_pathType = PathType::Directory;
        }
    } else {
        m_pathType = PathType::File;
    }
}

}  // namespace alba
