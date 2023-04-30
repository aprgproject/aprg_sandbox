#include <RagnarokOnline.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(RagnarokOnlineItemUpdateTest, DISABLED_RetrieveItemDataFromRmsWebPagesAndThenSaveTheData) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveItemDataFromRmsWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\RMS\ItemDatabaseTraversal\)");

    ragnarokOnline.saveItemIdToItemMapToFile(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\ItemIdToItemMap.txt)");
}

TEST(RagnarokOnlineItemTest, ReadItemIdToItemMapFromFileWorks) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.readItemIdToItemMapFromFile(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\ItemIdToItemMap.txt)");

    EXPECT_EQ(6225U, ragnarokOnline.getItemIdToItemMap().size());
}
TEST(RagnarokOnlineItemTest, RetrieveItemDataFromRmsWebPagesWorks) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveItemDataFromRmsWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\RMS\ItemDatabaseTraversal\)");

    EXPECT_EQ(6225U, ragnarokOnline.getItemIdToItemMap().size());
}
TEST(RagnarokOnlineItemTest, RetrieveItemDataFromRmsWebPageWorksWithExample1) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveItemDataFromRmsWebPage(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\RMS\ItemDatabaseTraversal\itemWithLetter_a_pageNumber_1.html)");

    ItemIdToItemMap const& itemIdToItemMap(ragnarokOnline.getItemIdToItemMap());
    ASSERT_EQ(12U, itemIdToItemMap.size());
    Item const& item1(itemIdToItemMap.at(4140U));
    EXPECT_EQ(4140U, item1.itemId);
    EXPECT_EQ("Abysmal Knight Card", item1.name);    EXPECT_EQ("Card", item1.type);
    EXPECT_EQ("Weapon Card", item1.itemClass);
    EXPECT_EQ(20U, item1.buyingPrice);
    EXPECT_EQ(10U, item1.sellingPrice);
    EXPECT_EQ(1U, item1.weight);
    EXPECT_EQ(0U, item1.attack);
    EXPECT_EQ(0U, item1.defense);
    EXPECT_EQ(0U, item1.requiredLevel);
    EXPECT_EQ(0U, item1.weaponLevel);
    EXPECT_EQ(0U, item1.slot);
    EXPECT_EQ(0U, item1.range);
    EXPECT_TRUE(item1.property.empty());
    EXPECT_EQ("Liberation", item1.prefixOrSuffix);
    EXPECT_TRUE(item1.applicableJobs.empty());
    EXPECT_EQ("Increase damage on Boss monster by 25%.", item1.description);
    EXPECT_EQ("{ bonus2 bAddClass,Class_Boss,25; },{},{}", item1.itemScript);
    ASSERT_EQ(1U, item1.droppedByMonstersWithRates.size());
    EXPECT_EQ("Knight of Abyss / Abysmal Knight", item1.droppedByMonstersWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(0.01, item1.droppedByMonstersWithRates.at(0).rate);

    Item const& item2(itemIdToItemMap.at(5406U));
    EXPECT_EQ(5406U, item2.itemId);
    EXPECT_EQ("Academy Freshman Hat", item2.name);
    EXPECT_EQ("Armor", item2.type);
    EXPECT_EQ("Upper Headgear", item2.itemClass);
    EXPECT_EQ(0U, item2.buyingPrice);
    EXPECT_EQ(0U, item2.sellingPrice);
    EXPECT_EQ(50U, item2.weight);
    EXPECT_EQ(0U, item2.attack);
    EXPECT_EQ(2U, item2.defense);
    EXPECT_EQ(0U, item2.requiredLevel);
    EXPECT_EQ(0U, item2.weaponLevel);
    EXPECT_EQ(0U, item2.slot);
    EXPECT_EQ(0U, item2.range);
    EXPECT_TRUE(item2.property.empty());
    EXPECT_TRUE(item2.prefixOrSuffix.empty());
    ASSERT_EQ(1U, item2.applicableJobs.size());
    EXPECT_EQ("Every Job", item2.applicableJobs.at(0));
    EXPECT_EQ(
        "Academy Freshman Hat! If you wear this, you should greet all of members of academy. Max HP + 80, Max SP + 10",
        item2.description);
    EXPECT_EQ("{ bonus bMaxHP,80; bonus bMaxSP,10; },{},{}", item2.itemScript);
    EXPECT_TRUE(item2.droppedByMonstersWithRates.empty());

    Item const& item3(itemIdToItemMap.at(5407U));
    EXPECT_EQ(5407U, item3.itemId);
    EXPECT_EQ("Academy Completion Hat", item3.name);
    EXPECT_EQ("Armor", item3.type);
    EXPECT_EQ("Upper Headgear", item3.itemClass);
    EXPECT_EQ(0U, item3.buyingPrice);
    EXPECT_EQ(0U, item3.sellingPrice);
    EXPECT_EQ(20U, item3.weight);
    EXPECT_EQ(0U, item3.attack);
    EXPECT_EQ(2U, item3.defense);
    EXPECT_EQ(0U, item3.requiredLevel);
    EXPECT_EQ(0U, item3.weaponLevel);
    EXPECT_EQ(1U, item3.slot);
    EXPECT_EQ(0U, item3.range);
    EXPECT_TRUE(item3.property.empty());
    EXPECT_TRUE(item3.prefixOrSuffix.empty());
    ASSERT_EQ(1U, item3.applicableJobs.size());
    EXPECT_EQ("Every Job", item3.applicableJobs.at(0));
    EXPECT_EQ("You can get this after you finish 1 course in academy. Max SP + 30", item3.description);
    EXPECT_EQ("{ bonus bMaxSP,30; },{},{}", item3.itemScript);
    EXPECT_TRUE(item3.droppedByMonstersWithRates.empty());

    Item const& item4(itemIdToItemMap.at(6069U));
    EXPECT_EQ(6069U, item4.itemId);
    EXPECT_EQ("Abundance", item4.name);
    EXPECT_EQ("Miscellaneous", item4.type);
    EXPECT_EQ("n/a", item4.itemClass);
    EXPECT_EQ(10U, item4.buyingPrice);
    EXPECT_EQ(5U, item4.sellingPrice);
    EXPECT_EQ(1U, item4.weight);
    EXPECT_EQ(0U, item4.attack);
    EXPECT_EQ(0U, item4.defense);
    EXPECT_EQ(0U, item4.requiredLevel);
    EXPECT_EQ(0U, item4.weaponLevel);
    EXPECT_EQ(0U, item4.slot);
    EXPECT_EQ(0U, item4.range);
    EXPECT_TRUE(item4.property.empty());
    EXPECT_TRUE(item4.prefixOrSuffix.empty());
    EXPECT_TRUE(item4.applicableJobs.empty());
    EXPECT_EQ("Not Available [iRO Description] Not Available", item4.description);
    EXPECT_EQ("{},{},{}", item4.itemScript);
    EXPECT_TRUE(item4.droppedByMonstersWithRates.empty());

    Item const& item5(itemIdToItemMap.at(6269U));
    EXPECT_EQ(6269U, item5.itemId);
    EXPECT_EQ("A Master's Blush", item5.name);
    EXPECT_EQ("Miscellaneous", item5.type);
    EXPECT_EQ("n/a", item5.itemClass);
    EXPECT_EQ(0U, item5.buyingPrice);
    EXPECT_EQ(0U, item5.sellingPrice);
    EXPECT_EQ(0U, item5.weight);
    EXPECT_EQ(0U, item5.attack);
    EXPECT_EQ(0U, item5.defense);
    EXPECT_EQ(0U, item5.requiredLevel);
    EXPECT_EQ(0U, item5.weaponLevel);
    EXPECT_EQ(0U, item5.slot);
    EXPECT_EQ(0U, item5.range);
    EXPECT_TRUE(item5.property.empty());
    EXPECT_TRUE(item5.prefixOrSuffix.empty());
    EXPECT_TRUE(item5.applicableJobs.empty());
    EXPECT_EQ(
        "A legendary brush which is used by a Master of dark arts. People says it's made of the best ivory and hair of "
        "a god.",
        item5.description);
    EXPECT_EQ("{},{},{}", item5.itemScript);
    EXPECT_TRUE(item5.droppedByMonstersWithRates.empty());

    Item const& item6(itemIdToItemMap.at(6270U));
    EXPECT_EQ(6270U, item6.itemId);
    EXPECT_EQ("A Picture Of Minstrel Song", item6.name);
    EXPECT_EQ("Miscellaneous", item6.type);
    EXPECT_EQ("n/a", item6.itemClass);
    EXPECT_EQ(0U, item6.buyingPrice);
    EXPECT_EQ(0U, item6.sellingPrice);
    EXPECT_EQ(0U, item6.weight);
    EXPECT_EQ(0U, item6.attack);
    EXPECT_EQ(0U, item6.defense);
    EXPECT_EQ(0U, item6.requiredLevel);
    EXPECT_EQ(0U, item6.weaponLevel);
    EXPECT_EQ(0U, item6.slot);
    EXPECT_EQ(0U, item6.range);
    EXPECT_TRUE(item6.property.empty());
    EXPECT_TRUE(item6.prefixOrSuffix.empty());
    EXPECT_TRUE(item6.applicableJobs.empty());
    EXPECT_EQ(
        "A picture of Maestro Song that was taken in front of Thanatos tower. Written on the back is 'I want to have a "
        "Teddy Bear. I need 33?'.",
        item6.description);
    EXPECT_EQ("{},{},{}", item6.itemScript);
    EXPECT_TRUE(item6.droppedByMonstersWithRates.empty());

    Item const& item7(itemIdToItemMap.at(6274U));
    EXPECT_EQ(6274U, item7.itemId);
    EXPECT_EQ("A Piece Of Cloth Of A Saint", item7.name);
    EXPECT_EQ("Miscellaneous", item7.type);
    EXPECT_EQ("n/a", item7.itemClass);
    EXPECT_EQ(0U, item7.buyingPrice);
    EXPECT_EQ(0U, item7.sellingPrice);
    EXPECT_EQ(0U, item7.weight);
    EXPECT_EQ(0U, item7.attack);
    EXPECT_EQ(0U, item7.defense);
    EXPECT_EQ(0U, item7.requiredLevel);
    EXPECT_EQ(0U, item7.weaponLevel);
    EXPECT_EQ(0U, item7.slot);
    EXPECT_EQ(0U, item7.range);
    EXPECT_TRUE(item7.property.empty());
    EXPECT_TRUE(item7.prefixOrSuffix.empty());
    EXPECT_TRUE(item7.applicableJobs.empty());
    EXPECT_EQ("Traces of a cloth which has been worn by a Saint.", item7.description);
    EXPECT_EQ("{},{},{}", item7.itemScript);
    EXPECT_TRUE(item7.droppedByMonstersWithRates.empty());

    Item const& item8(itemIdToItemMap.at(13717U));
    EXPECT_EQ(13717U, item8.itemId);
    EXPECT_EQ("Abrasive 5 Box", item8.name);
    EXPECT_EQ("Cash Shop Item", item8.type);
    EXPECT_EQ("n/a", item8.itemClass);
    EXPECT_EQ(20U, item8.buyingPrice);
    EXPECT_EQ(10U, item8.sellingPrice);
    EXPECT_EQ(1U, item8.weight);
    EXPECT_EQ(0U, item8.attack);
    EXPECT_EQ(0U, item8.defense);
    EXPECT_EQ(0U, item8.requiredLevel);
    EXPECT_EQ(0U, item8.weaponLevel);
    EXPECT_EQ(0U, item8.slot);
    EXPECT_EQ(0U, item8.range);
    EXPECT_TRUE(item8.property.empty());
    EXPECT_TRUE(item8.prefixOrSuffix.empty());
    EXPECT_TRUE(item8.applicableJobs.empty());
    EXPECT_EQ(
        "A box containing 5 Abrasive. For 5 minutes, the player will receive +30 Critical Rate. This rate is doubled "
        "by Katar weapons. Once this item is purchased, termination of contract is impossible. Also, this item is not "
        "refundable.",
        item8.description);
    EXPECT_EQ("{ getitem 14536,5; },{},{}", item8.itemScript);
    EXPECT_TRUE(item8.droppedByMonstersWithRates.empty());

    Item const& item9(itemIdToItemMap.at(13718U));
    EXPECT_EQ(13718U, item9.itemId);
    EXPECT_EQ("Abrasive 10 Box", item9.name);
    EXPECT_EQ("Cash Shop Item", item9.type);
    EXPECT_EQ("n/a", item9.itemClass);
    EXPECT_EQ(20U, item9.buyingPrice);
    EXPECT_EQ(10U, item9.sellingPrice);
    EXPECT_EQ(1U, item9.weight);
    EXPECT_EQ(0U, item9.attack);
    EXPECT_EQ(0U, item9.defense);
    EXPECT_EQ(0U, item9.requiredLevel);
    EXPECT_EQ(0U, item9.weaponLevel);
    EXPECT_EQ(0U, item9.slot);
    EXPECT_EQ(0U, item9.range);
    EXPECT_TRUE(item9.property.empty());
    EXPECT_TRUE(item9.prefixOrSuffix.empty());
    EXPECT_TRUE(item9.applicableJobs.empty());
    EXPECT_EQ(
        "A box containing 10 Abrasive. For 5 minutes, the player will receive +30 Critical Rate. This rate is doubled "
        "by Katar weapons. Once this item is purchased, termination of contract is impossible. Also, this item is not "
        "refundable.",
        item9.description);
    EXPECT_EQ("{ getitem 14536,10; },{},{}", item9.itemScript);
    EXPECT_TRUE(item9.droppedByMonstersWithRates.empty());

    Item const& item10(itemIdToItemMap.at(14110U));
    EXPECT_EQ(14110U, item10.itemId);
    EXPECT_EQ("Abrasive 5 Box", item10.name);
    EXPECT_EQ("Cash Shop Item", item10.type);
    EXPECT_EQ("n/a", item10.itemClass);
    EXPECT_EQ(20U, item10.buyingPrice);
    EXPECT_EQ(10U, item10.sellingPrice);
    EXPECT_EQ(1U, item10.weight);
    EXPECT_EQ(0U, item10.attack);
    EXPECT_EQ(0U, item10.defense);
    EXPECT_EQ(0U, item10.requiredLevel);
    EXPECT_EQ(0U, item10.weaponLevel);
    EXPECT_EQ(0U, item10.slot);
    EXPECT_EQ(0U, item10.range);
    EXPECT_TRUE(item10.property.empty());
    EXPECT_TRUE(item10.prefixOrSuffix.empty());
    EXPECT_TRUE(item10.applicableJobs.empty());
    EXPECT_EQ(
        "A box containing 5 Abrasive. Once this item is purchased, termination of contract is impossible. Also, this "
        "item is not refundable.",
        item10.description);
    EXPECT_EQ("{ getitem 14536,5; },{},{}", item10.itemScript);
    EXPECT_TRUE(item10.droppedByMonstersWithRates.empty());

    Item const& item11(itemIdToItemMap.at(14111U));
    EXPECT_EQ(14111U, item11.itemId);
    EXPECT_EQ("Abrasive 10 Box", item11.name);
    EXPECT_EQ("Cash Shop Item", item11.type);
    EXPECT_EQ("n/a", item11.itemClass);
    EXPECT_EQ(20U, item11.buyingPrice);
    EXPECT_EQ(10U, item11.sellingPrice);
    EXPECT_EQ(1U, item11.weight);
    EXPECT_EQ(0U, item11.attack);
    EXPECT_EQ(0U, item11.defense);
    EXPECT_EQ(0U, item11.requiredLevel);
    EXPECT_EQ(0U, item11.weaponLevel);
    EXPECT_EQ(0U, item11.slot);
    EXPECT_EQ(0U, item11.range);
    EXPECT_TRUE(item11.property.empty());
    EXPECT_TRUE(item11.prefixOrSuffix.empty());
    EXPECT_TRUE(item11.applicableJobs.empty());
    EXPECT_EQ(
        "A box containing 10 Abrasive. Once this item is purchased, termination of contract is impossible. Also, this "
        "item is not refundable.",
        item11.description);
    EXPECT_EQ("{ getitem 14536,10; },{},{}", item11.itemScript);
    EXPECT_TRUE(item11.droppedByMonstersWithRates.empty());

    Item const& item12(itemIdToItemMap.at(14536U));
    EXPECT_EQ(14536U, item12.itemId);
    EXPECT_EQ("Abrasive", item12.name);
    EXPECT_EQ("Usable Item", item12.type);
    EXPECT_EQ("n/a", item12.itemClass);
    EXPECT_EQ(0U, item12.buyingPrice);
    EXPECT_EQ(0U, item12.sellingPrice);
    EXPECT_EQ(1U, item12.weight);
    EXPECT_EQ(0U, item12.attack);
    EXPECT_EQ(0U, item12.defense);
    EXPECT_EQ(0U, item12.requiredLevel);
    EXPECT_EQ(0U, item12.weaponLevel);
    EXPECT_EQ(0U, item12.slot);
    EXPECT_EQ(0U, item12.range);
    EXPECT_TRUE(item12.property.empty());
    EXPECT_TRUE(item12.prefixOrSuffix.empty());
    ASSERT_EQ(1U, item12.applicableJobs.size());
    EXPECT_EQ("Every Job", item12.applicableJobs.at(0));
    EXPECT_EQ(
        "An abrasive that adds sharpness to a weapon. For 5 minutes, the player will receive +30 Critical Rate. This "
        "rate is doubled by Katar weapons.",
        item12.description);
    EXPECT_EQ("{ specialeffect2 EF_MAGICALATTHIT; sc_start SC_INCCRI,300000,30; },{},{}", item12.itemScript);
    EXPECT_TRUE(item12.droppedByMonstersWithRates.empty());
}

TEST(RagnarokOnlineItemTest, RetrieveItemDataFromRmsWebPageWorksWithExample2) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveItemDataFromRmsWebPage(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\RMS\ItemDatabaseTraversal\itemWithLetter_z_pageNumber_1.html)");

    ItemIdToItemMap const& itemIdToItemMap(ragnarokOnline.getItemIdToItemMap());
    ASSERT_EQ(12U, itemIdToItemMap.size());
    Item const& item1(itemIdToItemMap.at(912U));
    EXPECT_EQ(912U, item1.itemId);
    EXPECT_EQ("Zargon", item1.name);    EXPECT_EQ("Miscellaneous", item1.type);
    EXPECT_EQ("n/a", item1.itemClass);
    EXPECT_EQ(480U, item1.buyingPrice);
    EXPECT_EQ(240U, item1.sellingPrice);
    EXPECT_EQ(1U, item1.weight);
    EXPECT_EQ(0U, item1.attack);
    EXPECT_EQ(0U, item1.defense);
    EXPECT_EQ(0U, item1.requiredLevel);
    EXPECT_EQ(0U, item1.weaponLevel);
    EXPECT_EQ(0U, item1.slot);
    EXPECT_EQ(0U, item1.range);
    EXPECT_TRUE(item1.property.empty());
    EXPECT_TRUE(item1.prefixOrSuffix.empty());
    EXPECT_TRUE(item1.applicableJobs.empty());
    EXPECT_EQ("A small crystallization created by some monsters.", item1.description);
    EXPECT_EQ("{},{},{}", item1.itemScript);
    ASSERT_EQ(61U, item1.droppedByMonstersWithRates.size());
    EXPECT_EQ("Centipede", item1.droppedByMonstersWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(50, item1.droppedByMonstersWithRates.at(0).rate);
    EXPECT_EQ("Centipede Larva", item1.droppedByMonstersWithRates.at(1).name);
    EXPECT_DOUBLE_EQ(50, item1.droppedByMonstersWithRates.at(1).rate);
    EXPECT_EQ("Deviling", item1.droppedByMonstersWithRates.at(2).name);
    EXPECT_DOUBLE_EQ(48.5, item1.droppedByMonstersWithRates.at(2).rate);
    EXPECT_EQ("Wind Ghost", item1.droppedByMonstersWithRates.at(3).name);
    EXPECT_DOUBLE_EQ(45.59, item1.droppedByMonstersWithRates.at(3).rate);
    EXPECT_EQ("Fur Seal / Seal", item1.droppedByMonstersWithRates.at(4).name);
    EXPECT_DOUBLE_EQ(43.65, item1.droppedByMonstersWithRates.at(4).rate);
    EXPECT_EQ("Karakasa", item1.droppedByMonstersWithRates.at(5).name);
    EXPECT_DOUBLE_EQ(40.74, item1.droppedByMonstersWithRates.at(5).rate);
    EXPECT_EQ("Gargoyle", item1.droppedByMonstersWithRates.at(6).name);
    EXPECT_DOUBLE_EQ(38.8, item1.droppedByMonstersWithRates.at(6).rate);
    EXPECT_EQ("Kraben", item1.droppedByMonstersWithRates.at(7).name);
    EXPECT_DOUBLE_EQ(35, item1.droppedByMonstersWithRates.at(7).rate);
    EXPECT_EQ("Mobster", item1.droppedByMonstersWithRates.at(8).name);
    EXPECT_DOUBLE_EQ(25, item1.droppedByMonstersWithRates.at(8).rate);
    EXPECT_EQ("Mini Demon", item1.droppedByMonstersWithRates.at(9).name);
    EXPECT_DOUBLE_EQ(25, item1.droppedByMonstersWithRates.at(9).rate);
    EXPECT_EQ("Rotar Zairo", item1.droppedByMonstersWithRates.at(10).name);
    EXPECT_DOUBLE_EQ(25, item1.droppedByMonstersWithRates.at(10).rate);
    EXPECT_EQ("Ancient Worm", item1.droppedByMonstersWithRates.at(11).name);
    EXPECT_DOUBLE_EQ(25, item1.droppedByMonstersWithRates.at(11).rate);
    EXPECT_EQ("Requiem", item1.droppedByMonstersWithRates.at(12).name);
    EXPECT_DOUBLE_EQ(25, item1.droppedByMonstersWithRates.at(12).rate);
    EXPECT_EQ("Gajomart", item1.droppedByMonstersWithRates.at(13).name);
    EXPECT_DOUBLE_EQ(23, item1.droppedByMonstersWithRates.at(13).rate);
    EXPECT_EQ("Joker", item1.droppedByMonstersWithRates.at(14).name);
    EXPECT_DOUBLE_EQ(20, item1.droppedByMonstersWithRates.at(14).rate);
    EXPECT_EQ("Banaspaty (Re-Stats)", item1.droppedByMonstersWithRates.at(15).name);
    EXPECT_DOUBLE_EQ(20, item1.droppedByMonstersWithRates.at(15).rate);
    EXPECT_EQ("Freezer", item1.droppedByMonstersWithRates.at(16).name);
    EXPECT_DOUBLE_EQ(18, item1.droppedByMonstersWithRates.at(16).rate);
    EXPECT_EQ("Heater", item1.droppedByMonstersWithRates.at(17).name);
    EXPECT_DOUBLE_EQ(16.4, item1.droppedByMonstersWithRates.at(17).rate);
    EXPECT_EQ("Petite", item1.droppedByMonstersWithRates.at(18).name);
    EXPECT_DOUBLE_EQ(15, item1.droppedByMonstersWithRates.at(18).rate);
    EXPECT_EQ("Deviruchi", item1.droppedByMonstersWithRates.at(19).name);
    EXPECT_DOUBLE_EQ(15, item1.droppedByMonstersWithRates.at(19).rate);
    EXPECT_EQ("Petite", item1.droppedByMonstersWithRates.at(20).name);
    EXPECT_DOUBLE_EQ(15, item1.droppedByMonstersWithRates.at(20).rate);
    EXPECT_EQ("Alarm", item1.droppedByMonstersWithRates.at(21).name);
    EXPECT_DOUBLE_EQ(15, item1.droppedByMonstersWithRates.at(21).rate);
    EXPECT_EQ("Myst Case", item1.droppedByMonstersWithRates.at(22).name);
    EXPECT_DOUBLE_EQ(15, item1.droppedByMonstersWithRates.at(22).rate);
    EXPECT_EQ("Side Winder", item1.droppedByMonstersWithRates.at(23).name);
    EXPECT_DOUBLE_EQ(14, item1.droppedByMonstersWithRates.at(23).rate);
    EXPECT_EQ("High Orc", item1.droppedByMonstersWithRates.at(24).name);
    EXPECT_DOUBLE_EQ(13, item1.droppedByMonstersWithRates.at(24).rate);
    EXPECT_EQ("Hunter Fly", item1.droppedByMonstersWithRates.at(25).name);
    EXPECT_DOUBLE_EQ(13, item1.droppedByMonstersWithRates.at(25).rate);
    EXPECT_EQ("Assaulter", item1.droppedByMonstersWithRates.at(26).name);
    EXPECT_DOUBLE_EQ(12.4, item1.droppedByMonstersWithRates.at(26).rate);
    EXPECT_EQ("Solider", item1.droppedByMonstersWithRates.at(27).name);
    EXPECT_DOUBLE_EQ(12.4, item1.droppedByMonstersWithRates.at(27).rate);
    EXPECT_EQ("Permeter", item1.droppedByMonstersWithRates.at(28).name);
    EXPECT_DOUBLE_EQ(12.4, item1.droppedByMonstersWithRates.at(28).rate);
    EXPECT_EQ("Argiope", item1.droppedByMonstersWithRates.at(29).name);
    EXPECT_DOUBLE_EQ(12, item1.droppedByMonstersWithRates.at(29).rate);
    EXPECT_EQ("Kobold Leader", item1.droppedByMonstersWithRates.at(30).name);
    EXPECT_DOUBLE_EQ(12, item1.droppedByMonstersWithRates.at(30).rate);
    EXPECT_EQ("Brilight", item1.droppedByMonstersWithRates.at(31).name);
    EXPECT_DOUBLE_EQ(12, item1.droppedByMonstersWithRates.at(31).rate);
    EXPECT_EQ("Alligator", item1.droppedByMonstersWithRates.at(32).name);
    EXPECT_DOUBLE_EQ(10, item1.droppedByMonstersWithRates.at(32).rate);
    EXPECT_EQ("Jakk", item1.droppedByMonstersWithRates.at(33).name);
    EXPECT_DOUBLE_EQ(9, item1.droppedByMonstersWithRates.at(33).rate);
    EXPECT_EQ("Christmas Jakk", item1.droppedByMonstersWithRates.at(34).name);
    EXPECT_DOUBLE_EQ(9, item1.droppedByMonstersWithRates.at(34).rate);
    EXPECT_EQ("Chepet", item1.droppedByMonstersWithRates.at(35).name);
    EXPECT_DOUBLE_EQ(7.5, item1.droppedByMonstersWithRates.at(35).rate);
    EXPECT_EQ("Sasquatch", item1.droppedByMonstersWithRates.at(36).name);
    EXPECT_DOUBLE_EQ(7.5, item1.droppedByMonstersWithRates.at(36).rate);
    EXPECT_EQ("Verit", item1.droppedByMonstersWithRates.at(37).name);
    EXPECT_DOUBLE_EQ(7, item1.droppedByMonstersWithRates.at(37).rate);
    EXPECT_EQ("Kobold", item1.droppedByMonstersWithRates.at(38).name);
    EXPECT_DOUBLE_EQ(7, item1.droppedByMonstersWithRates.at(38).rate);
    EXPECT_EQ("Nightmare Verit (Re-Stats)", item1.droppedByMonstersWithRates.at(39).name);
    EXPECT_DOUBLE_EQ(7, item1.droppedByMonstersWithRates.at(39).rate);
    EXPECT_EQ("Horong", item1.droppedByMonstersWithRates.at(40).name);
    EXPECT_DOUBLE_EQ(5, item1.droppedByMonstersWithRates.at(40).rate);
    EXPECT_EQ("Nightmare Arclouse (Re-Stats)", item1.droppedByMonstersWithRates.at(41).name);
    EXPECT_DOUBLE_EQ(5, item1.droppedByMonstersWithRates.at(41).rate);
    EXPECT_EQ("Arclouse / Arclouze", item1.droppedByMonstersWithRates.at(42).name);
    EXPECT_DOUBLE_EQ(4.5, item1.droppedByMonstersWithRates.at(42).rate);
    EXPECT_EQ("Abysmal Kobold / Dark Hammer Kobold (Re-Stats)", item1.droppedByMonstersWithRates.at(43).name);
    EXPECT_DOUBLE_EQ(3.5, item1.droppedByMonstersWithRates.at(43).rate);
    EXPECT_EQ("Abysmal Kobold / Dark Mace Kobold (Re-Stats)", item1.droppedByMonstersWithRates.at(44).name);
    EXPECT_DOUBLE_EQ(3.5, item1.droppedByMonstersWithRates.at(44).rate);
    EXPECT_EQ("Abysmal Kobold / Dark Axe Kobold (Re-Stats)", item1.droppedByMonstersWithRates.at(45).name);
    EXPECT_DOUBLE_EQ(3.5, item1.droppedByMonstersWithRates.at(45).rate);
    EXPECT_EQ("Kobold Archer", item1.droppedByMonstersWithRates.at(46).name);
    EXPECT_DOUBLE_EQ(2.5, item1.droppedByMonstersWithRates.at(46).rate);
    EXPECT_EQ("Golem", item1.droppedByMonstersWithRates.at(47).name);
    EXPECT_DOUBLE_EQ(2.2, item1.droppedByMonstersWithRates.at(47).rate);
    EXPECT_EQ("Kobold", item1.droppedByMonstersWithRates.at(48).name);
    EXPECT_DOUBLE_EQ(2, item1.droppedByMonstersWithRates.at(48).rate);
    EXPECT_EQ("Christmas Cookie", item1.droppedByMonstersWithRates.at(49).name);
    EXPECT_DOUBLE_EQ(2, item1.droppedByMonstersWithRates.at(49).rate);
    EXPECT_EQ("Kobold", item1.droppedByMonstersWithRates.at(50).name);
    EXPECT_DOUBLE_EQ(2, item1.droppedByMonstersWithRates.at(50).rate);
    EXPECT_EQ("Gullinbursti", item1.droppedByMonstersWithRates.at(51).name);
    EXPECT_DOUBLE_EQ(1.6, item1.droppedByMonstersWithRates.at(51).rate);
    EXPECT_EQ("Abysmal / Dark Kobold Archer (Re-Stats)", item1.droppedByMonstersWithRates.at(52).name);
    EXPECT_DOUBLE_EQ(1.25, item1.droppedByMonstersWithRates.at(52).rate);
    EXPECT_EQ("Frilldora", item1.droppedByMonstersWithRates.at(53).name);
    EXPECT_DOUBLE_EQ(1.2, item1.droppedByMonstersWithRates.at(53).rate);
    EXPECT_EQ("Megalith", item1.droppedByMonstersWithRates.at(54).name);
    EXPECT_DOUBLE_EQ(1, item1.droppedByMonstersWithRates.at(54).rate);
    EXPECT_EQ("Aster", item1.droppedByMonstersWithRates.at(55).name);
    EXPECT_DOUBLE_EQ(0.6, item1.droppedByMonstersWithRates.at(55).rate);
    EXPECT_EQ("Magnolia", item1.droppedByMonstersWithRates.at(56).name);
    EXPECT_DOUBLE_EQ(0.1, item1.droppedByMonstersWithRates.at(56).rate);
    EXPECT_EQ("Magnolia", item1.droppedByMonstersWithRates.at(57).name);
    EXPECT_DOUBLE_EQ(0.1, item1.droppedByMonstersWithRates.at(57).rate);
    EXPECT_EQ("Poison Spore", item1.droppedByMonstersWithRates.at(58).name);
    EXPECT_DOUBLE_EQ(0.05, item1.droppedByMonstersWithRates.at(58).rate);
    EXPECT_EQ("Poison Spore", item1.droppedByMonstersWithRates.at(59).name);
    EXPECT_DOUBLE_EQ(0.05, item1.droppedByMonstersWithRates.at(59).rate);
    EXPECT_EQ("Smokie", item1.droppedByMonstersWithRates.at(60).name);
    EXPECT_DOUBLE_EQ(0.05, item1.droppedByMonstersWithRates.at(60).rate);

    Item const& item2(itemIdToItemMap.at(1044U));
    EXPECT_EQ(1044U, item2.itemId);
    EXPECT_EQ("Zenorc's Fang", item2.name);
    EXPECT_EQ("Miscellaneous", item2.type);
    EXPECT_EQ("n/a", item2.itemClass);
    EXPECT_EQ(264U, item2.buyingPrice);
    EXPECT_EQ(132U, item2.sellingPrice);
    EXPECT_EQ(1U, item2.weight);
    EXPECT_EQ(0U, item2.attack);
    EXPECT_EQ(0U, item2.defense);
    EXPECT_EQ(0U, item2.requiredLevel);
    EXPECT_EQ(0U, item2.weaponLevel);
    EXPECT_EQ(0U, item2.slot);
    EXPECT_EQ(0U, item2.range);
    EXPECT_TRUE(item2.property.empty());
    EXPECT_TRUE(item2.prefixOrSuffix.empty());
    EXPECT_TRUE(item2.applicableJobs.empty());
    EXPECT_EQ("A cuspid pulled out of a cursed Orc's mouth.", item2.description);
    EXPECT_EQ("{},{},{}", item2.itemScript);
    ASSERT_EQ(1U, item2.droppedByMonstersWithRates.size());
    EXPECT_EQ("Zenorc", item2.droppedByMonstersWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(55, item2.droppedByMonstersWithRates.at(0).rate);

    Item const& item3(itemIdToItemMap.at(1238U));
    EXPECT_EQ(1238U, item3.itemId);
    EXPECT_EQ("Zeny Knife", item3.name);
    EXPECT_EQ("Weapon", item3.type);
    EXPECT_EQ("Dagger", item3.itemClass);
    EXPECT_EQ(20U, item3.buyingPrice);
    EXPECT_EQ(10U, item3.sellingPrice);
    EXPECT_EQ(120U, item3.weight);
    EXPECT_EQ(64U, item3.attack);
    EXPECT_EQ(0U, item3.defense);
    EXPECT_EQ(70U, item3.requiredLevel);
    EXPECT_EQ(3U, item3.weaponLevel);
    EXPECT_EQ(0U, item3.slot);
    EXPECT_EQ(0U, item3.range);
    EXPECT_TRUE(item3.property.empty());
    EXPECT_TRUE(item3.prefixOrSuffix.empty());
    ASSERT_EQ(17U, item3.applicableJobs.size());
    EXPECT_EQ("Swordman", item3.applicableJobs.at(0));
    EXPECT_EQ("Mage", item3.applicableJobs.at(1));
    EXPECT_EQ("Archer", item3.applicableJobs.at(2));
    EXPECT_EQ("Merchant", item3.applicableJobs.at(3));
    EXPECT_EQ("Thief", item3.applicableJobs.at(4));
    EXPECT_EQ("Knight", item3.applicableJobs.at(5));
    EXPECT_EQ("Wizard", item3.applicableJobs.at(6));
    EXPECT_EQ("Blacksmith", item3.applicableJobs.at(7));
    EXPECT_EQ("Hunter", item3.applicableJobs.at(8));
    EXPECT_EQ("Assassin", item3.applicableJobs.at(9));
    EXPECT_EQ("Crusader", item3.applicableJobs.at(10));
    EXPECT_EQ("Sage", item3.applicableJobs.at(11));
    EXPECT_EQ("Rogue", item3.applicableJobs.at(12));
    EXPECT_EQ("Alchemist", item3.applicableJobs.at(13));
    EXPECT_EQ("Bard / Dancer", item3.applicableJobs.at(14));
    EXPECT_EQ("Soul Linker", item3.applicableJobs.at(15));
    EXPECT_EQ("Ninja", item3.applicableJobs.at(16));
    EXPECT_EQ("A dagger that steals Zeny from monsters upon their defeat.", item3.description);
    EXPECT_EQ("{ bonus2 bGetZenyNum,100,40; },{},{}", item3.itemScript);
    ASSERT_EQ(1U, item3.droppedByMonstersWithRates.size());
    EXPECT_EQ("Treasure Chest", item3.droppedByMonstersWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(3.75, item3.droppedByMonstersWithRates.at(0).rate);

    Item const& item4(itemIdToItemMap.at(1468U));
    EXPECT_EQ(1468U, item4.itemId);
    EXPECT_EQ("Zephyrus", item4.name);
    EXPECT_EQ("Weapon", item4.type);
    EXPECT_EQ("Two-handed Spear", item4.itemClass);
    EXPECT_EQ(20U, item4.buyingPrice);
    EXPECT_EQ(10U, item4.sellingPrice);
    EXPECT_EQ(200U, item4.weight);
    EXPECT_EQ(170U, item4.attack);
    EXPECT_EQ(0U, item4.defense);
    EXPECT_EQ(48U, item4.requiredLevel);
    EXPECT_EQ(4U, item4.weaponLevel);
    EXPECT_EQ(0U, item4.slot);
    EXPECT_EQ(3U, item4.range);
    EXPECT_EQ("Wind", item4.property);
    EXPECT_TRUE(item4.prefixOrSuffix.empty());
    ASSERT_EQ(3U, item4.applicableJobs.size());
    EXPECT_EQ("Swordman", item4.applicableJobs.at(0));
    EXPECT_EQ("Knight", item4.applicableJobs.at(1));
    EXPECT_EQ("Crusader", item4.applicableJobs.at(2));
    EXPECT_EQ(
        "A spear imbued with the Wind Property. Add a 10% chance of auto casting Level 3 Thunder Storm on the enemy "
        "when attacking. Causes Silence effect to enemies by 2% chance.",
        item4.description);
    EXPECT_EQ(
        R"({ bonus bAtkEle,Ele_Wind; bonus2 bAddEff,Eff_Silence,200; bonus3 bAutoSpell,"MG_THUNDERSTORM",3,100; },{},{})",
        item4.itemScript);
    ASSERT_EQ(1U, item4.droppedByMonstersWithRates.size());
    EXPECT_EQ("Knight of Windstorm / Stormy Knight", item4.droppedByMonstersWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(1.5, item4.droppedByMonstersWithRates.at(0).rate);

    Item const& item5(itemIdToItemMap.at(1481U));
    EXPECT_EQ(1481U, item5.itemId);
    EXPECT_EQ("Zephyrus", item5.name);
    EXPECT_EQ("Weapon", item5.type);
    EXPECT_EQ("Two-handed Spear", item5.itemClass);
    EXPECT_EQ(20U, item5.buyingPrice);
    EXPECT_EQ(10U, item5.sellingPrice);
    EXPECT_EQ(200U, item5.weight);
    EXPECT_EQ(170U, item5.attack);
    EXPECT_EQ(0U, item5.defense);
    EXPECT_EQ(48U, item5.requiredLevel);
    EXPECT_EQ(4U, item5.weaponLevel);
    EXPECT_EQ(3U, item5.slot);
    EXPECT_EQ(3U, item5.range);
    EXPECT_EQ("Wind", item5.property);
    EXPECT_TRUE(item5.prefixOrSuffix.empty());
    ASSERT_EQ(3U, item5.applicableJobs.size());
    EXPECT_EQ("Swordman", item5.applicableJobs.at(0));
    EXPECT_EQ("Knight", item5.applicableJobs.at(1));
    EXPECT_EQ("Crusader", item5.applicableJobs.at(2));
    EXPECT_EQ(
        "A spear imbued with the Wind Property. Add a 10% chance of auto casting Level 3 Thunder Storm on the enemy "
        "when attacking. Causes Silence effect to enemies by 2% chance.",
        item5.description);
    EXPECT_EQ(
        R"({ bonus bAtkEle,Ele_Wind; bonus2 bAddEff,Eff_Silence,200; bonus3 bAutoSpell,"MG_THUNDERSTORM",3,100; },{},{})",
        item5.itemScript);
    EXPECT_TRUE(item5.droppedByMonstersWithRates.empty());

    Item const& item6(itemIdToItemMap.at(4096U));
    EXPECT_EQ(4096U, item6.itemId);
    EXPECT_EQ("Zenorc Card", item6.name);
    EXPECT_EQ("Card", item6.type);
    EXPECT_EQ("Weapon Card", item6.itemClass);
    EXPECT_EQ(20U, item6.buyingPrice);
    EXPECT_EQ(10U, item6.sellingPrice);
    EXPECT_EQ(1U, item6.weight);
    EXPECT_EQ(0U, item6.attack);
    EXPECT_EQ(0U, item6.defense);
    EXPECT_EQ(0U, item6.requiredLevel);
    EXPECT_EQ(0U, item6.weaponLevel);
    EXPECT_EQ(0U, item6.slot);
    EXPECT_EQ(0U, item6.range);
    EXPECT_TRUE(item6.property.empty());
    EXPECT_EQ("Venomer's", item6.prefixOrSuffix);
    EXPECT_TRUE(item6.applicableJobs.empty());
    EXPECT_EQ("Poison an enemy when you Attack (Success Chance 4%). ATK + 10", item6.description);
    EXPECT_EQ("{ bonus2 bAddEff,Eff_Poison,400; bonus bBaseAtk,10; },{},{}", item6.itemScript);
    ASSERT_EQ(1U, item6.droppedByMonstersWithRates.size());
    EXPECT_EQ("Zenorc", item6.droppedByMonstersWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(0.01, item6.droppedByMonstersWithRates.at(0).rate);

    Item const& item7(itemIdToItemMap.at(4277U));
    EXPECT_EQ(4277U, item7.itemId);
    EXPECT_EQ("Zealotus Card", item7.name);
    EXPECT_EQ("Card", item7.type);
    EXPECT_EQ("Shield Card", item7.itemClass);
    EXPECT_EQ(20U, item7.buyingPrice);
    EXPECT_EQ(10U, item7.sellingPrice);
    EXPECT_EQ(1U, item7.weight);
    EXPECT_EQ(0U, item7.attack);
    EXPECT_EQ(0U, item7.defense);
    EXPECT_EQ(0U, item7.requiredLevel);
    EXPECT_EQ(0U, item7.weaponLevel);
    EXPECT_EQ(0U, item7.slot);
    EXPECT_EQ(0U, item7.range);
    EXPECT_TRUE(item7.property.empty());
    EXPECT_EQ("Dominatrix", item7.prefixOrSuffix);
    EXPECT_TRUE(item7.applicableJobs.empty());
    EXPECT_EQ(
        "LUK + 2 Inflict 10% more damage with Throw Arrow and Musical Strike. [Injustice Card Combo] More Information "
        "on Combo:Injustice Card & Zealotus Card",
        item7.description);
    EXPECT_EQ(
        R"({ bonus bLuk,2; bonus2 bSkillAtk,"BA_MUSICALSTRIKE",10; bonus2 bSkillAtk,"DC_THROWARROW",10; },{},{})",
        item7.itemScript);
    ASSERT_EQ(1U, item7.droppedByMonstersWithRates.size());
    EXPECT_EQ("Zherlthsh / Zealotus", item7.droppedByMonstersWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(0.01, item7.droppedByMonstersWithRates.at(0).rate);

    Item const& item8(itemIdToItemMap.at(5464U));
    EXPECT_EQ(5464U, item8.itemId);
    EXPECT_EQ("Zaha Doll Hat", item8.name);
    EXPECT_EQ("Armor", item8.type);
    EXPECT_EQ("Upper Headgear", item8.itemClass);
    EXPECT_EQ(20U, item8.buyingPrice);
    EXPECT_EQ(10U, item8.sellingPrice);
    EXPECT_EQ(0U, item8.weight);
    EXPECT_EQ(0U, item8.attack);
    EXPECT_EQ(1U, item8.defense);
    EXPECT_EQ(0U, item8.requiredLevel);
    EXPECT_EQ(0U, item8.weaponLevel);
    EXPECT_EQ(0U, item8.slot);
    EXPECT_EQ(0U, item8.range);
    EXPECT_TRUE(item8.property.empty());
    EXPECT_TRUE(item8.prefixOrSuffix.empty());
    ASSERT_EQ(1U, item8.applicableJobs.size());
    EXPECT_EQ("Every Job", item8.applicableJobs.at(0));
    EXPECT_EQ(
        "Zaha doll hat which resembles angel of Zaha. It looks great on your head. INT + 2 Enables use of Level 3 "
        "Magnificat. Impossible to refine this item. (Select to show Renewal description for later added effect).",
        item8.description);
    EXPECT_EQ(R"({ bonus bInt,2; skill "PR_MAGNIFICAT", 3; },{},{})", item8.itemScript);
    EXPECT_TRUE(item8.droppedByMonstersWithRates.empty());

    Item const& item9(itemIdToItemMap.at(5121U));
    EXPECT_EQ(5121U, item9.itemId);
    EXPECT_EQ("Zealotus Mask", item9.name);
    EXPECT_EQ("Armor", item9.type);
    EXPECT_EQ("Upper & Middle Headgear", item9.itemClass);
    EXPECT_EQ(20U, item9.buyingPrice);
    EXPECT_EQ(10U, item9.sellingPrice);
    EXPECT_EQ(40U, item9.weight);
    EXPECT_EQ(0U, item9.attack);
    EXPECT_EQ(3U, item9.defense);
    EXPECT_EQ(70U, item9.requiredLevel);
    EXPECT_EQ(0U, item9.weaponLevel);
    EXPECT_EQ(0U, item9.slot);
    EXPECT_EQ(0U, item9.range);
    EXPECT_TRUE(item9.property.empty());
    EXPECT_TRUE(item9.prefixOrSuffix.empty());
    ASSERT_EQ(1U, item9.applicableJobs.size());
    EXPECT_EQ("Every Job except Novice", item9.applicableJobs.at(0));
    EXPECT_EQ(
        "This mask, which is symbolic of Zherlthsh, mistress of the Glast Heim Underground Prison, makes its wearer "
        "feel like looking down on normal human peons. Inflicts 5% more damage on DemiHuman monster. Reduce 5% of the "
        "damage taken from DemiHuman monster.",
        item9.description);
    EXPECT_EQ(
        R"({ bonus2 bAddRace,RC_DemiHuman,5; bonus2 bAddRace,RC_Player,5; bonus2 bSubRace,RC_DemiHuman,5; bonus2 bSubRace,RC_Player,5; },{},{})",
        item9.itemScript);
    EXPECT_TRUE(item9.droppedByMonstersWithRates.empty());

    Item const& item10(itemIdToItemMap.at(9026U));
    EXPECT_EQ(9026U, item10.itemId);
    EXPECT_EQ("Zealotus Egg", item10.name);
    EXPECT_EQ("Monster Egg", item10.type);
    EXPECT_EQ("n/a", item10.itemClass);
    EXPECT_EQ(20U, item10.buyingPrice);
    EXPECT_EQ(10U, item10.sellingPrice);
    EXPECT_EQ(0U, item10.weight);
    EXPECT_EQ(0U, item10.attack);
    EXPECT_EQ(0U, item10.defense);
    EXPECT_EQ(0U, item10.requiredLevel);
    EXPECT_EQ(0U, item10.weaponLevel);
    EXPECT_EQ(0U, item10.slot);
    EXPECT_EQ(0U, item10.range);
    EXPECT_TRUE(item10.property.empty());
    EXPECT_TRUE(item10.prefixOrSuffix.empty());
    EXPECT_TRUE(item10.applicableJobs.empty());
    EXPECT_EQ(
        "An egg in which a Zherlthsh Cute Pet rests. Can be hatched by using a Pet Incubator. Increases your magic "
        "attack power by 2%. Increases magical damage to the DemiHuman by 2%.",
        item10.description);
    EXPECT_EQ("{},{},{}", item10.itemScript);
    EXPECT_TRUE(item10.droppedByMonstersWithRates.empty());

    Item const& item11(itemIdToItemMap.at(13525U));
    EXPECT_EQ(13525U, item11.itemId);
    EXPECT_EQ("Zeny Pet Egg Scroll Box", item11.name);
    EXPECT_EQ("Cash Shop Item", item11.type);
    EXPECT_EQ("n/a", item11.itemClass);
    EXPECT_EQ(20U, item11.buyingPrice);
    EXPECT_EQ(10U, item11.sellingPrice);
    EXPECT_EQ(1U, item11.weight);
    EXPECT_EQ(0U, item11.attack);
    EXPECT_EQ(0U, item11.defense);
    EXPECT_EQ(0U, item11.requiredLevel);
    EXPECT_EQ(0U, item11.weaponLevel);
    EXPECT_EQ(0U, item11.slot);
    EXPECT_EQ(0U, item11.range);
    EXPECT_TRUE(item11.property.empty());
    EXPECT_TRUE(item11.prefixOrSuffix.empty());
    EXPECT_TRUE(item11.applicableJobs.empty());
    EXPECT_EQ(
        "A box containing 1 Zeny Pet Egg Scroll. Once this item is purchased, termination of contract is impossible. "
        "Also, this item is not refundable.",
        item11.description);
    EXPECT_EQ("{ getitem 14508,1; },{},{}", item11.itemScript);
    EXPECT_TRUE(item11.droppedByMonstersWithRates.empty());

    Item const& item12(itemIdToItemMap.at(14508U));
    EXPECT_EQ(14508U, item12.itemId);
    EXPECT_EQ("Zeny Pet Egg Scroll", item12.name);
    EXPECT_EQ("Usable Item", item12.type);
    EXPECT_EQ("n/a", item12.itemClass);
    EXPECT_EQ(0U, item12.buyingPrice);
    EXPECT_EQ(0U, item12.sellingPrice);
    EXPECT_EQ(1U, item12.weight);
    EXPECT_EQ(0U, item12.attack);
    EXPECT_EQ(0U, item12.defense);
    EXPECT_EQ(0U, item12.requiredLevel);
    EXPECT_EQ(0U, item12.weaponLevel);
    EXPECT_EQ(0U, item12.slot);
    EXPECT_EQ(0U, item12.range);
    EXPECT_TRUE(item12.property.empty());
    EXPECT_TRUE(item12.prefixOrSuffix.empty());
    ASSERT_EQ(1U, item12.applicableJobs.size());
    EXPECT_EQ("Every Job", item12.applicableJobs.at(0));
    EXPECT_EQ("A scroll which gives you a random of amount zeny.", item12.description);
    EXPECT_EQ("{},{},{}", item12.itemScript);
    EXPECT_TRUE(item12.droppedByMonstersWithRates.empty());
}

}  // namespace alba
