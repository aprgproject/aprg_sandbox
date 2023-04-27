#pragma once

#include <string>

namespace alba {

enum class PathType { Empty, Directory, File };

class AlbaPathHandler {
public:
    explicit AlbaPathHandler(std::string_view slashCharacterString);
    explicit AlbaPathHandler(std::string_view path, std::string_view slashCharacterString);
    virtual ~AlbaPathHandler() = default;  // virtual destructor because of virtual functions (vtable exists)

    virtual void clear();
    virtual std::string getFullPath() const;
    virtual std::string getDirectory() const;
    void input(std::string_view path);
    void reInput();
    void goUp();
    std::string getImmediateDirectoryName() const;
    std::string getFile() const;
    std::string getFilenameOnly() const;
    std::string getExtension() const;
    PathType getPathType() const;
    bool isDirectory() const;
    bool isFile() const;
    bool isEmpty() const;

protected:
    virtual void save(std::string_view path);
    void setPath(std::string_view path);  // non virtual because used by constructor
    void setExtensionFromPath(std::string_view path);
    void setDirectoryAndFileFromPath(std::string_view path);
    void setFileType();
    PathType m_pathType;
    std::string m_slashCharacterString;
    std::string m_directory;
    std::string m_file;
    std::string m_extension;
};

}  // namespace alba
