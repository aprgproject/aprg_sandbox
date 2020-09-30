#pragma once

#include <string>
#include <functional>

using std::string;
using std::function;

namespace alba{

enum class PathType{Empty, Directory, File};

class AlbaPathHandler
{
public:
    explicit AlbaPathHandler(string const& slashCharacterString);
    virtual void inputPath(string const& path);
    virtual void clear();
    void goUp();
    void reInputPath();
    virtual string getFullPath() const;
    string getImmediateDirectoryName() const;
    string getDirectory() const;
    string getFile() const;
    string getFilenameOnly() const;
    string getExtension() const;
    PathType getPathType() const;
    bool isDirectory() const;
    bool isFile() const;
    bool isEmpty() const;

protected:
    void setExtensionFromPath(string const& path);
    void setDirectoryAndFileFromPath(string const& path);
    void setFileType();
    PathType m_pathType;
    string m_slashCharacterString;
    string m_directory;
    string m_file;
    string m_extension;
};

}//namespace alba
