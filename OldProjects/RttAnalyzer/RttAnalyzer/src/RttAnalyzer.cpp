#include "RttAnalyzer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

RttAnalyzer::RttAnalyzer() {}

void RttAnalyzer::processFile(std::string const& file) {
    AlbaLocalPathHandler pathHandler(file);
    ifstream logStream(pathHandler.getFullPath());
    pathHandler.input(pathHandler.getDirectory() + pathHandler.getFilenameOnly() + ".csv");
    ofstream collectedRttDetails(pathHandler.getFullPath());

    if (logStream.is_open()) {
        AlbaFileReader logFileReader(logStream);

        while (logFileReader.isNotFinished()) {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            processLine(lineInFile);
        }
    }

    saveAllRttDetails(collectedRttDetails);
}

void RttAnalyzer::processLine(std::string const& line) {
    static string dateTime;
    if (isStringFoundInsideTheOtherStringNotCaseSensitive(line, "0x4178")) {
        dateTime = getStringWithoutStartingAndTrailingWhiteSpace(getStringBeforeThisString(line, "["));
    } else if (
        isStringFoundInsideTheOtherStringNotCaseSensitive(line, "PSC") &&
        isStringFoundInsideTheOtherStringNotCaseSensitive(line, "(cx8)")) {
        strings titles;
        splitToStrings<SplitStringType::WithoutDelimeters>(titles, line, "|");
        processTitles(titles);
    } else if (
        isStringFoundInsideTheOtherStringNotCaseSensitive(line, "SET") &&
        isStringFoundInsideTheOtherStringNotCaseSensitive(line, "|")) {
        strings values;
        splitToStrings<SplitStringType::WithoutDelimeters>(values, line, "|");
        processValues(dateTime, values);
    } else if (!isStringFoundInsideTheOtherStringNotCaseSensitive(line, "------")) {
        m_cx8IndexOptional.reset();
        m_pnPosIndexOptional.reset();
    }
}

/*
void RttAnalyzer::processLine(std::string const& line)
{
    static string dateTime;
    if(isStringFoundInsideTheOtherStringNotCaseSensitive(line, "0x4179"))
    {
        dateTime = getStringWithoutStartingAndTrailingWhiteSpace(getStringBeforeThisString(line,"["));
    }
    else if(isStringFoundInsideTheOtherStringNotCaseSensitive(line, "(Cx8)") &&
isStringFoundInsideTheOtherStringNotCaseSensitive(line, "PN Pos"))
    {
        strings titles;
        splitToStrings<SplitStringType::WithoutDelimeters>(titles, line, "|");
        processTitles(titles);
    }
    else if(isStringFoundInsideTheOtherStringNotCaseSensitive(line, "|"))
    {
        strings values;
        splitToStrings<SplitStringType::WithoutDelimeters>(values, line, "|");
        processValues(dateTime, values);
    }
    else if(isStringFoundInsideTheOtherStringNotCaseSensitive(line, "-"))
    {
        m_posNumber = 0;
    }
    else
    {
        m_cx8IndexOptional.clear();
        m_pnPosIndexOptional.clear();
    }
}
*/

void RttAnalyzer::processTitles(strings const& titles) {
    unsigned int index = 0;
    for (string const& title : titles) {
        if (isStringFoundInsideTheOtherStringNotCaseSensitive(title, "(cx8)") && !m_cx8IndexOptional) {
            m_cx8IndexOptional = index;
            break;
        }
        index++;
    }
}

/*
void RttAnalyzer::processTitles(strings const& titles)
{
    unsigned int index=0;
    for(string const& title : titles)
    {
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(title, "(Cx8)") && !m_cx8IndexOptional)
        {
            m_cx8IndexOptional.setValue(index);
        }
        else if(isStringFoundInsideTheOtherStringNotCaseSensitive(title, "PN Pos") && !m_pnPosIndexOptional)
        {
            m_pnPosIndexOptional.setValue(index);
        }
        index++;
    }
}
*/

void RttAnalyzer::processValues(string const& dateTime, strings const& values) {
    static RttDetails rttDetails;
    if (m_cx8IndexOptional) {
        if (m_cx8IndexOptional.value() < values.size()) {
            unsigned int value = convertStringToNumber<unsigned int>(values[m_cx8IndexOptional.value()]);
            if (value != 0) {
                rttDetails.multiplePos[0] = value;
                rttDetails.dateTime = dateTime;
                m_allRttDetails.emplace_back(rttDetails);
            }
        }
    }
}

/*
void RttAnalyzer::processValues(string const& dateTime, strings const& values)
{
    static RttDetails rttDetails;
    if(m_cx8IndexOptional && m_pnPosIndexOptional)
    {
        if(m_cx8IndexOptional.getReference()<values.size() && m_pnPosIndexOptional.getReference()<values.size() &&
m_posNumber<6)
        {
            rttDetails.multiplePos[m_posNumber] = convertStringToNumber<unsigned
int>(values[m_cx8IndexOptional.getReference()]); if(m_posNumber==0)
            {
                rttDetails.pnPos = convertStringToNumber<unsigned int>(values[m_pnPosIndexOptional.getReference()]);
            }
        }
    }
    m_posNumber++;
    if(m_posNumber==6)
    {
        rttDetails.dateTime = dateTime;
        m_allRttDetails.emplace_back(rttDetails);
        m_posNumber=0;
    }
}
*/

void RttAnalyzer::saveAllRttDetails(ofstream& collectedRttDetails) const {
    collectedRttDetails << "dateTime,Position(cx8)\n";

    for (RttDetails const& rttDetails : m_allRttDetails) {
        collectedRttDetails << rttDetails.dateTime << ", " << rttDetails.multiplePos[0] << "\n";
    }
}

/*
void RttAnalyzer::saveAllRttDetails(ofstream & collectedRttDetails) const
{
    collectedRttDetails << "dateTime,pos1,pos2,pos3,pos4,pos5,pos6,pn
pos,diffPos1,diffPos2,diffPos3,diffPos4,diffPos5,diffPos6,minDifferencePos,maxDifferencePos\n";

    for(RttDetails const& rttDetails : m_allRttDetails)
    {
        collectedRttDetails << rttDetails.dateTime << ", ";
        unsigned int minPos(rttDetails.multiplePos[0]), maxPos(rttDetails.multiplePos[0]), totalPos(0);
        int differentWithPos[6];
        int minDifferencePos, maxDifferencePos;
        for(unsigned int index=0; index<6; index++)
        {
            unsigned int currentPos(rttDetails.multiplePos[index]);
            minPos = min(minPos, currentPos);
            maxPos = max(maxPos, currentPos);
            totalPos += currentPos;
            differentWithPos[index] = currentPos-rttDetails.pnPos;

            collectedRttDetails << currentPos << ", ";
        }

        minDifferencePos = minPos-rttDetails.pnPos;
        maxDifferencePos = maxPos-rttDetails.pnPos;

        collectedRttDetails << rttDetails.pnPos << ", ";
        for(unsigned int index=0; index<6; index++)
        {
            collectedRttDetails << differentWithPos[index] << ", ";
        }
        collectedRttDetails << minDifferencePos << ", ";
        collectedRttDetails << maxDifferencePos << ", ";
        collectedRttDetails << "\n";
    }
}
*/

}  // namespace alba
