#include "PidSimulatorConfiguration.hpp"


#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

PidSimulatorConfiguration::PidSimulatorConfiguration(stringHelper::strings const& argumentsInMain)
    : numberOfLoopsOfPeriodicInput(0)
    , amplitudeOfInput(0)
    , numberOfSamplesOfInputInOnePeriod(0)
    , addedOffsetOfInput(0)
    , targetInPidCalculation(0)
    , kp(0)
    , ki(0)
    , kd(0)
{
    std::map<std::string, std::string> argumentsToValuesMap;
    processArgumentsWithEqualDelimeter(argumentsToValuesMap, argumentsInMain);
    saveArgumentValues(argumentsToValuesMap);
}

void PidSimulatorConfiguration::saveArgumentValues(StringToStringMap & argumentsToValuesMap)
{
    kp = stringHelper::convertStringToNumber<double>(argumentsToValuesMap["kp"]);
    ki = stringHelper::convertStringToNumber<double>(argumentsToValuesMap["ki"]);
    kd = stringHelper::convertStringToNumber<double>(argumentsToValuesMap["kd"]);
    ALBA_PRINT3(kp, ki, kd);
    numberOfLoopsOfPeriodicInput = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["numberOfLoopsOfPeriodicInput"]);
    amplitudeOfInput = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["amplitudeOfInput"]);
    numberOfSamplesOfInputInOnePeriod = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["numberOfSamplesOfInputInOnePeriod"]);
    addedOffsetOfInput = stringHelper::convertStringToNumber<int>(argumentsToValuesMap["addedOffsetOfInput"]);
    targetInPidCalculation = stringHelper::convertStringToNumber<double>(argumentsToValuesMap["targetInPidCalculation"]);
    inputType = argumentsToValuesMap["inputType"];
    ALBA_PRINT6(numberOfLoopsOfPeriodicInput, amplitudeOfInput, numberOfSamplesOfInputInOnePeriod, addedOffsetOfInput, targetInPidCalculation, inputType);
}

void PidSimulatorConfiguration::processArgumentsWithEqualDelimeter(StringToStringMap & argumentsToValuesMap, stringHelper::strings const& argumentsInMain)
{
    for(string const& argumentInMain : argumentsInMain)
    {
        processOneArgumentWithEqualDelimeter(argumentsToValuesMap, argumentInMain);
    }
}

void PidSimulatorConfiguration::processOneArgumentWithEqualDelimeter(StringToStringMap & argumentsToValuesMap, string const& argument)
{
    string beforeEqual;
    string afterEqual;
    stringHelper::copyBeforeStringAndAfterString(argument, "=", beforeEqual, afterEqual);
    argumentsToValuesMap.emplace(beforeEqual, afterEqual);
}

}
