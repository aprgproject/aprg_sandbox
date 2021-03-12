#pragma once

#include <PathHandlers/AlbaPathHandler.hpp>
#include <PathHandlers/PathContantsAndTypes.hpp>
#include <Time/AlbaDateTime.hpp>

#include <functional>
#include <string>

namespace alba
{

class AlbaLinuxPathHandler: public AlbaPathHandler
{
public:
    typedef std::set<std::string> ListOfPaths;
    AlbaLinuxPathHandler(PathInitialValueSource const initialValueSource);
    AlbaLinuxPathHandler(std::string const& path);
    virtual ~AlbaLinuxPathHandler();

    void clear() override;
    double getFileSizeEstimate();
    AlbaDateTime getFileCreationTime();
    bool isFoundInLocalSystem() const;
    bool isRelativePath() const;
    void setPathToDetectedLocalPath();
    void createDirectoriesForNonExisitingDirectories() const;
    bool deleteFile();
    bool deleteDirectoryWithoutFilesAndDirectories(); //do tests
    void deleteFilesInDirectory(); //do tests
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
    void findFilesAndDirectoriesWithDepth(
            std::string const& currentDirectory,
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories,
            int depth) const;
    bool isPathADirectory(std::string const& fileOrDirectoryName) const;
    bool canBeLocated(std::string const& fileOrDirectoryName) const;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}//namespace alba
