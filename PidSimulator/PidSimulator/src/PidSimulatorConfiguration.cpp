#include "PidSimulatorConfiguration.hpp"

#include <iostream>

using namespace std;

namespace alba{

PidSimulatorConfiguration::PidSimulatorConfiguration(stringHelper::strings const& argumentsInMain)
    : numberOfLoopsOfPeriodicInput(0)    , amplitudeOfInput(0)
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
    numberOfLoopsOfPeriodicInput = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["numberOfLoopsOfPeriodicInput"]);
    amplitudeOfInput = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["amplitudeOfInput"]);
    numberOfSamplesOfInputInOnePeriod = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["numberOfSamplesOfInputInOnePeriod"]);    addedOffsetOfInput = stringHelper::convertStringToNumber<int>(argumentsToValuesMap["addedOffsetOfInput"]);
    targetInPidCalculation = stringHelper::convertStringToNumber<double>(argumentsToValuesMap["targetInPidCalculation"]);
    inputType = argumentsToValuesMap["inputType"];
    print();
}

void PidSimulatorConfiguration::processArgumentsWithEqualDelimeter(StringToStringMap & argumentsToValuesMap, stringHelper::strings const& argumentsInMain){
    for(string const& argumentInMain : argumentsInMain)
    {
        processOneArgumentWithEqualDelimeter(argumentsToValuesMap, argumentInMain);    }
}

void PidSimulatorConfiguration::processOneArgumentWithEqualDelimeter(StringToStringMap & argumentsToValuesMap, string const& argument)
{
    string beforeEqual;
    string afterEqual;
    stringHelper::copyBeforeStringAndAfterString(argument, "=", beforeEqual, afterEqual);
    argumentsToValuesMap.emplace(beforeEqual, afterEqual);
}

void PidSimulatorConfiguration::print() const
{
    cout << "kp:[" << kp << "]" << endl;
    cout << "ki:[" << ki << "]" << endl;
    cout << "kd:[" << kd << "]" << endl;
    cout << "numberOfLoopsOfPeriodicInput:[" << numberOfLoopsOfPeriodicInput << "]" << endl;
    cout << "amplitudeOfInput:[" << amplitudeOfInput << "]" << endl;
    cout << "numberOfSamplesOfInputInOnePeriod:[" << numberOfSamplesOfInputInOnePeriod << "]" << endl;
    cout << "addedOffsetOfInput:[" << addedOffsetOfInput << "]" << endl;
    cout << "targetInPidCalculation:[" << targetInPidCalculation << "]" << endl;
    cout << "inputType:[" << inputType << "]" << endl;
}

}