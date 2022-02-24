#include <SackFileReader/SackFileReader.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(DatabaseTest, InitialContentsAreEmpty)
{
    Database database;
    EXPECT_TRUE(database.fileToPathMap.empty());
    EXPECT_TRUE(database.constantNameToConstantDetailsMap.empty());
    EXPECT_TRUE(database.messageNameToMessageDetailsMap.empty());
    EXPECT_TRUE(database.structureNameToStructureDetailsMap.empty());
    EXPECT_TRUE(database.enumNameToEnumDetailsMap.empty());
    EXPECT_TRUE(database.messagesToGenerate.empty());
}

TEST(DatabaseTest, DISABLED_SaveAndLoadFile)
{
    Database databaseToBeSaved;
    databaseToBeSaved.fileToPathMap["ThisIsAFile"] = "ThisIsAMap";    databaseToBeSaved.constantNameToConstantDetailsMap["ConstantName"].name = "ConstantName";
    databaseToBeSaved.constantNameToConstantDetailsMap["ConstantName"].value = "ConstantValue";
    databaseToBeSaved.constantNameToConstantDetailsMap["ConstantName"].description = "ConstantDescription";
    databaseToBeSaved.constantNameToConstantDetailsMap["ConstantName"].descriptionFromUser = "ConstantDescriptionFromUser";    databaseToBeSaved.messageNameToMessageDetailsMap["MessageName"].name = "MessageName";
    databaseToBeSaved.messageNameToMessageDetailsMap["MessageName"].name = "StructureName";
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].name = "StructureName";
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].parameters["ParameterName"].type = "ParameterType";
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].parameters["ParameterName"].name = "ParameterName";
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].parameters["ParameterName"].description = "ParameterDescription";
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].parameters["ParameterName"].descriptionFromUser = "ParameterDescriptionFromUser";
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].parametersWithCorrectOrder.emplace_back("ParameterName");
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].isMessage = true;
    databaseToBeSaved.structureNameToStructureDetailsMap["StructureName"].isUsedInIfs = true;
    databaseToBeSaved.enumNameToEnumDetailsMap["EnumName"].name = "EnumName";
    databaseToBeSaved.enumNameToEnumDetailsMap["EnumName"].isUsedInIfs = true;
    databaseToBeSaved.enumNameToEnumDetailsMap["EnumName"].parameters["ParameterName"].name = "ParameterName";
    databaseToBeSaved.enumNameToEnumDetailsMap["EnumName"].parameters["ParameterName"].value = "ParameterValue";
    databaseToBeSaved.enumNameToEnumDetailsMap["EnumName"].parameters["ParameterName"].description = "ParameterDescription";
    databaseToBeSaved.enumNameToEnumDetailsMap["EnumName"].parameters["ParameterName"].descriptionFromUser = "ParameterDescriptionFromUser";
    databaseToBeSaved.messagesToGenerate.emplace("ThisIsAMessage");
    databaseToBeSaved.saveDatabaseToFile(R"(C:\APRG\SackReader\SackReader\TempFiles\SampleDatabase.txt)");

    Database loadedDatabase;
    loadedDatabase.loadDatabaseFromFile(R"(C:\APRG\SackReader\SackReader\TempFiles\SampleDatabase.txt)");
    EXPECT_EQ("ThisIsAMap", loadedDatabase.fileToPathMap.at("ThisIsAFile"));
    EXPECT_EQ("ConstantName", loadedDatabase.constantNameToConstantDetailsMap.at("ConstantName").name);
    EXPECT_EQ("ConstantValue", loadedDatabase.constantNameToConstantDetailsMap.at("ConstantName").value);
    EXPECT_EQ("ConstantDescription", loadedDatabase.constantNameToConstantDetailsMap.at("ConstantName").description);
    EXPECT_EQ("ConstantDescriptionFromUser", loadedDatabase.constantNameToConstantDetailsMap.at("ConstantName").descriptionFromUser);
    EXPECT_EQ("MessageName", loadedDatabase.messageNameToMessageDetailsMap.at("MessageName").name);
    EXPECT_EQ("StructureName", loadedDatabase.messageNameToMessageDetailsMap.at("MessageName").structureName);
    EXPECT_EQ("ParameterType", loadedDatabase.structureNameToStructureDetailsMap.at("StructureName").parameters.at("ParameterName").type);
    EXPECT_EQ("ParameterName", loadedDatabase.structureNameToStructureDetailsMap.at("StructureName").parameters.at("ParameterName").name);
    EXPECT_EQ("ParameterDescription", loadedDatabase.structureNameToStructureDetailsMap.at("StructureName").parameters.at("ParameterName").description);
    EXPECT_EQ("ParameterDescriptionFromUser", loadedDatabase.structureNameToStructureDetailsMap.at("StructureName").parameters.at("ParameterName").descriptionFromUser);
    EXPECT_EQ("ParameterName", loadedDatabase.structureNameToStructureDetailsMap.at("StructureName").parametersWithCorrectOrder.front());
    EXPECT_TRUE(loadedDatabase.structureNameToStructureDetailsMap.at("StructureName").isMessage);
    //EXPECT_TRUE(loadedDatabase.structureNameToStructureDetailsMap.at("StructureName").isUsedInIfs);
    EXPECT_EQ("EnumName", loadedDatabase.enumNameToEnumDetailsMap.at("EnumName").name);
    //EXPECT_TRUE(loadedDatabase.enumNameToEnumDetailsMap.at("EnumName").isUsedInIfs);
    EXPECT_EQ("ParameterName", loadedDatabase.enumNameToEnumDetailsMap.at("EnumName").parameters.at("ParameterName").name);
    EXPECT_EQ("ParameterValue", loadedDatabase.enumNameToEnumDetailsMap.at("EnumName").parameters.at("ParameterName").value);
    EXPECT_EQ("ParameterDescription", loadedDatabase.enumNameToEnumDetailsMap.at("EnumName").parameters.at("ParameterName").description);
    EXPECT_EQ("ParameterDescriptionFromUser", loadedDatabase.enumNameToEnumDetailsMap.at("EnumName").parameters.at("ParameterName").descriptionFromUser);
    //EXPECT_EQ("ThisIsAMessage", *loadedDatabase.messagesToGenerate.begin());
}

}
