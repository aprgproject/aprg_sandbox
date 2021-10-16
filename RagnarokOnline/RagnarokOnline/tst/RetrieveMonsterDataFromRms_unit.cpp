#include <RagnarokOnline.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(RagnarokOnlineMonsterUpdateTest, DISABLED_RetrieveMonsterDataFromRmsWebPagesAndThenSaveTheData)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveMonsterDataFromRmsWebpages(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MonsterDatabaseTraversal\)");

    ragnarokOnline.saveMonsterIdToMonsterMapToFile(R"(C:\Users\detectivemark7\Desktop\RO\MonsterIdToMonsterMap.txt)");
}

TEST(RagnarokOnlineMonsterTest, ReadMonsterIdToMonsterMapFromFileWorks)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.readMonsterIdToMonsterMapFromFile(R"(C:\Users\detectivemark7\Desktop\RO\MonsterIdToMonsterMap.txt)");

    EXPECT_EQ(1238U, ragnarokOnline.getMonsterIdToMonsterMap().size());
}

TEST(RagnarokOnlineMonsterTest, RetrieveMonsterDataFromRmsWebPagesWorks)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveMonsterDataFromRmsWebpages(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MonsterDatabaseTraversal\)");

    EXPECT_EQ(1238U, ragnarokOnline.getMonsterIdToMonsterMap().size());
}

TEST(RagnarokOnlineMonsterTest, RetrieveMonsterDataFromRmsWebPageWorksWithExample1)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveMonsterDataFromRmsWebPage(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MonsterDatabaseTraversal\monsterWithLetter_a_pageNumber_1.html)");

    MonsterIdToMonsterMap const& monsterIdToMonsterMap(ragnarokOnline.getMonsterIdToMonsterMap());
    ASSERT_EQ(10U, monsterIdToMonsterMap.size());

    Monster const& monster1(monsterIdToMonsterMap.at(1713U));
    EXPECT_EQ(1713U, monster1.monsterId);
    EXPECT_EQ("Acidus", monster1.name);
    EXPECT_EQ(51112U, monster1.hp);
    EXPECT_EQ(80U, monster1.level);
    EXPECT_EQ("Dragon", monster1.race);
    EXPECT_EQ("Holy 2", monster1.property);
    EXPECT_EQ("Large", monster1.size);
    EXPECT_EQ(171U, monster1.hitRequiredFor100Percent);
    EXPECT_EQ(258U, monster1.fleeRequiredFor95Percent);
    EXPECT_EQ(28043U, monster1.baseExperience);
    EXPECT_EQ(8023U, monster1.jobExperience);
    EXPECT_EQ("0.549:1", monster1.baseExperiencePerHp);
    EXPECT_EQ("0.157:1", monster1.jobExperiencePerHp);
    EXPECT_EQ("Average", monster1.walkSpeed);
    EXPECT_EQ("1.01s", monster1.attackDelay);
    EXPECT_EQ("Short", monster1.delayAfterHit);
    EXPECT_EQ(1289U, monster1.lowestAttack);
    EXPECT_EQ(2109U, monster1.highestAttack);
    EXPECT_EQ(29U, monster1.defense);
    EXPECT_EQ(69U, monster1.magicDefense);
    EXPECT_EQ(1U, monster1.strength);
    EXPECT_EQ(135U, monster1.intelligence);
    EXPECT_EQ(71U, monster1.agility);
    EXPECT_EQ(103U, monster1.dexterity);
    EXPECT_EQ(55U, monster1.vitality);
    EXPECT_EQ(69U, monster1.luck);
    EXPECT_EQ(2U, monster1.attackRange);
    EXPECT_EQ(10U, monster1.spellRange);
    EXPECT_EQ(12U, monster1.sightRange);
    EXPECT_EQ(100, monster1.neutralPercentage);
    EXPECT_EQ(50, monster1.waterPercentage);
    EXPECT_EQ(50, monster1.earthPercentage);
    EXPECT_EQ(50, monster1.firePercentage);
    EXPECT_EQ(50, monster1.windPercentage);
    EXPECT_EQ(50, monster1.poisonPercentage);
    EXPECT_EQ(-25, monster1.holyPercentage);
    EXPECT_EQ(150, monster1.shadowPercentage);
    EXPECT_EQ(50, monster1.ghostPercentage);
    EXPECT_EQ(125, monster1.undeadPercentage);
    ASSERT_EQ(3U, monster1.maps.size());
    EXPECT_EQ("3@tower(10)", monster1.maps.at(0));
    EXPECT_EQ("abyss_02", monster1.maps.at(1));
    EXPECT_EQ("abyss_03", monster1.maps.at(2));
    ASSERT_EQ(4U, monster1.modes.size());
    EXPECT_EQ("Aggressive", monster1.modes.at(0));
    EXPECT_EQ("Cast Sensor (Idle)", monster1.modes.at(1));
    EXPECT_EQ("Change Target (Attack)", monster1.modes.at(2));
    EXPECT_EQ("Change Target (Chase)", monster1.modes.at(3));
    ASSERT_EQ(7U, monster1.monsterSkills.size());
    EXPECT_EQ("Magnum Break [Lv9]", monster1.monsterSkills.at(0));
    EXPECT_EQ("Fire Ball [Lv9]", monster1.monsterSkills.at(1));
    EXPECT_EQ("Teleportation [Lv1]", monster1.monsterSkills.at(2));
    EXPECT_EQ("Fire Pillar [Lv3]", monster1.monsterSkills.at(3));
    EXPECT_EQ("Defense disregard attack [Lv 1]", monster1.monsterSkills.at(4));
    EXPECT_EQ("Stun Attack [Lv 5]", monster1.monsterSkills.at(5));
    EXPECT_EQ("Fire Attribute Attack [Lv 6]", monster1.monsterSkills.at(6));
    ASSERT_EQ(8U, monster1.dropsWithRates.size());
    EXPECT_EQ("Orange", monster1.dropsWithRates.at(0).name);
    EXPECT_DOUBLE_EQ(51, monster1.dropsWithRates.at(0).rate);
    EXPECT_EQ("Dragon Canine", monster1.dropsWithRates.at(1).name);
    EXPECT_DOUBLE_EQ(40, monster1.dropsWithRates.at(1).rate);
    EXPECT_EQ("Dragon Scale", monster1.dropsWithRates.at(2).name);
    EXPECT_DOUBLE_EQ(35.89, monster1.dropsWithRates.at(2).rate);
    EXPECT_EQ("Inverse Scale", monster1.dropsWithRates.at(3).name);
    EXPECT_DOUBLE_EQ(0.1, monster1.dropsWithRates.at(3).rate);
    EXPECT_EQ("Stone Buckler [1]", monster1.dropsWithRates.at(4).name);
    EXPECT_DOUBLE_EQ(0.5, monster1.dropsWithRates.at(4).rate);
    EXPECT_EQ("Gold Acidus Card", monster1.dropsWithRates.at(5).name);
    EXPECT_DOUBLE_EQ(0.01, monster1.dropsWithRates.at(5).rate);
    EXPECT_EQ("Treasure Box", monster1.dropsWithRates.at(6).name);
    EXPECT_DOUBLE_EQ(0.05, monster1.dropsWithRates.at(6).rate);
    EXPECT_EQ("Yellow Bijou", monster1.dropsWithRates.at(7).name);
    EXPECT_DOUBLE_EQ(8, monster1.dropsWithRates.at(7).rate);
}

}
