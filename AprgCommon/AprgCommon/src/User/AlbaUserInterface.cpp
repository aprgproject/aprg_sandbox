#include <User/AlbaUserInterface.hpp>
#include <iostream>

using namespace std;
namespace alba
{

string AlbaUserInterface::getUserInput()
{
    static constexpr int bufferSize = 1000;
    char buffer[bufferSize];
    cin.getline(buffer, bufferSize);
    return string(buffer);
}

}//namespace alba
