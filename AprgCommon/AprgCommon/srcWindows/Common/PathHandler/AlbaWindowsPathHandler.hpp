#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>
#include <Common/PathHandler/PathContantsAndTypes.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <functional>
#include <string>

namespace alba {

class AlbaWindowsPathHandler : public AlbaPathHandler {
public:
    AlbaWindowsPathHandler(std::string_view path);

    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    static AlbaWindowsPathHandler createPathHandlerForDetectedPath();

    void clear() override;
    std::string getDriveOrRoot() const;
    double getFileSizeEstimate();
    AlbaDateTime getFileCreationTime();
    bool isFoundInLocalSystem() const;
    bool isRelativePath() const;
    void createDirectoriesForNonExisitingDirectories() const;
    bool deleteFile();
    bool deleteDirectoryWithoutFilesAndDirectories();  // do tests
    void deleteFilesInDirectory();                     // do tests
    void deleteInnerFilesAndDirectories();             // do tests
    void deleteDirectoryWithFilesAndDirectories();     // do tests
    bool copyToNewFile(std::string_view newFilePath);
    bool renameFile(std::string_view newFileName);
    bool renameImmediateDirectory(std::string_view newDirectoryName);
    void findFilesAndDirectoriesOneDepth(
        std::string_view wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;
    void findFilesAndDirectoriesMultipleDepth(
        std::string_view wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories, int depth) const;
    void findFilesAndDirectoriesUnlimitedDepth(
        std::string_view wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;

private:
    static std::string getCurrentDetectedPath();
    void save(std::string_view path) override;
    void setPath(std::string_view path);
    void setDriveOrRoot();
    void findFilesAndDirectoriesWithDepth(
        std::string_view currentDirectory, std::string_view wildCardSearch, ListOfPaths& listOfFiles,
        ListOfPaths& listOfDirectories, int depth) const;
    bool canBeLocated(std::string_view fullPath) const;
    bool isSlashNeededAtTheEnd(std::string_view correctedPath, std::string_view originalPath) const;
    std::string m_driveOrRoot;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}  // namespace alba
