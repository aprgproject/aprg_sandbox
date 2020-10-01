#pragma once

#include <AlbaPathHandler.hpp>
#include <functional>
#include <set>
#include <string>

using std::set;
using std::string;
namespace alba{

class AlbaWindowsPathHandler: public AlbaPathHandler{
public:
    AlbaWindowsPathHandler();
    void inputPath(string const& path) override;
    void clear() override;
    string getDrive() const;
    string getWildCardSearch() const;
    double getFileSizeEstimate();
    bool isFoundInLocalSystem() const;
    void createDirectoriesIfItDoesNotExist() const;
    void deleteFile();
    void renameFile(string const& newFileName);
    bool isRelativePath() const;
    void findFilesAndDirectoriesOneDepth(
            string const& wildCardSearch,
            set<string>& listOfFiles,
            set<string>& listOfDirectories) const;
    void findFilesAndDirectoriesMultipleDepth(
            string const& wildCardSearch,
            set<string>& listOfFiles,
            set<string>& listOfDirectories,
            int depth) const;
    void findFilesAndDirectoriesUnlimitedDepth(
            string const& wildCardSearch,
            set<string>& listOfFiles,
            set<string>& listOfDirectories) const;
private:
    void setDrive();
    void findFilesAndDirectoriesWithDepth(
            string const& currentDirectory,
            string const& wildCardSearch,
            set<string>& listOfFiles,
            set<string>& listOfDirectories,
            int depth) const;
    string m_drive;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}//namespace alba
