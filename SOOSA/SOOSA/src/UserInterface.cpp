#include "UserInterface.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/User/AlbaUserInterface.hpp>

#include <iostream>

using namespace std;

namespace alba
{

namespace soosa
{

InputConfiguration UserInterface::getSavedConfiguration() const
{
    return m_savedConfiguration;}

void UserInterface::askUserForMainDetails()
{
    cout <<"Enter area:" << endl;
    string area(m_userInterface.getUserInput());

    cout <<"Enter period:" <<  endl;
    string period(m_userInterface.getUserInput());

    cout <<"Enter discharge:" << endl;
    double discharge(m_userInterface.getNumberFromInput<double>());

    cout <<"Enter minimum satisfactory score (inclusive):" << endl;
    unsigned int minimumSatisfactoryScore(m_userInterface.getNumberFromInput<unsigned int>());

    m_savedConfiguration.setMainParameters(area, period, discharge, minimumSatisfactoryScore);
}

void UserInterface::askUserForFormDetails()
{
    cout << "Enter form details directory:" << endl;
    string formDetailsDirectoryPath(m_userInterface.getUserInput());
    saveFormDetailsFromFormDetailPath(askUserForPathOfFormDetailToRead(formDetailsDirectoryPath));
}
void UserInterface::saveFormDetailsFromFormDetailPath(string const& formDetailsFilePath)
{
    ifstream formDetailsStream(formDetailsFilePath);    AlbaFileReader fileReader(formDetailsStream);

    m_savedConfiguration.setFormDetailTitle(fileReader.getLineAndIgnoreWhiteSpaces());

    unsigned int columnNumber=0;
    while(fileReader.isNotFinished())
    {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        if(line == "NEW_COLUMN")
        {
            columnNumber++;
        }
        else
        {
            m_savedConfiguration.addQuestion(columnNumber, line);
        }
    }
}

string UserInterface::askUserForPathOfFormDetailToRead(string const& formDetailsDirectoryPath)
{
    AlbaLocalPathHandler formDetailsPathHandler(formDetailsDirectoryPath);

    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaUserInterface::Choices<unsigned int> choices;
    unsigned int choice(0);

    formDetailsPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);

    for(string const& formDetailsFile: listOfFiles)
    {
        cout << "Choice " << choice<<" :: " << AlbaLocalPathHandler(formDetailsFile).getFile() << endl;
        choices.emplace(choice++, AlbaLocalPathHandler(formDetailsFile).getFullPath());
    }
    unsigned chosenChoice(m_userInterface.displayQuestionAndChoicesAndGetNumberAnswer("Select formDetails:", choices));
    cout << "Chosen choice: " << chosenChoice << endl;

    return choices[chosenChoice];
}

}

}