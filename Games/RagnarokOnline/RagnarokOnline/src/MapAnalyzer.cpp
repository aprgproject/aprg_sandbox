#include "MapAnalyzer.hpp"

#include <Common/Debug/AlbaDebug.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

MapAnalyzer::MapAnalyzer() {}

void MapAnalyzer::initialize() {
    m_ragnarokOnline.readItemIdToItemMapFromFile(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\ItemIdToItemMap.txt)");
    m_ragnarokOnline.readMonsterIdToMonsterMapFromFile(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\MonsterIdToMonsterMap.txt)");
    m_ragnarokOnline.readMapNameToRoMapFromFile(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\MapNameToRoMap.txt)");
    // m_ragnarokOnline.readBuyingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\BuyingShopItemsCurrentData.txt)");
    // m_ragnarokOnline.readSellingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\SellingShopItemsCurrentData.txt)");
    m_ragnarokOnline.readBuyingShopItems(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\BuyingShopItemsCumulativeData.txt)");
    m_ragnarokOnline.readSellingShopItems(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\SellingShopItemsCumulativeData.txt)");
    m_ragnarokOnline.buildItemNameToItemId();
    m_ragnarokOnline.buildMonsterNameToMonsterId();
}

void MapAnalyzer::analyze() {
    for (auto const& mapNameToRoMap : m_ragnarokOnline.getMapNameToRoMap()) {
        MapAnalyzerData mapAnalyzerData{};
        mapAnalyzerData.mapName = mapNameToRoMap.first;
        struct MonsterData {
            unsigned int spawnCount;
            double potentialZeny;
            double potentialBaseExperience;
            double potentialJobExperience;
            bool isAnnoyance;
        };
        RoMap const& roMap(mapNameToRoMap.second);

        map<string, MonsterData> monstersNameToDataMap;
        bool isMapAcceptable(true);
        unsigned int totalSpawnCount(0), undeadSpawnCount(0);
        for (MonsterDetailsOnRoMap const& monsterDetailsOnMap : roMap.monstersDetailsOnMap) {
            Monster monster(m_ragnarokOnline.getMonster(monsterDetailsOnMap.monsterName));
            if (!monster.isMvp()) {
                if (false)
                // if(monster.hp > 30000) // for sniper
                // if(monster.fleeRequiredFor95Percent > 220 || monster.hitRequiredFor100Percent > 135 || monster.hp >
                // 10000 || monster.vitality > 50 || monster.defense > 40) // for merchant if(monster.hp > 30000 ||
                // monster.attackRange > 3 ) // for wizard if(monster.fleeRequiredFor95Percent > 297 ||
                // monster.hitRequiredFor100Percent > 161) // for rogue if(monster.fleeRequiredFor95Percent > 310 ||
                // monster.hitRequiredFor100Percent > 170) // for assassin if(monster.hitRequiredFor100Percent > 154 ||
                // monster.hitRequiredFor100Percent > 254) // for knight
                {
                    isMapAcceptable = false;
                    break;
                }
                if (monstersNameToDataMap.find(monsterDetailsOnMap.monsterName) != monstersNameToDataMap.cend()) {
                    monstersNameToDataMap[monsterDetailsOnMap.monsterName].spawnCount = 0U;
                }
                monstersNameToDataMap[monsterDetailsOnMap.monsterName].spawnCount += monsterDetailsOnMap.spawnCount;
                totalSpawnCount += monsterDetailsOnMap.spawnCount;
                if (monster.race == "Undead") {
                    undeadSpawnCount += monsterDetailsOnMap.spawnCount;
                }
            }
        }
        // bool isMajorityUndead = ((double)undeadSpawnCount/totalSpawnCount) > 0.5;
        // isMapAcceptable = isMapAcceptable & isMajorityUndead;
        if (isMapAcceptable && !monstersNameToDataMap.empty()) {
            double totalPotentialZeny = 0;
            double totalPotentialBaseExperience = 0;
            double totalPotentialJobExperience = 0;
            for (auto& monsterNameToDataPair : monstersNameToDataMap) {
                Monster monster(m_ragnarokOnline.getMonster(monsterNameToDataPair.first));
                MonsterData& monsterData(monsterNameToDataPair.second);
                monsterData.potentialZeny = getPotentialZenyFromMonster(monster) * monsterData.spawnCount;
                monsterData.potentialBaseExperience =
                    getMultiplierForExperience(roMap.name) * monster.baseExperience * monsterData.spawnCount;
                monsterData.potentialJobExperience =
                    getMultiplierForExperience(roMap.name) * monster.jobExperience * monsterData.spawnCount;
                if (mapAnalyzerData.mapName == "prt_maze01") {
                    ALBA_PRINT_PRECISION(10);
                    ALBA_PRINT1(mapAnalyzerData.mapName);
                    ALBA_PRINT4(
                        monster.name, monsterData.potentialZeny, getPotentialZenyFromMonster(monster),
                        monsterData.spawnCount);
                    ALBA_PRINT6(
                        monster.name, monster.monsterId, monster.baseExperience, monsterData.spawnCount,
                        monster.hitRequiredFor100Percent, monster.fleeRequiredFor95Percent);
                    // ALBA_PRINT5(mapAnalyzerData.mapName,
                    // monster.name, monsterData.potentialJobExperience, monster.jobExperience, monsterData.spawnCount);
                    for (auto const& dropWithRates : monster.dropsWithRates) {
                        ALBA_PRINT2(dropWithRates.name, dropWithRates.rate);
                    }
                }
                // if (monster.fleeRequiredFor95Percent <= 200) {} // for homunculus lvling
                if (monster.size == "Small")  // for homunculus star glad farming
                {
                    totalPotentialZeny += monsterData.potentialZeny;
                    ALBA_PRINT3(monster.name, monster.size, totalPotentialZeny);
                }
                totalPotentialBaseExperience += monsterData.potentialBaseExperience;
                totalPotentialJobExperience += monsterData.potentialJobExperience;
            }            mapAnalyzerData.zenyPotential = totalPotentialZeny;
            mapAnalyzerData.baseExperiencePotential = totalPotentialBaseExperience;
            mapAnalyzerData.jobExperiencePotential = totalPotentialJobExperience;
            double averagePotentialZeny = totalPotentialZeny / monstersNameToDataMap.size();            for (auto& monsterNameToDataPair : monstersNameToDataMap) {
                Monster monster(m_ragnarokOnline.getMonster(monsterNameToDataPair.first));
                MonsterData& monsterData(monsterNameToDataPair.second);
                monsterData.isAnnoyance = monsterData.potentialZeny / averagePotentialZeny < 0.5;
                if (monsterData.isAnnoyance) {
                    mapAnalyzerData.annoyanceHp += monster.hp;
                }
                // if (!monsterData.isAnnoyance && monster.isAggressive()) {  // annoying mobs
                // if (monster.isAggressive()) { // aggressive mobs
                if (monster.walkSpeed != "Immovable") {  // moving mobs
                    mapAnalyzerData.mobCount += monsterData.spawnCount;
                }
            }            m_mapsAnalyzerData.emplace_back(mapAnalyzerData);
        }
    }
    // printPotentialZenyFromMonster("Demon Pungus");
    // printPotentialZenyFromMonster("Sleeper");

    // printPotentialZenyFromMonster("Incubus");
    // printPotentialZenyFromMonster("Succubus");
    // printPotentialZenyFromMonster("Violy");

    // printPotentialZenyFromMonster("Anolian");
    // printPotentialZenyFromMonster("Drainliar");
    // printPotentialZenyFromMonster("Gargoyle");

    // printPotentialZenyFromMonster("Kraben");
    // printPotentialZenyFromMonster("Tamruan");
    // printPotentialZenyFromMonster("Whisper");

    // printPotentialZenyFromMonster("Evil Cloud Hermit / Taoist Hermit");
    // printPotentialZenyFromMonster("Wicked Nymph / Evil Nymph");
    // printPotentialZenyFromMonster("Wild Ginseng / Hermit Plant");

    // printPotentialZenyFromMonster("Ghoul");
    // printPotentialZenyFromMonster("Zombie Slaughter");
    // printPotentialZenyFromMonster("Ragged Zombie");
    // printPotentialZenyFromMonster("Hell Poodle");
    // printPotentialZenyFromMonster("Banshee");
    // printPotentialZenyFromMonster("Flame Skull");

    // printPotentialZenyFromMonster("Zombie Prisoner");
    // printPotentialZenyFromMonster("Injustice");

    printPotentialZenyFromMonster("Cenere (Re-Stats)");
    printPotentialZenyFromMonster("Antique Book (Re-Stats)");
    printPotentialZenyFromMonster("Blue Lichtern / Lichtern (Re-Stats)");
    printPotentialZenyFromMonster("Yellow Lichtern / Lichtern (Re-Stats)");
}

void MapAnalyzer::sortData() {
    sort(
        m_mapsAnalyzerData.begin(), m_mapsAnalyzerData.end(),
        [](MapAnalyzerData const& first, MapAnalyzerData const& second) {
            if (first.zenyPotential == second.zenyPotential) {  // the first one is always tweaked depending on goal
                if (first.zenyPotential == second.zenyPotential) {
                    if (first.annoyanceHp == second.annoyanceHp) {
                        return first.mobCount > second.mobCount;                    } else {
                        return first.annoyanceHp < second.annoyanceHp;
                    }
                } else {                    return first.zenyPotential > second.zenyPotential;
                }
            } else {
                return first.zenyPotential > second.zenyPotential;
            }
        });
}

void MapAnalyzer::printResult() const {
    cout.precision(10);
    for (MapAnalyzerData const& mapData : m_mapsAnalyzerData) {
        cout << "Map:[" << mapData.mapName << "] Zeny:[" << mapData.zenyPotential << "] BaseExp:["
             << mapData.baseExperiencePotential << "] JobExp:[" << mapData.jobExperiencePotential << "] Annoyance:["
             << mapData.annoyanceHp << "] MobCount:[" << mapData.mobCount << "]\n";
    }
}

double MapAnalyzer::getPotentialZenyFromMonster(Monster const& monster) const {
    double potentialZeny = 0;
    for (NameAndRate const& dropWithRate : monster.dropsWithRates) {
        if (isDropRateAcceptable(dropWithRate.rate)) {
            Item item(m_ragnarokOnline.getItem(dropWithRate.name));
            double bestPrice(getBestPrice(item));
            potentialZeny += bestPrice * getTalonRoDropRate(dropWithRate.rate) / 100;
        }
    }
    return potentialZeny;
}

void MapAnalyzer::printPotentialZenyFromMonster(string const& monsterName) const {
    cout.precision(10);
    cout << "\n";
    cout << "Monster name: [" << monsterName << "]\n";
    Monster monster(m_ragnarokOnline.getMonster(monsterName));
    for (NameAndRate const& dropWithRate : monster.dropsWithRates) {
        if (isDropRateAcceptable(dropWithRate.rate)) {
            Item item(m_ragnarokOnline.getItem(dropWithRate.name));
            string fixedItemName(m_ragnarokOnline.getFixedItemName(item));
            double bestPrice(getBestPrice(item));
            double itemPotentialZeny = bestPrice * getTalonRoDropRate(dropWithRate.rate) / 100;
            cout << "Item name: [" << fixedItemName << "] Item potential zeny: [" << itemPotentialZeny
                 << "] Talon RO drop rate: [" << getTalonRoDropRate(dropWithRate.rate) << "] Best price: [" << bestPrice
                 << "] NPC price: [" << item.sellingPrice << "] TalonRo buying price: ["
                 << m_ragnarokOnline.getTalonRoBuyingPrice(fixedItemName) << "] TalonRo selling price: ["
                 << m_ragnarokOnline.getTalonRoSellingPrice(fixedItemName) << "]\n";
        }
    }
    cout << "\n";
}

double MapAnalyzer::getMultiplierForExperience(string const& mapName) {
    double multiplier(1);
    if (isStringFoundInsideTheOtherStringCaseSensitive(mapName, "xmas_") ||
        isStringFoundInsideTheOtherStringCaseSensitive(mapName, "man_") ||
        isStringFoundInsideTheOtherStringCaseSensitive(mapName, "dic_")) {
        multiplier = 2;
    }
    return multiplier;
}

bool MapAnalyzer::isDropRateAcceptable(double const /*dropRate*/) const {
    return true;
    // return dropRate >= 1; // This removes hard farming
}

double MapAnalyzer::getTalonRoDropRate(double const dropRate) const {
    double talonRoDropRate(dropRate * 3);
    if (talonRoDropRate > 100) {
        talonRoDropRate = 100;
    }
    return talonRoDropRate;
}

double MapAnalyzer::getBestPrice(Item const& item) const {
    double result;
    string fixedItemName(m_ragnarokOnline.getFixedItemName(item));
    double npcPrice = item.sellingPrice;
    double talonRoBuyingPrice = m_ragnarokOnline.getTalonRoBuyingPrice(fixedItemName);
    double talonRoSellingPrice = m_ragnarokOnline.getTalonRoSellingPrice(fixedItemName);
    result = npcPrice;
    if (result < talonRoBuyingPrice) {
        result = talonRoBuyingPrice;  // remove this if buying shops are ignored
    }
    if (result < talonRoSellingPrice) {
        // result = talonRoSellingPrice; //remove this if selling shops are ignored
    }
    return result;
}

}  // namespace alba
