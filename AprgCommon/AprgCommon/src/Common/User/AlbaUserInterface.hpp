#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <map>
#include <string>

namespace alba {

class AlbaUserInterface {
public:
    template <typename AnswerType>
    using Choices = std::map<AnswerType, std::string>;

    // rule of zero

    std::string getUserInput();
    std::string getFilePathInput();

    std::string displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(
        std::string_view question, Choices<std::string> const& choices);

    template <typename NumberType>
    NumberType getNumberFromInput();

    template <typename NumberType>
    NumberType displayQuestionAndChoicesAndGetNumberAnswer(
        std::string_view question, Choices<NumberType> const& choices);

private:
    static constexpr int c_bufferSize = 1000;
    char buffer[c_bufferSize];
};

template <typename NumberType>
NumberType AlbaUserInterface::getNumberFromInput() {
    return stringHelper::convertStringToNumber<NumberType>(getUserInput());
}

}  // namespace alba
