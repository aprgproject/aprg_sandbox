#include <SOOSA.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SoosaTest, SampleTest1)
{
    SOOSA::SoosaConfiguration configuration;
    configuration.path = R"(C:\APRG\SOOSA\SOOSA\tst\FilesForTests\TestRotate.bmp)";
    configuration.formDetailsPath = R"(C:\APRG\SOOSA\SOOSA\basis\FormDetails\)";
    configuration.area = "area";
    configuration.period = "period";
    configuration.discharge = "discharge";
    SOOSA soosa(configuration);
    soosa.process();
}
