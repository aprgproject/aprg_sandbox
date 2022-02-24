#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace alba
{

enum class ShopType
{
    BuyingShop,
    SellingShop
};

struct NameAndRate
{
    std::string name;
    double rate;
};

struct MonsterDetailsOnRoMap
{
    std::string monsterName;
    unsigned int spawnCount;
    std::string spawnRate;
};

using NamesAndRates = std::vector<NameAndRate>;
using MonstersDetailsOnRoMap = std::vector<MonsterDetailsOnRoMap>;

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
    stringHelper::strings maps;
    stringHelper::strings modes;
    stringHelper::strings monsterSkills;
    NamesAndRates dropsWithRates;
    bool isAggressive() const;
    bool isMvp() const;
    bool hasStoneCurseSkill() const;
};

struct RoMap
{
    std::string name;
    std::string fullName;
    MonstersDetailsOnRoMap monstersDetailsOnMap;
};

struct ShopItemDetail
{
    std::string itemName;
    double averagePrice;
    unsigned int totalNumber;
};

using ItemIdToItemMap = std::map<unsigned int, Item>;
using MonsterIdToMonsterMap = std::map<unsigned int, Monster>;
using MapNameToRoMap = std::map<std::string, RoMap>;
using ItemNameToShopItemDetailMap = std::map<std::string, ShopItemDetail>;


class RagnarokOnline
{
public:
    RagnarokOnline();

    void retrieveItemDataFromRmsWebpages(std::string const& directoryPathOfWebPages);
    void retrieveItemDataFromRmsWebPage(std::string const& filePathOfWebPage);
    void retrieveMonsterDataFromRmsWebpages(std::string const& directoryPathOfWebPages);
    void retrieveMonsterDataFromRmsWebPage(std::string const& filePathOfWebPage);
    void retrieveMapDataFromRmsWebpages(std::string const& directoryPathOfWebPages);
    void retrieveMapDataFromRmsWebPage(std::string const& filePathOfWebPage);
    void retrieveBuyingShopDataFromTalonRoWebpages(std::string const& directoryPathOfWebPages);
    void retrieveSellingShopDataFromTalonRoWebpages(std::string const& directoryPathOfWebPages);
    void retrieveShopDataFromTalonRoWebPage(std::string const& filePathOfWebPage, ShopType const shopType);

    void readItemIdToItemMapFromFile(std::string const& inputFilePath);
    void readMonsterIdToMonsterMapFromFile(std::string const& inputFilePath);
    void readMapNameToRoMapFromFile(std::string const& inputFilePath);
    void readBuyingShopItems(std::string const& inputFilePath);
    void readSellingShopItems(std::string const& inputFilePath);

    void buildItemNameToItemId();
    void buildMonsterNameToMonsterId();

    ItemIdToItemMap const& getItemIdToItemMap() const;
    MonsterIdToMonsterMap const& getMonsterIdToMonsterMap() const;
    MapNameToRoMap const& getMapNameToRoMap() const;
    ItemNameToShopItemDetailMap const& getBuyingItemShops() const;
    ItemNameToShopItemDetailMap const& getSellingItemShops() const;

    Item getItem(std::string const& fixedItemName) const;
    Monster getMonster(std::string const& monsterName) const;
    std::string getFixedItemName(Item const& item) const;
    double getTalonRoBuyingPrice(std::string const& fixedItemName) const;
    double getTalonRoSellingPrice(std::string const& fixedItemName) const;

    void saveItemIdToItemMapToFile(std::string const& outputFilePath) const;
    void saveMonsterIdToMonsterMapToFile(std::string const& outputFilePath) const;
    void saveMapNameToRoMapToFile(std::string const& outputFilePath) const;
    void saveBuyingShopItems(std::string const& outputFilePath) const;
    void saveSellingShopItems(std::string const& outputFilePath) const;

    void printItemIdToItemMap() const;
    void printMonsterIdToMonsterMap() const;
    void printMapNameToRoMap() const;
    void printBuyingShopItems() const;
    void printSellingShopItems() const;

private:
    std::string fixText(std::string const& text);
    ItemIdToItemMap m_itemIdToItemMap;
    MonsterIdToMonsterMap m_monsterIdToMonsterMap;
    MapNameToRoMap m_mapNameToRoMap;
    std::map<std::string, unsigned int> m_itemNameToItemIdMap;
    std::map<std::string, unsigned int> m_monsterNameToMonsterIdMap;
    ItemNameToShopItemDetailMap m_buyingShopItems;
    ItemNameToShopItemDetailMap m_sellingShopItems;
};

std::ostream & operator<<(std::ostream & out, NameAndRate const& nameAndRate);
std::ostream & operator<<(std::ostream & out, MonsterDetailsOnRoMap const& monsterDetailsOnRoMap);
std::ostream & operator<<(std::ostream & out, Item const& item);
std::ostream & operator<<(std::ostream & out, Monster const& monster);
std::ostream & operator<<(std::ostream & out, ShopItemDetail const& shopItemDetail);
std::ostream & operator<<(std::ostream & out, RoMap const& roMap);
std::ostream & operator<<(std::ostream & out, ItemIdToItemMap const& itemIdToItemMap);
std::ostream & operator<<(std::ostream & out, MonsterIdToMonsterMap const& monsterIdToMonsterMap);
std::ostream & operator<<(std::ostream & out, MapNameToRoMap const& mapNameToRoMap);
std::ostream & operator<<(std::ostream & out, ItemNameToShopItemDetailMap const& itemNameToShopItemDetailMap);

std::istream & operator>>(std::istream & in, NameAndRate & nameAndRate);
std::istream & operator>>(std::istream & in, MonsterDetailsOnRoMap & monsterDetailsOnRoMap);
std::istream & operator>>(std::istream & in, Item & item);
std::istream & operator>>(std::istream & in, Monster & monster);
std::istream & operator>>(std::istream & in, ShopItemDetail & shopItemDetail);
std::istream & operator>>(std::istream & in, RoMap & roMap);
std::istream & operator>>(std::istream & in, ItemIdToItemMap & itemIdToItemMap);
std::istream & operator>>(std::istream & in, MonsterIdToMonsterMap & monsterIdToMonsterMap);
std::istream & operator>>(std::istream & in, MapNameToRoMap & mapNameToRoMap);
std::istream & operator>>(std::istream & in, ItemNameToShopItemDetailMap & itemNameToShopItemDetailMap);


}
