#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <gtest/gtest.h>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <array>

using namespace alba;
using namespace std;

TEST(SampleTest, GenerateFeatureSpecificComponentFiles)
{
    AlbaWindowsPathHandler currentDirectory(AlbaWindowsPathHandler::InitialValue::PathFromWindows);
    AlbaWindowsPathHandler featureSpecificDirectory(R"(C:\APRG\DesignDocumentCreator\DesignDocumentCreator\src\RAN3374\FeatureSpecificFiles)");

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



