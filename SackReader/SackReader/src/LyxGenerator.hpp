#pragma once

#include <Database.hpp>
#include <User/DisplayTable.hpp>

#include <fstream>
#include <string>

namespace alba
{

class LyxGenerator
{
public:
    LyxGenerator(std::string const& pathOfLog, Database const& database);
    void generateLyxDocument(std::string const& ifsTemplatePath, std::string const& finalDocumentPath);

private:
    void saveSubsection(std::string const& subsectionName, std::ofstream & lyxOutputFileStream) const;
    void saveMessageDefinitions(std::ofstream & lyxOutputFileStream);
    void saveStructureDefinitions(std::ofstream & lyxOutputFileStream);
    void saveEnumDefinitions(std::ofstream & lyxOutputFileStream);
    void saveUnionDefinitions(std::ofstream & lyxOutputFileStream);
    void saveConstantDefinitions(std::ofstream & lyxOutputFileStream);
    void saveTypedefDefinitions(std::ofstream & lyxOutputFileStream);
    void saveMessageDefinitionSubsubsection(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureDefinitionSubsubsection(std::string const& structureName, std::ofstream & structureDefinitionsStream);
    void saveEnumDefinitionSubsubsection(std::string const& enumName, std::ofstream & enumDefinitionsStream);
    void saveUnionDefinitionSubsubsection(std::string const& unionName, std::ofstream & unionDefinitionsStream);
    void saveConstantDefinitionSubsubsection(std::string const& constantName, std::ofstream & unionDefinitionsStream);
    void saveTypedefDefinitionSubsubsectionFromDatabase(std::ofstream& lyxOutputFileStream);
    void saveTypedefDefinitionSubsubsectionUsingTypedefName(std::string const& typedefName, std::ofstream & typedefDefinitionsStream);
    void saveTypedefDefinitionSubsubsectionForPrimitiveTypes(std::ofstream & typedefDefinitionsStream);
    void saveTypedefDefinitionSubsubsectionForPrimitiveType(std::string const& primitiveTypeName, std::ofstream & typedefDefinitionsStream);
    void saveTypedefDefinitionSubsubsectionWithTypedefDetails(TypedefDetails const& typedefDetails, std::ofstream& typedefDefinitionsStream);
    void saveMessageTable(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureTable(std::string const& structureName, std::ofstream & structureTableStream);
    void saveEnumTable(std::string const& enumName, std::ofstream & enumTableStream);
    void saveUnionTable(std::string const& unionName, std::ofstream & unionTableStream);
    void saveConstantTable(std::string const& constantName, std::ofstream & constantTableStream);
    void saveTypedefTable(TypedefDetails const& typedefDetails, std::ofstream & typedefTableStream);
    void saveDisplayTable(DisplayTable const& messageTable, std::ofstream & messageTableStream) const;
    void generateStructureForDisplayTablesIfNeeded(std::string const& structureName, DisplayTable & messageTable, std::string const& indentionInType, bool const areInnerStructuresGenerated);
    void generateEnumForDisplayTablesIfNeeded(std::string const& enumName, DisplayTable & displayTable);
    void generateUnionForDisplayTablesIfNeeded(std::string const& unionName, DisplayTable & displayTable, std::string const& indentionInType, bool const areInnerStructuresGenerated);
    void generateConstantForDisplayTablesIfNeeded(std::string const& constantName, DisplayTable & displayTable);
    void generateTypedefForDisplayTablesIfNeeded(TypedefDetails const& typedefDetails, DisplayTable & displayTable);
    std::string getDescriptionString(std::string const& printIdentifier, std::string const& description, std::string const& descriptionFromUser);
    std::ofstream m_logStream;
    Database const& m_database;
};

}
