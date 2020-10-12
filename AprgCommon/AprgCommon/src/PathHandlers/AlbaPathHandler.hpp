#pragma once

#include <functional>
#include <string>

using std::string;
using std::function;

namespace alba{

enum class PathType{Empty, Directory, File};

class AlbaPathHandler
{
public:
    explicit AlbaPathHandler(string const& slashCharacterString);
    explicit AlbaPathHandler(string const& path, string const& slashCharacterString);
    virtual void clear();
    virtual string getFullPath() const;
    void input(string const& path);
    void reInput();
    void goUp();
    string getImmediateDirectoryName() const;
    string getDirectory() const;
    string getFile() const;    string getFilenameOnly() const;
    string getExtension() const;
    PathType getPathType() const;
    bool isDirectory() const;
    bool isFile() const;
    bool isEmpty() const;

protected:
    virtual void save(string const& path);
    void setExtensionFromPath(string const& path);
    void setDirectoryAndFileFromPath(string const& path);
    void setFileType();    PathType m_pathType;
    string m_slashCharacterString;
    string m_directory;
    string m_file;
    string m_extension;
};

}//namespace alba
