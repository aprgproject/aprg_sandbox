#include <FileDestructor.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SampleTest, DestroyTest)
{
    FileDestructor fileDestructor;
    fileDestructor.destroy(R"(C:\APRG\FileDestructor\FileDestructor\tst\TestFolderForDestruction)");
}
