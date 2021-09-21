#include "MapAnalyzer.hpp"

#include <algorithm>
#include <iostream>


#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

MapAnalyzer::MapAnalyzer()
{}

void MapAnalyzer::initialize()
{
    m_ragnarokOnline.readItemIdToItemMapFromFile(R"(C:\Users\detectivemark7\Desktop\RO\ItemIdToItemMap.txt)");
    m_ragnarokOnline.readMonsterIdToMonsterMapFromFile(R"(C:\Users\detectivemark7\Desktop\RO\MonsterIdToMonsterMap.txt)");
    m_ragnarokOnline.readMapNameToRoMapFromFile(R"(C:\Users\detectivemark7\Desktop\RO\MapNameToRoMap.txt)");
    m_ragnarokOnline.buildItemNameToItemId();
    m_ragnarokOnline.buildMonsterNameToMonsterId();
}

void MapAnalyzer::analyze()
{
    for(auto const& mapNameToRoMap : m_ragnarokOnline.getMapNameToRoMap())
    {
        MapAnalyzerData mapAnalyzerData{};
        mapAnalyzerData.mapName = mapNameToRoMap.first;
        struct MonsterData
        {
            unsigned int spawnCount;
            double potentialZeny;
            bool isAnnoyance;
        };
        RoMap const& roMap(mapNameToRoMap.second);
        map<string, MonsterData> monstersNameToDataMap;
        bool isMapAcceptable(true);
        for(MonsterDetailsOnRoMap const& monsterDetailsOnMap : roMap.monstersDetailsOnMap)
        {
            Monster monster(m_ragnarokOnline.getMonster(monsterDetailsOnMap.monsterName));
            if(!monster.isMvp())
            {
                if(monster.hp > 15000)
                {
                    isMapAcceptable = false;
                    break;
                }
                if(monstersNameToDataMap.find(monsterDetailsOnMap.monsterName) != monstersNameToDataMap.cend())
                {
                    monstersNameToDataMap[monsterDetailsOnMap.monsterName].spawnCount = 0U;
                }
                monstersNameToDataMap[monsterDetailsOnMap.monsterName].spawnCount += monsterDetailsOnMap.spawnCount;
            }
        }
        if(isMapAcceptable)
        {
            double totalPotentialZeny=0;
            for(auto & monsterNameToDataPair : monstersNameToDataMap)
            {
                Monster monster(m_ragnarokOnline.getMonster(monsterNameToDataPair.first));
                MonsterData & monsterData(monsterNameToDataPair.second);
                monsterData.potentialZeny = getPotentialZenyFromMonster(monster) * monsterData.spawnCount;
                if(mapAnalyzerData.mapName == "yuno_fild06")
                {
                    ALBA_PRINT_PRECISION(10);
                    ALBA_PRINT6(mapAnalyzerData.mapName, totalPotentialZeny, monster.name, monsterData.potentialZeny, getPotentialZenyFromMonster(monster), monsterData.spawnCount);
                }
                totalPotentialZeny += monsterData.potentialZeny;
            }
            mapAnalyzerData.zenyPotential = totalPotentialZeny;
            double averagePotentialZeny = totalPotentialZeny/monstersNameToDataMap.size();
            for(auto & monsterNameToDataPair : monstersNameToDataMap)
            {
                Monster monster(m_ragnarokOnline.getMonster(monsterNameToDataPair.first));
                MonsterData & monsterData(monsterNameToDataPair.second);
                monsterData.isAnnoyance = monsterData.potentialZeny/averagePotentialZeny < 0.5;
                if(monsterData.isAnnoyance)
                {
                    mapAnalyzerData.annoyanceHp += monster.hp;
                }
                if(!monsterData.isAnnoyance && monster.isAggressive())
                {
                    mapAnalyzerData.mobCount += monsterData.spawnCount;
                }
            }
            m_mapsAnalyzerData.emplace_back(mapAnalyzerData);
        }
    }

    printPotentialZenyFromMonster("Goat");
    printPotentialZenyFromMonster("Demon Pungus");
    printPotentialZenyFromMonster("Sleeper");
}

void MapAnalyzer::sortData()
{
    sort(m_mapsAnalyzerData.begin(), m_mapsAnalyzerData.end(), [](
         MapAnalyzerData const& first,
         MapAnalyzerData const& second)
    {
        if(first.zenyPotential == second.zenyPotential)
        {
            if(first.annoyanceHp == second.annoyanceHp)
            {
                return first.mobCount > second.mobCount;
            }
            else
            {
                return first.annoyanceHp < second.annoyanceHp;
            }
        }
        else
        {
            return first.zenyPotential > second.zenyPotential;
        }
    });
}

void MapAnalyzer::printResult() const
{
    cout.precision(10);
    for(MapAnalyzerData const& mapData : m_mapsAnalyzerData)
    {
        cout << "Name: [" << mapData.mapName
             << "][" << mapData.zenyPotential
             << "][" << mapData.annoyanceHp
             << "][" << mapData.mobCount
             << "]" << endl;
    }
}

double MapAnalyzer::getPotentialZenyFromMonster(
        Monster const& monster) const
{
    double potentialZeny=0;
    for(NameAndRate const& dropWithRate : monster.dropsWithRates)
    {
        if(dropWithRate.rate >= 1)
        {
            Item item(m_ragnarokOnline.getItem(dropWithRate.name));
            potentialZeny += item.sellingPrice * getTalonRoDropRate(dropWithRate.rate) / 100;
        }
    }
    return potentialZeny;
}

void MapAnalyzer::printPotentialZenyFromMonster(
        string const& monsterName) const
{
    cout.precision(10);
    cout << "Monster name: [" << monsterName << "]" << endl;
    Monster monster(m_ragnarokOnline.getMonster(monsterName));
    double monsterPotentialZeny=0;
    for(NameAndRate const& dropWithRate : monster.dropsWithRates)
    {
        if(dropWithRate.rate >= 1)
        {
            Item item(m_ragnarokOnline.getItem(dropWithRate.name));
            double itemPotentialZeny = item.sellingPrice * getTalonRoDropRate(dropWithRate.rate) / 100;
            monsterPotentialZeny += itemPotentialZeny;
            cout << "Item name: [" << item.name
                 << "] Item potential zeny: [" << itemPotentialZeny
                 << "] Selling price: [" << item.sellingPrice
                 << "] Talon RO drop rate: [" << getTalonRoDropRate(dropWithRate.rate)
                 << "]" << endl;
        }
    }
    cout << "Monster name: [" << monsterName << "] monster potential zeny: [" << monsterPotentialZeny << "]" << endl;
}

double MapAnalyzer::getTalonRoDropRate(
        double const dropRate) const
{
    double talonRoDropRate(dropRate*3);
    if(talonRoDropRate > 100)
    {
        talonRoDropRate = 100;
    }
    return talonRoDropRate;
}

}
