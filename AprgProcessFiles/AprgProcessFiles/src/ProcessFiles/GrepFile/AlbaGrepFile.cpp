#include "AlbaGrepFile.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <fstream>

using namespace std;

namespace alba
{

AlbaGrepFile::AlbaGrepFile(string const& lineCondition)
    : m_isOutputFileWritten(false)
    , m_lineGrepEvaluator(lineCondition)
    , m_updateFunctionAfterOneIterationOptional()
{}

AlbaGrepFile::AlbaGrepFile(string const& lineCondition, UpdateFunctionWithPercentage const& function)
    : m_isOutputFileWritten(false)
    , m_lineGrepEvaluator(lineCondition)
    , m_updateFunctionAfterOneIterationOptional(function)
{}

bool AlbaGrepFile::isOutputFileWritten() const
{
    return m_isOutputFileWritten;
}

void AlbaGrepFile::processFile(string const& inputFilePath, string const& outputFilePath)
{
    m_isOutputFileWritten=false;
    AlbaLocalPathHandler inputPathHandler(inputFilePath);
    AlbaLocalPathHandler outputPathHandler(outputFilePath);
    ifstream inputFileStream(inputPathHandler.getFullPath());
    ofstream outputFileStream(outputPathHandler.getFullPath());
    AlbaFileReader fileReader(inputFileStream);
    double sizeOfFile = fileReader.getFileSize();
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(m_lineGrepEvaluator.evaluate(lineInLogs))
        {
            m_isOutputFileWritten=true;
            outputFileStream << lineInLogs << "\n";
        }
        if(fileReader.isNotFinished())
        {            updateAfterOneIteration(fileReader.getCurrentLocation()*100/sizeOfFile);
        }
    }
    updateAfterOneIteration(100);}

AlbaGrepStringEvaluator& AlbaGrepFile::getGrepEvaluator()
{
    return m_lineGrepEvaluator;
}

void AlbaGrepFile::updateAfterOneIteration(double const percentage)
{
    if(m_updateFunctionAfterOneIterationOptional)
    {
        m_updateFunctionAfterOneIterationOptional.value()(percentage);
    }
}

}
