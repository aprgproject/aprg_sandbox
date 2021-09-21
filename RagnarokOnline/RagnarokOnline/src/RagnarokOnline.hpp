#pragma once

#include <String/AlbaStringHelper.hpp>

#include <map>
#include <iostream>
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

using ItemIdToItemMap = std::map<unsigned int, Item>;


class RagnarokOnline
{
public:
    RagnarokOnline();

    void retrieveItemDataFromRmsWebpages(std::string const& directoryPathOfWebPages);
    void retrieveItemDataFromRmsWebPage(std::string const& filePathOfWebPage);

    ItemIdToItemMap const& getItemIdToItemMap() const;

    void printItemIdToItemMap() const;

private:
    std::string fixText(std::string const& text);
    ItemIdToItemMap m_itemIdToItemMap;
};

std::ostream & operator<<(std::ostream & out, NameAndRate const& nameAndRate);
std::ostream & operator<<(std::ostream & out, Item const& item);
std::ostream & operator<<(std::ostream & out, ItemIdToItemMap const& itemIdToItemMap);

std::istream & operator>>(std::istream & in, NameAndRate & nameAndRate);
std::istream & operator>>(std::istream & in, Item & item);
std::istream & operator>>(std::istream & in, ItemIdToItemMap & itemIdToItemMap);

}