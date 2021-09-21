#include <RagnarokOnline.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(RagnarokOnlineTest, DISABLED_RetrieveMapDataFromRmsWebPagesAndThenSaveTheData)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveMapDataFromRmsWebpages(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MapDatabaseTraversal\)");

    ragnarokOnline.saveMapNameToRoMapToFile(R"(C:\Users\detectivemark7\Desktop\RO\MapNameToRoMap.txt)");
}

TEST(RagnarokOnlineTest, ReadMapNameToRoMapFromFileWorks)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.readMapNameToRoMapFromFile(R"(C:\Users\detectivemark7\Desktop\RO\MapNameToRoMap.txt)");

    EXPECT_EQ(316U, ragnarokOnline.getMapNameToRoMap().size());
}

TEST(RagnarokOnlineTest, RetrieveMapDataFromRmsWebPagesWorks)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveMapDataFromRmsWebpages(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MapDatabaseTraversal\)");

    EXPECT_EQ(316U, ragnarokOnline.getMapNameToRoMap().size());
}

TEST(RagnarokOnlineTest, RetrieveMapDataFromRmsWebPageWorksWithExample1)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveMapDataFromRmsWebPage(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MapDatabaseTraversal\areaNumber_1001.html)");

    MapNameToRoMap const& mapNameToRoMap(ragnarokOnline.getMapNameToRoMap());
    ASSERT_EQ(4U, mapNameToRoMap.size());

    RoMap const& roMap1(mapNameToRoMap.at("abyss_01"));
    EXPECT_EQ("abyss_01", roMap1.name);
    EXPECT_EQ("Area: Abyss Lake Dungeon - Abyss Lakes Underground Cave F1", roMap1.fullName);
    ASSERT_EQ(11U, roMap1.monstersDetailsOnMap.size());
    EXPECT_EQ("Mimic", roMap1.monstersDetailsOnMap.at(0).monsterName);
    EXPECT_EQ(10U, roMap1.monstersDetailsOnMap.at(0).spawnCount);
    EXPECT_EQ("10 min", roMap1.monstersDetailsOnMap.at(0).spawnRate);
    EXPECT_EQ("Penomena", roMap1.monstersDetailsOnMap.at(1).monsterName);
    EXPECT_EQ(15U, roMap1.monstersDetailsOnMap.at(1).spawnCount);
    EXPECT_EQ("11~16 min", roMap1.monstersDetailsOnMap.at(1).spawnRate);
    EXPECT_EQ("Penomena", roMap1.monstersDetailsOnMap.at(2).monsterName);
    EXPECT_EQ(5U, roMap1.monstersDetailsOnMap.at(2).spawnCount);
    EXPECT_EQ("12~17 min", roMap1.monstersDetailsOnMap.at(2).spawnRate);
    EXPECT_EQ("Penomena", roMap1.monstersDetailsOnMap.at(3).monsterName);
    EXPECT_EQ(10U, roMap1.monstersDetailsOnMap.at(3).spawnCount);
    EXPECT_EQ("13~18 min", roMap1.monstersDetailsOnMap.at(3).spawnRate);
    EXPECT_EQ("Ancient Mimic", roMap1.monstersDetailsOnMap.at(4).monsterName);
    EXPECT_EQ(10U, roMap1.monstersDetailsOnMap.at(4).spawnCount);
    EXPECT_EQ("10 min", roMap1.monstersDetailsOnMap.at(4).spawnRate);
    EXPECT_EQ("Ferus", roMap1.monstersDetailsOnMap.at(5).monsterName);
    EXPECT_EQ(30U, roMap1.monstersDetailsOnMap.at(5).spawnCount);
    EXPECT_TRUE(roMap1.monstersDetailsOnMap.at(5).spawnRate.empty());
    EXPECT_EQ("Novus", roMap1.monstersDetailsOnMap.at(6).monsterName);
    EXPECT_EQ(9U, roMap1.monstersDetailsOnMap.at(6).spawnCount);
    EXPECT_TRUE(roMap1.monstersDetailsOnMap.at(6).spawnRate.empty());
    EXPECT_EQ("Ferus", roMap1.monstersDetailsOnMap.at(7).monsterName);
    EXPECT_EQ(55U, roMap1.monstersDetailsOnMap.at(7).spawnCount);
    EXPECT_EQ("5 min", roMap1.monstersDetailsOnMap.at(7).spawnRate);
    EXPECT_EQ("Novus", roMap1.monstersDetailsOnMap.at(8).monsterName);
    EXPECT_EQ(9U, roMap1.monstersDetailsOnMap.at(8).spawnCount);
    EXPECT_TRUE(roMap1.monstersDetailsOnMap.at(8).spawnRate.empty());
    EXPECT_EQ("Dragon Egg", roMap1.monstersDetailsOnMap.at(9).monsterName);
    EXPECT_EQ(3U, roMap1.monstersDetailsOnMap.at(9).spawnCount);
    EXPECT_EQ("20~30 min", roMap1.monstersDetailsOnMap.at(9).spawnRate);
    EXPECT_EQ("Dragon Egg", roMap1.monstersDetailsOnMap.at(10).monsterName);
    EXPECT_EQ(5U, roMap1.monstersDetailsOnMap.at(10).spawnCount);
    EXPECT_EQ("30~40 min", roMap1.monstersDetailsOnMap.at(10).spawnRate);
}

TEST(RagnarokOnlineTest, RetrieveMapDataFromRmsWebPageWorksWithExample2)
{
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveMapDataFromRmsWebPage(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MapDatabaseTraversal\areaNumber_2001.html)");

    MapNameToRoMap const& mapNameToRoMap(ragnarokOnline.getMapNameToRoMap());
    ASSERT_EQ(9U, mapNameToRoMap.size());

    RoMap const& roMap1(mapNameToRoMap.at("cmd_fild01"));
    EXPECT_EQ("cmd_fild01", roMap1.name);
    EXPECT_EQ("Area: Comodo Field - Papuchicha Forest", roMap1.fullName);
    ASSERT_EQ(7U, roMap1.monstersDetailsOnMap.size());
    EXPECT_EQ("Poporing", roMap1.monstersDetailsOnMap.at(0).monsterName);
    EXPECT_EQ(30U, roMap1.monstersDetailsOnMap.at(0).spawnCount);
    EXPECT_TRUE(roMap1.monstersDetailsOnMap.at(0).spawnRate.empty());
    EXPECT_EQ("Poison Spore", roMap1.monstersDetailsOnMap.at(1).monsterName);
    EXPECT_EQ(20U, roMap1.monstersDetailsOnMap.at(1).spawnCount);
    EXPECT_TRUE(roMap1.monstersDetailsOnMap.at(1).spawnRate.empty());
    EXPECT_EQ("Blue Plant", roMap1.monstersDetailsOnMap.at(2).monsterName);
    EXPECT_EQ(6U, roMap1.monstersDetailsOnMap.at(2).spawnCount);
    EXPECT_EQ("30~45 min", roMap1.monstersDetailsOnMap.at(2).spawnRate);
    EXPECT_EQ("Green Plant", roMap1.monstersDetailsOnMap.at(3).monsterName);
    EXPECT_EQ(5U, roMap1.monstersDetailsOnMap.at(3).spawnCount);
    EXPECT_EQ("30~45 min", roMap1.monstersDetailsOnMap.at(3).spawnRate);
    EXPECT_EQ("Shining Plant", roMap1.monstersDetailsOnMap.at(4).monsterName);
    EXPECT_EQ(1U, roMap1.monstersDetailsOnMap.at(4).spawnCount);
    EXPECT_EQ("30~45 min", roMap1.monstersDetailsOnMap.at(4).spawnRate);
    EXPECT_EQ("Savage", roMap1.monstersDetailsOnMap.at(5).monsterName);
    EXPECT_EQ(30U, roMap1.monstersDetailsOnMap.at(5).spawnCount);
    EXPECT_TRUE(roMap1.monstersDetailsOnMap.at(5).spawnRate.empty());
    EXPECT_EQ("Alligator", roMap1.monstersDetailsOnMap.at(6).monsterName);
    EXPECT_EQ(60U, roMap1.monstersDetailsOnMap.at(6).spawnCount);
    EXPECT_TRUE(roMap1.monstersDetailsOnMap.at(6).spawnRate.empty());
}

}
