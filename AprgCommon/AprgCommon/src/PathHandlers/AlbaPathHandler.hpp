#pragma once

#include <string>

namespace alba{

enum class PathType{Empty, Directory, File};

class AlbaPathHandler
{
public:
    explicit AlbaPathHandler(std::string const& slashCharacterString);
    explicit AlbaPathHandler(std::string const& path, std::string const& slashCharacterString);
    virtual void clear();
    virtual std::string getFullPath() const;
    void input(std::string const& path);
    void reInput();
    void goUp();
    std::string getImmediateDirectoryName() const;
    std::string getDirectory() const;
    std::string getFile() const;
    std::string getFilenameOnly() const;
    std::string getExtension() const;
    PathType getPathType() const;
    bool isDirectory() const;
    bool isFile() const;
    bool isEmpty() const;

protected:
    virtual void save(std::string const& path);
    void setExtensionFromPath(std::string const& path);
    void setDirectoryAndFileFromPath(std::string const& path);
    void setFileType();
    PathType m_pathType;
    std::string m_slashCharacterString;
    std::string m_directory;
    std::string m_file;
    std::string m_extension;
};

}//namespace alba



