#include <PidSimulator.hpp>
#include <PidSimulatorConfiguration.hpp>
#include <String/AlbaStringHelper.hpp>

using namespace alba;
using namespace std;


int main(int argc, char * argv[])
{
    stringHelper::strings argumentsInMain;
    stringHelper::fetchArgumentsToStringInMain(argumentsInMain, argc, argv);

    argumentsInMain.emplace_back("kp=0.1");
    argumentsInMain.emplace_back("ki=0.2");
    argumentsInMain.emplace_back("kd=0.02");
    argumentsInMain.emplace_back("numberOfLoopsOfPeriodicInput=1");
    argumentsInMain.emplace_back("amplitudeOfInput=10");
    argumentsInMain.emplace_back("numberOfSamplesOfInputInOnePeriod=100");
    argumentsInMain.emplace_back("addedOffsetOfInput=5");
    argumentsInMain.emplace_back("targetInPidCalculation=6");
    argumentsInMain.emplace_back("inputType=random");

    PidSimulator simulator(argumentsInMain);
    simulator.generateInput();
    simulator.calculateAndGenerateOutputImage();
}