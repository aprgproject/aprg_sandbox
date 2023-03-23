#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>
#include <Common/PathHandler/PathContantsAndTypes.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <dirent.h>

#include <functional>
#include <string>

namespace alba
{

class AlbaLinuxPathHandler: public AlbaPathHandler
{
public:
    AlbaLinuxPathHandler(std::string const& path);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    static AlbaLinuxPathHandler createPathHandlerForDetectedPath();
	
    void clear() override;
    bool isFoundInLocalSystem() const;
    bool isRelativePath() const;
    double getFileSizeEstimate() const;
    AlbaDateTime getFileCreationTime() const;
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
    static std::string getCurrentDetectedPath();
    void save(std::string const& path) override;
    void findFilesAndDirectoriesWithDepth(
            std::string const& currentDirectory,
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories,
            int depth) const;
    void loopAllFilesAndDirectoriesInDirectoryStream(
            DIR *directoryStream,
            std::string const& currentDirectory,
            std::string const& wildCardSearch,
            std::set<std::string>& listOfFiles,
            std::set<std::string>& listOfDirectories,
            int depth) const;
    bool isPathADirectory(std::string const& fileOrDirectoryName) const;
    bool canBeLocated(std::string const& fullPath) const;
    bool isSlashNeededAtTheEnd(std::string const& correctedPath, std::string const& originalPath) const;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}//namespace alba
