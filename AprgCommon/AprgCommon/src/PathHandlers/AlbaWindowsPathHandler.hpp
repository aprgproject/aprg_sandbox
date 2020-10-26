#pragma once

#include <PathHandlers/AlbaPathHandler.hpp>
#include <PathHandlers/PathContantsAndTypes.hpp>

#include <functional>
#include <string>

namespace alba{

class AlbaWindowsPathHandler: public AlbaPathHandler
{
public:
    typedef std::set<std::string> ListOfPaths;
    AlbaWindowsPathHandler(PathInitialValueSource const initialValueSource);
    AlbaWindowsPathHandler(std::string const& path);
    void clear() override;
    std::string getDriveOrRoot() const;
    double getFileSizeEstimate();
    bool isFoundInLocalSystem() const;
    bool isRelativePath() const;
    void setPathToDetectedLocalPath();
    void createDirectoriesForNonExisitingDirectories() const;
    bool deleteFile();
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
    void setDriveOrRoot();
    void findFilesAndDirectoriesWithDepth(
            std::string const& currentDirectory,
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories,
            int depth) const;
    std::string getLastFormattedErrorMessage() const;
    std::string m_driveOrRoot;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}//namespace alba



