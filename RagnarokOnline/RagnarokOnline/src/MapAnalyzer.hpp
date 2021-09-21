#pragma once

#include <RagnarokOnline.hpp>

#include <string>
#include <vector>

namespace alba
{

struct MapAnalyzerData
{
    std::string mapName;
    double zenyPotential;
    double annoyanceHp;
    unsigned int mobCount;
};

using MapsAnalyzerData = std::vector<MapAnalyzerData>;

class MapAnalyzer
{
public:
    MapAnalyzer();

    void initialize();
    void analyze();
    void sortData();
    void printResult() const;

    double getPotentialZenyFromMonster(Monster const& monster) const;
    void printPotentialZenyFromMonster(
            std::string const& monsterName) const;

private:
    double getTalonRoDropRate(double const dropRate) const;
    RagnarokOnline m_ragnarokOnline;
    MapsAnalyzerData m_mapsAnalyzerData;
};


}
