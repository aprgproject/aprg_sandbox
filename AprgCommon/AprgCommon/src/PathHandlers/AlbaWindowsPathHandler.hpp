#pragma once

#include <functional>
#include <PathHandlers/AlbaPathHandler.hpp>
#include <set>
#include <string>

namespace alba{

class AlbaWindowsPathHandler: public AlbaPathHandler
{
public:
    enum class InitialValue
    {
        DetectedLocalPath
    };
    typedef std::set<std::string> ListOfPaths;
    AlbaWindowsPathHandler(InitialValue const initialValue);
    AlbaWindowsPathHandler(std::string const& path);
    void clear() override;
    std::string getDrive() const;
    double getFileSizeEstimate();
    bool isFoundInLocalSystem() const;
    bool isRelativePath() const;
    void setPathToCurrentPathFromWindows();
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
    void setDrive();
    void findFilesAndDirectoriesWithDepth(
            std::string const& currentDirectory,
            std::string const& wildCardSearch,
            ListOfPaths& listOfFiles,
            ListOfPaths& listOfDirectories,
            int depth) const;
    void printErrorMessageFromWindows() const;
    std::string getLastFormattedErrorMessage(int const errorCode) const;
    std::string m_drive;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}//namespace alba
