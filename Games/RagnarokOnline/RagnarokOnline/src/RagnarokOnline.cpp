#include "RagnarokOnline.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Stream/AlbaStreamParameterReader.hpp>
#include <Common/Stream/AlbaStreamParameterWriter.hpp>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

bool Monster::isAggressive() const {
    bool result(false);
    for (string const& mode : modes) {
        if ("Aggressive" == mode) {
            result = true;
            break;
        }
    }
    return result;
}

bool Monster::isMvp() const {
    bool result(false);
    for (string const& mode : modes) {
        if ("MVP Boss" == mode) {
            result = true;
            break;
        }
    }
    return result;
}

bool Monster::hasStoneCurseSkill() const {
    bool result(false);
    for (string const& monsterSkill : monsterSkills) {
        if (isStringFoundInsideTheOtherStringCaseSensitive(monsterSkill, "Stone Curse")) {
            result = true;
            break;
        }
    }
    return result;
}

RagnarokOnline::RagnarokOnline() {}

void RagnarokOnline::retrieveItemDataFromRmsWebpages(string const& directoryPathOfWebPages) {
    AlbaLocalPathHandler directoryPathHandler(directoryPathOfWebPages);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesOneDepth("*.html", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        retrieveItemDataFromRmsWebPage(filePath);
    }
}

void RagnarokOnline::retrieveItemDataFromRmsWebPage(string const& filePathOfWebPage) {
    AlbaLocalPathHandler filePathHandler(filePathOfWebPage);
    ifstream fileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(fileStream);
    fileReader.setMaxBufferSize(100000);
    bool isContextBoxEncountered(false);
    Item item{};
    string parameterName;
    string description;
    bool isDescriptionNotComplete(false);
    string itemScript;
    bool isItemScriptNotComplete(false);
    while (fileReader.isNotFinished()) {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        bool shouldItemBeCleared(false);
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(table class="content_box_item")")) {
            isContextBoxEncountered = true;
            shouldItemBeCleared = true;
        }
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(class="content_box_body")")) {
            isContextBoxEncountered = false;
            shouldItemBeCleared = true;
        }
        if (shouldItemBeCleared) {
            if (item.itemId != 0) {
                m_itemIdToItemMap.emplace(item.itemId, item);
            }
            item = Item{};
            parameterName.clear();
        }

        if (isContextBoxEncountered) {
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td valign="bottom"><b>)")) {
                item.name = fixText(getStringInBetweenTwoStrings(line, R"(<td valign="bottom"><b>)", R"(</b>)"));
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(Item ID#)")) {
                item.itemId = convertStringToNumber<unsigned int>(
                    fixText(getStringInBetweenTwoStrings(line, R"(Item ID#)", R"( ()")));
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td class="bb" align="right">)")) {
                string value =
                    fixText(getStringInBetweenTwoStrings(line, R"(<td class="bb" align="right">)", R"(</td>)"));
                if ("Type" == parameterName) {
                    item.type = value;
                } else if ("Class" == parameterName) {
                    item.itemClass = value;
                } else if ("Buy" == parameterName) {
                    item.buyingPrice = convertStringToNumber<unsigned int>(value);
                } else if ("Sell" == parameterName) {
                    item.sellingPrice = convertStringToNumber<unsigned int>(value);
                } else if ("Weight" == parameterName) {
                    item.weight = convertStringToNumber<unsigned int>(value);
                } else if ("Attack" == parameterName) {
                    item.attack = convertStringToNumber<unsigned int>(value);
                } else if ("Defense" == parameterName) {
                    item.defense = convertStringToNumber<unsigned int>(value);
                } else if ("Required Lvl" == parameterName) {
                    item.requiredLevel = convertStringToNumber<unsigned int>(value);
                } else if ("Weapon Lvl" == parameterName) {
                    item.weaponLevel = convertStringToNumber<unsigned int>(value);
                } else if ("Slot" == parameterName) {
                    item.slot = convertStringToNumber<unsigned int>(value);
                } else if ("Range" == parameterName) {
                    item.range = convertStringToNumber<unsigned int>(value);
                } else if ("Pre/Suffix" == parameterName) {
                    item.prefixOrSuffix = value;
                }
            }
            if ("Property" == parameterName) {
                if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<th class="bb" align="right">)")) {
                    item.property =
                        fixText(getStringInBetweenTwoStrings(line, R"(<th class="bb" align="right">)", R"(</th>)"));
                }
            } else if ("Description" == parameterName) {
                if (isDescriptionNotComplete) {
                    description += " ";
                    if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</td>)")) {
                        description += getStringBeforeThisString(line, R"(</td>)");
                        isDescriptionNotComplete = false;
                        item.description = fixText(description);
                    } else {
                        description += line;
                    }
                } else if (isStringFoundInsideTheOtherStringCaseSensitive(
                               line, R"(<td colspan="9" class="bb" valign="top">)")) {
                    if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</td>)")) {
                        description = getStringInBetweenTwoStrings(
                            line, R"(<td colspan="9" class="bb" valign="top">)", R"(</td>)");
                        isDescriptionNotComplete = false;
                        item.description = fixText(description);
                    } else {
                        description = getStringAfterThisString(line, R"(<td colspan="9" class="bb" valign="top">)");
                        isDescriptionNotComplete = true;
                    }
                }
            } else if ("Item Script" == parameterName) {
                if (isItemScriptNotComplete) {
                    itemScript += " ";
                    if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</div>)")) {
                        itemScript += getStringBeforeThisString(line, R"(</div>)");
                        isItemScriptNotComplete = false;
                        item.itemScript = fixText(itemScript);
                    } else {
                        itemScript += line;
                    }
                } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<div class="db_script_txt">)")) {
                    if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</div>)")) {
                        itemScript = getStringInBetweenTwoStrings(line, R"(<div class="db_script_txt">)", R"(</div>)");
                        isItemScriptNotComplete = false;
                        item.itemScript = fixText(itemScript);
                    } else {
                        itemScript = getStringAfterThisString(line, R"(<div class="db_script_txt">)");
                        isItemScriptNotComplete = true;
                    }
                }
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<th class="lmd")")) {
                parameterName = fixText(getStringInBetweenTwoStrings(line, R"(align="left">)", R"(</th>)"));
                if ("Applicable Jobs" == parameterName) {
                    string lineWithJobs(line);
                    while (isStringFoundInsideTheOtherStringCaseSensitive(lineWithJobs, R"(<td width="100">)")) {
                        string value =
                            fixText(getStringInBetweenTwoStrings(lineWithJobs, R"(<td width="100">)", R"(</td>)"));
                        item.applicableJobs.emplace_back(value);
                        lineWithJobs = getStringAfterThisString(lineWithJobs, R"(<td width="100">)");
                    }
                } else if ("Dropped By" == parameterName) {
                    string lineWithDroppedBy(line);
                    while (isStringFoundInsideTheOtherStringCaseSensitive(
                        lineWithDroppedBy, R"(<div class="tipstext">)")) {
                        string monsterName = fixText(
                            getStringInBetweenTwoStrings(lineWithDroppedBy, ")\">", R"(<div class="tipstext">)"));
                        string monsterRate = fixText(
                            getStringInBetweenTwoStrings(lineWithDroppedBy, R"(<div class="tipstext">)", R"(</div>)"));
                        item.droppedByMonstersWithRates.emplace_back(
                            NameAndRate{monsterName, convertStringToNumber<double>(monsterRate)});
                        lineWithDroppedBy = getStringAfterThisString(lineWithDroppedBy, R"(<div class="tipstext">)");
                    }
                }
            }
        }
    }
}

void RagnarokOnline::retrieveMonsterDataFromRmsWebpages(string const& directoryPathOfWebPages) {
    AlbaLocalPathHandler directoryPathHandler(directoryPathOfWebPages);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesOneDepth("*.html", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        retrieveMonsterDataFromRmsWebPage(filePath);
    }
}

void RagnarokOnline::retrieveMonsterDataFromRmsWebPage(string const& filePathOfWebPage) {
    AlbaLocalPathHandler filePathHandler(filePathOfWebPage);
    ifstream fileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(fileStream);
    fileReader.setMaxBufferSize(100000);
    bool isContextBoxEncountered(false);
    Monster monster{};
    string parameterName;
    while (fileReader.isNotFinished()) {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        bool shouldItemBeCleared(false);
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(table class="content_box_mob")")) {
            isContextBoxEncountered = true;
            shouldItemBeCleared = true;
        }
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(class="content_box_body")")) {
            isContextBoxEncountered = false;
            shouldItemBeCleared = true;
        }
        if (shouldItemBeCleared) {
            if (monster.monsterId != 0) {
                m_monsterIdToMonsterMap.emplace(monster.monsterId, monster);
            }
            monster = Monster{};
            parameterName.clear();
        }

        if (isContextBoxEncountered) {
            if (isStringFoundInsideTheOtherStringCaseSensitive(
                    line, R"(<div style="width: 400px; margin: 0px 5px;">)")) {
                monster.name = fixText(
                    getStringInBetweenTwoStrings(line, R"(<div style="width: 400px; margin: 0px 5px;">)", R"(&nbsp;)"));
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(Mob-ID#)")) {
                monster.monsterId = convertStringToNumber<unsigned int>(
                    fixText(getStringInBetweenTwoStrings(line, R"(Mob-ID#)", R"(</div>)")));
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td class="bb")") &&
                isStringFoundInsideTheOtherStringCaseSensitive(line, R"(align="right">)")) {
                string value = fixText(getStringInBetweenTwoStrings(line, R"(align="right">)", R"(</td>)"));
                if ("HP" == parameterName) {
                    monster.hp = convertStringToNumber<unsigned int>(value);
                } else if ("Level" == parameterName) {
                    monster.level = convertStringToNumber<unsigned int>(value);
                } else if ("Race" == parameterName) {
                    monster.race = value;
                } else if ("Property" == parameterName) {
                    monster.property = value;
                } else if ("Size" == parameterName) {
                    monster.size = value;
                } else if ("Hit(100%)" == parameterName) {
                    monster.hitRequiredFor100Percent = convertStringToNumber<unsigned int>(value);
                } else if ("Flee(95%)" == parameterName) {
                    monster.fleeRequiredFor95Percent = convertStringToNumber<unsigned int>(value);
                } else if ("Base Experience" == parameterName) {
                    monster.baseExperience = convertStringToNumber<unsigned int>(value);
                } else if ("Job Experience" == parameterName) {
                    monster.jobExperience = convertStringToNumber<unsigned int>(value);
                } else if ("Base Exp Per HP" == parameterName) {
                    monster.baseExperiencePerHp = value;
                } else if ("Job Exp Per HP" == parameterName) {
                    monster.jobExperiencePerHp = value;
                } else if ("Walk Speed" == parameterName) {
                    monster.walkSpeed = value;
                } else if ("Atk Delay" == parameterName) {
                    monster.attackDelay = value;
                } else if ("Delay After Hit" == parameterName) {
                    monster.delayAfterHit = value;
                } else if ("Attack" == parameterName) {
                    monster.lowestAttack = convertStringToNumber<unsigned int>(getStringBeforeThisString(value, "-"));
                    monster.highestAttack = convertStringToNumber<unsigned int>(getStringAfterThisString(value, "-"));
                } else if ("Def" == parameterName) {
                    monster.defense = convertStringToNumber<unsigned int>(value);
                } else if ("Magic Def" == parameterName) {
                    monster.magicDefense = convertStringToNumber<unsigned int>(value);
                } else if ("Str" == parameterName) {
                    monster.strength = convertStringToNumber<unsigned int>(value);
                } else if ("Int" == parameterName) {
                    monster.intelligence = convertStringToNumber<unsigned int>(value);
                } else if ("Agi" == parameterName) {
                    monster.agility = convertStringToNumber<unsigned int>(value);
                } else if ("Dex" == parameterName) {
                    monster.dexterity = convertStringToNumber<unsigned int>(value);
                } else if ("Vit" == parameterName) {
                    monster.vitality = convertStringToNumber<unsigned int>(value);
                } else if ("Luk" == parameterName) {
                    monster.luck = convertStringToNumber<unsigned int>(value);
                } else if ("Atk Range" == parameterName) {
                    monster.attackRange = convertStringToNumber<unsigned int>(value);
                } else if ("Spell Range" == parameterName) {
                    monster.spellRange = convertStringToNumber<unsigned int>(value);
                } else if ("Sight Range" == parameterName) {
                    monster.sightRange = convertStringToNumber<unsigned int>(value);
                } else if ("Neutral" == parameterName) {
                    monster.neutralPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Water" == parameterName) {
                    monster.waterPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Earth" == parameterName) {
                    monster.earthPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Fire" == parameterName) {
                    monster.firePercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Wind" == parameterName) {
                    monster.windPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Poison" == parameterName) {
                    monster.poisonPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Holy" == parameterName) {
                    monster.holyPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Shadow" == parameterName) {
                    monster.shadowPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Ghost" == parameterName) {
                    monster.ghostPercentage = convertStringToNumber<unsigned int>(value);
                } else if ("Undead" == parameterName) {
                    monster.undeadPercentage = convertStringToNumber<unsigned int>(value);
                }
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(onclick="return popItem)")) {
                if ("Drops" == parameterName) {
                    string dropName = fixText(getStringInBetweenTwoStrings(line, R"(">)", R"(<b>)"));
                    string slot = fixText(getStringInBetweenTwoStrings(line, R"([</b>)", R"(<b>])"));
                    if (!slot.empty()) {
                        dropName += " [";
                        dropName += slot;
                        dropName += "]";
                    }
                    string dropRate = fixText(getStringInBetweenTwoStrings(line, R"((</b>)", R"(<b>))"));
                    monster.dropsWithRates.emplace_back(NameAndRate{dropName, convertStringToNumber<double>(dropRate)});
                }
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<div class="tipstext">)") &&
                isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</div>)")) {
                if ("Mode" == parameterName) {
                    string modes = getStringInBetweenTwoStrings(line, R"(<div class="tipstext">)", R"(</div>)");
                    while (isStringFoundInsideTheOtherStringCaseSensitive(modes, R"(<br>)")) {
                        string mode(fixText(getStringBeforeThisString(modes, R"(<br>)")));
                        transformReplaceStringIfFound(mode, "- ", "");
                        monster.modes.emplace_back(mode);
                        modes = getStringAfterThisString(modes, R"(<br>)");
                    }
                }
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td class="bb" width="180" valign="top">)")) {
                string lineWithMaps(line);
                while (isStringFoundInsideTheOtherStringCaseSensitive(lineWithMaps, "map_dim)\">")) {
                    string value = fixText(getStringInBetweenTwoStrings(lineWithMaps, "map_dim)\">", R"(</a>)"));
                    monster.maps.emplace_back(value);
                    lineWithMaps = getStringAfterThisString(lineWithMaps, "map_dim)\">");
                }
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<table width="100%" border="0">)")) {
                if ("Monster Skills" == parameterName) {
                    string lineWithMonsterSkills(line);
                    while (isStringFoundInsideTheOtherStringCaseSensitive(lineWithMonsterSkills, R"(circle.gif">)")) {
                        string value =
                            fixText(getStringInBetweenTwoStrings(lineWithMonsterSkills, R"(circle.gif">)", R"(</td>)"));
                        monster.monsterSkills.emplace_back(value);
                        lineWithMonsterSkills = getStringAfterThisString(lineWithMonsterSkills, R"(circle.gif">)");
                    }
                }
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<th class="lmd")")) {
                parameterName = fixText(getStringInBetweenTwoStrings(line, R"(align="left">)", R"(</th>)"));
            } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(align="center">Drops</th>)")) {
                parameterName = "Drops";
            } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(align="center">Mode</th>)")) {
                parameterName = "Mode";
            } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(align="center">Monster Skills</th>)")) {
                parameterName = "Monster Skills";
            }
        }
    }
}

void RagnarokOnline::retrieveMapDataFromRmsWebpages(string const& directoryPathOfWebPages) {
    AlbaLocalPathHandler directoryPathHandler(directoryPathOfWebPages);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesOneDepth("*.html", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        retrieveMapDataFromRmsWebPage(filePath);
    }
}

void RagnarokOnline::retrieveMapDataFromRmsWebPage(string const& filePathOfWebPage) {
    AlbaLocalPathHandler filePathHandler(filePathOfWebPage);
    ifstream fileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(fileStream);
    fileReader.setMaxBufferSize(100000);
    bool isContextBoxEncountered(false);
    RoMap map{};
    while (fileReader.isNotFinished()) {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        bool shouldItemBeCleared(false);
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(table class="content_box_db")")) {
            isContextBoxEncountered = true;
            shouldItemBeCleared = true;
        }
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(class="content_box_body")")) {
            isContextBoxEncountered = false;
            shouldItemBeCleared = true;
        }
        if (shouldItemBeCleared) {
            if (!map.name.empty()) {
                m_mapNameToRoMap.emplace(map.name, map);
            }
            map = RoMap{};
        }

        if (isContextBoxEncountered) {
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(- Map: )") &&
                isStringFoundInsideTheOtherStringCaseSensitive(line, R"( -)")) {
                map.name = fixText(getStringInBetweenTwoStrings(line, R"(- Map: )", R"( -)"));
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<b>Map: )") &&
                isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</b>)")) {
                map.name = fixText(getStringInBetweenTwoStrings(line, R"(<b>Map: )", R"(</b>)"));
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td class="bborder" align="right">)") &&
                isStringFoundInsideTheOtherStringCaseSensitive(line, R"(</td>)")) {
                map.fullName =
                    fixText(getStringInBetweenTwoStrings(line, R"(<td class="bborder" align="right">)", R"(</td>)"));
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(
                    line, R"(Click on a monster below to view its detail:)")) {
                string lineWithMonsters(line);
                while (isStringFoundInsideTheOtherStringCaseSensitive(
                    lineWithMonsters, "onmouseout=\"hideddrivetip_image()\">")) {
                    MonsterDetailsOnRoMap monsterDetailsOnMap{};
                    string wholeMonsterString = getStringInBetweenTwoStrings(
                        lineWithMonsters, "onmouseout=\"hideddrivetip_image()\">", R"(</a>)");
                    string wholeSpawnString =
                        getStringInBetweenTwoStrings(wholeMonsterString, R"(<b>(</b>)", R"(<b>)</b>)");
                    monsterDetailsOnMap.monsterName =
                        fixText(getStringBeforeThisString(wholeMonsterString, R"(<b>(</b>)"));
                    transformReplaceStringIfFound(monsterDetailsOnMap.monsterName, "[MVP]", "");
                    if (isStringFoundInsideTheOtherStringCaseSensitive(wholeSpawnString, "/")) {
                        monsterDetailsOnMap.spawnCount = convertStringToNumber<unsigned int>(
                            fixText(getStringBeforeThisString(wholeSpawnString, R"(/)")));
                        monsterDetailsOnMap.spawnRate = fixText(getStringAfterThisString(wholeSpawnString, R"(/)"));
                    } else {
                        monsterDetailsOnMap.spawnCount = convertStringToNumber<unsigned int>(fixText(wholeSpawnString));
                    }
                    map.monstersDetailsOnMap.emplace_back(monsterDetailsOnMap);
                    lineWithMonsters =
                        getStringAfterThisString(lineWithMonsters, "onmouseout=\"hideddrivetip_image()\">");
                }
            }
        }
    }
}

void RagnarokOnline::retrieveBuyingShopDataFromTalonRoWebpages(string const& directoryPathOfWebPages) {
    AlbaLocalPathHandler directoryPathHandler(directoryPathOfWebPages);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesOneDepth("*.html", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        retrieveShopDataFromTalonRoWebPage(filePath, ShopType::BuyingShop);
    }
}

void RagnarokOnline::retrieveSellingShopDataFromTalonRoWebpages(string const& directoryPathOfWebPages) {
    AlbaLocalPathHandler directoryPathHandler(directoryPathOfWebPages);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesOneDepth("*.html", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        retrieveShopDataFromTalonRoWebPage(filePath, ShopType::SellingShop);
    }
}

void RagnarokOnline::retrieveShopDataFromTalonRoWebPage(string const& filePathOfWebPage, ShopType const shopType) {
    AlbaLocalPathHandler filePathHandler(filePathOfWebPage);
    ifstream fileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(fileStream);
    fileReader.setMaxBufferSize(100000);
    while (fileReader.isNotFinished()) {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, R"(<td class="sorting_1">)")) {
            string lineWithItems(line);
            while (isStringFoundInsideTheOtherStringCaseSensitive(lineWithItems, R"(<td class="sorting_1">)")) {
                string itemString = getStringInBetweenTwoStrings(
                    lineWithItems, R"(<td class="sorting_1">)", R"(<span class="d-none">)");
                lineWithItems = getStringAfterThisString(lineWithItems, R"(<td class="sorting_1">)");
                string priceString = getStringInBetweenTwoStrings(lineWithItems, R"(</span></td><td>)", R"(</td><td>)");
                lineWithItems = getStringAfterThisString(lineWithItems, R"(</span></td><td>)");
                string numberString = getStringInBetweenTwoStrings(lineWithItems, R"(</td><td>)", R"(</td><td>)");

                ShopItemDetail newDetail{};
                newDetail.itemName = fixText(itemString);
                newDetail.averagePrice = convertStringToNumber<double>(fixText(priceString));
                newDetail.totalNumber = convertStringToNumber<unsigned int>(fixText(numberString));

                if (ShopType::BuyingShop == shopType) {
                    ItemNameToShopItemDetailMap::iterator it = m_buyingShopItems.find(newDetail.itemName);
                    if (it != m_buyingShopItems.cend()) {
                        unsigned newTotalNumber = it->second.totalNumber + newDetail.totalNumber;
                        double newAveragePrice = ((it->second.averagePrice * it->second.totalNumber) +
                                                  (newDetail.averagePrice * newDetail.totalNumber)) /
                                                 newTotalNumber;
                        it->second.totalNumber = newTotalNumber;
                        it->second.averagePrice = newAveragePrice;
                    } else {
                        m_buyingShopItems[newDetail.itemName] = newDetail;
                    }
                } else if (ShopType::SellingShop == shopType) {
                    ItemNameToShopItemDetailMap::iterator it = m_sellingShopItems.find(newDetail.itemName);
                    if (it != m_sellingShopItems.cend()) {
                        unsigned newTotalNumber = it->second.totalNumber + newDetail.totalNumber;
                        double newAveragePrice = ((it->second.averagePrice * it->second.totalNumber) +
                                                  (newDetail.averagePrice * newDetail.totalNumber)) /
                                                 newTotalNumber;
                        it->second.totalNumber = newTotalNumber;
                        it->second.averagePrice = newAveragePrice;
                    } else {
                        m_sellingShopItems[newDetail.itemName] = newDetail;
                    }
                }
            }
        }
    }
}

void RagnarokOnline::readItemIdToItemMapFromFile(string const& inputFilePath) {
    ifstream inputStream(inputFilePath);
    AlbaStreamParameterReader reader(inputStream);
    reader.readMapData<unsigned int, Item>(m_itemIdToItemMap);
}

void RagnarokOnline::readMonsterIdToMonsterMapFromFile(string const& inputFilePath) {
    ifstream inputStream(inputFilePath);
    AlbaStreamParameterReader reader(inputStream);
    reader.readMapData<unsigned int, Monster>(m_monsterIdToMonsterMap);
}

void RagnarokOnline::readMapNameToRoMapFromFile(string const& inputFilePath) {
    ifstream inputStream(inputFilePath);
    AlbaStreamParameterReader reader(inputStream);
    reader.readMapData<string, RoMap>(m_mapNameToRoMap);
}

void RagnarokOnline::readBuyingShopItems(string const& inputFilePath) {
    ifstream inputStream(inputFilePath);
    AlbaStreamParameterReader reader(inputStream);
    reader.readMapData<string, ShopItemDetail>(m_buyingShopItems);
}

void RagnarokOnline::readSellingShopItems(string const& inputFilePath) {
    ifstream inputStream(inputFilePath);
    AlbaStreamParameterReader reader(inputStream);
    reader.readMapData<string, ShopItemDetail>(m_sellingShopItems);
}

void RagnarokOnline::buildItemNameToItemId() {
    for (auto const& itemIdItemPair : m_itemIdToItemMap) {
        Item const& item(itemIdItemPair.second);
        string fixedItemName(getFixedItemName(item));
        m_itemNameToItemIdMap.emplace(fixedItemName, itemIdItemPair.first);
    }
}

void RagnarokOnline::buildMonsterNameToMonsterId() {
    for (auto const& monsterIdMonsterPair : m_monsterIdToMonsterMap) {
        Monster const& monster(monsterIdMonsterPair.second);
        m_monsterNameToMonsterIdMap.emplace(monster.name, monsterIdMonsterPair.first);
    }
}

ItemIdToItemMap const& RagnarokOnline::getItemIdToItemMap() const { return m_itemIdToItemMap; }

MonsterIdToMonsterMap const& RagnarokOnline::getMonsterIdToMonsterMap() const { return m_monsterIdToMonsterMap; }

MapNameToRoMap const& RagnarokOnline::getMapNameToRoMap() const { return m_mapNameToRoMap; }

ItemNameToShopItemDetailMap const& RagnarokOnline::getBuyingItemShops() const { return m_buyingShopItems; }

ItemNameToShopItemDetailMap const& RagnarokOnline::getSellingItemShops() const { return m_sellingShopItems; }

Item RagnarokOnline::getItem(string const& fixedItemName) const {
    Item result{};
    auto it1 = m_itemNameToItemIdMap.find(fixedItemName);
    if (it1 != m_itemNameToItemIdMap.cend()) {
        auto it2 = m_itemIdToItemMap.find(it1->second);
        if (it2 != m_itemIdToItemMap.cend()) {
            result = it2->second;
        } else {
            // cout << "ITEM ID NOT FOUND! [" << it1->second << "]\n";
        }
    } else {
        // cout << "ITEM NAME NOT FOUND! [" << fixedItemName << "]\n";
    }
    return result;
}

Monster RagnarokOnline::getMonster(string const& monsterName) const {
    Monster result{};
    auto it1 = m_monsterNameToMonsterIdMap.find(monsterName);
    if (it1 != m_monsterNameToMonsterIdMap.cend()) {
        auto it2 = m_monsterIdToMonsterMap.find(it1->second);
        if (it2 != m_monsterIdToMonsterMap.cend()) {
            result = it2->second;
        } else {
            cout << "MONSTER ID NOT FOUND! [" << it1->second << "]\n";
        }
    } else {
        cout << "MONSTER NAME NOT FOUND! [" << monsterName << "]\n";
    }
    return result;
}

string RagnarokOnline::getFixedItemName(Item const& item) const {
    string result(item.name);
    if (item.slot != 0) {
        stringstream slotStream;
        slotStream << " [" << item.slot << "]";
        result += slotStream.str();
    }
    return result;
}

double RagnarokOnline::getTalonRoBuyingPrice(string const& fixedItemName) const {
    double result(0);
    auto it = m_buyingShopItems.find(fixedItemName);
    if (it != m_buyingShopItems.cend()) {
        result = it->second.averagePrice;
    }
    return result;
}

double RagnarokOnline::getTalonRoSellingPrice(string const& fixedItemName) const {
    double result(0);
    auto it = m_sellingShopItems.find(fixedItemName);
    if (it != m_sellingShopItems.cend()) {
        result = it->second.averagePrice;
    }
    return result;
}

void RagnarokOnline::saveItemIdToItemMapToFile(string const& outputFilePath) const {
    ofstream outputStream(outputFilePath);
    AlbaStreamParameterWriter writer(outputStream);
    writer.writeMapData<unsigned int, Item>(m_itemIdToItemMap);
    writer.flush();
}

void RagnarokOnline::saveMonsterIdToMonsterMapToFile(string const& outputFilePath) const {
    ofstream outputStream(outputFilePath);
    AlbaStreamParameterWriter writer(outputStream);
    writer.writeMapData<unsigned int, Monster>(m_monsterIdToMonsterMap);
    writer.flush();
}

void RagnarokOnline::saveMapNameToRoMapToFile(string const& outputFilePath) const {
    ofstream outputStream(outputFilePath);
    AlbaStreamParameterWriter writer(outputStream);
    writer.writeMapData<string, RoMap>(m_mapNameToRoMap);
    writer.flush();
}

void RagnarokOnline::saveBuyingShopItems(string const& outputFilePath) const {
    ofstream outputStream(outputFilePath);
    AlbaStreamParameterWriter writer(outputStream);
    writer.writeMapData<string, ShopItemDetail>(m_buyingShopItems);
    writer.flush();
}

void RagnarokOnline::saveSellingShopItems(string const& outputFilePath) const {
    ofstream outputStream(outputFilePath);
    AlbaStreamParameterWriter writer(outputStream);
    writer.writeMapData<string, ShopItemDetail>(m_sellingShopItems);
    writer.flush();
}

void RagnarokOnline::printItemIdToItemMap() const {
    for (auto const& itemIdItemPair : m_itemIdToItemMap) {
        cout << "Item ID: " << itemIdItemPair.first << "\n";
        Item const& item(itemIdItemPair.second);
        cout << "Item name: " << item.name << "\n";
        cout << "Item type: " << item.type << "\n";
        cout << "Item class: " << item.itemClass << "\n";
        cout << "Buying price: " << item.buyingPrice << "\n";
        cout << "Selling price: " << item.sellingPrice << "\n";
        cout << "Weight: " << item.weight << "\n";
        cout << "Attack: " << item.attack << "\n";
        cout << "Defense: " << item.defense << "\n";
        cout << "Required Level: " << item.requiredLevel << "\n";
        cout << "Weapon Level: " << item.weaponLevel << "\n";
        cout << "Slot: " << item.slot << "\n";
        cout << "Range: " << item.range << "\n";
        cout << "Property: " << item.property << "\n";
        cout << "Prefix or Suffix: " << item.prefixOrSuffix << "\n";
        cout << "Applicable jobs: {";
        for (string const& applicableJob : item.applicableJobs) {
            cout << "[" << applicableJob << "], ";
        }
        cout << "}\n";
        cout << "Description: " << item.description << "\n";
        cout << "Item script: " << item.itemScript << "\n";
        cout << "Dropped by monsters with rates: {";
        for (NameAndRate const& droppedByMonsterWithRate : item.droppedByMonstersWithRates) {
            cout << "[" << droppedByMonsterWithRate.name << "," << droppedByMonsterWithRate.rate << "], ";
        }
        cout << "}\n";
    }
}

void RagnarokOnline::printMonsterIdToMonsterMap() const {
    for (auto const& monsterIdMonsterPair : m_monsterIdToMonsterMap) {
        cout << "Monster ID: " << monsterIdMonsterPair.first << "\n";
        Monster const& monster(monsterIdMonsterPair.second);
        cout << "Monster name: " << monster.name << "\n";
        cout << "HP: " << monster.hp << "\n";
        cout << "Level: " << monster.level << "\n";
        cout << "Race: " << monster.race << "\n";
        cout << "Property: " << monster.property << "\n";
        cout << "Size: " << monster.size << "\n";
        cout << "Hit required for 100%: " << monster.hitRequiredFor100Percent << "\n";
        cout << "Flee required for 95%: " << monster.fleeRequiredFor95Percent << "\n";
        cout << "Base experience: " << monster.baseExperience << "\n";
        cout << "Job experience: " << monster.jobExperience << "\n";
        cout << "Base experience per HP: " << monster.baseExperiencePerHp << "\n";
        cout << "Job experience per HP: " << monster.jobExperiencePerHp << "\n";
        cout << "Walk speed: " << monster.walkSpeed << "\n";
        cout << "Attack delay: " << monster.attackDelay << "\n";
        cout << "Delay after hit: " << monster.delayAfterHit << "\n";
        cout << "Lowest attack: " << monster.lowestAttack << "\n";
        cout << "Highest attack: " << monster.highestAttack << "\n";
        cout << "Defense: " << monster.defense << "\n";
        cout << "Magic defense: " << monster.magicDefense << "\n";
        cout << "Strength: " << monster.strength << "\n";
        cout << "Intelligence: " << monster.intelligence << "\n";
        cout << "Agility: " << monster.agility << "\n";
        cout << "Dexterity: " << monster.dexterity << "\n";
        cout << "Vitality: " << monster.vitality << "\n";
        cout << "Luck: " << monster.luck << "\n";
        cout << "Attack range: " << monster.attackRange << "\n";
        cout << "Spell range: " << monster.spellRange << "\n";
        cout << "Sight range: " << monster.sightRange << "\n";
        cout << "Neutral %: " << monster.neutralPercentage << "\n";
        cout << "Water %: " << monster.waterPercentage << "\n";
        cout << "Earth %: " << monster.earthPercentage << "\n";
        cout << "Fire %: " << monster.firePercentage << "\n";
        cout << "Wind %: " << monster.windPercentage << "\n";
        cout << "Poison %: " << monster.poisonPercentage << "\n";
        cout << "Holy %: " << monster.holyPercentage << "\n";
        cout << "Shadow %: " << monster.shadowPercentage << "\n";
        cout << "Ghost %: " << monster.ghostPercentage << "\n";
        cout << "Undead %: " << monster.undeadPercentage << "\n";
        cout << "Maps: {";
        for (string const& map : monster.maps) {
            cout << "[" << map << "], ";
        }
        cout << "}\n";
        cout << "Modes: {";
        for (string const& mode : monster.modes) {
            cout << "[" << mode << "], ";
        }
        cout << "}\n";
        cout << "Monster skills: {";
        for (string const& monsterSkills : monster.monsterSkills) {
            cout << "[" << monsterSkills << "], ";
        }
        cout << "}\n";
        cout << "Drops with rates: {";
        for (NameAndRate const& dropWithRate : monster.dropsWithRates) {
            cout << "[" << dropWithRate.name << "," << dropWithRate.rate << "], ";
        }
        cout << "}\n";
    }
}

void RagnarokOnline::printMapNameToRoMap() const {
    for (auto const& mapNameToRoMap : m_mapNameToRoMap) {
        cout << "Map name: " << mapNameToRoMap.first << "\n";
        RoMap const& roMap(mapNameToRoMap.second);
        cout << "Map full name: " << roMap.fullName << "\n";
        cout << "Monsters: {";
        for (MonsterDetailsOnRoMap const& monsterDetailsOnMap : roMap.monstersDetailsOnMap) {
            cout << "[" << monsterDetailsOnMap.monsterName << "," << monsterDetailsOnMap.spawnCount << ","
                 << monsterDetailsOnMap.spawnRate << "], ";
        }
        cout << "}\n";
    }
}

void RagnarokOnline::printBuyingShopItems() const {
    cout.precision(20);
    for (auto const& shopItem : m_buyingShopItems) {
        cout << "Shop item name: " << shopItem.first << "\n";
        ShopItemDetail const& detail(shopItem.second);
        cout << "Average price: " << detail.averagePrice << "\n";
        cout << "Total number: " << detail.totalNumber << "\n";
    }
}

void RagnarokOnline::printSellingShopItems() const {
    cout.precision(20);
    for (auto const& shopItem : m_sellingShopItems) {
        cout << "Shop item name: " << shopItem.first << "\n";
        ShopItemDetail const& detail(shopItem.second);
        cout << "Average price: " << detail.averagePrice << "\n";
        cout << "Total number: " << detail.totalNumber << "\n";
    }
}

string RagnarokOnline::fixText(string const& text) {
    string fixedText(text);
    transformReplaceStringIfFound(fixedText, "<br>", " ");
    transformReplaceStringIfFound(fixedText, "&amp;", "&");
    transformReplaceStringIfFound(fixedText, "&nbsp;", " ");
    while (isStringFoundInsideTheOtherStringCaseSensitive(fixedText, "<") &&
           isStringFoundInsideTheOtherStringCaseSensitive(fixedText, ">")) {
        string htmlTag("<");
        htmlTag += getStringInBetweenTwoStrings(fixedText, "<", ">");
        htmlTag += ">";
        transformReplaceStringIfFound(fixedText, htmlTag, "");
    }
    return getStringWithoutStartingAndTrailingWhiteSpace(getStringWithoutRedundantWhiteSpace(fixedText));
}

ostream& operator<<(ostream& out, NameAndRate const& nameAndRate) {
    out.precision(20);
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(nameAndRate.name);
    writer.writeData<double>(nameAndRate.rate);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, MonsterDetailsOnRoMap const& monsterDetailsOnRoMap) {
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(monsterDetailsOnRoMap.monsterName);
    writer.writeData<unsigned int>(monsterDetailsOnRoMap.spawnCount);
    writer.writeData<string>(monsterDetailsOnRoMap.spawnRate);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, Item const& item) {
    AlbaStreamParameterWriter writer(out);
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
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, Monster const& monster) {
    AlbaStreamParameterWriter writer(out);
    writer.writeData<unsigned int>(monster.monsterId);
    writer.writeData<string>(monster.name);
    writer.writeData<unsigned int>(monster.hp);
    writer.writeData<unsigned int>(monster.level);
    writer.writeData<string>(monster.race);
    writer.writeData<string>(monster.property);
    writer.writeData<string>(monster.size);
    writer.writeData<unsigned int>(monster.hitRequiredFor100Percent);
    writer.writeData<unsigned int>(monster.fleeRequiredFor95Percent);
    writer.writeData<unsigned int>(monster.baseExperience);
    writer.writeData<unsigned int>(monster.jobExperience);
    writer.writeData<string>(monster.baseExperiencePerHp);
    writer.writeData<string>(monster.jobExperiencePerHp);
    writer.writeData<string>(monster.walkSpeed);
    writer.writeData<string>(monster.attackDelay);
    writer.writeData<string>(monster.delayAfterHit);
    writer.writeData<unsigned int>(monster.lowestAttack);
    writer.writeData<unsigned int>(monster.highestAttack);
    writer.writeData<unsigned int>(monster.defense);
    writer.writeData<unsigned int>(monster.magicDefense);
    writer.writeData<unsigned int>(monster.strength);
    writer.writeData<unsigned int>(monster.intelligence);
    writer.writeData<unsigned int>(monster.agility);
    writer.writeData<unsigned int>(monster.dexterity);
    writer.writeData<unsigned int>(monster.vitality);
    writer.writeData<unsigned int>(monster.luck);
    writer.writeData<unsigned int>(monster.attackRange);
    writer.writeData<unsigned int>(monster.spellRange);
    writer.writeData<unsigned int>(monster.sightRange);
    writer.writeData<int>(monster.neutralPercentage);
    writer.writeData<int>(monster.waterPercentage);
    writer.writeData<int>(monster.earthPercentage);
    writer.writeData<int>(monster.firePercentage);
    writer.writeData<int>(monster.windPercentage);
    writer.writeData<int>(monster.poisonPercentage);
    writer.writeData<int>(monster.holyPercentage);
    writer.writeData<int>(monster.shadowPercentage);
    writer.writeData<int>(monster.ghostPercentage);
    writer.writeData<int>(monster.undeadPercentage);
    writer.writeVectorData<string>(monster.maps);
    writer.writeVectorData<string>(monster.modes);
    writer.writeVectorData<string>(monster.monsterSkills);
    writer.writeVectorData<NameAndRate>(monster.dropsWithRates);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, ShopItemDetail const& shopItemDetail) {
    out.precision(20);
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(shopItemDetail.itemName);
    writer.writeData<double>(shopItemDetail.averagePrice);
    writer.writeData<unsigned int>(shopItemDetail.totalNumber);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, RoMap const& roMap) {
    AlbaStreamParameterWriter writer(out);
    writer.writeData<string>(roMap.name);
    writer.writeData<string>(roMap.fullName);
    writer.writeVectorData<MonsterDetailsOnRoMap>(roMap.monstersDetailsOnMap);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, ItemIdToItemMap const& itemIdToItemMap) {
    AlbaStreamParameterWriter writer(out);
    writer.writeMapData<unsigned int, Item>(itemIdToItemMap);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, MonsterIdToMonsterMap const& monsterIdToMonsterMap) {
    AlbaStreamParameterWriter writer(out);
    writer.writeMapData<unsigned int, Monster>(monsterIdToMonsterMap);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, MapNameToRoMap const& mapNameToRoMap) {
    AlbaStreamParameterWriter writer(out);
    writer.writeMapData<string, RoMap>(mapNameToRoMap);
    writer.flush();
    return out;
}

ostream& operator<<(ostream& out, ItemNameToShopItemDetailMap const& itemNameToShopItemDetailMap) {
    AlbaStreamParameterWriter writer(out);
    writer.writeMapData<string, ShopItemDetail>(itemNameToShopItemDetailMap);
    writer.flush();
    return out;
}

istream& operator>>(istream& in, NameAndRate& nameAndRate) {
    in.precision(20);
    AlbaStreamParameterReader reader(in);
    nameAndRate.name = reader.readData<string>();
    nameAndRate.rate = reader.readData<double>();
    return in;
}

istream& operator>>(istream& in, MonsterDetailsOnRoMap& monsterDetailsOnRoMap) {
    AlbaStreamParameterReader reader(in);
    monsterDetailsOnRoMap.monsterName = reader.readData<string>();
    monsterDetailsOnRoMap.spawnCount = reader.readData<unsigned int>();
    monsterDetailsOnRoMap.spawnRate = reader.readData<string>();
    return in;
}

istream& operator>>(istream& in, Item& item) {
    AlbaStreamParameterReader reader(in);
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

istream& operator>>(istream& in, Monster& monster) {
    AlbaStreamParameterReader reader(in);
    monster.monsterId = reader.readData<unsigned int>();
    monster.name = reader.readData<string>();
    monster.hp = reader.readData<unsigned int>();
    monster.level = reader.readData<unsigned int>();
    monster.race = reader.readData<string>();
    monster.property = reader.readData<string>();
    monster.size = reader.readData<string>();
    monster.hitRequiredFor100Percent = reader.readData<unsigned int>();
    monster.fleeRequiredFor95Percent = reader.readData<unsigned int>();
    monster.baseExperience = reader.readData<unsigned int>();
    monster.jobExperience = reader.readData<unsigned int>();
    monster.baseExperiencePerHp = reader.readData<string>();
    monster.jobExperiencePerHp = reader.readData<string>();
    monster.walkSpeed = reader.readData<string>();
    monster.attackDelay = reader.readData<string>();
    monster.delayAfterHit = reader.readData<string>();
    monster.lowestAttack = reader.readData<unsigned int>();
    monster.highestAttack = reader.readData<unsigned int>();
    monster.defense = reader.readData<unsigned int>();
    monster.magicDefense = reader.readData<unsigned int>();
    monster.strength = reader.readData<unsigned int>();
    monster.intelligence = reader.readData<unsigned int>();
    monster.agility = reader.readData<unsigned int>();
    monster.dexterity = reader.readData<unsigned int>();
    monster.vitality = reader.readData<unsigned int>();
    monster.luck = reader.readData<unsigned int>();
    monster.attackRange = reader.readData<unsigned int>();
    monster.spellRange = reader.readData<unsigned int>();
    monster.sightRange = reader.readData<unsigned int>();
    monster.neutralPercentage = reader.readData<int>();
    monster.waterPercentage = reader.readData<int>();
    monster.earthPercentage = reader.readData<int>();
    monster.firePercentage = reader.readData<int>();
    monster.windPercentage = reader.readData<int>();
    monster.poisonPercentage = reader.readData<int>();
    monster.holyPercentage = reader.readData<int>();
    monster.shadowPercentage = reader.readData<int>();
    monster.ghostPercentage = reader.readData<int>();
    monster.undeadPercentage = reader.readData<int>();
    reader.readVectorData<string>(monster.maps);
    reader.readVectorData<string>(monster.modes);
    reader.readVectorData<string>(monster.monsterSkills);
    reader.readVectorData<NameAndRate>(monster.dropsWithRates);
    return in;
}

istream& operator>>(istream& in, ShopItemDetail& shopItemDetail) {
    in.precision(20);
    AlbaStreamParameterReader reader(in);
    shopItemDetail.itemName = reader.readData<string>();
    shopItemDetail.averagePrice = reader.readData<double>();
    shopItemDetail.totalNumber = reader.readData<unsigned int>();
    return in;
}

istream& operator>>(istream& in, RoMap& roMap) {
    AlbaStreamParameterReader reader(in);
    roMap.name = reader.readData<string>();
    roMap.fullName = reader.readData<string>();
    reader.readVectorData<MonsterDetailsOnRoMap>(roMap.monstersDetailsOnMap);
    return in;
}

istream& operator>>(istream& in, ItemIdToItemMap& itemIdToItemMap) {
    AlbaStreamParameterReader reader(in);
    reader.readMapData<unsigned int, Item>(itemIdToItemMap);
    return in;
}

istream& operator>>(istream& in, MonsterIdToMonsterMap& monsterIdToMonsterMap) {
    AlbaStreamParameterReader reader(in);
    reader.readMapData<unsigned int, Monster>(monsterIdToMonsterMap);
    return in;
}

istream& operator>>(istream& in, MapNameToRoMap& mapNameToRoMap) {
    AlbaStreamParameterReader reader(in);
    reader.readMapData<string, RoMap>(mapNameToRoMap);
    return in;
}

istream& operator>>(istream& in, ItemNameToShopItemDetailMap& itemNameToShopItemDetailMap) {
    AlbaStreamParameterReader reader(in);
    reader.readMapData<string, ShopItemDetail>(itemNameToShopItemDetailMap);
    return in;
}

}  // namespace alba
