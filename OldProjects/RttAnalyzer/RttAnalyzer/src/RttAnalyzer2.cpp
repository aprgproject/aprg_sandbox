#include "RttAnalyzer2.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

RttAnalyzer2::RttAnalyzer2(string const& outputFilePath)
    : m_outputLogStream(outputFilePath)
{}

void RttAnalyzer2::processFile(string const& file)
{
    AlbaLocalPathHandler pathHandler(file);
    ifstream logStream(pathHandler.getFullPath());
    ofstream outputLogStream(pathHandler.getDirectory()+"BtsLogRtt.csv");
    pathHandler.input(pathHandler.getDirectory()+pathHandler.getFilenameOnly()+".csv");
    ofstream collectedRttDetails(pathHandler.getFullPath());

    if(logStream.is_open())
    {
        AlbaFileReader logFileReader(logStream);

        while(logFileReader.isNotFinished())
        {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInFile, "final RTT value reported to DSP explorer"))
            {
                processLine(outputLogStream, lineInFile);
            }
        }
    }
}

void RttAnalyzer2::processLine(ofstream& outputFile, string const& line)
{
    static string dateTime;
    string time = getStringInBetweenTwoStrings(line, "<", "Z>");
    unsigned int rtt = convertStringToNumber<unsigned int>(getStringAfterThisString(line, "final RTT value reported to DSP explorer = "));
    outputFile << time << "," << rtt << "\n";
}

void RttAnalyzer2::saveTitle2()
{
    m_outputLogStream  << "fileName,dateTime,maxPos,refPos,difference\n";
}

void RttAnalyzer2::processFile2(string const& file)
{
    AlbaLocalPathHandler pathHandler(file);
    ifstream logStream(pathHandler.getFullPath());

    if(logStream.is_open())
    {
        AlbaFileReader logFileReader(logStream);

        while(logFileReader.isNotFinished())
        {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            processLine2(pathHandler.getFile(), lineInFile);
        }
    }
}

void RttAnalyzer2::processLine2(string const& fileName, string const& line)
{
    static string dateTime;
    if(isStringFoundInsideTheOtherStringNotCaseSensitive(line, "2019 Apr"))
    {
        dateTime = getStringInBetweenTwoStrings(line, "2019 Apr  3  ", "  [");
    }
    else if(isStringFoundInsideTheOtherStringNotCaseSensitive(line, "RXD_FILT"))
    {
        unsigned int maxPos = convertStringToNumber<unsigned int>(getNumberAfterThisString(line, "max_pos[0]: "));
        unsigned int refPos = convertStringToNumber<unsigned int>(getNumberAfterThisString(line, "ref_pos: "));
        int difference = static_cast<int>(maxPos)-static_cast<int>(refPos);
        m_outputLogStream << fileName <<"," << dateTime << ","<< maxPos << "," << refPos << "," << difference << "\n";
    }
}

void RttAnalyzer2::processFile3(string const& file)
{
    AlbaLocalPathHandler pathHandler(file);
    ifstream logStream(pathHandler.getFullPath());
    ofstream outputLogStream(pathHandler.getDirectory()+"PeakPosCx8FromUeLogs.csv");
    pathHandler.input(pathHandler.getDirectory()+pathHandler.getFilenameOnly()+".csv");
    ofstream collectedRttDetails(pathHandler.getFullPath());

    outputLogStream  << "peak_pos_cx8\n";

    if(logStream.is_open())
    {
        AlbaFileReader logFileReader(logStream);

        while(logFileReader.isNotFinished())
        {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            if(isStringFoundInsideTheOtherStringNotCaseSensitive(lineInFile, "peak_pos_cx8"))
            {
                processLine3(outputLogStream, lineInFile);
            }
        }
    }
}

void RttAnalyzer2::processLine3(ofstream& outputFile, string const& line)
{
    static string dateTime;
    unsigned int peakPosCx8 = convertStringToNumber<unsigned int>(getNumberAfterThisString(line, "peak_pos_cx8 "));
    outputFile << peakPosCx8  << "\n";
}

}
