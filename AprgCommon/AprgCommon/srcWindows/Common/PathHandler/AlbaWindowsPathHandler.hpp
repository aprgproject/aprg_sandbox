#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>
#include <Common/PathHandler/PathContantsAndTypes.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <functional>
#include <string>

namespace alba
{

class AlbaWindowsPathHandler: public AlbaPathHandler
{
public:
    AlbaWindowsPathHandler(PathInitialValueSource const initialValueSource);
    AlbaWindowsPathHandler(std::string const& path);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    void clear() override;
    std::string getDriveOrRoot() const;
    double getFileSizeEstimate();
    AlbaDateTime getFileCreationTime();
    bool isFoundInLocalSystem() const;
    bool isRelativePath() const;
    void setPathToDetectedLocalPath();
    void createDirectoriesForNonExisitingDirectories() const;
    bool deleteFile();
    bool deleteDirectoryWithoutFilesAndDirectories(); //do tests
    void deleteFilesInDirectory(); //do tests
    void deleteInnerFilesAndDirectories(); //do tests
    void deleteDirectoryWithFilesAndDirectories(); //do tests
    bool copyToNewFile(std::string const& newFilePath);
    bool renameFile(std::string const& newFileName);
    bool renameImmediateDirectory(std::string const& newDirectoryName);
    void findFilesAndDirectoriesOneDepth(
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories) const;
    void findFilesAndDirectoriesMultipleDepth(
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories,
            int depth) const;
    void findFilesAndDirectoriesUnlimitedDepth(
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories) const;
private:
    void save(std::string const& path) override;
    void setPath(std::string const& path);
    void setDriveOrRoot();
    void findFilesAndDirectoriesWithDepth(
            std::string const& currentDirectory,
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories,
            int depth) const;
    bool canBeLocated(std::string const& fullPath) const;
    bool isSlashNeededAtTheEnd(std::string const& correctedPath, std::string const& originalPath) const;
    std::string m_driveOrRoot;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}//namespace alba
