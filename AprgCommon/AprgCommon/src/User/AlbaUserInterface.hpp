#pragma once

#include <string>

namespace alba
{


class AlbaUserInterface
{
public:
    std::string getUserInput();
    std::string getFilePathInput();
    template <typename NumberType> NumberType getNumberFromInput();

private:
    static constexpr int c_bufferSize = 1000;
    char buffer[c_bufferSize];
};

}//namespace alba
