#include <PidSimulator.hpp>
#include <PidSimulatorConfiguration.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba;
using namespace std;

int main(int argc, char * argv[])
{
    strings argumentsInMain(getArgumentsToStringInMain(argc, argv));

    /*argumentsInMain.emplace_back("kp=0.1");
    argumentsInMain.emplace_back("ki=0.2");    argumentsInMain.emplace_back("kd=0.02");
    argumentsInMain.emplace_back("numberOfLoopsOfPeriodicInputDemand=1");
    argumentsInMain.emplace_back("amplitudeOfInputDemand=10");
    argumentsInMain.emplace_back("numberOfSamplesOfInputDemandInOnePeriod=100");    argumentsInMain.emplace_back("addedOffsetOfInputDemand=5");
    argumentsInMain.emplace_back("targetInPidCalculation=6");
    argumentsInMain.emplace_back("maxCellTxPower=30");
    argumentsInMain.emplace_back("inputType=sine");
    argumentsInMain.emplace_back("machsModelType=MachsModel1");*/

    PidSimulator simulator(argumentsInMain);
    simulator.generateInput();

    simulator.calculateAndGenerateOutputImage();
}
