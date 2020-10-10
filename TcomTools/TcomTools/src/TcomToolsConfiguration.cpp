#include <TcomToolsConfiguration.hpp>

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>

using namespace alba;
using namespace std;

namespace tcomToolsGui
{

TcomToolsConfiguration::TcomToolsConfiguration()
    : isExtractStepOn(false)
    , isCombineAndSortStepOn(false)
    , isGrepStepOn(false)
    , isCropStepOn(false)
    , isGrepTcomEnabled(false)
    , isGrepErrEnabled(false)
    , isGrepErrWrnTcomEnabled(false)
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
    , isGrepChEnabled(false)
    , isGrepHschEnabled(false)
    , isGrepDmgrEnabled(false)
    , grepConditionForTcom()
    , grepConditionForErr()
    , grepConditionForErrWrnTcom()
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
    , grepConditionForCh()
    , grepConditionForHsch()
    , grepConditionForDmgr()
    , inputFileOrDirectory()
    , extractGrepCondition()
    , acceptedFilesGrepCondition()
    , otherGrepCondition()
    , prioritizedLogPrint()
{
    loadConfigurationFromFile();
}

void TcomToolsConfiguration::loadConfigurationFromFile()
{
    std::ifstream inputFileStream(CONFIGURATION_FILE);
    AlbaFileReader fileReader(inputFileStream);
    while(fileReader.isNotFinished())
    {
        string lineInConfiguration(fileReader.getLineAndIgnoreWhiteSpaces());
        string beforeColon;
        string afterColon;
        stringHelper::copyBeforeStringAndAfterString(lineInConfiguration, ":", beforeColon, afterColon);

        if("isExtractStepOn" == beforeColon)
        {
            isExtractStepOn = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isCombineAndSortStepOn" == beforeColon)
        {
            isCombineAndSortStepOn = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepStepOn" == beforeColon)
        {
            isGrepStepOn = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isCropStepOn" == beforeColon)
        {
            isCropStepOn = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepTcomEnabled" == beforeColon)
        {
            isGrepTcomEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepErrEnabled" == beforeColon)
        {
            isGrepErrEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepErrWrnTcomEnabled" == beforeColon)
        {
            isGrepErrWrnTcomEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepBtsStatusEnabled" == beforeColon)
        {
            isGrepBtsStatusEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepRecoveryEnabled" == beforeColon)
        {
            isGrepRecoveryEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepAllocationEnabled" == beforeColon)
        {
            isGrepAllocationEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepFaultEnabled" == beforeColon)
        {
            isGrepFaultEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepLrmEnabled" == beforeColon)
        {
            isGrepLrmEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepGrmEnabled" == beforeColon)
        {
            isGrepGrmEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepToamEnabled" == beforeColon)
        {
            isGrepToamEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepTupcEnabled" == beforeColon)
        {
            isGrepTupcEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepRlhEnabled" == beforeColon)
        {
            isGrepRlhEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepCchhEnabled" == beforeColon)
        {
            isGrepCchhEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepChEnabled" == beforeColon)
        {
            isGrepChEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepHschEnabled" == beforeColon)
        {
            isGrepHschEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepDmgrEnabled" == beforeColon)
        {
            isGrepDmgrEnabled = !(0==stringHelper::stringToNumber<int>(afterColon));
        }
        else if("grepConditionForTcom" == beforeColon)
        {
            grepConditionForTcom = afterColon;
        }
        else if("grepConditionForErr" == beforeColon)
        {
            grepConditionForErr = afterColon;
        }
        else if("grepConditionForErrWrnTcom" == beforeColon)
        {
            grepConditionForErrWrnTcom = afterColon;
        }
        else if("grepConditionForBtsStatus" == beforeColon)
        {
            grepConditionForBtsStatus = afterColon;
        }
        else if("grepConditionForRecovery" == beforeColon)
        {
            grepConditionForRecovery = afterColon;
        }
        else if("grepConditionForAllocation" == beforeColon)
        {
            grepConditionForAllocation = afterColon;
        }
        else if("grepConditionForFault" == beforeColon)
        {
            grepConditionForFault = afterColon;
        }
        else if("grepConditionForLrm" == beforeColon)
        {
            grepConditionForLrm = afterColon;
        }
        else if("grepConditionForGrm" == beforeColon)
        {
            grepConditionForGrm = afterColon;
        }
        else if("grepConditionForToam" == beforeColon)
        {
            grepConditionForToam = afterColon;
        }
        else if("grepConditionForTupc" == beforeColon)
        {
            grepConditionForTupc = afterColon;
        }
        else if("grepConditionForRlh" == beforeColon)
        {
            grepConditionForRlh = afterColon;
        }
        else if("grepConditionForCchh" == beforeColon)
        {
            grepConditionForCchh = afterColon;
        }
        else if("grepConditionForCh" == beforeColon)
        {
            grepConditionForCh = afterColon;
        }
        else if("grepConditionForHsch" == beforeColon)
        {
            grepConditionForHsch = afterColon;
        }
        else if("grepConditionForDmgr" == beforeColon)
        {
            grepConditionForDmgr = afterColon;
        }
        else if("inputFileOrDirectory" == beforeColon)
        {
            inputFileOrDirectory = afterColon;
        }
        else if("extractGrepCondition" == beforeColon)
        {
            extractGrepCondition = afterColon;
        }
        else if("acceptedFilesGrepCondition" == beforeColon)
        {
            acceptedFilesGrepCondition = afterColon;
        }
        else if("otherGrepCondition" == beforeColon)
        {
            otherGrepCondition = afterColon;
        }
        else if("prioritizedLogPrint" == beforeColon)
        {
            prioritizedLogPrint = afterColon;
        }
        else if("pathOfLogsWithoutPcTime" == beforeColon)
        {
            pathOfLogsWithoutPcTime = afterColon;
        }
        else if("sorterConfigurationWithPcTime.m_directoryForBlocks" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_directoryForBlocks = afterColon;
        }
        else if("sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumFileStreams = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumFileStreams = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_directoryForBlocks" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_directoryForBlocks = afterColon;
        }
        else if("sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumFileStreams = stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumFileStreams = stringHelper::stringToNumber<int>(afterColon);
        }
    }
}

void TcomToolsConfiguration::saveConfigurationToFile() const
{
    std::ofstream outputFileStream(CONFIGURATION_FILE);
    outputFileStream << "isExtractStepOn:" << static_cast<int>(isExtractStepOn) << endl;
    outputFileStream << "isCombineAndSortStepOn:" << static_cast<int>(isCombineAndSortStepOn) << endl;
    outputFileStream << "isGrepStepOn:" << static_cast<int>(isGrepStepOn) << endl;
    outputFileStream << "isCropStepOn:" << static_cast<int>(isCropStepOn) << endl;
    outputFileStream << "isGrepTcomEnabled:" << static_cast<int>(isGrepTcomEnabled) << endl;
    outputFileStream << "isGrepErrEnabled:" << static_cast<int>(isGrepErrEnabled) << endl;
    outputFileStream << "isGrepErrWrnTcomEnabled:" << static_cast<int>(isGrepErrWrnTcomEnabled) << endl;
    outputFileStream << "isGrepBtsStatusEnabled:" << static_cast<int>(isGrepBtsStatusEnabled) << endl;
    outputFileStream << "isGrepRecoveryEnabled:" << static_cast<int>(isGrepRecoveryEnabled) << endl;
    outputFileStream << "isGrepAllocationEnabled:" << static_cast<int>(isGrepAllocationEnabled) << endl;
    outputFileStream << "isGrepFaultEnabled:" << static_cast<int>(isGrepFaultEnabled) << endl;
    outputFileStream << "isGrepLrmEnabled:" << static_cast<int>(isGrepLrmEnabled) << endl;
    outputFileStream << "isGrepGrmEnabled:" << static_cast<int>(isGrepGrmEnabled) << endl;
    outputFileStream << "isGrepToamEnabled:" << static_cast<int>(isGrepToamEnabled) << endl;
    outputFileStream << "isGrepTupcEnabled:" << static_cast<int>(isGrepTupcEnabled) << endl;
    outputFileStream << "isGrepRlhEnabled:" << static_cast<int>(isGrepRlhEnabled) << endl;
    outputFileStream << "isGrepCchhEnabled:" << static_cast<int>(isGrepCchhEnabled) << endl;
    outputFileStream << "isGrepChEnabled:" << static_cast<int>(isGrepChEnabled) << endl;
    outputFileStream << "isGrepHschEnabled:" << static_cast<int>(isGrepHschEnabled) << endl;
    outputFileStream << "isGrepDmgrEnabled:" << static_cast<int>(isGrepDmgrEnabled) << endl;
    outputFileStream << "grepConditionForTcom:" << grepConditionForTcom << endl;
    outputFileStream << "grepConditionForErr:" << grepConditionForErr << endl;
    outputFileStream << "grepConditionForErrWrnTcom:" << grepConditionForErrWrnTcom << endl;
    outputFileStream << "grepConditionForBtsStatus:" << grepConditionForBtsStatus << endl;
    outputFileStream << "grepConditionForRecovery:" << grepConditionForRecovery << endl;
    outputFileStream << "grepConditionForAllocation:" << grepConditionForAllocation << endl;
    outputFileStream << "grepConditionForFault:" << grepConditionForFault << endl;
    outputFileStream << "grepConditionForLrm:" << grepConditionForLrm << endl;
    outputFileStream << "grepConditionForGrm:" << grepConditionForGrm << endl;
    outputFileStream << "grepConditionForToam:" << grepConditionForToam << endl;
    outputFileStream << "grepConditionForTupc:" << grepConditionForTupc << endl;
    outputFileStream << "grepConditionForRlh:" << grepConditionForRlh << endl;
    outputFileStream << "grepConditionForCchh:" << grepConditionForCchh << endl;
    outputFileStream << "grepConditionForCh:" << grepConditionForCh << endl;
    outputFileStream << "grepConditionForHsch:" << grepConditionForHsch << endl;
    outputFileStream << "grepConditionForDmgr:" << grepConditionForDmgr << endl;
    outputFileStream << "inputFileOrDirectory:" << inputFileOrDirectory<< endl;
    outputFileStream << "extractGrepCondition:" << extractGrepCondition<< endl;
    outputFileStream << "acceptedFilesGrepCondition:" << acceptedFilesGrepCondition<< endl;
    outputFileStream << "otherGrepCondition:" << otherGrepCondition << endl;
    outputFileStream << "pathOfLogsWithoutPcTime:" << pathOfLogsWithoutPcTime << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_directoryForBlocks:" << sorterConfigurationWithPcTime.m_directoryForBlocks << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock:" << sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock:" << sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory:" << sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_maximumFileStreams:" << sorterConfigurationWithPcTime.m_maximumFileStreams << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_directoryForBlocks:" << sorterConfigurationWithoutPcTime.m_directoryForBlocks << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock:" << sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock:" << sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory:" << sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_maximumFileStreams:" << sorterConfigurationWithoutPcTime.m_maximumFileStreams << endl;
}

string TcomToolsConfiguration::getGrepCondition() const
{
    string condition;
    if(isGrepTcomEnabled)
    {
        condition += grepConditionForTcom + " || ";
    }
    if(isGrepErrEnabled)
    {
        condition += grepConditionForErr + " || ";
    }
    if(isGrepErrWrnTcomEnabled)
    {
        condition += grepConditionForErrWrnTcom + " || ";
    }
    if(isGrepBtsStatusEnabled)
    {
        condition += grepConditionForBtsStatus + " || ";
    }
    if(isGrepRecoveryEnabled)
    {
        condition += grepConditionForRecovery + " || ";
    }
    if(isGrepAllocationEnabled)
    {
        condition += grepConditionForAllocation + " || ";
    }
    if(isGrepFaultEnabled)
    {
        condition += grepConditionForFault + " || ";
    }
    if(isGrepLrmEnabled)
    {
        condition += grepConditionForLrm + " || ";
    }
    if(isGrepGrmEnabled)
    {
        condition += grepConditionForGrm + " || ";
    }
    if(isGrepToamEnabled)
    {
        condition += grepConditionForToam + " || ";
    }
    if(isGrepTupcEnabled)
    {
        condition += grepConditionForTupc + " || ";
    }
    if(isGrepRlhEnabled)
    {
        condition += grepConditionForRlh + " || ";
    }
    if(isGrepCchhEnabled)
    {
        condition += grepConditionForCchh + " || ";
    }
    if(isGrepChEnabled)
    {
        condition += grepConditionForCh + " || ";
    }
    if(isGrepDmgrEnabled)
    {
        condition += grepConditionForDmgr + " || ";
    }
    if(isGrepHschEnabled)
    {
        condition += grepConditionForHsch + " || ";
    }
    condition += otherGrepCondition;
    int lastBracketIndex(condition.find_last_of("]"));
    if(stringHelper::isNotNpos(lastBracketIndex))
    {
        condition = condition.substr(0, lastBracketIndex+1);
    }
    return condition;
}

string TcomToolsConfiguration::getGrepFileName() const
{
    string fileName;
    if(isGrepTcomEnabled)
    {
        fileName += "Tcom";
    }
    if(isGrepErrEnabled)
    {
        fileName += "Err";
    }
    if(isGrepErrWrnTcomEnabled)
    {
        fileName += "ErrWrn";
    }
    if(isGrepBtsStatusEnabled)
    {
        fileName += "BtsStatus";
    }
    if(isGrepRecoveryEnabled)
    {
        fileName += "Recovery";
    }
    if(isGrepAllocationEnabled)
    {
        fileName += "Allocation";
    }
    if(isGrepFaultEnabled)
    {
        fileName += "Fault";
    }
    if(isGrepLrmEnabled)
    {
        fileName += "Lrm";
    }
    if(isGrepGrmEnabled)
    {
        fileName += "Grm";
    }
    if(isGrepToamEnabled)
    {
        fileName += "Toam";
    }
    if(isGrepTupcEnabled)
    {
        fileName += "Tupc";
    }
    if(isGrepRlhEnabled)
    {
        fileName += "Rlh";
    }
    if(isGrepCchhEnabled)
    {
        fileName += "Cchh";
    }
    if(isGrepChEnabled)
    {
        fileName += "Ch";
    }
    if(isGrepDmgrEnabled)
    {
        fileName += "Dmgr";
    }
    if(isGrepHschEnabled)
    {
        fileName += "Hsch";
    }
    fileName += stringHelper::getStringWithoutCharAtTheEnd(stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(otherGrepCondition), '_';
    fileName += ".log";
    return fileName;
}

}
