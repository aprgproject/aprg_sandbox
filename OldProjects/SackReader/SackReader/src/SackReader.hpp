#pragma once

//Todo
//typedefs
//introduction dag dag from DSP MCU IFS
//refactor to LyxGenerator
//put directory location in Lyx

#include <Database.hpp>

namespace alba
{

class SackReader
{
public:
    SackReader(std::string const& path, std::string const& pathOfLog);
    std::string getFileFullPath(std::string const& fileName) const;
    void gatherAllFiles();
    void readFilesNeededForIfs();
    void readAndMarkFilesNecessaryForIfs();
    void saveDatabaseToFile(std::string const& path);
    void loadDatabaseFromFile(std::string const& path);
    void loadMessagesToGenerate(std::string const& path);
    void loadDescriptionToAdd(std::string const& path);
    void performHacks();
    void performHackPrimitiveType(std::string const& primitiveType);
    void generateLyxDocument(std::string const& ifsTemplatePath, std::string const& finalDocumentPath);

private:
    void readAndMarkTypeAsNeededInIfsRecursively(std::string const& typeName);
    void markStructureAsNeededForIfsRecursively(std::string const & structureName);
    void markUnionAsNeededForIfsRecursively(std::string const & unionName);
    void markEnumAsNeededForIfsRecursively(std::string const& enumName);
    void markTypedefAsNeededForIfsRecursively(std::string const& typedefName);
    void markConstantAsNeededForIfs(std::string const& enumName);
    void readOamTcomTupcMessageFiles();
    void readConstantFiles();
    void readFileUsingTypeName(std::string const& fileName);
    void readFileUsingTypeFileName(std::string const& typeFileName);
    void updateDescriptionFromUser(IfsDefinitionType const currentDefinitionType, std::string const& name, std::string const& parameterName, std::string const& description);
    void updateDescriptionFromUserWithoutParameter(IfsDefinitionType const currentDefinitionType, std::string const& name, std::string const& description);
    void updateDescriptionFromUserWithParameter(IfsDefinitionType const currentDefinitionType, std::string const& name, std::string const& parameterName, std::string const& description);
private:
    std::string m_path;
    std::string m_pathOfLog;
    Database m_database;
};

}
