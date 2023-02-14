#include "LyxGenerator.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <fstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

LyxGenerator::LyxGenerator(std::string const& pathOfLog, Database const& database)
    : m_logStream(pathOfLog)
    , m_database(database)
{

}

void LyxGenerator::generateLyxDocument(string const& ifsTemplatePath, string const& finalDocumentPath)
{
    ifstream lyxDocumentTemplate(ifsTemplatePath);
    ofstream lyxFinalDocumentStream(finalDocumentPath);
    AlbaFileReader lyxDocumentTemplateReader(lyxDocumentTemplate);

    bool isInsideGeneratedCode(false);
    while(lyxDocumentTemplateReader.isNotFinished())
    {
        string line(lyxDocumentTemplateReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(line,"LYX_START_GENERATED_CODE"))
        {
            isInsideGeneratedCode = true;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(line,"LYX_END_GENERATED_CODE"))
        {
            isInsideGeneratedCode = false;
            saveMessageDefinitions(lyxFinalDocumentStream);
            saveStructureDefinitions(lyxFinalDocumentStream);
            saveUnionDefinitions(lyxFinalDocumentStream);
            saveEnumDefinitions(lyxFinalDocumentStream);
            saveTypedefDefinitions(lyxFinalDocumentStream);
            saveConstantDefinitions(lyxFinalDocumentStream);
        }
        else if(!isInsideGeneratedCode)
        {
            lyxFinalDocumentStream << line << endl;
        }
    }
}

void LyxGenerator::saveSubsection(string const& subsectionName, ofstream & lyxOutputFileStream) const
{
    ifstream subsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\Subsection.txt)");
    AlbaFileReader subsectionReader(subsectionStream);

    while(subsectionReader.isNotFinished())
    {
        string subsectionLine(subsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(subsectionLine,"LYX_SUBSECTION_NAME_REPLACE"))
        {
            lyxOutputFileStream << subsectionName << endl;
        }
        else
        {
            lyxOutputFileStream << subsectionLine << endl;
        }
    }
}

void LyxGenerator::saveMessageDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Message Definitions", lyxOutputFileStream);
    for(string const& messageName : m_database.messagesToGenerate)
    {
        saveMessageDefinitionSubsubsection(messageName, lyxOutputFileStream);
    }
}

void LyxGenerator::saveStructureDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Structure Definitions", lyxOutputFileStream);
    for(auto const& pair : m_database.structureNameToStructureDetailsMap)
    {
        if(!pair.second.isMessage && pair.second.isUsedInIfs)
        {            saveStructureDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}
void LyxGenerator::saveEnumDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Enum Definitions", lyxOutputFileStream);
    for(auto const& pair : m_database.enumNameToEnumDetailsMap)
    {
        if(pair.second.isUsedInIfs)
        {            saveEnumDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}
void LyxGenerator::saveUnionDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Union Definitions", lyxOutputFileStream);
    for(auto const& pair : m_database.unionNameToUnionDetailsMap)
    {
        if(pair.second.isUsedInIfs)
        {            saveUnionDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}
void LyxGenerator::saveConstantDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Constant Definitions", lyxOutputFileStream);
    for(auto const& pair : m_database.constantNameToConstantDetailsMap)
    {
        if(pair.second.isUsedInIfs)
        {            saveConstantDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}
void LyxGenerator::saveTypedefDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Typedef Definitions", lyxOutputFileStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveTypes(lyxOutputFileStream);
    saveTypedefDefinitionSubsubsectionFromDatabase(lyxOutputFileStream);
}

void LyxGenerator::saveMessageDefinitionSubsubsection(string const& messageName, ofstream & messageDefinitionsStream)
{
    ifstream messageSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\MessageSubsubsection.txt)");
    AlbaFileReader messageSubsubsectionReader(messageSubsubsectionStream);
    MessageDetails messageDetails(m_database.getMessageDetails(messageName));
    StructureDetails structureDetails(m_database.getStructureDetails(messageDetails.structureName));

    while(messageSubsubsectionReader.isNotFinished())
    {
        string messageSubsubsectionLine(messageSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_NAME_REPLACE", messageDetails.name);
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_PATH_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_PATH_REPLACE", messageDetails.path);
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_STRUCTURE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_STRUCTURE_NAME_REPLACE", structureDetails.name);
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_STRUCTURE_PATH_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_STRUCTURE_PATH_REPLACE", structureDetails.path);
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveMessageTable(messageName, messageDefinitionsStream);
        }
        else
        {
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
    }
}

void LyxGenerator::saveStructureDefinitionSubsubsection(string const& structureName, ofstream & structureDefinitionsStream)
{
    ifstream structureSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\StructureSubsubsection.txt)");
    AlbaFileReader structureSubsubsectionReader(structureSubsubsectionStream);
    StructureDetails structureDetails(m_database.getStructureDetails(structureName));

    while(structureSubsubsectionReader.isNotFinished())
    {
        string structureSubsubsectionLine(structureSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(structureSubsubsectionLine,"LYX_TABLE_STRUCTURE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(structureSubsubsectionLine, "LYX_TABLE_STRUCTURE_NAME_REPLACE", structureDetails.name);
            structureDefinitionsStream << structureSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(structureSubsubsectionLine,"LYX_TABLE_STRUCTURE_PATH_REPLACE"))
        {
            transformReplaceStringIfFound(structureSubsubsectionLine, "LYX_TABLE_STRUCTURE_PATH_REPLACE", structureDetails.path);
            structureDefinitionsStream << structureSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(structureSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveStructureTable(structureName, structureDefinitionsStream);
        }
        else
        {
            structureDefinitionsStream << structureSubsubsectionLine << endl;
        }
    }
}

void LyxGenerator::saveEnumDefinitionSubsubsection(string const& enumName, ofstream & enumDefinitionsStream)
{
    ifstream enumSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\EnumSubsubsection.txt)");
    AlbaFileReader enumSubsubsectionReader(enumSubsubsectionStream);
    EnumDetails enumDetails(m_database.getEnumDetails(enumName));

    while(enumSubsubsectionReader.isNotFinished())
    {
        string enumSubsubsectionLine(enumSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(enumSubsubsectionLine,"LYX_TABLE_ENUM_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(enumSubsubsectionLine, "LYX_TABLE_ENUM_NAME_REPLACE", enumDetails.name);
            enumDefinitionsStream << enumSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(enumSubsubsectionLine,"LYX_TABLE_ENUM_PATH_REPLACE"))
        {
            transformReplaceStringIfFound(enumSubsubsectionLine, "LYX_TABLE_ENUM_PATH_REPLACE", enumDetails.path);
            enumDefinitionsStream << enumSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(enumSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveEnumTable(enumName, enumDefinitionsStream);
        }
        else
        {
            enumDefinitionsStream << enumSubsubsectionLine << endl;
        }
    }
}

void LyxGenerator::saveUnionDefinitionSubsubsection(string const& unionName, ofstream & unionDefinitionsStream)
{
    ifstream unionSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\UnionSubsubsection.txt)");
    AlbaFileReader unionSubsubsectionReader(unionSubsubsectionStream);
    UnionDetails unionDetails(m_database.getUnionDetails(unionName));

    while(unionSubsubsectionReader.isNotFinished())
    {
        string unionSubsubsectionLine(unionSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(unionSubsubsectionLine,"LYX_TABLE_UNION_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(unionSubsubsectionLine, "LYX_TABLE_UNION_NAME_REPLACE", unionDetails.name);
            unionDefinitionsStream << unionSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(unionSubsubsectionLine,"LYX_TABLE_UNION_PATH_REPLACE"))
        {
            transformReplaceStringIfFound(unionSubsubsectionLine, "LYX_TABLE_UNION_PATH_REPLACE", unionDetails.path);
            unionDefinitionsStream << unionSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(unionSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveUnionTable(unionName, unionDefinitionsStream);
        }
        else
        {
            unionDefinitionsStream << unionSubsubsectionLine << endl;
        }
    }
}

void LyxGenerator::saveConstantDefinitionSubsubsection(string const& constantName, ofstream & constantDefinitionsStream)
{
    ifstream constantSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\CommentSubsubsection.txt)");
    AlbaFileReader constantSubsubsectionReader(constantSubsubsectionStream);
    ConstantDetails constantDetails(m_database.getConstantDetails(constantName));

    while(constantSubsubsectionReader.isNotFinished())
    {
        string constantSubsubsectionLine(constantSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(constantSubsubsectionLine,"LYX_TABLE_COMMENT_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(constantSubsubsectionLine, "LYX_TABLE_COMMENT_NAME_REPLACE", constantDetails.name);
            constantDefinitionsStream << constantSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(constantSubsubsectionLine,"LYX_TABLE_COMMENT_PATH_REPLACE"))
        {
            transformReplaceStringIfFound(constantSubsubsectionLine, "LYX_TABLE_COMMENT_PATH_REPLACE", constantDetails.path);
            constantDefinitionsStream << constantSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(constantSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveConstantTable(constantName, constantDefinitionsStream);
        }
        else
        {
            constantDefinitionsStream << constantSubsubsectionLine << endl;
        }
    }
}

void LyxGenerator::saveTypedefDefinitionSubsubsectionFromDatabase(ofstream& lyxOutputFileStream)
{
    for(auto const& pair : m_database.typedefNameToTypedefDetailsMap)
    {
        if(pair.second.isUsedInIfs)
        {            saveTypedefDefinitionSubsubsectionUsingTypedefName(pair.first, lyxOutputFileStream);
        }
    }
}
void LyxGenerator::saveTypedefDefinitionSubsubsectionUsingTypedefName(string const& typedefName, ofstream & typedefDefinitionsStream)
{
    TypedefDetails typedefDetails(m_database.getTypedefDetails(typedefName));
    saveTypedefDefinitionSubsubsectionWithTypedefDetails(typedefDetails, typedefDefinitionsStream);
}

void LyxGenerator::saveTypedefDefinitionSubsubsectionForPrimitiveTypes(ofstream & typedefDefinitionsStream)
{
    saveTypedefDefinitionSubsubsectionForPrimitiveType("u8", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("u16", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("u32", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("i8", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("i16", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("i32", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("r32", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("r64", typedefDefinitionsStream);
    saveTypedefDefinitionSubsubsectionForPrimitiveType("r128", typedefDefinitionsStream);
}

void LyxGenerator::saveTypedefDefinitionSubsubsectionForPrimitiveType(string const& primitiveTypeName, ofstream & typedefDefinitionsStream)
{
    TypedefDetails typedefDetails;
    typedefDetails.name = primitiveTypeName;
    typedefDetails.description = getPrimitiveTypeDescription(primitiveTypeName);
    saveTypedefDefinitionSubsubsectionWithTypedefDetails(typedefDetails, typedefDefinitionsStream);
}

void LyxGenerator::saveTypedefDefinitionSubsubsectionWithTypedefDetails(TypedefDetails const& typedefDetails, ofstream& typedefDefinitionsStream)
{
    ifstream typedefSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\TypedefSubsubsection.txt)");
    AlbaFileReader typedefSubsubsectionReader(typedefSubsubsectionStream);

    while(typedefSubsubsectionReader.isNotFinished())
    {
        string typedefSubsubsectionLine(typedefSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(typedefSubsubsectionLine,"LYX_TABLE_TYPEDEF_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(typedefSubsubsectionLine, "LYX_TABLE_TYPEDEF_NAME_REPLACE", typedefDetails.name);
            typedefDefinitionsStream << typedefSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(typedefSubsubsectionLine,"LYX_TABLE_TYPEDEF_PATH_REPLACE"))
        {
            transformReplaceStringIfFound(typedefSubsubsectionLine, "LYX_TABLE_TYPEDEF_PATH_REPLACE", typedefDetails.path);
            typedefDefinitionsStream << typedefSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(typedefSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveTypedefTable(typedefDetails, typedefDefinitionsStream);
        }
        else
        {
            typedefDefinitionsStream << typedefSubsubsectionLine << endl;
        }
    }
}

void LyxGenerator::saveMessageTable(string const& messageName, ofstream & messageTableStream)
{
    DisplayTable messageTable;
    messageTable.setBorders("-"," | ");
    messageTable.addRow();
    messageTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    messageTable.getLastRow().addCell("\\series bold \nIE Type");
    messageTable.getLastRow().addCell("\\series bold \nDescription");
    generateStructureForDisplayTablesIfNeeded(m_database.getMessageStructure(messageName), messageTable, "", true);
    //cout<<messageTable.drawOutput()<<endl;
    saveDisplayTable(messageTable, messageTableStream);
}

void LyxGenerator::saveStructureTable(string const& structureName, ofstream & structureTableStream)
{
    DisplayTable structureTable;
    structureTable.setBorders("-"," | ");
    structureTable.addRow();
    structureTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    structureTable.getLastRow().addCell("\\series bold \nIE Type");
    structureTable.getLastRow().addCell("\\series bold \nDescription");
    generateStructureForDisplayTablesIfNeeded(structureName, structureTable, "", false);
    if(structureTable.getTotalRows()>1)
    {
        //cout<<structureTable.drawOutput()<<endl;
        saveDisplayTable(structureTable, structureTableStream);
    }
}

void LyxGenerator::saveEnumTable(string const& enumName, ofstream & enumTableStream)
{
    DisplayTable enumTable;
    enumTable.setBorders("-"," | ");
    enumTable.addRow();
    enumTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    enumTable.getLastRow().addCell("\\series bold \n Value");
    enumTable.getLastRow().addCell("\\series bold \nDescription");
    generateEnumForDisplayTablesIfNeeded(enumName, enumTable);
    //cout<<enumTable.drawOutput()<<endl;
    saveDisplayTable(enumTable, enumTableStream);
}

void LyxGenerator::saveUnionTable(string const& unionName, ofstream & unionTableStream)
{
    DisplayTable unionTable;
    unionTable.setBorders("-"," | ");
    unionTable.addRow();
    unionTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    unionTable.getLastRow().addCell("\\series bold \nIE Type");
    unionTable.getLastRow().addCell("\\series bold \nDescription");
    generateUnionForDisplayTablesIfNeeded(unionName, unionTable, "", false);
    if(unionTable.getTotalRows()>1)
    {
        //cout<<unionTable.drawOutput()<<endl;
        saveDisplayTable(unionTable, unionTableStream);
    }
}

void LyxGenerator::saveConstantTable(string const& constantName, ofstream & constantTableStream)
{
    DisplayTable constantTable;
    constantTable.setBorders("-"," | ");
    constantTable.addRow();
    constantTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    constantTable.getLastRow().addCell("\\series bold \nIE Value");
    constantTable.getLastRow().addCell("\\series bold \nDescription");
    generateConstantForDisplayTablesIfNeeded(constantName, constantTable);
    if(constantTable.getTotalRows()>1)
    {
        //cout<<constantTable.drawOutput()<<endl;
        saveDisplayTable(constantTable, constantTableStream);
    }
}

void LyxGenerator::saveTypedefTable(TypedefDetails const& typedefDetails, ofstream & typedefTableStream)
{
    DisplayTable typedefTable;
    typedefTable.setBorders("-"," | ");
    typedefTable.addRow();
    typedefTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    typedefTable.getLastRow().addCell("\\series bold \nIE Type");
    typedefTable.getLastRow().addCell("\\series bold \nDescription");
    generateTypedefForDisplayTablesIfNeeded(typedefDetails, typedefTable);
    if(typedefTable.getTotalRows()>1)
    {
        //cout<<typedefTable.drawOutput()<<endl;
        saveDisplayTable(typedefTable, typedefTableStream);
    }
}

void LyxGenerator::saveDisplayTable(DisplayTable const& displayTable, ofstream & displayTableStream) const
{
    ifstream tableTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\Table.txt)");
    AlbaFileReader tableTemplateReader(tableTemplateStream);
    while(tableTemplateReader.isNotFinished())
    {
        string tableTemplateLine(tableTemplateReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_REPLACE"))
        {
            for(unsigned int row=0; row<displayTable.getTotalRows(); row++)
            {
                ifstream tableRowTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\TableRow.txt)");
                AlbaFileReader tableRowTemplateReader(tableRowTemplateStream);
                while(tableRowTemplateReader.isNotFinished())
                {
                    string tableRowTemplateLine(tableRowTemplateReader.getLine());
                    if(isStringFoundInsideTheOtherStringCaseSensitive(tableRowTemplateLine,"LYX_TABLE_ROW_REPLACE"))
                    {
                        for(unsigned int column=0; column<displayTable.getTotalColumns(); column++)
                        {
                            ifstream tableCellTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\TableCell.txt)");
                            AlbaFileReader tableCellTemplateReader(tableCellTemplateStream);
                            while(tableCellTemplateReader.isNotFinished())
                            {
                                string tableCellTemplateLine(tableCellTemplateReader.getLine());
                                if(isStringFoundInsideTheOtherStringCaseSensitive(tableCellTemplateLine,"LYX_TABLE_CELL_REPLACE"))
                                {
                                    displayTableStream << displayTable.getCellAt(row, column).getText()<<endl;
                                }
                                else
                                {
                                    displayTableStream << tableCellTemplateLine << endl;
                                }
                            }
                        }
                    }
                    else
                    {
                        displayTableStream << tableRowTemplateLine << endl;
                    }
                }
            }
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_NUM_ROW_REPLACE")
                || isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_NUM_COLUMN_REPLACE"))
        {
            transformReplaceStringIfFound(tableTemplateLine, "LYX_TABLE_NUM_ROW_REPLACE", convertToString(displayTable.getTotalRows()));
            transformReplaceStringIfFound(tableTemplateLine, "LYX_TABLE_NUM_COLUMN_REPLACE", convertToString(displayTable.getTotalColumns()));
            displayTableStream << tableTemplateLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_COLUMN_REPLACE"))        {
            for(unsigned int i=0; i<displayTable.getTotalColumns()-1; i++) //until description
            {
                displayTableStream << tableTemplateLine << endl;            }
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_DESCRIPTION_COLUMN_REPLACE"))
        {
            displayTableStream << tableTemplateLine << endl; //for description
        }
        else
        {
            displayTableStream << tableTemplateLine << endl;
        }
    }
}

void LyxGenerator::generateStructureForDisplayTablesIfNeeded(string const& structureName, DisplayTable & displayTable, string const& indentionInType, bool const areInnerStructuresGenerated)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisStructureExists(structureName))
    {
        StructureDetails structureDetails(m_database.getStructureDetails(structureName));
        for(string const& parameterName : structureDetails.parametersWithCorrectOrder)
        {
            ParameterDetails parameterDetails = m_database.getStructureParameterDetails(structureName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+indentionInType+" "+parameterDetails.name);
            string finalType(parameterDetails.type);
            if(parameterDetails.isAnArray)
            {
                finalType = finalType+" ["+parameterDetails.arraySize+"]";
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalType);

            string finalDescription(getDescriptionString(structureName+" "+parameterName, parameterDetails.description, parameterDetails.descriptionFromUser));
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
            if(areInnerStructuresGenerated)
            {
                generateStructureForDisplayTablesIfNeeded(parameterDetails.type, displayTable, indentionInType+">", true);
            }
        }
    }
}

void LyxGenerator::generateEnumForDisplayTablesIfNeeded(string const& enumName, DisplayTable & displayTable)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisEnumExists(enumName))
    {
        EnumDetails enumDetails(m_database.getEnumDetails(enumName));

        vector<string> sortedEnumParameterNamesByValue;
        for(auto const& parameterPair : enumDetails.parameters)
        {
            sortedEnumParameterNamesByValue.emplace_back(parameterPair.first);
        }        sort(sortedEnumParameterNamesByValue.begin(), sortedEnumParameterNamesByValue.end(), [&](string const& parameterName1, string const& parameterName2)
        {
            EnumParameterDetails parameterDetails1 = m_database.getEnumParameterDetails(enumName, parameterName1);
            EnumParameterDetails parameterDetails2 = m_database.getEnumParameterDetails(enumName, parameterName2);            return convertHexStringToNumber<unsigned int>(parameterDetails1.value)<convertHexStringToNumber<unsigned int>(parameterDetails2.value);
        });

        for(string const& parameterName : sortedEnumParameterNamesByValue)
        {
            EnumParameterDetails parameterDetails = m_database.getEnumParameterDetails(enumName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+" "+parameterDetails.name);
            displayTable.getLastRow().addCell(smallTextModifier+parameterDetails.value);
            string finalDescription(getDescriptionString(enumName+" "+parameterName, parameterDetails.description, parameterDetails.descriptionFromUser));
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
        }
    }
}

void LyxGenerator::generateUnionForDisplayTablesIfNeeded(string const& unionName, DisplayTable & displayTable, string const& indentionInType, bool const areInnerStructuresGenerated)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisUnionExists(unionName))
    {
        UnionDetails unionDetails(m_database.getUnionDetails(unionName));
        for(string const& parameterName : unionDetails.parametersWithCorrectOrder)
        {
            ParameterDetails parameterDetails = m_database.getUnionParameterDetails(unionName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+indentionInType+" "+parameterDetails.name);
            string finalType(parameterDetails.type);
            if(parameterDetails.isAnArray)
            {
                finalType = finalType+" ["+parameterDetails.arraySize+"]";
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalType);
            string finalDescription(getDescriptionString(unionName+" "+parameterName, parameterDetails.description, parameterDetails.descriptionFromUser));
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
            if(areInnerStructuresGenerated)
            {
                generateUnionForDisplayTablesIfNeeded(parameterDetails.type, displayTable, indentionInType+">", true);
            }
        }
    }
}

void LyxGenerator::generateConstantForDisplayTablesIfNeeded(string const& constantName, DisplayTable & displayTable)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisConstantExists(constantName))
    {
        ConstantDetails constantDetails(m_database.getConstantDetails(constantName));
        displayTable.addRow();
        displayTable.getLastRow().addCell(smallTextModifier+constantDetails.name);
        displayTable.getLastRow().addCell(smallTextModifier+constantDetails.value);
        string finalDescription(getDescriptionString(constantName, constantDetails.description, constantDetails.descriptionFromUser));
        displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
    }
}

void LyxGenerator::generateTypedefForDisplayTablesIfNeeded(TypedefDetails const& typedefDetails, DisplayTable & displayTable)
{
    string smallTextModifier("\\size footnotesize\n");
    displayTable.addRow();
    displayTable.getLastRow().addCell(smallTextModifier+typedefDetails.name);
    displayTable.getLastRow().addCell(smallTextModifier+typedefDetails.typedefDerivedName);
    string finalDescription(
                getPrimitiveTypeDescription(typedefDetails.typedefDerivedName)+" "+
                getDescriptionString(typedefDetails.name, typedefDetails.description, typedefDetails.descriptionFromUser));
    displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
}

string LyxGenerator::getDescriptionString(string const& printIdentifier, string const& description, string const& descriptionFromUser)
{
    string sackDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(description)));
    string userDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(descriptionFromUser)));
    string finalDescription;
    if(!userDescription.empty())
    {
        if(sackDescription!=userDescription)
        {
            m_logStream<<"The description needs to be aligned with sack. "<<printIdentifier<<" sackDescription: ["<<sackDescription<<"] userDescription: ["<<userDescription<<"]"<<endl;
        }
        finalDescription = userDescription;
    }
    else
    {
        finalDescription = sackDescription;
    }
    return finalDescription;
}

}
