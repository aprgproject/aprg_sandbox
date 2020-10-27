#pragma once

#include "../DatabaseTypes.hpp"

#include <vector>

using std::vector;

namespace codeReview
{

enum class RecursionDirectionType{Inner, Outer};

class CMakeDatabase;

typedef set<string> SetOfFiles;
typedef set<string> SetOfDirectories;
typedef vector<CMakeDatabase> SubCMakeDatabases;

class CMakeDatabase
{
public:
    CMakeDatabase();
    CMakeDatabase(CMakeDatabase& parentCMake);
    CMakeDatabase(CMakeDatabase&&) = default;

    SetOfFiles& getSetOfFilesReference();
    SetOfDirectories& getSetOfDirectoriesReference();
    SubCMakeDatabases& getSubCMakeDatabasesReference();
    void printFilesAndDirectories() const;
    void addFileOrDirectory(string const& fileOrDirectory);
    void setCMakeFileDirectoryPath(string const& cMakeFileDirectoryPath);
    void allowNonExistentDirectories();
    CMakeDatabase& addCMakeSubDirectory();
    CMakeDatabase& find_InnerDirection(
            string const& stringPathIn,
            bool& isFoundResult,
            string& stringFullPathOut);
    CMakeDatabase& find_OuterDirection(
            string const& stringPathIn,
            bool& isFoundResult,
            string& stringFullPathOut);
    void clear();
private:
    template <RecursionDirectionType direction> CMakeDatabase& findFile(
            string const& stringPathIn,
            string const& fileName,
            bool& isFoundResult,
            string& stringFullPathOut);
    template <RecursionDirectionType direction> CMakeDatabase& findDirectory(
            string const& stringPathIn,
            bool& isFoundResult,
            string& stringFullPathOut);
    template <RecursionDirectionType direction> CMakeDatabase& proceedToNextFile(
            string const& stringPathIn,
            string const& wildCardSearch,
            bool& isFoundResult,
            string& stringFullPathOut);
    template <RecursionDirectionType direction> CMakeDatabase& proceedToNextDirectory(
            string const& stringPathIn,
            bool& isFoundResult,
            string& stringFullPathOut);
    SetOfFiles m_setOfFiles;
    SetOfDirectories m_setOfDirectories;
    SubCMakeDatabases m_subCMakeDatabases;
    string m_cMakeFileDirectoryPath;
    bool m_isNonExistentDirectoriesAllowed;
    CMakeDatabase& m_parentCMake;
    bool m_hasCMakeParent;
};


}// namespace codeReview
