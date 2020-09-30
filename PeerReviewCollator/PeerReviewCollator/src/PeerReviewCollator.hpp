#pragma once

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

namespace alba
{

struct Answer
{
    string m_person;
    int m_questionNumber;
    string m_answer;
    string m_answerForPerson;
};

class PeerReviewCollator
{
public:
    typedef map<int, string> Questions;
    typedef vector<Answer> Answers;

    void processDirectory(string const& directoryPath);
    void processFile(string const& filePath);
    void processLineForPerson(string const& person, string const& lineInFile);
    Questions& getQuestionsReference();
    Answers& getAnswersReference();
    void copyStringsInEachCell(string const& lineInCsvFile, vector<string>& stringsInEachCell) const;

    void generateOutput(string const& outputDirectoryPath) const;

private:
    int m_currentQuestionNumber;
    Questions m_questions;
    Answers m_answers;
};

}
