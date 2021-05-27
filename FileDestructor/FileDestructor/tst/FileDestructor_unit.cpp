#include <FileDestructor.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SampleTest, DestroyTest)
{
    FileDestructor fileDestructor;
    fileDestructor.destroy(R"(C:\APRG\FileDestructor\FileDestructor\tst\TestFolderForDestruction)");
}

}
