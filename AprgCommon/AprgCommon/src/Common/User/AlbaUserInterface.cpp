#include "AlbaUserInterface.hpp"

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

string AlbaUserInterface::getUserInput()
{
    cin.getline(buffer, c_bufferSize);
    return string(buffer);
}

string AlbaUserInterface::getFilePathInput()
{
    while(true)
    {
        string pathString(getUserInput());
        AlbaLocalPathHandler filePath(pathString);
        if(filePath.isFoundInLocalSystem() && filePath.isFile())
        {
            return filePath.getFullPath();
        }
        else
        {
            cout<<"File not found\n";
        }
    }
}

template <typename NumberType>
NumberType AlbaUserInterface::getNumberFromInput()
{
    return convertStringToNumber<NumberType>(getUserInput());
}
template int AlbaUserInterface::getNumberFromInput<int>();
template unsigned int AlbaUserInterface::getNumberFromInput<unsigned int>();
template float AlbaUserInterface::getNumberFromInput<float>();
template double AlbaUserInterface::getNumberFromInput<double>();


template <typename NumberType>
NumberType AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(string const& question, Choices<NumberType> const& choices)
{
    cout<<question<<"\n";

    StringConverterWithFormatting converter(5, ' ');

    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Choice", DisplayTableCellMode::right);
    table.getLastRow().addCell("  :  ");
    table.getLastRow().addCell("Description", DisplayTableCellMode::left);
    for(auto const& choice: choices)
    {
        table.addRow();
        table.getLastRow().addCell(string("["+converter.convertToString<NumberType>(choice.first)+"]"), DisplayTableCellMode::right);
        table.getLastRow().addCell("  :  ");
        table.getLastRow().addCell(choice.second, DisplayTableCellMode::left);
    }
    cout<<table<<"\n";

    cout << "Input your answer: ";
    return convertStringToNumber<NumberType>(getUserInput());
}
template int AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(string const& question, Choices<int> const& choices);
template unsigned int AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(string const& question, Choices<unsigned int> const& choices);


string AlbaUserInterface::displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(string const& question, Choices<string> const& choices)
{
    cout<<question<<"\n";

    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Choice", DisplayTableCellMode::right);
    table.getLastRow().addCell("  :  ");
    table.getLastRow().addCell("Description", DisplayTableCellMode::left);
    for(auto const& choice: choices)
    {
        table.addRow();
        table.getLastRow().addCell(string("["+getStringWithCapitalLetters(choice.first)+"]"), DisplayTableCellMode::right);
        table.getLastRow().addCell("  :  ");
        table.getLastRow().addCell(choice.second, DisplayTableCellMode::left);
    }
    cout<<table<<"\n";

    cout << "Input your answer: ";
    return getStringWithCapitalLetters(getUserInput());
}

}//namespace alba
