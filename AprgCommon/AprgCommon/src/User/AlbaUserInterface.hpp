#pragma once

#include <string>

namespace alba{


class AlbaUserInterface
{
public:
    std::string getUserInput();
    std::string getFilePathInput();
    template <typename NumberType> NumberType getNumberFromInput();

private:
    static constexpr int bufferSize = 1000;
    char buffer[bufferSize];
};

}//namespace alba
