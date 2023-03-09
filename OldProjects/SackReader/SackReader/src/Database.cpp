#include "Database.hpp"

#include <Common/Stream/AlbaStreamParameterReader.hpp>
#include <Common/Stream/AlbaStreamParameterWriter.hpp>

#include <algorithm>
#include <fstream>

using namespace std;

namespace alba
{

void Database::saveDatabaseToFile(string const& path)
{
    ofstream fileStream(path);
    AlbaStreamParameterWriter writer(fileStream);
    writer.writeMapData(fileToPathMap);
    writer.writeMapData(constantNameToConstantDetailsMap);
    writer.writeMapData(messageNameToMessageDetailsMap);
    writer.writeMapData(structureNameToStructureDetailsMap);
    writer.writeMapData(unionNameToUnionDetailsMap);
    writer.writeMapData(enumNameToEnumDetailsMap);
    writer.writeMapData(typedefNameToTypedefDetailsMap);
    writer.writeSetData(messagesToGenerate);
    writer.flush();
}

void Database::loadDatabaseFromFile(string const& path){
    ifstream fileStream(path);
    AlbaStreamParameterReader reader(fileStream);
    reader.readMapData(fileToPathMap);    reader.readMapData(constantNameToConstantDetailsMap);
    reader.readMapData(messageNameToMessageDetailsMap);
    reader.readMapData(structureNameToStructureDetailsMap);
    reader.readMapData(unionNameToUnionDetailsMap);
    reader.readMapData(enumNameToEnumDetailsMap);
    reader.readMapData(typedefNameToTypedefDetailsMap);
    reader.readSetData(messagesToGenerate);
}

string Database::getFileFullPath(string const& fileName) const
{
    string result;
    if(fileToPathMap.find(fileName)!=fileToPathMap.cend())
    {
        result = fileToPathMap.at(fileName);
    }
    return result;
}

ConstantDetails Database::getConstantDetails(string const& constantName) const
{
    ConstantDetails result;
    if(doesThisConstantExists(constantName))
    {
        result = constantNameToConstantDetailsMap.at(constantName);
    }
    return result;
}

MessageDetails Database::getMessageDetails(string const& messageName) const
{
    MessageDetails result;
    if(doesThisMessageExists(messageName))
    {
        result = messageNameToMessageDetailsMap.at(messageName);
    }
    return result;
}

string Database::getMessageStructure(string const& messageName) const
{
    string result;
    if(doesThisMessageExists(messageName))
    {
        result = messageNameToMessageDetailsMap.at(messageName).structureName;
    }
    return result;
}

StructureDetails Database::getStructureDetails(string const& structureName) const
{
    StructureDetails result;
    if(doesThisStructureExists(structureName))
    {
        result = structureNameToStructureDetailsMap.at(structureName);
    }
    return result;
}

ParameterDetails Database::getStructureParameterDetails(string const& structureName, string const& parameterName) const
{
    ParameterDetails result;
    if(doesThisStructureAndParameterExists(structureName, parameterName))
    {
        result = structureNameToStructureDetailsMap.at(structureName).parameters.at(parameterName);
    }
    return result;
}

EnumDetails Database::getEnumDetails(string const& enumName) const
{
    EnumDetails result;
    if(doesThisEnumExists(enumName))
    {
        result = enumNameToEnumDetailsMap.at(enumName);
    }
    return result;
}

EnumParameterDetails Database::getEnumParameterDetails(string const& enumName, string const& parameterName) const
{
    EnumParameterDetails result;
    if(doesThisEnumAndParameterExists(enumName, parameterName))
    {
        result = enumNameToEnumDetailsMap.at(enumName).parameters.at(parameterName);
    }
    return result;
}

UnionDetails Database::getUnionDetails(string const& unionName) const
{
    UnionDetails result;
    if(doesThisUnionExists(unionName))
    {
        result = unionNameToUnionDetailsMap.at(unionName);
    }
    return result;
}

ParameterDetails Database::getUnionParameterDetails(string const& unionName, string const& parameterName) const
{
    ParameterDetails result;
    if(doesThisUnionAndParameterExists(unionName, parameterName))
    {
        result = unionNameToUnionDetailsMap.at(unionName).parameters.at(parameterName);
    }
    return result;
}

TypedefDetails Database::getTypedefDetails(string const& typedefName) const
{
    TypedefDetails result;
    if(doesThisTypedefExists(typedefName))
    {
        result = typedefNameToTypedefDetailsMap.at(typedefName);
    }
    return result;
}

bool Database::doesThisStructureAndParameterExists(string const& structureName, string const& parameterName) const
{
    bool result(false);
    if(doesThisStructureExists(structureName))
    {
        StructureDetails const & structureDetails = structureNameToStructureDetailsMap.at(structureName);
        StructureDetails::ParameterMap const & parameters(structureDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result = true;
        }
    }
    return result;
}

bool Database::doesThisStructureAndParameterExistsInVector(string const& structureName, string const& parameterName) const
{
    bool result(false);
    if(doesThisStructureExists(structureName))
    {
        StructureDetails const & structureDetails = structureNameToStructureDetailsMap.at(structureName);
        vector<string> const & parametersWithCorrectOrder(structureDetails.parametersWithCorrectOrder);
        if(find(parametersWithCorrectOrder.cbegin(), parametersWithCorrectOrder.cend(), parameterName)!=parametersWithCorrectOrder.cend())
        {
            result = true;
        }
    }
    return result;
}

bool Database::doesThisEnumAndParameterExists(string const& enumName, string const& parameterName) const
{
    bool result(false);
    if(doesThisEnumExists(enumName))
    {
        EnumDetails const & enumDetails = enumNameToEnumDetailsMap.at(enumName);
        EnumDetails::ParameterMap const & parameters(enumDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result=true;
        }
    }
    return result;
}

bool Database::doesThisUnionAndParameterExists(string const& unionName, string const& parameterName) const
{
    bool result(false);
    if(doesThisUnionExists(unionName))
    {
        UnionDetails const & unionDetails = unionNameToUnionDetailsMap.at(unionName);
        UnionDetails::ParameterMap const & parameters(unionDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result = true;
        }
    }
    return result;
}

bool Database::doesThisUnionAndParameterExistsInVector(string const& unionName, string const& parameterName) const
{
    bool result(false);
    if(doesThisUnionExists(unionName))
    {
        UnionDetails const & unionDetails = unionNameToUnionDetailsMap.at(unionName);
        vector<string> const & parametersWithCorrectOrder(unionDetails.parametersWithCorrectOrder);
        if(find(parametersWithCorrectOrder.cbegin(), parametersWithCorrectOrder.cend(), parameterName)!=parametersWithCorrectOrder.cend())
        {
            result = true;
        }
    }
    return result;
}

bool Database::doesThisConstantExists(string const& constantName) const
{
    bool result(false);
    if(constantNameToConstantDetailsMap.find(constantName)!=constantNameToConstantDetailsMap.cend())
    {
        result = true;
    }
    return result;
}

bool Database::doesThisMessageExists(string const& messageName) const
{
    bool result(false);
    if(messageNameToMessageDetailsMap.find(messageName)!=messageNameToMessageDetailsMap.cend())
    {
        result = true;
    }
    return result;
}

bool Database::doesThisFullDetailedStructureExists(string const& structureName) const
{
    bool result(false);
    if(doesThisStructureExists(structureName))
    {
        result = !getStructureDetails(structureName).name.empty();
    }
    return result;
}

bool Database::doesThisStructureExists(string const& structureName) const
{
    bool result(false);
    if(structureNameToStructureDetailsMap.find(structureName)!=structureNameToStructureDetailsMap.cend())
    {
        result = true;
    }
    return result;
}

bool Database::doesThisEnumExists(string const& enumName) const
{
    bool result(false);
    if(enumNameToEnumDetailsMap.find(enumName)!=enumNameToEnumDetailsMap.cend())
    {
        result = true;
    }
    return result;
}

bool Database::doesThisUnionExists(string const& unionName) const
{
    bool result(false);
    if(unionNameToUnionDetailsMap.find(unionName)!=unionNameToUnionDetailsMap.cend())
    {
        result = true;
    }
    return result;
}

bool Database::doesThisTypedefExists(string const& typedefName) const
{
    bool result(false);
    if(typedefNameToTypedefDetailsMap.find(typedefName)!=typedefNameToTypedefDetailsMap.cend())
    {
        result = true;
    }
    return result;
}


}
