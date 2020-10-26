#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>
#include <gtest/gtest.h>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <array>

using namespace alba;
using namespace std;

TEST(SampleTest, GenerateFeatureSpecificComponentFiles)
{
    AlbaLocalPathHandler currentDirectory(PathInitialValueSource::DetectedLocalPath);
    AlbaLocalPathHandler featureSpecificDirectory(APRG_DIR R"(DesignDocumentCreator\DesignDocumentCreator\src\RAN3374\FeatureSpecificFiles)");

    ofstream addComponentFile(featureSpecificDirectory.getFullPath()+"AddComponent.hpp");
    ofstream componentsIncludesFile(featureSpecificDirectory.getFullPath()+"ComponentsIncludes.hpp");
    ofstream convertToStringComponentNameFile(featureSpecificDirectory.getFullPath()+"ConvertToStringComponentName.hpp");

    array<string> ran3374components = {"DMGR", "GRM", "LRM", "Rake", "RF", "TLH", "TOAM", "WRC"};

    for(string const& componentName : ran3374components)
    {
        if(!componentName.empty())
        {
            addComponentFile<<R"(ADD_COMPONENT(ComponentName::)"<<componentName<<", "<<componentName<<")"<<endl;
            componentsIncludesFile<<R"(#include <RAN3374/Components/)"<<componentName<<".hpp"<<endl;
            convertToStringComponentNameFile<<R"(GET_ENUM_STRING(ComponentName::)"<<componentName<<")"<<endl;
        }
    }
}



