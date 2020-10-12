#pragma once

#include <functional>
#include <PathHandlers/AlbaPathHandler.hpp>
#include <set>
#include <string>

namespace alba{

class AlbaWindowsPathHandler: public AlbaPathHandler
{
public:
    typedef std::set<std::string> ListOfPaths;
    AlbaWindowsPathHandler(std::string const& path);
    void clear() override;
    std::string getDrive() const;
    double getFileSizeEstimate();
    bool isFoundInLocalSystem() const;
    void createDirectoriesIfItDoesNotExist() const;
    void deleteFile();
    void renameFile(std::string const& newFileName);
    bool isRelativePath() const;
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
    std::string m_drive;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};
}//namespace alba