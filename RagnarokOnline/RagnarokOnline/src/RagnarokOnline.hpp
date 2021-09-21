#pragma once

#include <String/AlbaStringHelper.hpp>

#include <iostream>
#include <map>
#include <string>
#include <vector>
namespace alba
{
struct NameAndRate
{
    std::string name;
    double rate;
};

using NamesAndRates = std::vector<NameAndRate>;

struct Item
{
    unsigned int itemId;
    std::string name;
    std::string type;
    std::string itemClass;
    unsigned int buyingPrice;
    unsigned int sellingPrice;
    unsigned int weight;
    unsigned int attack;
    unsigned int defense;
    unsigned int requiredLevel;
    unsigned int weaponLevel;
    unsigned int slot;
    unsigned int range;
    std::string property;
    std::string prefixOrSuffix;
    stringHelper::strings applicableJobs;
    std::string description;
    std::string itemScript;
    NamesAndRates droppedByMonstersWithRates;
};

struct Monster
{
    unsigned int monsterId;
    std::string name;
    unsigned int hp;
    unsigned int level;
    std::string race;
    std::string property;
    std::string size;
    unsigned int hitRequiredFor100Percent;
    unsigned int fleeRequiredFor95Percent;
    unsigned int baseExperience;
    unsigned int jobExperience;
    std::string baseExperiencePerHp;
    std::string jobExperiencePerHp;
    std::string walkSpeed;
    std::string attackDelay;
    std::string delayAfterHit;
    unsigned int lowestAttack;
    unsigned int highestAttack;
    unsigned int defense;
    unsigned int magicDefense;
    unsigned int strength;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int dexterity;
    unsigned int vitality;
    unsigned int luck;
    unsigned int attackRange;
    unsigned int spellRange;
    unsigned int sightRange;
    int neutralPercentage;
    int waterPercentage;
    int earthPercentage;
    int firePercentage;
    int windPercentage;
    int poisonPercentage;
    int holyPercentage;
    int shadowPercentage;
    int ghostPercentage;
    int undeadPercentage;
    NamesAndRates dropsWithRates;
};

using ItemIdToItemMap = std::map<unsigned int, Item>;
using MonsterIdToMonsterMap = std::map<unsigned int, Monster>;


class RagnarokOnline{
public:
    RagnarokOnline();

    void retrieveItemDataFromRmsWebpages(std::string const& directoryPathOfWebPages);
    void retrieveItemDataFromRmsWebPage(std::string const& filePathOfWebPage);
    void retrieveMonsterDataFromRmsWebpages(std::string const& directoryPathOfWebPages);
    void retrieveMonsterDataFromRmsWebPage(std::string const& filePathOfWebPage);

    void readItemIdToItemMapFromFile(std::string const& inputFilePath);
    void readMonsterIdToMonsterMapFromFile(std::string const& inputFilePath);

    ItemIdToItemMap const& getItemIdToItemMap() const;
    MonsterIdToMonsterMap const& getMonsterIdToMonsterMap() const;

    void saveItemIdToItemMapToFile(std::string const& outputFilePath) const;
    void saveMonsterIdToMonsterMapToFile(std::string const& outputFilePath) const;

    void printItemIdToItemMap() const;
    void printMonsterIdToMonsterMap() const;

private:
    std::string fixText(std::string const& text);
    ItemIdToItemMap m_itemIdToItemMap;
    MonsterIdToMonsterMap m_monsterIdToMonsterMap;
};

std::ostream & operator<<(std::ostream & out, NameAndRate const& nameAndRate);
std::ostream & operator<<(std::ostream & out, Item const& item);
std::ostream & operator<<(std::ostream & out, Monster const& monster);
std::ostream & operator<<(std::ostream & out, ItemIdToItemMap const& itemIdToItemMap);
std::ostream & operator<<(std::ostream & out, MonsterIdToMonsterMap const& monsterIdToMonsterMap);

std::istream & operator>>(std::istream & in, NameAndRate & nameAndRate);
std::istream & operator>>(std::istream & in, Item & item);
std::istream & operator>>(std::istream & in, Monster & monster);
std::istream & operator>>(std::istream & in, ItemIdToItemMap & itemIdToItemMap);
std::istream & operator>>(std::istream & in, MonsterIdToMonsterMap & monsterIdToMonsterMap);


}