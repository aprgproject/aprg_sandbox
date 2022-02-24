#include "SackReader.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <LyxGenerator.hpp>
#include <SackFileReader/SackFileReader.hpp>

#include <fstream>
using namespace alba::stringHelper;
using namespace std;
namespace alba
{

SackReader::SackReader(string const& path, string const& pathOfLog)
    : m_path(path)
    , m_pathOfLog(pathOfLog)
{
    m_path = AlbaLocalPathHandler(path).getFullPath();
}

string SackReader::getFileFullPath(string const& fileName) const
{
    return m_database.getFileFullPath(fileName);
}

void SackReader::gatherAllFiles()
{
    AlbaLocalPathHandler pathHandler(m_path);
    ListOfPaths files;
    ListOfPaths directories;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(string const& file : files)
    {
        AlbaLocalPathHandler filePathHandler(file);
        string extension(filePathHandler.getExtension());
        if("c" == extension || "cpp" == extension || "h" == extension || "hpp" == extension || "sig" == extension)
        {
            m_database.fileToPathMap.emplace(filePathHandler.getFile(), filePathHandler.getFullPath());
        }
    }
}

void SackReader::readFilesNeededForIfs()
{
    readConstantFiles();
    readOamTcomTupcMessageFiles();
}

void SackReader::readAndMarkFilesNecessaryForIfs()
{
    for(string const& messageName : m_database.messagesToGenerate)
    {
        string typeName(m_database.getMessageStructure(messageName));
        readAndMarkTypeAsNeededInIfsRecursively(typeName);
    }
}

void SackReader::saveDatabaseToFile(string const& path)
{
    m_database.saveDatabaseToFile(path);
}

void SackReader::loadDatabaseFromFile(string const& path)
{
    m_database.loadDatabaseFromFile(path);
}

void SackReader::loadMessagesToGenerate(string const& path)
{
    ifstream messageToGenerateStream(path);
    AlbaFileReader messageToGenerateReader(messageToGenerateStream);
    while(messageToGenerateReader.isNotFinished())
    {
        string line(messageToGenerateReader.getLine());
        if(!line.empty())
        {
            m_database.messagesToGenerate.emplace(line);
        }
    }
}

void SackReader::loadDescriptionToAdd(string const& path)
{
    ifstream messageToGenerateStream(path);
    AlbaFileReader messageToGenerateReader(messageToGenerateStream);
    string name, parameterName;
    IfsDefinitionType currentDefinitionType;
    while(messageToGenerateReader.isNotFinished())
    {
        string line(messageToGenerateReader.getLineAndIgnoreWhiteSpaces());
        if(!line.empty())
        {
            if(line.substr(0,2) != R"(//)")
            {
                if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&struct:"))
                {
                    name = getStringWithoutStartingAndTrailingWhiteSpace(getStringAfterThisString(line, "&&&struct:"));
                    currentDefinitionType = IfsDefinitionType::Struct;
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&union:"))
                {
                    name = getStringWithoutStartingAndTrailingWhiteSpace(getStringAfterThisString(line, "&&union:"));
                    currentDefinitionType = IfsDefinitionType::Union;
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&enum:"))
                {
                    name = getStringWithoutStartingAndTrailingWhiteSpace(getStringAfterThisString(line, "&&enum:"));
                    currentDefinitionType = IfsDefinitionType::Enum;
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&typedef:"))
                {
                    name = getStringWithoutStartingAndTrailingWhiteSpace(getStringAfterThisString(line, "&&typedef:"));
                    currentDefinitionType = IfsDefinitionType::Typedef;
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&constant:"))
                {
                    name = getStringWithoutStartingAndTrailingWhiteSpace(getStringAfterThisString(line, "&&constant:"));
                    currentDefinitionType = IfsDefinitionType::Constant;
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&param:"))
                {
                    parameterName = getStringWithoutStartingAndTrailingWhiteSpace(getStringAfterThisString(line, "&&&param:"));
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&description:"))
                {
                    string description(getStringWithoutStartingAndTrailingWhiteSpace(getStringAfterThisString(line, "&&&description:")));
                    updateDescriptionFromUser(currentDefinitionType, name, parameterName, description);
                }
            }
        }
    }
}

void SackReader::performHacks()
{
    //This should be hacked because syscom defines causes a different definition.
    StructureDetails & structureDetailsSMessageAddress(m_database.structureNameToStructureDetailsMap["SMessageAddress"]);
    structureDetailsSMessageAddress.name = "SMessageAddress";
    structureDetailsSMessageAddress.isMessage = false;
    structureDetailsSMessageAddress.isUsedInIfs = true;
    structureDetailsSMessageAddress.parametersWithCorrectOrder.clear();
    structureDetailsSMessageAddress.parametersWithCorrectOrder.emplace_back("board");
    structureDetailsSMessageAddress.parametersWithCorrectOrder.emplace_back("cpu");
    structureDetailsSMessageAddress.parametersWithCorrectOrder.emplace_back("task");
    structureDetailsSMessageAddress.parameters["board"].name = "board";
    structureDetailsSMessageAddress.parameters["board"].type = "TBoard";
    structureDetailsSMessageAddress.parameters["board"].isAnArray = false;
    structureDetailsSMessageAddress.parameters["board"].descriptionFromUser = "Board in SMessageAddress";
    structureDetailsSMessageAddress.parameters["cpu"].name = "cpu";
    structureDetailsSMessageAddress.parameters["cpu"].type = "TCpu";
    structureDetailsSMessageAddress.parameters["cpu"].isAnArray = false;
    structureDetailsSMessageAddress.parameters["cpu"].descriptionFromUser = "Cpu in SMessageAddress";
    structureDetailsSMessageAddress.parameters["task"].name = "task";
    structureDetailsSMessageAddress.parameters["task"].type = "TTask";
    structureDetailsSMessageAddress.parameters["task"].isAnArray = false;
    structureDetailsSMessageAddress.parameters["task"].descriptionFromUser = "Task in SMessageAddress";
    /*performHackPrimitiveType("u8");
    performHackPrimitiveType("u16");
    performHackPrimitiveType("u32");
    performHackPrimitiveType("i8");
    performHackPrimitiveType("i16");
    performHackPrimitiveType("i32");
    performHackPrimitiveType("r32");
    performHackPrimitiveType("r64");
    performHackPrimitiveType("r128");*/
    m_database.constantNameToConstantDetailsMap["MAX_NUM_OF_HSPA_SCHEDULERS"].value = "16";
}

void SackReader::performHackPrimitiveType(string const& primitiveType)
{
    m_database.typedefNameToTypedefDetailsMap[primitiveType].name = primitiveType;
    m_database.typedefNameToTypedefDetailsMap[primitiveType].typedefDerivedName = primitiveType;
}

void SackReader::generateLyxDocument(string const& ifsTemplatePath, string const& finalDocumentPath)
{
    LyxGenerator generator(m_pathOfLog, m_database);
    generator.generateLyxDocument(ifsTemplatePath, finalDocumentPath);
}

void SackReader::readAndMarkTypeAsNeededInIfsRecursively(string const& typeName)
{
    if(!m_database.doesThisFullDetailedStructureExists(typeName) &&
            !m_database.doesThisUnionExists(typeName) &&
            !m_database.doesThisEnumExists(typeName) &&
            !m_database.doesThisTypedefExists(typeName))
    {
        readFileUsingTypeName(typeName);
    }
    markStructureAsNeededForIfsRecursively(typeName);
    markUnionAsNeededForIfsRecursively(typeName);
    markEnumAsNeededForIfsRecursively(typeName);
    markTypedefAsNeededForIfsRecursively(typeName);
}

void SackReader::markStructureAsNeededForIfsRecursively(string const& structureName)
{
    if(m_database.doesThisStructureExists(structureName))
    {
        m_database.structureNameToStructureDetailsMap[structureName].isUsedInIfs=true;
        StructureDetails structureDetails(m_database.getStructureDetails(structureName));
        for(string const& parameterName : structureDetails.parametersWithCorrectOrder)
        {
            ParameterDetails parameterDetails = m_database.getStructureParameterDetails(structureName, parameterName);
            if(parameterDetails.isAnArray)
            {
                markConstantAsNeededForIfs(parameterDetails.arraySize);
            }
            readAndMarkTypeAsNeededInIfsRecursively(parameterDetails.type);
        }
    }
}

void SackReader::markUnionAsNeededForIfsRecursively(string const& unionName)
{
    if(m_database.doesThisUnionExists(unionName))
    {
        m_database.unionNameToUnionDetailsMap[unionName].isUsedInIfs=true;
        UnionDetails unionDetails(m_database.getUnionDetails(unionName));
        for(string const& parameterName : unionDetails.parametersWithCorrectOrder)
        {
            ParameterDetails parameterDetails = m_database.getUnionParameterDetails(unionName, parameterName);
            if(parameterDetails.isAnArray)
            {
                markConstantAsNeededForIfs(parameterDetails.arraySize);
            }
            readAndMarkTypeAsNeededInIfsRecursively(parameterDetails.type);
        }
    }
}

void SackReader::markEnumAsNeededForIfsRecursively(string const& enumName)
{
    if(m_database.doesThisEnumExists(enumName))
    {
        m_database.enumNameToEnumDetailsMap[enumName].isUsedInIfs=true;
        EnumDetails::ParameterMap const& parameters(m_database.enumNameToEnumDetailsMap[enumName].parameters);
        for(EnumDetails::ParameterPair pair : parameters)
        {
            markConstantAsNeededForIfs(pair.second.value);
        }
    }
}

void SackReader::markTypedefAsNeededForIfsRecursively(string const& typedefName)
{
    if(m_database.doesThisTypedefExists(typedefName))
    {
        m_database.typedefNameToTypedefDetailsMap[typedefName].isUsedInIfs=true;
    }
}

void SackReader::markConstantAsNeededForIfs(string const& constantName)
{
    if(!constantName.empty())
    {
        char firstCharacter = constantName[0];
        if(firstCharacter!='E' && isCapitalLetter(firstCharacter))
        {
            m_database.constantNameToConstantDetailsMap[constantName].isUsedInIfs = true;
        }
    }
}

void SackReader::readOamTcomTupcMessageFiles()
{
    readFileUsingTypeFileName("MessageId_OamAtm.sig");
    readFileUsingTypeFileName("MessageId_OamTcom.sig");
    readFileUsingTypeFileName("MessageId_TassuTtm.sig");
    readFileUsingTypeFileName("MessageId_OamFault.h");
    readFileUsingTypeFileName("MessageId_Platform.h");
    readFileUsingTypeFileName("MessageId_OamPmService.h");
    readFileUsingTypeFileName("Oam_Atm.h");
    readFileUsingTypeFileName("oam_tcom.h");
    readFileUsingTypeFileName("Oam_Tcom_TestModelService.h");
    readFileUsingTypeFileName("Oam_Tcom_LoopTestService.h");
    readFileUsingTypeFileName("tassu_ttm.h");
    readFileUsingTypeFileName("SFaultInd.h");
    readFileUsingTypeFileName("SModeChangeReq.h");
    readFileUsingTypeFileName("SModeChangeResp.h");
    readFileUsingTypeFileName("FetchCountersReq.h");
    readFileUsingTypeFileName("FetchCountersResp.h");
    readFileUsingTypeFileName("StoreCountersInd.h");
}

void SackReader::readConstantFiles()
{
    readFileUsingTypeFileName("IfAaSysComGw_Defs.h");
    readFileUsingTypeFileName("DBtsomTcomConstants.h");
    readFileUsingTypeFileName("DOpenIUBCommonDefs.h");
    readFileUsingTypeFileName("Glo_bs.h");
    readFileUsingTypeFileName("DTechLogDef.h");
    readFileUsingTypeFileName("DFromTc_dsp.h");
}

void SackReader::readFileUsingTypeName(string const& typeName)
{
    readFileUsingTypeFileName(typeName+".h");
}

void SackReader::readFileUsingTypeFileName(string const& typeFileName)
{
    SackFileReader sackFileReader(m_database);
    sackFileReader.readFile(m_database.getFileFullPath(typeFileName));
}

void SackReader::updateDescriptionFromUser(IfsDefinitionType const currentDefinitionType, string const& name, string const& parameterName, string const& description)
{
    if(currentDefinitionType == IfsDefinitionType::Typedef || currentDefinitionType == IfsDefinitionType::Constant)
    {
        updateDescriptionFromUserWithoutParameter(currentDefinitionType, name, description);
    }
    else if(currentDefinitionType == IfsDefinitionType::Struct || currentDefinitionType == IfsDefinitionType::Union || currentDefinitionType == IfsDefinitionType::Enum)
    {
        updateDescriptionFromUserWithParameter(currentDefinitionType, name, parameterName, description);
    }
}

void SackReader::updateDescriptionFromUserWithoutParameter(IfsDefinitionType const currentDefinitionType, string const& name, string const& description)
{
    if(currentDefinitionType == IfsDefinitionType::Typedef)
    {
        if(m_database.doesThisTypedefExists(name))
        {
            m_database.typedefNameToTypedefDetailsMap[name].descriptionFromUser = description;
        }
    }
    else if(currentDefinitionType == IfsDefinitionType::Constant)
    {
        if(m_database.doesThisConstantExists(name))
        {
            m_database.constantNameToConstantDetailsMap[name].descriptionFromUser = description;
        }
    }
}

void SackReader::updateDescriptionFromUserWithParameter(IfsDefinitionType const currentDefinitionType, string const& name, string const& parameterName, string const& description)
{
    if(currentDefinitionType == IfsDefinitionType::Struct)
    {
        if(m_database.doesThisStructureAndParameterExists(name, parameterName))
        {
            m_database.structureNameToStructureDetailsMap[name].parameters[parameterName].descriptionFromUser = description;
        }
    }
    else if(currentDefinitionType == IfsDefinitionType::Union)
    {
        if(m_database.doesThisUnionAndParameterExists(name, parameterName))
        {
            m_database.unionNameToUnionDetailsMap[name].parameters[parameterName].descriptionFromUser = description;
        }
    }
    else if(currentDefinitionType == IfsDefinitionType::Enum)
    {
        if(m_database.doesThisEnumAndParameterExists(name, parameterName))
        {
            m_database.enumNameToEnumDetailsMap[name].parameters[parameterName].descriptionFromUser = description;
        }
    }
}



}
