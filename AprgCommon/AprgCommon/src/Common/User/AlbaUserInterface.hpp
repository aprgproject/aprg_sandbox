#pragma once

#include <map>
#include <string>

namespace alba
{


class AlbaUserInterface
{
public:
    template <typename AnswerType> using Choices = std::map<AnswerType, std::string>;

    // rule of zero

    std::string getUserInput();
    std::string getFilePathInput();
    template <typename NumberType> NumberType getNumberFromInput();    template <typename NumberType> NumberType displayQuestionAndChoicesAndGetNumberAnswer(std::string const& question, Choices<NumberType> const& choices);
    std::string displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(std::string const& question, Choices<std::string> const& choices);

private:    static constexpr int c_bufferSize = 1000;
    char buffer[c_bufferSize];
};

}//namespace alba
