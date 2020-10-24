#pragma once

#include <iostream>
#include <string>

namespace mse
{

class UserInterface
{
public:
    void execute();
    void executeRandomSubSampling();
    void executeKFold();
    int getModeInput();
    std::string getFilePathInput();
    int getNumberFromInput();

private:
    static constexpr int bufferSize = 1000;
    char buffer[1000];
};

}
