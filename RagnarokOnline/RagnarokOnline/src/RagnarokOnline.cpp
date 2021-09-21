#include "RagnarokOnline.hpp"

#include <File/AlbaFileParameterReader.hpp>
#include <File/AlbaFileParameterWriter.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>


#include <Debug/AlbaDebug.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

RagnarokOnline::RagnarokOnline()
{}

void RagnarokOnline::retrieveItemDataFromRmsWebpages(
        string const& directoryPathOfWebPages)
{
    AlbaLocalPathHandler directoryPathHandler(directoryPathOfWebPages);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesOneDepth("*.html", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        retrieveItemDataFromRmsWebPage(filePath);
    }
}

void RagnarokOnline::retrieveItemDataFromRmsWebPage(
        string const& filePathOfWebPage)
{
    AlbaLocalPathHandler filePathHandler(filePathOfWebPage);
    ifstream fileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(fileStream);
    fileReader.setMaxBufferSize(100000);
    bool isContextBoxItemEncountered(false);
    Item item{};
    string property;
    string description;
    bool isDescriptionNotComplete(false);
    string itemScript;
    bool isItemScriptNotComplete(false);
    while(fileReader.isNotFinished())
    {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        bool shouldItemBeCleared(false);
        if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(table class="content_box_item")"))
        {
            isContextBoxItemEncountered = true;
            shouldItemBeCleared = true;
        }
        if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(class="content_box_body")"))
        {
            isContextBoxItemEncountered = false;
            shouldItemBeCleared = true;
        }
        if(shouldItemBeCleared)
        {
            if(item.itemId != 0)
            {
                m_itemIdToItemMap.emplace(item.itemId, item);
            }
            item = Item{};
            property.clear();
        }

        if(isContextBoxItemEncountered)
        {
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td valign="bottom"><b>)"))
            {
                item.name = fixText(getStringInBetweenTwoStrings(line, R"(<td valign="bottom"><b>)", R"(</b>)"));
            }
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(Item ID#)"))
            {
                item.itemId = convertStringToNumber<unsigned int>(fixText(getStringInBetweenTwoStrings(line, R"(Item ID#)", R"( ()")));
            }
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td class="bb" align="right">)"))
            {
                string value = fixText(getStringInBetweenTwoStrings(line, R"(<td class="bb" align="right">)", R"(</td>)"));
                if("Type" == property)
                {
                    item.type = value;
                }
                else if("Class" == property)
                {
                    item.itemClass = value;
                }
                else if("Buy" == property)
                {
                    item.buyingPrice = convertStringToNumber<unsigned int>(value);
                }
                else if("Sell" == property)
                {
                    item.sellingPrice = convertStringToNumber<unsigned int>(value);
                }
                else if("Weight" == property)
                {
                    item.weight = convertStringToNumber<unsigned int>(value);
                }
                else if("Attack" == property)
                {
                    item.attack = convertStringToNumber<unsigned int>(value);
                }
                else if("Defense" == property)
                {
                    item.defense = convertStringToNumber<unsigned int>(value);
                }
                else if("Required Lvl" == property)
                {
                    item.requiredLevel = convertStringToNumber<unsigned int>(value);
                }
                else if("Weapon Lvl" == property)
                {
                    item.weaponLevel = convertStringToNumber<unsigned int>(value);
                }
                else if("Slot" == property)
                {
                    item.slot = convertStringToNumber<unsigned int>(value);
                }
                else if("Range" == property)
                {
                    item.range = convertStringToNumber<unsigned int>(value);
                }
                else if("Pre/Suffix" == property)
                {
                    item.prefixOrSuffix = value;
                }
            }
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<th class="bb" align="right">)"))
            {
                string value = fixText(getStringInBetweenTwoStrings(line, R"(<th class="bb" align="right">)", R"(</th>)"));
                if("Property" == property)
                {
                    item.property = value;
                }
            }
            if("Description" == property)
            {
                if(isDescriptionNotComplete)
                {
                    description += " ";
                    if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</td>)"))
                    {
                        description += fixText(getStringBeforeThisString(line, R"(</td>)"));
                        isDescriptionNotComplete = false;
                        item.description = description;
                    }
                    else
                    {
                        description += line;
                    }
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td colspan="9" class="bb" valign="top">)"))
                {
                    if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</td>)"))
                    {
                        description = fixText(getStringInBetweenTwoStrings(line, R"(<td colspan="9" class="bb" valign="top">)", R"(</td>)"));
                        isDescriptionNotComplete = false;
                        item.description = description;
                    }
                    else
                    {
                        description = fixText(getStringAfterThisString(line, R"(<td colspan="9" class="bb" valign="top">)"));
                        isDescriptionNotComplete = true;
                    }
                }
            }
            if("Item Script" == property)
            {
                if(isItemScriptNotComplete)
                {
                    itemScript += " ";
                    if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</div>)"))
                    {
                        itemScript += fixText(getStringBeforeThisString(line, R"(</div>)"));
                        isItemScriptNotComplete = false;
                        item.itemScript = itemScript;
                    }
                    else
                    {
                        itemScript += line;
                    }
                }
                else if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<div class="db_script_txt">)"))
                {
                    if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</div>)"))
                    {
                        itemScript = fixText(getStringInBetweenTwoStrings(line, R"(<div class="db_script_txt">)", R"(</div>)"));
                        isItemScriptNotComplete = false;
                        item.itemScript = itemScript;
                    }
                    else
                    {
                        itemScript = fixText(getStringAfterThisString(line, R"(<div class="db_script_txt">)"));
                        isItemScriptNotComplete = true;
                    }
                }
            }
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<th class="lmd")"))
            {
                property = fixText(getStringInBetweenTwoStrings(line, R"(align="left">)", R"(</th>)"));
                if("Applicable Jobs" == property)
                {
                    string lineWithJobs(line);
                    while(isStringFoundInsideTheOtherStringCaseSensitive(lineWithJobs, R"(<td width="100">)"))
                    {
                        string value = fixText(getStringInBetweenTwoStrings(lineWithJobs, R"(<td width="100">)", R"(</td>)"));
                        item.applicableJobs.emplace_back(value);
                        lineWithJobs = getStringAfterThisString(lineWithJobs, R"(<td width="100">)");
                    }
                }
                else if("Dropped By" == property)
                {
                    string lineWithDroppedBy(line);
                    while(isStringFoundInsideTheOtherStringCaseSensitive(lineWithDroppedBy, R"(<div class="tipstext">)"))
                    {
                        string monsterName = fixText(getStringInBetweenTwoStrings(lineWithDroppedBy, ")\">", R"(<div class="tipstext">)"));
                        string monsterRate = fixText(getStringInBetweenTwoStrings(lineWithDroppedBy, R"(<div class="tipstext">)", R"(</div>)"));
                        item.droppedByMonstersWithRates.emplace_back(NameAndRate{monsterName, convertStringToNumber<double>(monsterRate)});
                        lineWithDroppedBy = getStringAfterThisString(lineWithDroppedBy, R"(<div class="tipstext">)");
                    }
                }
            }
        }
    }
}

ItemIdToItemMap const& RagnarokOnline::getItemIdToItemMap() const
{
    return m_itemIdToItemMap;
}

void RagnarokOnline::printItemIdToItemMap() const
{
    for(auto const& itemIdItemPair : m_itemIdToItemMap)
    {
        cout << "Item ID: " << itemIdItemPair.first << endl;
        Item const& item(itemIdItemPair.second);
        cout << "Item name: " << item.name << endl;
        cout << "Item type: " << item.type << endl;
        cout << "Item class: " << item.itemClass << endl;
        cout << "Buying price: " << item.buyingPrice << endl;
        cout << "Selling price: " << item.sellingPrice << endl;
        cout << "Weight: " << item.weight << endl;
        cout << "Attack: " << item.attack << endl;
        cout << "Defense: " << item.defense << endl;
        cout << "Required Level: " << item.requiredLevel << endl;
        cout << "Weapon Level: " << item.weaponLevel << endl;
        cout << "Slot: " << item.slot << endl;
        cout << "Range: " << item.range << endl;
        cout << "Property: " << item.property << endl;
        cout << "Prefix or Suffix: " << item.prefixOrSuffix << endl;
        cout << "Applicable jobs: {";
        for(string const& applicableJob : item.applicableJobs)
        {
            cout << "[" << applicableJob << "], ";
        }
        cout << "}" << endl;
        cout << "Description: " << item.description << endl;
        cout << "Item script: " << item.itemScript << endl;
        cout << "Dropped by monsters with rates: {";
        for(NameAndRate const& droppedByMonsterWithRate : item.droppedByMonstersWithRates)
        {
            cout << "[" << droppedByMonsterWithRate.name << "," << droppedByMonsterWithRate.rate << "], ";
        }
        cout << "}" << endl;
    }
}

string RagnarokOnline::fixText(
        string const& text)
{
    return getStringWithoutStartingAndTrailingWhiteSpace(text);
}

ostream & operator<<(ostream & out, NameAndRate const& nameAndRate)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(nameAndRate.name);
    writer.writeData<double>(nameAndRate.rate);
    return out;
}

ostream & operator<<(ostream & out, Item const& item)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<unsigned int>(item.itemId);
    writer.writeData<string>(item.name);
    writer.writeData<string>(item.type);
    writer.writeData<string>(item.itemClass);
    writer.writeData<unsigned int>(item.buyingPrice);
    writer.writeData<unsigned int>(item.sellingPrice);
    writer.writeData<unsigned int>(item.weight);
    writer.writeData<unsigned int>(item.attack);
    writer.writeData<unsigned int>(item.defense);
    writer.writeData<unsigned int>(item.requiredLevel);
    writer.writeData<unsigned int>(item.weaponLevel);
    writer.writeData<unsigned int>(item.slot);
    writer.writeData<unsigned int>(item.range);
    writer.writeData<string>(item.property);
    writer.writeData<string>(item.prefixOrSuffix);
    writer.writeVectorData<string>(item.applicableJobs);
    writer.writeData<string>(item.description);
    writer.writeData<string>(item.itemScript);
    writer.writeVectorData<NameAndRate>(item.droppedByMonstersWithRates);
    return out;
}

ostream & operator<<(ostream & out, ItemIdToItemMap const& itemIdToItemMap)
{
    AlbaFileParameterWriter writer(out);
    writer.writeMapData<unsigned int, Item>(itemIdToItemMap);
    return out;
}

istream & operator>>(istream & in, NameAndRate & nameAndRate)
{
    AlbaFileParameterReader reader(in);
    nameAndRate.name = reader.readData<string>();
    nameAndRate.rate = reader.readData<double>();
    return in;
}

istream & operator>>(istream & in, Item & item)
{
    AlbaFileParameterReader reader(in);
    item.itemId = reader.readData<unsigned int>();
    item.name = reader.readData<string>();
    item.type = reader.readData<string>();
    item.itemClass = reader.readData<string>();
    item.buyingPrice = reader.readData<unsigned int>();
    item.sellingPrice = reader.readData<unsigned int>();
    item.weight = reader.readData<unsigned int>();
    item.attack = reader.readData<unsigned int>();
    item.defense = reader.readData<unsigned int>();
    item.requiredLevel = reader.readData<unsigned int>();
    item.weaponLevel = reader.readData<unsigned int>();
    item.slot = reader.readData<unsigned int>();
    item.range = reader.readData<unsigned int>();
    item.property = reader.readData<string>();
    item.prefixOrSuffix = reader.readData<string>();
    reader.readVectorData<string>(item.applicableJobs);
    item.description = reader.readData<string>();
    item.itemScript = reader.readData<string>();
    reader.readVectorData<NameAndRate>(item.droppedByMonstersWithRates);
    return in;
}

istream & operator>>(istream & in, ItemIdToItemMap & itemIdToItemMap)
{
    AlbaFileParameterReader reader(in);
    reader.readMapData<unsigned int, Item>(itemIdToItemMap);
    return in;
}

}