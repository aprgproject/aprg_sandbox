#include <FileDestructor.hpp>

using namespace alba;

int main()
{
    FileDestructor fileDestructor;
    fileDestructor.destroy();
    system("pause");
    return 0;
}
