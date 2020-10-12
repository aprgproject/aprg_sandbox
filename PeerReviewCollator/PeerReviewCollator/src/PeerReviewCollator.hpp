#pragma once

#include <map>
#include <string>
#include <vector>


namespace alba
{
struct Answer
{
    std::string m_person;
    int m_questionNumber;
    std::string m_answer;
    std::string m_answerForPerson;
};

class PeerReviewCollator
{
public:
    typedef std::map<int, std::string> Questions;
    typedef std::vector<Answer> Answers;

    void processDirectory(std::string const& directoryPath);
    void processFile(std::string const& filePath);
    void processLineForPerson(std::string const& person, std::string const& lineInFile);
    Questions& getQuestionsReference();
    Answers& getAnswersReference();
    void copyStringsInEachCell(std::string const& lineInCsvFile, std::vector<std::string> & stringsInEachCell) const;

    void generateOutput(std::string const& outputDirectoryPath) const;

private:
    int m_currentQuestionNumber;    Questions m_questions;
    Answers m_answers;
};
}
