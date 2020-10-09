#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <string>

#define CONFIGURATION_FILE R"(C:\APRG\TcomTools\TcomTools\configuration\configuration.txt)"

using std::string;

struct TcomtoolsConfiguration
{
    TcomtoolsConfiguration()
    {
        std::ifstream fileStream(CONFIGURATION_FILE);
        alba::AlbaFileReader fileReader(fileStream);
        while(fileReader.isNotFinished())
        {
            string lineInConfiguration(fileReader.getLineAndIgnoreWhiteSpaces());
            string beforeColon;
            string afterColon;
            alba::stringHelper::copyBeforeStringAndAfterString(lineInConfiguration, ":", beforeColon, afterColon);

            if("isExtractStepOn" == beforeColon)
            {
                isExtractStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isCombineAndSortStepOn" == beforeColon)
            {
                isCombineAndSortStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepStepOn" == beforeColon)
            {
                isGrepStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isCropStepOn" == beforeColon)
            {
                isCropStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepTcomEnabled" == beforeColon)
            {
                isGrepTcomEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepErrEnabled" == beforeColon)
            {
                isGrepErrEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepErrWrnTcomEnabled" == beforeColon)
            {
                isGrepErrWrnTcomEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepBtsStatusEnabled" == beforeColon)
            {
                isGrepBtsStatusEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepRecoveryEnabled" == beforeColon)
            {
                isGrepRecoveryEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepAllocationEnabled" == beforeColon)
            {
                isGrepAllocationEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepFaultEnabled" == beforeColon)
            {
                isGrepFaultEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepLrmEnabled" == beforeColon)
            {
                isGrepLrmEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepGrmEnabled" == beforeColon)
            {
                isGrepGrmEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepToamEnabled" == beforeColon)
            {
                isGrepToamEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepTupcEnabled" == beforeColon)
            {
                isGrepTupcEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepRlhEnabled" == beforeColon)
            {
                isGrepRlhEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepCchhBchsenderEnabled" == beforeColon)
            {
                isGrepCchhBchsenderEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepHschEnabled" == beforeColon)
            {
                isGrepHschEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
            }
            else if("isGrepDmgrEnabled" == beforeColon)
            {
                isGrepDmgrEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
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
        }
    }
    bool isExtractStepOn;
    bool isCombineAndSortStepOn;
    bool isGrepStepOn;
    bool isCropStepOn;
    bool isGrepTcomEnabled;
    bool isGrepErrEnabled;
    bool isGrepErrWrnTcomEnabled;
    bool isGrepBtsStatusEnabled;
    bool isGrepRecoveryEnabled;
    bool isGrepAllocationEnabled;
    bool isGrepFaultEnabled;
    bool isGrepLrmEnabled;
    bool isGrepGrmEnabled;
    bool isGrepToamEnabled;
    bool isGrepTupcEnabled;
    bool isGrepRlhEnabled;
    bool isGrepCchhBchsenderEnabled;
    bool isGrepHschEnabled;
    bool isGrepDmgrEnabled;
    string acceptedFilesGrepCondition;
    string otherGrepCondition;
    string prioritizedLogPrint;
};
