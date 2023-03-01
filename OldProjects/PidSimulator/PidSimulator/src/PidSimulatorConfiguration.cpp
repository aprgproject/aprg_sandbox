#include "PidSimulatorConfiguration.hpp"

#include <iostream>

using namespace std;

namespace alba
{

PidSimulatorConfiguration::PidSimulatorConfiguration(stringHelper::strings const& argumentsInMain)
    : numberOfLoopsOfPeriodicInputDemand(0)
    , amplitudeOfInputDemand(0)
    , numberOfSamplesOfInputDemandInOnePeriod(0)
    , addedOffsetOfInputDemand(0)
    , targetInPidCalculation(0)
    , maxCellTxPower(0)
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
    numberOfLoopsOfPeriodicInputDemand = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["numberOfLoopsOfPeriodicInputDemand"]);
    amplitudeOfInputDemand = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["amplitudeOfInputDemand"]);
    numberOfSamplesOfInputDemandInOnePeriod = stringHelper::convertStringToNumber<unsigned int>(argumentsToValuesMap["numberOfSamplesOfInputDemandInOnePeriod"]);
    addedOffsetOfInputDemand = stringHelper::convertStringToNumber<int>(argumentsToValuesMap["addedOffsetOfInputDemand"]);
    targetInPidCalculation = stringHelper::convertStringToNumber<double>(argumentsToValuesMap["targetInPidCalculation"]);
    maxCellTxPower = stringHelper::convertStringToNumber<double>(argumentsToValuesMap["maxCellTxPower"]);
    inputType = argumentsToValuesMap["inputType"];
    machsModelType = argumentsToValuesMap["machsModelType"];
    print();
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

void PidSimulatorConfiguration::print() const
{
    cout << "kp:[" << kp << "]\n";
    cout << "ki:[" << ki << "]\n";
    cout << "kd:[" << kd << "]\n";
    cout << "numberOfLoopsOfPeriodicInputDemand:[" << numberOfLoopsOfPeriodicInputDemand << "]\n";
    cout << "amplitudeOfInputDemand:[" << amplitudeOfInputDemand << "]\n";
    cout << "numberOfSamplesOfInputDemandInOnePeriod:[" << numberOfSamplesOfInputDemandInOnePeriod << "]\n";
    cout << "addedOffsetOfInputDemand:[" << addedOffsetOfInputDemand << "]\n";
    cout << "targetInPidCalculation:[" << targetInPidCalculation << "]\n";
    cout << "maxCellTxPower:[" << maxCellTxPower << "]\n";
    cout << "inputType:[" << inputType << "]\n";
    cout << "machsModelType:[" << machsModelType << "]\n";

}
}