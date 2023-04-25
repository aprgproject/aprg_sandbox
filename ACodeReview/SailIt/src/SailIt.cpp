#include "SailIt.hpp"

#include "CPlusPlus/Analyzer/TermAnalyzer.hpp"
#include "CPlusPlus/Translator/TermTranslator.hpp"
#include <AlbaLocalPathHandler.hpp>

#include <algorithm>
#include <iostream>

using namespace std;
using namespace alba;

namespace codeReview {

void SailIt::printAll(ostream& outputStream) {
    outputStream << "FileDirectoryDatabase:\n";
    m_fileDirectoryDatabase.printFilesAndDirectories(outputStream);
    outputStream << "\n";
    for (FileCPlusPlusDatabasesPair fileCPlusPlusDatabasesPair : m_fileCPlusPlusDatabasesMap) {
        outputStream << "CPlusPlusDatabase of " << fileCPlusPlusDatabasesPair.first << "\n";
        fileCPlusPlusDatabasesPair.second.print(outputStream);
        outputStream << "Findings for " << fileCPlusPlusDatabasesPair.first << "\n";
        m_fileFindingsMap[fileCPlusPlusDatabasesPair.first].printFindings(outputStream);
    }
}

void SailIt::printFindings(ostream& outputStream, string const& finding) {
    for (FileCPlusPlusDatabasesPair fileCPlusPlusDatabasesPair : m_fileCPlusPlusDatabasesMap) {
        outputStream << "Findings for " << fileCPlusPlusDatabasesPair.first << "\n";
        m_fileFindingsMap[fileCPlusPlusDatabasesPair.first].printFindings(outputStream, finding);
    }
}

bool SailIt::isCPlusPlusDatabaseAvailableForThisFile(string const& fullPathFile) {
    return m_fileCPlusPlusDatabasesMap.find(fullPathFile) != m_fileCPlusPlusDatabasesMap.end();
}

FileDirectoryDatabase& SailIt::getFileDirectoryDatabaseReference() { return m_fileDirectoryDatabase; }

CPlusPlusDatabase& SailIt::getCPlusPlusDatabaseReferenceForThisFile(string const& fullPathFile) {
    return m_fileCPlusPlusDatabasesMap[fullPathFile];
}

void SailIt::addCPlusPlusDatabaseReferenceForThisFileIfNeeded(string const& fullPathFile) {
    if (!isCPlusPlusDatabaseAvailableForThisFile(fullPathFile)) {
        addAndAnalyzeThisFileToCPlusPlusDatabase(fullPathFile);
    }
}

void SailIt::addAndAnalyzeThisFileToCPlusPlusDatabase(string const& fullPathFile) {
    AlbaLocalPathHandler pathHandler;
    pathHandler.inputPath(fullPathFile);
    if (pathHandler.isFoundInLocalSystem()) {
        CPlusPlusDatabase& database = m_fileCPlusPlusDatabasesMap[fullPathFile];
        Findings& findings = m_fileFindingsMap[fullPathFile];
        findings.setFileName(fullPathFile);
        DequeOfTerms terms;
        TermTranslator termTranslator(fullPathFile, findings, terms);
        termTranslator.readFile();
        TermAnalyzer termAnalyzer(terms, database, findings, *this);
        termAnalyzer.setFileName(pathHandler.getDirectory(), pathHandler.getFile());
        termAnalyzer.analyze();
    }
}

}  // namespace codeReview
