#include "AlbaUserInterface.hpp"

#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>
#include <User/DisplayTable.hpp>

#include <iostream>

using namespace std;

namespace alba{

string AlbaUserInterface::getUserInput()
{
    cin.getline(buffer, c_bufferSize);
    return string(buffer);
}

string AlbaUserInterface::getFilePathInput()
{
    while (1)
    {
        string pathString(getUserInput());
        AlbaLocalPathHandler filePath(pathString);
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


template <typename NumberType>
NumberType AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(string const& question, Choices<NumberType> choices)
{
    cout<<question<<endl;

    stringHelper::NumberToStringConverter converter;
    converter.setFieldWidth(5);

    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Choice", DisplayTableCellMode::right, DisplayTableCellMode::center);
    table.getLastRow().addCell("  :  ");
    table.getLastRow().addCell("Description", DisplayTableCellMode::left, DisplayTableCellMode::center);
    for(auto const& choice: choices)
    {
        table.addRow();
        table.getLastRow().addCell(string("["+converter.convert<NumberType>(choice.first)+"]"), DisplayTableCellMode::right, DisplayTableCellMode::center);
        table.getLastRow().addCell("  :  ");
        table.getLastRow().addCell(choice.second, DisplayTableCellMode::left, DisplayTableCellMode::center);
    }
    cout<<table.drawOutput()<<endl;

    cout << "Input your answer: ";
    return stringHelper::convertStringToNumber<NumberType>(getUserInput());
}
template int AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(std::string const& question, Choices<int> choices);
template unsigned int AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(std::string const& question, Choices<unsigned int> choices);


string AlbaUserInterface::displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(string const& question, Choices<string> choices)
{
    cout<<question<<endl;

    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Choice", DisplayTableCellMode::right, DisplayTableCellMode::center);
    table.getLastRow().addCell("  :  ");
    table.getLastRow().addCell("Description", DisplayTableCellMode::left, DisplayTableCellMode::center);
    for(auto const& choice: choices)
    {
        table.addRow();
        table.getLastRow().addCell(string("["+stringHelper::getStringWithCapitalLetters(choice.first)+"]"), DisplayTableCellMode::right, DisplayTableCellMode::center);
        table.getLastRow().addCell("  :  ");
        table.getLastRow().addCell(choice.second, DisplayTableCellMode::left, DisplayTableCellMode::center);
    }
    cout<<table.drawOutput()<<endl;

    cout << "Input your answer: ";
    return stringHelper::getStringWithCapitalLetters(getUserInput());
}

}//namespace alba
