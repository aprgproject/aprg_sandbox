#pragma once

#include "DatabaseTypes.hpp"

#include <ostream>

namespace codeReview {
typedef set<string> SetOfFiles;
typedef set<string> SetOfDirectories;

class FileDirectoryDatabase {
public:
    void printFilesAndDirectories(std::ostream& outputStream) const;
    bool isFileIncluded(string const& baseDirectory, string const& fileName) const;
    string getFullPathOfFile(string const& baseDirectory, string const& fileName) const;
    SetOfFiles& getSetOfFilesReference();
    SetOfDirectories& getSetOfDirectoriesReference();
    bool isFileInFullPath(string const& fullPathFromDatabase, string const& fileName) const;

    void allowNonExistentDirectories();
    void addFileOrDirectory(string const& fileOrDirectory);

private:
    SetOfDirectories m_directories;
    SetOfFiles m_files;
    bool m_isNonExistentDirectoriesAllowed;
};

}  // namespace codeReview
