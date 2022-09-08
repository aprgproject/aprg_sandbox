#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SOOSA.hpp>
#include <UserInterface.hpp>

using namespace alba;
using namespace alba::soosa;
using namespace alba::stringHelper;
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Survey Output Optical Scan Analyzer developed by IRPDS\n" << endl;
    cout << "code version: " << APRG_CODE_REVISION << endl;

    if(argc==2)
    {
        AlbaLocalPathHandler detectedPath(PathInitialValueSource::DetectedLocalPath);
        AlbaLocalPathHandler pathToProcess(getStringWithoutCharAtTheEnd(string(argv[1]), '"'));

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
        cout << "Exiting program because the number of input arguments is wrong." << endl;
    }
}