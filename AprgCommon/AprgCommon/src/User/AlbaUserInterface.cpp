#include "AlbaUserInterface.hpp"

#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;

namespace alba
{

string AlbaUserInterface::getUserInput()
{
    cin.getline(buffer, bufferSize);
    return string(buffer);
}

string AlbaUserInterface::getFilePathInput()
{
    while (1)
    {
        string pathString(getUserInput());
        AlbaWindowsPathHandler filePath(pathString);
        if(filePath.isFoundInLocalSystem() && filePath.isFile())
        {
            return filePath.getFullPath();
        }
        else
        {
            cout<<"File not found"<<endl;
        }
    }
}

template <typename NumberType>
NumberType AlbaUserInterface::getNumberFromInput()
{
    return stringHelper::convertStringToNumber<NumberType>(getUserInput());
}

template int AlbaUserInterface::getNumberFromInput<int>();
template unsigned int AlbaUserInterface::getNumberFromInput<unsigned int>();
template float AlbaUserInterface::getNumberFromInput<float>();
template double AlbaUserInterface::getNumberFromInput<double>();

}//namespace alba
