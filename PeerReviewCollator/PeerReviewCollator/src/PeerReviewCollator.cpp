#include "PeerReviewCollator.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

void PeerReviewCollator::processDirectory(string const& directoryPath)
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaWindowsPathHandler(directoryPath).findFilesAndDirectoriesOneDepth("*.csv", listOfFiles, listOfDirectories);
    for(string const& filePath: listOfFiles)
    {
        processFile(filePath);
    }
    if(listOfFiles.empty())
    {
        cout<<"processDirectory -> No csv files found"<<endl;
    }
}

void PeerReviewCollator::processFile(string const& filePath)
{
    AlbaWindowsPathHandler pathHandler(filePath);
    cout<<"processFile -> Processing File: "<<pathHandler.getFile()<<endl;
    ifstream inputFile(filePath);
    AlbaFileReader fileReader(inputFile);
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        processLineForPerson(pathHandler.getFilenameOnly(), lineInFile);
    }
}

void PeerReviewCollator::processLineForPerson(string const& person, string const& lineInFile)
{
    vector<string> stringsInEachCell;
    copyStringsInEachCell(lineInFile, stringsInEachCell);

    bool isQuestionLine(false);
    bool isAnswerLine(false);
    string questionString;
    string answerString;
    string answerForPerson;
    for(string const& cellString : stringsInEachCell)
    {
        if(isQuestionLine)
        {
            questionString += cellString;
        }
        else if(isAnswerLine)
        {
            answerString += cellString;
        }
        else
        {
            isQuestionLine = 'Q'==cellString[0] && isNumber(cellString[1]);
            if(isQuestionLine)
            {
                m_currentQuestionNumber = convertStringToNumber<int>(cellString.substr(1));
            }
            isAnswerLine = " about "==cellString.substr(0, 7);
            if(isAnswerLine)
            {
                answerForPerson = getStringAfterThisString(cellString, " about ");
            }
        }
    }
    if(isQuestionLine)
    {
        m_questions[m_currentQuestionNumber] = questionString;
    }
    else if(isAnswerLine)
    {
        m_answers.push_back({person, m_currentQuestionNumber, answerString, answerForPerson});
    }
}

PeerReviewCollator::Questions& PeerReviewCollator::getQuestionsReference()
{
    return m_questions;
}

PeerReviewCollator::Answers& PeerReviewCollator::getAnswersReference()
{
    return m_answers;
}

void PeerReviewCollator::copyStringsInEachCell(string const& lineInCsvFile, vector<string>& stringsInEachCell) const
{
    int index(0);
    int length = lineInCsvFile.length();
    bool isInsideString(false);
    string temporaryString;
    while(index < length)
    {
        char currentCharacter = lineInCsvFile[index];
        if(isInsideString)
        {
            if('\"' == currentCharacter)
            {
                isInsideString = false;
            }
            else
            {
                temporaryString += currentCharacter;
            }
        }
        else
        {
            if('\"' == currentCharacter)
            {
                isInsideString = true;
            }
            else if(',' == currentCharacter)
            {
                stringsInEachCell.emplace_back(temporaryString);
                temporaryString.clear();
            }
            else
            {
                temporaryString += currentCharacter;
            }
        }
        index++;
    }
    stringsInEachCell.emplace_back(temporaryString);
}

void PeerReviewCollator::generateOutput(string const& outputDirectoryPath) const
{
    cout<<"generateOutput -> Generating output files"<<endl;
    map<string, multimap<int,pair<string, string>>> outputDatabase;
    for(Answer const& answer : m_answers)
    {
        outputDatabase[answer.m_answerForPerson].emplace(answer.m_questionNumber, pair<string, string>(answer.m_person, answer.m_answer));
    }
    for(auto const& mapOfPerson : outputDatabase)
    {
        ofstream outputFile(AlbaWindowsPathHandler(outputDirectoryPath + R"(\)" + mapOfPerson.first + ".csv").getFullPath());
        int questionNumber = 0;
        for(auto const& mapPerQuestion : mapOfPerson.second)
        {
            if(questionNumber != mapPerQuestion.first)
            {
                questionNumber = mapPerQuestion.first;
                outputFile << "Q" << questionNumber << R"(,")" << m_questions.at(questionNumber) << R"(")" << endl;
            }
            outputFile << R"("From )" << mapPerQuestion.second.first << R"(",")" <<mapPerQuestion.second.second << R"(")" << endl;
        }
    }
    cout<<"generateOutput -> Done"<<endl;
}

}
