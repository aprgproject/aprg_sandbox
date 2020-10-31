#pragma once

#include <string>
#include <map>

namespace alba
{


class AlbaUserInterface
{
public:
    template <typename AnswerType> using Choices = std::map<AnswerType, std::string>;

    std::string getUserInput();
    std::string getFilePathInput();
    template <typename NumberType> NumberType getNumberFromInput();
    template <typename NumberType> NumberType displayQuestionAndChoicesAndGetNumberAnswer(std::string const& question, Choices<NumberType> choices);
    std::string displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(std::string const& question, Choices<std::string> choices);

private:
    static constexpr int c_bufferSize = 1000;
    char buffer[c_bufferSize];
};

}//namespace alba
