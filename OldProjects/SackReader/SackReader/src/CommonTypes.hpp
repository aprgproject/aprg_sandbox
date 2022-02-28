#pragma once

#include <map>
#include <string>
#include <vector>

namespace alba
{

enum class IfsDefinitionType
{
    Struct,
    Union,
    Enum,
    Typedef,
    Constant
};

struct ConstantDetails
{
    std::string name;
    std::string value;
    std::string description;
    std::string descriptionFromUser;
    std::string path;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        value.clear();
        description.clear();
        descriptionFromUser.clear();
        isUsedInIfs=false;
    }
    friend std::ostream & operator<<(std::ostream & out, ConstantDetails const& constantDetails);
    friend std::istream & operator>>(std::istream & in, ConstantDetails& constantDetails);
};

struct MessageDetails
{
    std::string name;
    std::string structureName;
    std::string path;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        structureName.clear();
        path.clear();
        isUsedInIfs=false;
    }
    friend std::ostream & operator<<(std::ostream & out, MessageDetails const& messageDetails);
    friend std::istream & operator>>(std::istream & in, MessageDetails& messageDetails);
};

struct EnumParameterDetails
{
    std::string name;
    std::string value;
    std::string description;
    std::string descriptionFromUser;
    void clear()
    {
        name.clear();
        value.clear();
        description.clear();
        descriptionFromUser.clear();
    }
    friend std::ostream & operator<<(std::ostream & out, EnumParameterDetails const& enumParameterDetails);
    friend std::istream & operator>>(std::istream & in, EnumParameterDetails& enumParameterDetails);
};

struct EnumDetails
{
    using ParameterMap = std::map<std::string, EnumParameterDetails>;
    using ParameterPair = std::pair<std::string, EnumParameterDetails>;
    std::string name;
    ParameterMap parameters;
    std::string path;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        parameters.clear();
        isUsedInIfs=false;
    }
    friend std::ostream & operator<<(std::ostream & out, EnumDetails const& enumDetails);
    friend std::istream & operator>>(std::istream & in, EnumDetails& enumDetails);
};

struct ParameterDetails
{
    std::string type;
    std::string name;
    std::string description;
    std::string descriptionFromUser;
    bool isAnArray;
    std::string arraySize;
    void clear()
    {
        type.clear();
        name.clear();
        description.clear();
        descriptionFromUser.clear();
        isAnArray=false;
        arraySize.clear();
    }
    friend std::ostream & operator<<(std::ostream & out, ParameterDetails const& parameterDetails);
    friend std::istream & operator>>(std::istream & in, ParameterDetails& parameterDetails);
};

struct StructureDetails
{
    using ParameterMap = std::map<std::string, ParameterDetails>;
    using ParameterPair = std::pair<std::string, ParameterDetails>;
    std::string name;
    ParameterMap parameters;
    std::vector<std::string> parametersWithCorrectOrder; // unordered_map
    std::string path;
    bool isMessage;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        parameters.clear();
        parametersWithCorrectOrder.clear();
        isMessage=false;
        isUsedInIfs=false;
    }
    friend std::ostream & operator<<(std::ostream & out, StructureDetails const& structureDetails);
    friend std::istream & operator>>(std::istream & in, StructureDetails& structureDetails);
};

struct UnionDetails
{
    using ParameterMap = std::map<std::string, ParameterDetails>;
    using ParameterPair = std::pair<std::string, ParameterDetails>;
    std::string name;
    ParameterMap parameters;
    std::vector<std::string> parametersWithCorrectOrder; // unordered_map
    std::string path;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        parameters.clear();
        parametersWithCorrectOrder.clear();
        isUsedInIfs=false;
    }
    friend std::ostream & operator<<(std::ostream & out, UnionDetails const& unionDetails);
    friend std::istream & operator>>(std::istream & in, UnionDetails& unionDetails);
};

struct TypedefDetails
{
    std::string name;
    std::string typedefDerivedName;
    std::string description;
    std::string descriptionFromUser;
    std::string path;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        typedefDerivedName.clear();
        description.clear();
        descriptionFromUser.clear();
        path.clear();
        isUsedInIfs=false;
    }
    friend std::ostream & operator<<(std::ostream & out, TypedefDetails const& typedefDetails);
    friend std::istream & operator>>(std::istream & in, TypedefDetails& typedefDetails);
};

std::string getPrimitiveTypeDescription(std::string const& primitiveType);

using FileToPathMap = std::map<std::string, std::string>;
using FileToPathPair = std::pair<std::string, std::string>;
using ConstantNameToConstantDetailsMap = std::map<std::string, ConstantDetails>;
using ConstantNameToConstantDetailsPair = std::pair<std::string, ConstantDetails>;
using MessageNameToMessageDetailsMap = std::map<std::string, MessageDetails>;
using MessageNameToMessageDetailsPair = std::pair<std::string, MessageDetails>;
using StructureNameToStructureDetailsMap = std::map<std::string, StructureDetails>;
using StructureNameToStructureDetailsPair = std::pair<std::string, StructureDetails>;
using UnionNameToUnionDetailsMap = std::map<std::string, UnionDetails>;
using UnionNameToUnionDetailsPair = std::pair<std::string, UnionDetails>;
using EnumNameToEnumDetailsMap = std::map<std::string, EnumDetails>;
using EnumNameToEnumDetailsPair = std::pair<std::string, EnumDetails>;
using TypedefNameToTypedefDetailsMap = std::map<std::string, TypedefDetails>;
using TypedefNameToTypedefDetailsPair = std::pair<std::string, TypedefDetails>;


} // namespace alba
