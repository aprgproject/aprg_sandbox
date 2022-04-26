#include "CommonTypes.hpp"

#include <Common/Stream/AlbaStreamParameterReader.hpp>
#include <Common/Stream/AlbaStreamParameterWriter.hpp>

using namespace std;
namespace alba
{

ostream& operator<<(ostream & out, ConstantDetails const& constantDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(constantDetails.name);
    writer.writeData<string>(constantDetails.value);
    writer.writeData<string>(constantDetails.description);    writer.writeData<string>(constantDetails.descriptionFromUser);
    writer.writeData<string>(constantDetails.path);
    writer.writeData<bool>(constantDetails.isUsedInIfs);
    return out;}

istream& operator>>(istream & in, ConstantDetails& constantDetails)
{
    AlbaStreamParameterReader reader(in);
    constantDetails.name = reader.readData<string>();
    constantDetails.value = reader.readData<string>();
    constantDetails.description = reader.readData<string>();    constantDetails.descriptionFromUser = reader.readData<string>();
    constantDetails.path = reader.readData<string>();
    constantDetails.isUsedInIfs = reader.readData<bool>();
    return in;}

ostream& operator<<(ostream & out, MessageDetails const& messageDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(messageDetails.name);
    writer.writeData<string>(messageDetails.structureName);
    writer.writeData<string>(messageDetails.path);    writer.writeData<bool>(messageDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, MessageDetails& messageDetails)
{
    AlbaStreamParameterReader reader(in);
    messageDetails.name = reader.readData<string>();
    messageDetails.structureName = reader.readData<string>();
    messageDetails.path = reader.readData<string>();    messageDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, EnumParameterDetails const& enumParameterDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(enumParameterDetails.name);
    writer.writeData<string>(enumParameterDetails.value);
    writer.writeData<string>(enumParameterDetails.description);    writer.writeData<string>(enumParameterDetails.descriptionFromUser);
    return out;
}

istream& operator>>(istream & in, EnumParameterDetails& enumParameterDetails)
{
    AlbaStreamParameterReader reader(in);
    enumParameterDetails.name = reader.readData<string>();
    enumParameterDetails.value = reader.readData<string>();
    enumParameterDetails.description = reader.readData<string>();    enumParameterDetails.descriptionFromUser = reader.readData<string>();
    return in;
}

ostream& operator<<(ostream & out, EnumDetails const& enumDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(enumDetails.name);
    writer.writeMapData(enumDetails.parameters);
    writer.writeData<string>(enumDetails.path);    writer.writeData<bool>(enumDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, EnumDetails& enumDetails)
{
    AlbaStreamParameterReader reader(in);
    enumDetails.name = reader.readData<string>();
    reader.readMapData(enumDetails.parameters);
    enumDetails.path = reader.readData<string>();    enumDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, ParameterDetails const& parameterDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(parameterDetails.type);
    writer.writeData<string>(parameterDetails.name);
    writer.writeData<string>(parameterDetails.description);    writer.writeData<string>(parameterDetails.descriptionFromUser);
    writer.writeData<bool>(parameterDetails.isAnArray);
    writer.writeData<string>(parameterDetails.arraySize);
    return out;}

istream& operator>>(istream & in, ParameterDetails& parameterDetails)
{
    AlbaStreamParameterReader reader(in);
    parameterDetails.type = reader.readData<string>();
    parameterDetails.name = reader.readData<string>();
    parameterDetails.description = reader.readData<string>();    parameterDetails.descriptionFromUser = reader.readData<string>();
    parameterDetails.isAnArray = reader.readData<bool>();
    parameterDetails.arraySize = reader.readData<string>();
    return in;}

ostream& operator<<(ostream & out, StructureDetails const& structureDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(structureDetails.name);
    writer.writeMapData(structureDetails.parameters);
    writer.writeVectorData(structureDetails.parametersWithCorrectOrder);    writer.writeData(structureDetails.path);
    writer.writeData<bool>(structureDetails.isMessage);
    writer.writeData<bool>(structureDetails.isUsedInIfs);
    return out;}

istream& operator>>(istream & in, StructureDetails& structureDetails)
{
    AlbaStreamParameterReader reader(in);
    structureDetails.name = reader.readData<string>();
    reader.readMapData(structureDetails.parameters);
    reader.readVectorData(structureDetails.parametersWithCorrectOrder);    structureDetails.path = reader.readData<string>();
    structureDetails.isMessage = reader.readData<bool>();
    structureDetails.isUsedInIfs = reader.readData<bool>();
    return in;}

ostream& operator<<(ostream & out, UnionDetails const& unionDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(unionDetails.name);
    writer.writeMapData(unionDetails.parameters);
    writer.writeVectorData(unionDetails.parametersWithCorrectOrder);    writer.writeData(unionDetails.path);
    writer.writeData<bool>(unionDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, UnionDetails& unionDetails)
{
    AlbaStreamParameterReader reader(in);
    unionDetails.name = reader.readData<string>();
    reader.readMapData(unionDetails.parameters);
    reader.readVectorData(unionDetails.parametersWithCorrectOrder);    unionDetails.path = reader.readData<string>();
    unionDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, TypedefDetails const& typedefDetails)
{
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(typedefDetails.name);
    writer.writeData<string>(typedefDetails.typedefDerivedName);
    writer.writeData<string>(typedefDetails.description);    writer.writeData<string>(typedefDetails.descriptionFromUser);
    writer.writeData<string>(typedefDetails.path);
    writer.writeData<bool>(typedefDetails.isUsedInIfs);
    return out;}

istream& operator>>(istream & in, TypedefDetails& typedefDetails)
{
    AlbaStreamParameterReader reader(in);
    typedefDetails.name = reader.readData<string>();
    typedefDetails.typedefDerivedName = reader.readData<string>();
    typedefDetails.description = reader.readData<string>();    typedefDetails.descriptionFromUser = reader.readData<string>();
    typedefDetails.path = reader.readData<string>();
    typedefDetails.isUsedInIfs = reader.readData<bool>();
    return in;}

string getPrimitiveTypeDescription(string const& primitiveType)
{
    string result;
    if("u8"==primitiveType)
    {
        result="Eight bits unsigned character.";
    }
    else if("u16"==primitiveType)
    {
        result="Sixteen bits unsigned integer.";
    }
    else if("u32"==primitiveType)
    {
        result="Thirty two bits unsigned integer.";
    }
    else if("i8"==primitiveType)
    {
        result="Eight bits signed character.";
    }
    else if("i16"==primitiveType)
    {
        result="Sixteen bits signed integer.";
    }
    else if("i32"==primitiveType)
    {
        result="Thirty two bits signed integer.";
    }
    else if("r32"==primitiveType)
    {
        result="Thirty two bits single-precision floating-point value.";
    }
    else if("r64"==primitiveType)
    {
        result="Sixty four bits double-precision floating-point value.";
    }
    else if("r128"==primitiveType)
    {
        result="One hundred twenty eight bits quadruple-precision floating-point value.";
    }
    return result;
}

}
