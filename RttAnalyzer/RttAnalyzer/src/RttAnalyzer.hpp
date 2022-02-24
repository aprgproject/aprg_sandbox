#pragma once

#include <Common/Optional/AlbaOptional.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <fstream>
#include <string>#include <vector>

namespace alba
{
struct RttDetails
{
    std::string dateTime;
    unsigned int multiplePos[6];
    unsigned int pnPos;
};

class RttAnalyzer
{
public:
    RttAnalyzer();
    void processFile(std::string const& file);
    void processLine(std::string const& line);
    void processTitles(alba::stringHelper::strings const& titles);
    void processValues(std::string const& dateTime, alba::stringHelper::strings const& values);
    void saveAllRttDetails(std::ofstream & collectedRttDetails) const;

private:
    std::vector<RttDetails> m_allRttDetails;
    alba::AlbaOptional<unsigned int> m_cx8IndexOptional;
    alba::AlbaOptional<unsigned int> m_pnPosIndexOptional;
    unsigned int m_posNumber;

};

}
