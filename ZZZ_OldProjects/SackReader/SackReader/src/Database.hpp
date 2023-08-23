#pragma once

#include <CommonTypes.hpp>

#include <set>
#include <string>

namespace alba {

struct Database {
    void saveDatabaseToFile(std::string const& path);
    void loadDatabaseFromFile(std::string const& path);
    std::string getFileFullPath(std::string const& fileName) const;
    ConstantDetails getConstantDetails(std::string const& constantName) const;
    MessageDetails getMessageDetails(std::string const& messageName) const;
    std::string getMessageStructure(std::string const& messageName) const;
    StructureDetails getStructureDetails(std::string const& structureName) const;
    ParameterDetails getStructureParameterDetails(
        std::string const& structureName, std::string const& parameterName) const;
    EnumDetails getEnumDetails(std::string const& enumName) const;
    EnumParameterDetails getEnumParameterDetails(
        std::string const& enumName, std::string const& enumParameterName) const;
    UnionDetails getUnionDetails(std::string const& unionName) const;
    ParameterDetails getUnionParameterDetails(std::string const& unionName, std::string const& parameterName) const;
    TypedefDetails getTypedefDetails(std::string const& typedefName) const;
    bool doesThisStructureAndParameterExists(std::string const& structureName, std::string const& parameterName) const;
    bool doesThisStructureAndParameterExistsInVector(
        std::string const& structureName, std::string const& parameterName) const;
    bool doesThisEnumAndParameterExists(std::string const& enumName, std::string const& parameterName) const;
    bool doesThisUnionAndParameterExists(std::string const& unionName, std::string const& parameterName) const;
    bool doesThisUnionAndParameterExistsInVector(std::string const& unionName, std::string const& parameterName) const;
    bool doesThisConstantExists(std::string const& constantName) const;
    bool doesThisMessageExists(std::string const& messageName) const;
    bool doesThisFullDetailedStructureExists(std::string const& structureName) const;
    bool doesThisStructureExists(std::string const& structureName) const;
    bool doesThisEnumExists(std::string const& enumName) const;
    bool doesThisUnionExists(std::string const& unionName) const;
    bool doesThisTypedefExists(std::string const& typedefName) const;
    FileToPathMap fileToPathMap;
    ConstantNameToConstantDetailsMap constantNameToConstantDetailsMap;
    MessageNameToMessageDetailsMap messageNameToMessageDetailsMap;
    StructureNameToStructureDetailsMap structureNameToStructureDetailsMap;
    UnionNameToUnionDetailsMap unionNameToUnionDetailsMap;
    EnumNameToEnumDetailsMap enumNameToEnumDetailsMap;
    TypedefNameToTypedefDetailsMap typedefNameToTypedefDetailsMap;
    std::set<std::string> messagesToGenerate;
};

}  // namespace alba
