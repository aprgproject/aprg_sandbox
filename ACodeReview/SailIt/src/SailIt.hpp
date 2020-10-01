#pragma once

#include "CPlusPlus/Database/CPlusPlusDatabase.hpp"
#include "CPlusPlus/Findings/Findings.hpp"
#include "FileDirectoryDatabase/FileDirectoryDatabase.hpp"

namespace codeReview
{
typedef map<string, CPlusPlusDatabase> FileCPlusPlusDatabasesMap;
typedef pair<string, CPlusPlusDatabase> FileCPlusPlusDatabasesPair;
typedef map<string, Findings> FileFindingsMap;
typedef pair<string, Findings> FileFindingsPair;

class SailIt
{
public:

    void printAll(ostream& outputStream);
    void printFindings(ostream& outputStream, string const& finding);
    bool isCPlusPlusDatabaseAvailableForThisFile(string const& fullPathFile);
    FileDirectoryDatabase& getFileDirectoryDatabaseReference();
    CPlusPlusDatabase& getCPlusPlusDatabaseReferenceForThisFile(string const& fullPathFile);
    void addCPlusPlusDatabaseReferenceForThisFileIfNeeded(string const& fullPathFile);
    void addAndAnalyzeThisFileToCPlusPlusDatabase(string const& fullPathFile);

private:
    bool m_isValid;
    FileCPlusPlusDatabasesMap m_fileCPlusPlusDatabasesMap;
    FileFindingsMap m_fileFindingsMap;
    FileDirectoryDatabase m_fileDirectoryDatabase;
};

}
