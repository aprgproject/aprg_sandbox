#include "WcdmaToolsConfiguration.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <fstream>
#include <iostream>

using namespace alba;
using namespace std;

char const*const orOperator = " || ";

namespace wcdmaToolsGui
{

WcdmaToolsConfiguration::WcdmaToolsConfiguration()
    : isExtractStepOn(false)
    , isCombineAndSortStepOn(false)
    , isGrepStepOn(false)
    , isCropStepOn(false)
    , isFilterSubStepOn(false)
    , isGrepTcomEnabled(false)
    , isGrepErrEnabled(false)
    , isGrepErrWrnNoSpamEnabled(false)
    , isGrepBtsStatusEnabled(false)
    , isGrepRecoveryEnabled(false)
    , isGrepAllocationEnabled(false)
    , isGrepFaultEnabled(false)
    , isGrepLrmEnabled(false)
    , isGrepGrmEnabled(false)
    , isGrepToamEnabled(false)
    , isGrepTupcEnabled(false)
    , isGrepRlhEnabled(false)
    , isGrepCchhEnabled(false)
    , isGrepBchsenderEnabled(false)
    , isGrepHschEnabled(false)
    , isGrepDmgrEnabled(false)
    , isGrepCodecEnabled(false)
    , isGrepLtcomEnabled(false)
    , isGrepLomEnabled(false)
    , isGrepRakeEnabled(false)
    , isGrepPicEnabled(false)
    , isGrepHsdpaEnabled(false)
    , isGrepHsTupEnabled(false)
    , isGrepHsupaL2Enabled(false)
    , grepConditionForTcom()
    , grepConditionForErr()
    , grepConditionForErrWrn()
    , grepConditionForBtsStatus()
    , grepConditionForRecovery()
    , grepConditionForAllocation()
    , grepConditionForFault()
    , grepConditionForLrm()
    , grepConditionForGrm()
    , grepConditionForToam()
    , grepConditionForTupc()
    , grepConditionForRlh()
    , grepConditionForCchh()
    , grepConditionForBchsender()
    , grepConditionForHsch()
    , grepConditionForDmgr()
    , grepConditionForCodec()
    , grepConditionForLtcom()
    , grepConditionForLom()
    , grepConditionForRake()
    , grepConditionForPic()
    , grepConditionForHsdpa()
    , grepConditionForHsTup()
    , grepConditionForHsupaL2()
    , inputFileOrDirectory()
    , extractGrepCondition()
    , acceptedFilesGrepCondition()
    , filterGrepCondition()
    , otherGrepCondition()
    , prioritizedLogCondition()
    , cropSize(0)
{
    determineVariousLocationsBasedOnCurrentLocation();
    loadConfigurationFromFile(configurationFileLocation);
}

void WcdmaToolsConfiguration::loadDefaultConfigurationFile()
{
    loadConfigurationFromFile(defaultConfigurationFileLocation);
}

void WcdmaToolsConfiguration::saveToConfigurationFile() const
{
    ofstream outputFileStream(configurationFileLocation);
    outputFileStream << "isExtractStepOn:" << static_cast<int>(isExtractStepOn) << "\n";
    outputFileStream << "isCombineAndSortStepOn:" << static_cast<int>(isCombineAndSortStepOn) << "\n";
    outputFileStream << "isGrepStepOn:" << static_cast<int>(isGrepStepOn) << "\n";
    outputFileStream << "isCropStepOn:" << static_cast<int>(isCropStepOn) << "\n";
    outputFileStream << "isFilterSubStepOn:" << static_cast<int>(isFilterSubStepOn) << "\n";
    outputFileStream << "isGrepTcomEnabled:" << static_cast<int>(isGrepTcomEnabled) << "\n";
    outputFileStream << "isGrepErrEnabled:" << static_cast<int>(isGrepErrEnabled) << "\n";
    outputFileStream << "isGrepErrWrnNoSpamEnabled:" << static_cast<int>(isGrepErrWrnNoSpamEnabled) << "\n";
    outputFileStream << "isGrepBtsStatusEnabled:" << static_cast<int>(isGrepBtsStatusEnabled) << "\n";
    outputFileStream << "isGrepRecoveryEnabled:" << static_cast<int>(isGrepRecoveryEnabled) << "\n";
    outputFileStream << "isGrepAllocationEnabled:" << static_cast<int>(isGrepAllocationEnabled) << "\n";
    outputFileStream << "isGrepFaultEnabled:" << static_cast<int>(isGrepFaultEnabled) << "\n";
    outputFileStream << "isGrepLrmEnabled:" << static_cast<int>(isGrepLrmEnabled) << "\n";
    outputFileStream << "isGrepGrmEnabled:" << static_cast<int>(isGrepGrmEnabled) << "\n";
    outputFileStream << "isGrepToamEnabled:" << static_cast<int>(isGrepToamEnabled) << "\n";
    outputFileStream << "isGrepTupcEnabled:" << static_cast<int>(isGrepTupcEnabled) << "\n";
    outputFileStream << "isGrepRlhEnabled:" << static_cast<int>(isGrepRlhEnabled) << "\n";
    outputFileStream << "isGrepCchhEnabled:" << static_cast<int>(isGrepCchhEnabled) << "\n";
    outputFileStream << "isGrepBchsenderEnabled:" << static_cast<int>(isGrepBchsenderEnabled) << "\n";
    outputFileStream << "isGrepHschEnabled:" << static_cast<int>(isGrepHschEnabled) << "\n";
    outputFileStream << "isGrepDmgrEnabled:" << static_cast<int>(isGrepDmgrEnabled) << "\n";
    outputFileStream << "isGrepCodecEnabled:" << static_cast<int>(isGrepCodecEnabled) << "\n";
    outputFileStream << "isGrepLtcomEnabled:" << static_cast<int>(isGrepLtcomEnabled) << "\n";
    outputFileStream << "isGrepLomEnabled:" << static_cast<int>(isGrepLomEnabled) << "\n";
    outputFileStream << "isGrepRakeEnabled:" << static_cast<int>(isGrepRakeEnabled) << "\n";
    outputFileStream << "isGrepPicEnabled:" << static_cast<int>(isGrepPicEnabled) << "\n";
    outputFileStream << "isGrepHsdpaEnabled:" << static_cast<int>(isGrepHsdpaEnabled) << "\n";
    outputFileStream << "isGrepHsTupEnabled:" << static_cast<int>(isGrepHsTupEnabled) << "\n";
    outputFileStream << "isGrepHsupaL2Enabled:" << static_cast<int>(isGrepHsupaL2Enabled) << "\n";
    outputFileStream << "grepConditionForTcom:" << grepConditionForTcom << "\n";
    outputFileStream << "grepConditionForErr:" << grepConditionForErr << "\n";
    outputFileStream << "grepConditionForErrWrn:" << grepConditionForErrWrn << "\n";
    outputFileStream << "grepConditionForBtsStatus:" << grepConditionForBtsStatus << "\n";
    outputFileStream << "grepConditionForRecovery:" << grepConditionForRecovery << "\n";
    outputFileStream << "grepConditionForAllocation:" << grepConditionForAllocation << "\n";
    outputFileStream << "grepConditionForFault:" << grepConditionForFault << "\n";
    outputFileStream << "grepConditionForLrm:" << grepConditionForLrm << "\n";
    outputFileStream << "grepConditionForGrm:" << grepConditionForGrm << "\n";
    outputFileStream << "grepConditionForToam:" << grepConditionForToam << "\n";
    outputFileStream << "grepConditionForTupc:" << grepConditionForTupc << "\n";
    outputFileStream << "grepConditionForRlh:" << grepConditionForRlh << "\n";
    outputFileStream << "grepConditionForCchh:" << grepConditionForCchh << "\n";
    outputFileStream << "grepConditionForBchsender:" << grepConditionForBchsender << "\n";
    outputFileStream << "grepConditionForHsch:" << grepConditionForHsch << "\n";
    outputFileStream << "grepConditionForDmgr:" << grepConditionForDmgr << "\n";
    outputFileStream << "grepConditionForCodec:" << grepConditionForCodec << "\n";
    outputFileStream << "grepConditionForLtcom:" << grepConditionForLtcom << "\n";
    outputFileStream << "grepConditionForLom:" << grepConditionForLom << "\n";
    outputFileStream << "grepConditionForRake:" << grepConditionForRake << "\n";
    outputFileStream << "grepConditionForPic:" << grepConditionForPic << "\n";
    outputFileStream << "grepConditionForHsdpa:" << grepConditionForHsdpa << "\n";
    outputFileStream << "grepConditionForHsTup:" << grepConditionForHsTup << "\n";
    outputFileStream << "grepConditionForHsupaL2:" << grepConditionForHsupaL2 << "\n";
    outputFileStream << "inputFileOrDirectory:" << inputFileOrDirectory<< "\n";
    outputFileStream << "extractGrepCondition:" << extractGrepCondition<< "\n";
    outputFileStream << "acceptedFilesGrepCondition:" << acceptedFilesGrepCondition<< "\n";
    outputFileStream << "filterGrepCondition:" << filterGrepCondition<< "\n";
    outputFileStream << "otherGrepCondition:" << otherGrepCondition << "\n";
    outputFileStream << "prioritizedLogCondition:" << prioritizedLogCondition<< "\n";
    outputFileStream << "cropSize:" << cropSize << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory << "\n";
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams << "\n";
}

string WcdmaToolsConfiguration::getGrepCondition() const
{
    string condition;
    addConditionIntoGrepCondition(condition, isGrepTcomEnabled, grepConditionForTcom);
    addConditionIntoGrepCondition(condition, isGrepErrEnabled, grepConditionForErr);
    addConditionIntoGrepCondition(condition, isGrepErrWrnNoSpamEnabled, grepConditionForErrWrn);
    addConditionIntoGrepCondition(condition, isGrepBtsStatusEnabled, grepConditionForBtsStatus);
    addConditionIntoGrepCondition(condition, isGrepRecoveryEnabled, grepConditionForRecovery);
    addConditionIntoGrepCondition(condition, isGrepAllocationEnabled, grepConditionForAllocation);
    addConditionIntoGrepCondition(condition, isGrepFaultEnabled, grepConditionForFault);
    addConditionIntoGrepCondition(condition, isGrepLrmEnabled, grepConditionForLrm);
    addConditionIntoGrepCondition(condition, isGrepGrmEnabled, grepConditionForGrm);
    addConditionIntoGrepCondition(condition, isGrepToamEnabled, grepConditionForToam);
    addConditionIntoGrepCondition(condition, isGrepTupcEnabled, grepConditionForTupc);
    addConditionIntoGrepCondition(condition, isGrepRlhEnabled, grepConditionForRlh);
    addConditionIntoGrepCondition(condition, isGrepCchhEnabled, grepConditionForCchh);
    addConditionIntoGrepCondition(condition, isGrepBchsenderEnabled, grepConditionForBchsender);
    addConditionIntoGrepCondition(condition, isGrepHschEnabled, grepConditionForHsch);
    addConditionIntoGrepCondition(condition, isGrepDmgrEnabled, grepConditionForDmgr);
    addConditionIntoGrepCondition(condition, isGrepCodecEnabled, grepConditionForCodec);
    addConditionIntoGrepCondition(condition, isGrepLtcomEnabled, grepConditionForLtcom);
    addConditionIntoGrepCondition(condition, isGrepLomEnabled, grepConditionForLom);
    addConditionIntoGrepCondition(condition, isGrepRakeEnabled, grepConditionForRake);
    addConditionIntoGrepCondition(condition, isGrepPicEnabled, grepConditionForPic);
    addConditionIntoGrepCondition(condition, isGrepHsdpaEnabled, grepConditionForHsdpa);
    addConditionIntoGrepCondition(condition, isGrepHsTupEnabled, grepConditionForHsTup);
    addConditionIntoGrepCondition(condition, isGrepHsupaL2Enabled, grepConditionForHsupaL2);
    if(!stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(otherGrepCondition).empty())
    {
        condition += otherGrepCondition + orOperator;
    }
    if(!condition.empty())
    {
        condition = condition.substr(0, condition.length()-string(orOperator).length());
    }
    return condition;
}

string WcdmaToolsConfiguration::getGrepFileName() const
{
    string fileName("grepped");
    addGrepIntoFileName(fileName, isGrepTcomEnabled, "Tcom");
    addGrepIntoFileName(fileName, isGrepErrEnabled, "Err");
    addGrepIntoFileName(fileName, isGrepErrWrnNoSpamEnabled, "ErrWrn");
    addGrepIntoFileName(fileName, isGrepBtsStatusEnabled, "BtsStatus");
    addGrepIntoFileName(fileName, isGrepRecoveryEnabled, "Recovery");
    addGrepIntoFileName(fileName, isGrepAllocationEnabled, "Allocation");
    addGrepIntoFileName(fileName, isGrepFaultEnabled, "Fault");
    addGrepIntoFileName(fileName, isGrepLrmEnabled, "Lrm");
    addGrepIntoFileName(fileName, isGrepGrmEnabled, "Grm");
    addGrepIntoFileName(fileName, isGrepToamEnabled, "Toam");
    addGrepIntoFileName(fileName, isGrepTupcEnabled, "Tupc");
    addGrepIntoFileName(fileName, isGrepRlhEnabled, "Rlh");
    addGrepIntoFileName(fileName, isGrepCchhEnabled, "Cchh");
    addGrepIntoFileName(fileName, isGrepBchsenderEnabled, "Bchsender");
    addGrepIntoFileName(fileName, isGrepHschEnabled, "Hsch");
    addGrepIntoFileName(fileName, isGrepDmgrEnabled, "Dmgr");
    addGrepIntoFileName(fileName, isGrepCodecEnabled, "Codec");
    addGrepIntoFileName(fileName, isGrepLtcomEnabled, "Ltcom");
    addGrepIntoFileName(fileName, isGrepLomEnabled, "Lom");
    addGrepIntoFileName(fileName, isGrepRakeEnabled, "Rake");
    addGrepIntoFileName(fileName, isGrepPicEnabled, "Pic");
    addGrepIntoFileName(fileName, isGrepHsdpaEnabled, "Hsdpa");
    addGrepIntoFileName(fileName, isGrepHsTupEnabled, "HsTup");
    addGrepIntoFileName(fileName, isGrepHsupaL2Enabled, "HsupaL2");
    fileName += stringHelper::getStringWithoutCharAtTheStartAndEnd(stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(otherGrepCondition), '_');
    fileName = fileName.substr(0, 50); //think of a better way to limit filename size
    fileName += ".log";
    return fileName;
}

string WcdmaToolsConfiguration::getSortedFileName() const
{
    string fileName("sorted");
    fileName += stringHelper::getStringWithoutCharAtTheStartAndEnd(stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(filterGrepCondition), '_');
    fileName = fileName.substr(0, 50); //think of a better way to limit filename size
    fileName += ".log";
    return fileName;
}

string WcdmaToolsConfiguration::getCropFileName() const
{
    string fileName("cropped");
    fileName += stringHelper::getStringWithoutCharAtTheStartAndEnd(stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(prioritizedLogCondition), '_');
    fileName = fileName.substr(0, 50); //think of a better way to limit filename size
    fileName += ".log";
    return fileName;
}

void WcdmaToolsConfiguration::determineVariousLocationsBasedOnCurrentLocation()
{
    AlbaLocalPathHandler currentLocalPathHandler(AlbaLocalPathHandler::createPathHandlerForDetectedPath());
    currentLocalPathHandler.goUp();

    AlbaLocalPathHandler sevenZipPathHandler(currentLocalPathHandler.getDirectory()+R"(\7z32\7z.exe)");    locationOf7zExecutable = sevenZipPathHandler.getFullPath();

    AlbaLocalPathHandler configurationFilePathHandler(currentLocalPathHandler.getDirectory()+R"(\configuration\configuration.txt)");
    configurationFilePathHandler.createDirectoriesForNonExisitingDirectories();    configurationFileLocation = configurationFilePathHandler.getFullPath();

    AlbaLocalPathHandler defaultConfigurationFilePathHandler(currentLocalPathHandler.getDirectory()+R"(\configuration\defaultConfiguration.txt)");
    defaultConfigurationFilePathHandler.createDirectoriesForNonExisitingDirectories();
    defaultConfigurationFileLocation = defaultConfigurationFilePathHandler.getFullPath();

    AlbaLocalPathHandler temporaryFilePathHandler(currentLocalPathHandler.getDirectory()+R"(\temporaryFiles\)");
    temporaryFilePathHandler.input(temporaryFilePathHandler.getDriveOrRoot()+R"(:\Temp\)");
    btsLogSorterConfiguration.m_pathOfTempFiles = temporaryFilePathHandler.getFullPath();
    temporaryFilePathHandler.createDirectoriesForNonExisitingDirectories();

    cout<<"locationOf7zExecutable: ["<<locationOf7zExecutable<<"]\n";
    cout<<"configurationFileLocation: ["<<configurationFileLocation<<"]\n";
    cout<<"btsLogSorterConfiguration.m_pathOfTempFiles: ["<<btsLogSorterConfiguration.m_pathOfTempFiles<<"]\n";
}

void WcdmaToolsConfiguration::loadConfigurationFromFile(string const& filePath)
{
    NameToValueMap nameToValueMap;
    copyNamesAndValuesFromFile(nameToValueMap, filePath);
    loadNamesAndValues(nameToValueMap);
}

void WcdmaToolsConfiguration::copyNamesAndValuesFromFile(NameToValueMap & nameToValueMap, string const& filePath)
{
    ifstream inputFileStream(filePath);
    if(inputFileStream.is_open())
    {
        AlbaFileReader fileReader(inputFileStream);
        while(fileReader.isNotFinished())
        {
            string lineInConfiguration(fileReader.getLineAndIgnoreWhiteSpaces());
            string beforeColon;
            string afterColon;
            stringHelper::copyBeforeStringAndAfterString(lineInConfiguration, ":", beforeColon, afterColon);
            nameToValueMap.emplace(beforeColon, afterColon);
        }
    }
}

void WcdmaToolsConfiguration::loadNamesAndValues(NameToValueMap & nameToValueMap)
{
    isExtractStepOn = stringHelper::convertStringToBool(nameToValueMap["isExtractStepOn"]);
    isCombineAndSortStepOn = stringHelper::convertStringToBool(nameToValueMap["isCombineAndSortStepOn"]);
    isGrepStepOn = stringHelper::convertStringToBool(nameToValueMap["isGrepStepOn"]);
    isCropStepOn = stringHelper::convertStringToBool(nameToValueMap["isCropStepOn"]);
    isFilterSubStepOn = stringHelper::convertStringToBool(nameToValueMap["isFilterSubStepOn"]);
    isGrepTcomEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepTcomEnabled"]);
    isGrepErrEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepErrEnabled"]);
    isGrepErrWrnNoSpamEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepErrWrnNoSpamEnabled"]);
    isGrepBtsStatusEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepBtsStatusEnabled"]);
    isGrepRecoveryEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepRecoveryEnabled"]);
    isGrepAllocationEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepAllocationEnabled"]);
    isGrepFaultEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepFaultEnabled"]);
    isGrepLrmEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepLrmEnabled"]);
    isGrepGrmEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepGrmEnabled"]);
    isGrepToamEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepToamEnabled"]);
    isGrepTupcEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepTupcEnabled"]);
    isGrepRlhEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepRlhEnabled"]);
    isGrepCchhEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepCchhEnabled"]);
    isGrepBchsenderEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepBchsenderEnabled"]);
    isGrepHschEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepBchsenderEnabled"]);
    isGrepDmgrEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepDmgrEnabled"]);
    isGrepCodecEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepCodecEnabled"]);
    isGrepLtcomEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepLtcomEnabled"]);
    isGrepLomEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepLomEnabled"]);
    isGrepRakeEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepRakeEnabled"]);
    isGrepPicEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepPicEnabled"]);
    isGrepHsdpaEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepHsdpaEnabled"]);
    isGrepHsTupEnabled = stringHelper::convertStringToBool(nameToValueMap["isGrepHsTupEnabled"]);
    isGrepHsupaL2Enabled = stringHelper::convertStringToBool(nameToValueMap["isGrepHsupaL2Enabled"]);
    grepConditionForTcom = nameToValueMap["grepConditionForTcom"];
    grepConditionForErr = nameToValueMap["grepConditionForErr"];
    grepConditionForErrWrn = nameToValueMap["grepConditionForErrWrn"];
    grepConditionForBtsStatus = nameToValueMap["grepConditionForBtsStatus"];
    grepConditionForRecovery = nameToValueMap["grepConditionForRecovery"];
    grepConditionForAllocation = nameToValueMap["grepConditionForAllocation"];
    grepConditionForFault = nameToValueMap["grepConditionForFault"];
    grepConditionForLrm = nameToValueMap["grepConditionForLrm"];
    grepConditionForGrm = nameToValueMap["grepConditionForGrm"];
    grepConditionForToam = nameToValueMap["grepConditionForToam"];
    grepConditionForTupc = nameToValueMap["grepConditionForTupc"];
    grepConditionForRlh = nameToValueMap["grepConditionForRlh"];
    grepConditionForCchh = nameToValueMap["grepConditionForCchh"];
    grepConditionForBchsender = nameToValueMap["grepConditionForBchsender"];
    grepConditionForHsch = nameToValueMap["grepConditionForHsch"];
    grepConditionForDmgr = nameToValueMap["grepConditionForDmgr"];
    grepConditionForCodec = nameToValueMap["grepConditionForCodec"];
    grepConditionForLtcom = nameToValueMap["grepConditionForLtcom"];
    grepConditionForLom = nameToValueMap["grepConditionForLom"];
    grepConditionForRake = nameToValueMap["grepConditionForRake"];
    grepConditionForPic = nameToValueMap["grepConditionForPic"];
    grepConditionForHsdpa = nameToValueMap["grepConditionForHsdpa"];
    grepConditionForHsTup = nameToValueMap["grepConditionForHsTup"];
    grepConditionForHsupaL2 = nameToValueMap["grepConditionForHsupaL2"];
    inputFileOrDirectory = nameToValueMap["inputFileOrDirectory"];
    extractGrepCondition = nameToValueMap["extractGrepCondition"];
    acceptedFilesGrepCondition = nameToValueMap["acceptedFilesGrepCondition"];
    filterGrepCondition = nameToValueMap["filterGrepCondition"];
    otherGrepCondition = nameToValueMap["otherGrepCondition"];
    prioritizedLogCondition = nameToValueMap["prioritizedLogCondition"];
    cropSize = stringHelper::convertStringToNumber<double>(nameToValueMap["cropSize"]);
    btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock"]);
    btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock"]);
    btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory"]);
    btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams"]);
    btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams"]);
    btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock"]);
    btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock"]);
    btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory"]);
    btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams"]);
    btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(nameToValueMap["btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams"]);
}

void WcdmaToolsConfiguration::addConditionIntoGrepCondition(string & condition, bool const isGrepEnabled, string const& grepCondition) const
{
    if(isGrepEnabled)
    {
        condition += grepCondition + orOperator;
    }
}

void WcdmaToolsConfiguration::addGrepIntoFileName(string & wholeFileName, bool const isGrepEnabled, string const& grepName) const
{
    if(isGrepEnabled)
    {
        wholeFileName += grepName;
    }
}

}
