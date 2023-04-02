#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <SOOSA.hpp>
#include <UserInterface.hpp>

using namespace alba;
using namespace alba::soosa;
using namespace alba::stringHelper;
using namespace std;


int main(int argc, char *argv[])
{
    cout << "Survey Output Optical Scan Analyzer developed by the IRPDS\n";
    cout << "Code version: " << APRG_CODE_REVISION << "\n\n";

    strings argumentsInMain(getArgumentsToStringInMain(argc, argv));
    if(argumentsInMain.size()==2)
    {
        AlbaLocalPathHandler detectedPath(AlbaLocalPathHandler::createPathHandlerForDetectedPath());        AlbaLocalPathHandler pathToProcess(getStringWithoutCharAtTheEnd(argumentsInMain.at(1), '"'));

        UserInterface ui;
        ui.setPath(pathToProcess.getFullPath());
        ui.askUserForMainDetails();
        ui.askUserForFormDetails();

        SoosaConfiguration soosaConfiguration;
        soosaConfiguration.loadConfigurationFromFile(detectedPath.getDirectory() + "SoosaConfiguration.txt");
        SOOSA soosa(soosaConfiguration, ui.getSavedConfiguration());

        soosa.process();
    }
    else
    {
        cout << "Exiting program because the number of input arguments is wrong.\n";
    }
    cout << "\n";
    cout.flush();

    system("pause");
}