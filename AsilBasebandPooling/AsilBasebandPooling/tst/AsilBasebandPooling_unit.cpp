#include <AsilBasebandPooling.hpp>
#include <User/DisplayTable.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;
namespace alba
{
TEST(KeplerTest, KeplerWorksCorrectly)
{
    Kepler kepler1(0x1450);
    Kepler kepler2(0x1460);

    EXPECT_TRUE(kepler1.operator<(kepler2));
    EXPECT_FALSE(kepler2.operator<(kepler1));
    EXPECT_EQ(0x1450, kepler1.getNid());
}

TEST(BasebandCardTest, BasebandCardWorksCorrectly)
{
    BasebandCard basebandCard1(0x12, {0x1230, 0x1240});
    BasebandCard basebandCard2(0x14, {0x1430, 0x1440, 0x1450, 0x1460});

    EXPECT_TRUE(basebandCard1.operator<(basebandCard2));
    EXPECT_FALSE(basebandCard2.operator<(basebandCard1));

    EXPECT_EQ(0x12, basebandCard1.getBoardId());

    SetOfKeplers keplersInBasebandCard1(basebandCard1.getKeplers());
    ASSERT_EQ(2U, keplersInBasebandCard1.size());
    SetOfKeplers::iterator iteratorToTraverse(keplersInBasebandCard1.cbegin());
    EXPECT_EQ(0x1230U, iteratorToTraverse++->getNid());
    EXPECT_EQ(0x1240U, iteratorToTraverse++->getNid());
}

TEST(BasebandCardTest, LcgWorksCorrectly){
    Lcg lcg1(1, 40);
    Lcg lcg2(2, 60);
    EXPECT_TRUE(lcg1.operator<(lcg2));
    EXPECT_FALSE(lcg2.operator<(lcg1));

    EXPECT_EQ(1, lcg1.getLcgId());
    EXPECT_EQ(40, lcg1.getPercentageShare());
}

TEST(AsilBasebandPoolingTest, AreLcgAndBasebandCardsValidIsCorrect)
{
    EXPECT_FALSE(AsilBasebandPooling(
    {Lcg(1, 40), Lcg(2, 60)},
    {BasebandCard(0x12, {0x1230, 0x1240})})
                 .areLcgAndBasebandCardsValid());

    EXPECT_TRUE(AsilBasebandPooling(
    {Lcg(1, 40), Lcg(2, 60)},
    {BasebandCard(0x12, {0x1230, 0x1240, 0x1250, 0x1260})})
                .areLcgAndBasebandCardsValid());

    EXPECT_TRUE(AsilBasebandPooling(
    {Lcg(1, 40), Lcg(2, 60)},
    {BasebandCard(0x12, {0x1230, 0x1240}), BasebandCard(0x13, {0x1330, 0x1340})})
                .areLcgAndBasebandCardsValid());
}

TEST(AsilBasebandPoolingTest, CanMultipleLcgsBePutOnBasebandCardIsCorrect)
{
    AsilBasebandPooling pooling;
    BasebandCard basebandCardWith1Kepler(0x12, {0x1230});
    BasebandCard basebandCardWith2Keplers(0x12, {0x1230, 0x1240});
    BasebandCard basebandCardWith3Keplers(0x12, {0x1230, 0x1240, 0x1250});
    BasebandCard basebandCardWith4Keplers(0x12, {0x1230, 0x1240, 0x1250, 0x1260});

    EXPECT_FALSE(pooling.canMultipleLcgsBePutOnBasebandCard(basebandCardWith1Kepler));
    EXPECT_FALSE(pooling.canMultipleLcgsBePutOnBasebandCard(basebandCardWith2Keplers));
    EXPECT_FALSE(pooling.canMultipleLcgsBePutOnBasebandCard(basebandCardWith3Keplers));
    EXPECT_TRUE(pooling.canMultipleLcgsBePutOnBasebandCard(basebandCardWith4Keplers));
}

TEST(AsilBasebandPoolingTest, GetNumberBasebandCardsWithMultipleLcgsIsCorrect)
{
    EXPECT_EQ(1U, AsilBasebandPooling(
    {Lcg(1, 50), Lcg(2, 50)},
    {BasebandCard(0x12, {0x1230, 0x1240})})
              .getNumberBasebandCardsWithMultipleLcgs());

    EXPECT_EQ(0U, AsilBasebandPooling(
    {Lcg(1, 50), Lcg(2, 50)},
    {BasebandCard(0x12, {0x1230, 0x1240}), BasebandCard(0x13, {0x1330, 0x1340})})
              .getNumberBasebandCardsWithMultipleLcgs());}

TEST(AsilBasebandPoolingTest, GetMaxNumberOfLcgsInBasebandCardIsCorrect)
{    AsilBasebandPooling pooling;
    BasebandCard basebandCardWith1Kepler(0x12, {0x1230});
    BasebandCard basebandCardWith2Keplers(0x12, {0x1230, 0x1240});
    BasebandCard basebandCardWith3Keplers(0x12, {0x1230, 0x1240, 0x1250});
    BasebandCard basebandCardWith4Keplers(0x12, {0x1230, 0x1240, 0x1250, 0x1260});

    EXPECT_EQ(0U, pooling.getMaxNumberOfLcgsInBasebandCard(basebandCardWith1Kepler));
    EXPECT_EQ(1U, pooling.getMaxNumberOfLcgsInBasebandCard(basebandCardWith2Keplers));
    EXPECT_EQ(1U, pooling.getMaxNumberOfLcgsInBasebandCard(basebandCardWith3Keplers));
    EXPECT_EQ(2U, pooling.getMaxNumberOfLcgsInBasebandCard(basebandCardWith4Keplers));
}

TEST(AsilBasebandPoolingTest, GetMaxNumberOfLcgsInAllBasebandCardsIsCorrect)
{
    EXPECT_EQ(1U, AsilBasebandPooling(
    {Lcg(1, 100)},
    {BasebandCard(0x12, {0x1230, 0x1240})})
              .getMaxNumberOfLcgsInAllBasebandCards());

    EXPECT_EQ(2U, AsilBasebandPooling(
    {Lcg(1, 100)},
    {BasebandCard(0x12, {0x1230, 0x1240}), BasebandCard(0x13, {0x1330, 0x1340})})
              .getMaxNumberOfLcgsInAllBasebandCards());}

TEST(AsilBasebandPoolingTest, GetLcgsInPriorityOrderIsCorrect)
{    AsilBasebandPooling pooling(
    {Lcg(1, 10), Lcg(2, 25), Lcg(3, 40), Lcg(4, 25)},
    {BasebandCard(0x12, {0x1230, 0x1240})});

    VectorOfLcgs lcgs(pooling.getLcgsInPriorityOrder());
    ASSERT_EQ(4U, lcgs.size());
    EXPECT_EQ(3U, lcgs[0].getLcgId());
    EXPECT_EQ(2U, lcgs[1].getLcgId());
    EXPECT_EQ(4U, lcgs[2].getLcgId());
    EXPECT_EQ(1U, lcgs[3].getLcgId());
}

TEST(AsilBasebandPoolingTest, GetBasebandCardsBasedOnNumberOfLcgsIsCorrect){
    AsilBasebandPooling pooling(
    {Lcg(1, 100)},
    {BasebandCard(0x11, {0x1130, 0x1140}),     BasebandCard(0x12, {0x1230, 0x1240, 0x1250}),
     BasebandCard(0x13, {0x1330, 0x1340, 0x1350, 0x1360}),
     BasebandCard(0x14, {0x1430, 0x1440, 0x1450, 0x1460, 0x1470}),
     BasebandCard(0x15, {0x1530, 0x1540, 0x1550, 0x1560}),
     BasebandCard(0x16, {0x1630, 0x1640}),
     BasebandCard(0x17, {0x1730})});

    BasebandCardsSplitBasedOnNumberOfLcgs basebandCardsWith0MultipleLcgs(pooling.getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(0));
    ASSERT_EQ(7U, basebandCardsWith0MultipleLcgs.basebandCardsWithOneLcg.size());
    SetOfBasebandCards::const_iterator iteratorToTraverse = basebandCardsWith0MultipleLcgs.basebandCardsWithOneLcg.cbegin();
    EXPECT_EQ(0x11, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x12, iteratorToTraverse++->getBoardId());    EXPECT_EQ(0x13, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x14, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x15, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x16, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x17, iteratorToTraverse++->getBoardId());
    ASSERT_EQ(0U, basebandCardsWith0MultipleLcgs.basebandCardsWithMultipleLcgs.size());

    BasebandCardsSplitBasedOnNumberOfLcgs basebandCardsWith1MultipleLcgs(pooling.getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(1));
    ASSERT_EQ(6U, basebandCardsWith1MultipleLcgs.basebandCardsWithOneLcg.size());
    iteratorToTraverse = basebandCardsWith1MultipleLcgs.basebandCardsWithOneLcg.cbegin();
    EXPECT_EQ(0x11, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x12, iteratorToTraverse++->getBoardId());    EXPECT_EQ(0x13, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x14, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x16, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x17, iteratorToTraverse++->getBoardId());
    ASSERT_EQ(1U, basebandCardsWith1MultipleLcgs.basebandCardsWithMultipleLcgs.size());
    iteratorToTraverse = basebandCardsWith1MultipleLcgs.basebandCardsWithMultipleLcgs.cbegin();
    EXPECT_EQ(0x15, iteratorToTraverse++->getBoardId());

    BasebandCardsSplitBasedOnNumberOfLcgs basebandCardsWith2MultipleLcgs(pooling.getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(2));
    ASSERT_EQ(5U, basebandCardsWith2MultipleLcgs.basebandCardsWithOneLcg.size());
    iteratorToTraverse = basebandCardsWith2MultipleLcgs.basebandCardsWithOneLcg.cbegin();
    EXPECT_EQ(0x11, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x12, iteratorToTraverse++->getBoardId());    EXPECT_EQ(0x13, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x16, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x17, iteratorToTraverse++->getBoardId());
    ASSERT_EQ(2U, basebandCardsWith2MultipleLcgs.basebandCardsWithMultipleLcgs.size());
    iteratorToTraverse = basebandCardsWith2MultipleLcgs.basebandCardsWithMultipleLcgs.cbegin();
    EXPECT_EQ(0x14, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x15, iteratorToTraverse++->getBoardId());

    BasebandCardsSplitBasedOnNumberOfLcgs basebandCardsWith3MultipleLcgs(pooling.getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(3));
    ASSERT_EQ(4U, basebandCardsWith3MultipleLcgs.basebandCardsWithOneLcg.size());
    iteratorToTraverse = basebandCardsWith3MultipleLcgs.basebandCardsWithOneLcg.cbegin();
    EXPECT_EQ(0x11, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x12, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x16, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x17, iteratorToTraverse++->getBoardId());
    ASSERT_EQ(3U, basebandCardsWith3MultipleLcgs.basebandCardsWithMultipleLcgs.size());
    iteratorToTraverse = basebandCardsWith3MultipleLcgs.basebandCardsWithMultipleLcgs.cbegin();
    EXPECT_EQ(0x13, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x14, iteratorToTraverse++->getBoardId());    EXPECT_EQ(0x15, iteratorToTraverse++->getBoardId());

    BasebandCardsSplitBasedOnNumberOfLcgs basebandCardsWith4MultipleLcgs(pooling.getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(4));
    ASSERT_EQ(4U, basebandCardsWith4MultipleLcgs.basebandCardsWithOneLcg.size());
    iteratorToTraverse = basebandCardsWith4MultipleLcgs.basebandCardsWithOneLcg.cbegin();
    EXPECT_EQ(0x11, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x12, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x16, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x17, iteratorToTraverse++->getBoardId());
    ASSERT_EQ(3U, basebandCardsWith4MultipleLcgs.basebandCardsWithMultipleLcgs.size());
    iteratorToTraverse = basebandCardsWith4MultipleLcgs.basebandCardsWithMultipleLcgs.cbegin();
    EXPECT_EQ(0x13, iteratorToTraverse++->getBoardId());
    EXPECT_EQ(0x14, iteratorToTraverse++->getBoardId());    EXPECT_EQ(0x15, iteratorToTraverse++->getBoardId());
}

TEST(AsilBasebandPoolingTest, SortAndPrioritizeBasebandCardsIsCorrect){
    AsilBasebandPooling pooling;
    VectorOfBasebandCards basebandCards
    {BasebandCard(0x11, {0x1130, 0x1140}),
                BasebandCard(0x12, {0x1230, 0x1240, 0x1250}),
                BasebandCard(0x13, {0x1330, 0x1340, 0x1350, 0x1360}),
                BasebandCard(0x14, {0x1430, 0x1440, 0x1450, 0x1460, 0x1470}),
                BasebandCard(0x15, {0x1530, 0x1540, 0x1550, 0x1560}),
                BasebandCard(0x16, {0x1630, 0x1640}),
                BasebandCard(0x17, {0x1730})};

    pooling.sortAndPrioritizeBasebandCards(basebandCards);

    ASSERT_EQ(7U, basebandCards.size());
    EXPECT_EQ(0x14U, basebandCards[0].getBoardId());
    EXPECT_EQ(0x13U, basebandCards[1].getBoardId());
    EXPECT_EQ(0x15U, basebandCards[2].getBoardId());
    EXPECT_EQ(0x12U, basebandCards[3].getBoardId());
    EXPECT_EQ(0x11U, basebandCards[4].getBoardId());
    EXPECT_EQ(0x16U, basebandCards[5].getBoardId());
    EXPECT_EQ(0x17U, basebandCards[6].getBoardId());
}

TEST(AsilBasebandPoolingTest, SortAndPrioritizeLcgsIsCorrect){
    AsilBasebandPooling pooling;
    VectorOfLcgs lcgs{Lcg(1, 10), Lcg(2, 25), Lcg(3, 40), Lcg(4, 25)};

    pooling.sortAndPrioritizeLcgs(lcgs);

    ASSERT_EQ(4U, lcgs.size());
    EXPECT_EQ(3U, lcgs[0].getLcgId());
    EXPECT_EQ(2U, lcgs[1].getLcgId());
    EXPECT_EQ(4U, lcgs[2].getLcgId());
    EXPECT_EQ(1U, lcgs[3].getLcgId());
}

TEST(AsilBasebandPoolingTest, AssignBasebandCardsWithOneLcgIsCorrect){
    AsilBasebandPooling pooling;
    KeplerNidToLcgMap poolingMap;
    VectorOfLcgs lcgs{Lcg(1, 40), Lcg(2, 30), Lcg(3, 20), Lcg(4, 10)};    SetOfBasebandCards basebandCards{
        BasebandCard(0x12, {0x1230, 0x1240, 0x1250}),
                BasebandCard(0x13, {0x1330, 0x1340, 0x1350, 0x1360}),
                BasebandCard(0x14, {0x1430, 0x1440, 0x1450, 0x1460, 0x1470}),
                BasebandCard(0x15, {0x1530, 0x1540, 0x1550, 0x1560})};
    pooling.assignBasebandCardsWithOneLcg(poolingMap, lcgs, basebandCards);

    ASSERT_EQ(16U, poolingMap.size());
    EXPECT_EQ(4U, poolingMap.at(0x1230));
    EXPECT_EQ(4U, poolingMap.at(0x1240));
    EXPECT_EQ(4U, poolingMap.at(0x1250));
    EXPECT_EQ(2U, poolingMap.at(0x1330));
    EXPECT_EQ(2U, poolingMap.at(0x1340));
    EXPECT_EQ(2U, poolingMap.at(0x1350));
    EXPECT_EQ(2U, poolingMap.at(0x1360));
    EXPECT_EQ(1U, poolingMap.at(0x1430));
    EXPECT_EQ(1U, poolingMap.at(0x1440));
    EXPECT_EQ(1U, poolingMap.at(0x1450));
    EXPECT_EQ(1U, poolingMap.at(0x1460));
    EXPECT_EQ(1U, poolingMap.at(0x1470));
    EXPECT_EQ(3U, poolingMap.at(0x1530));
    EXPECT_EQ(3U, poolingMap.at(0x1540));
    EXPECT_EQ(3U, poolingMap.at(0x1550));
    EXPECT_EQ(3U, poolingMap.at(0x1560));
}

TEST(AsilBasebandPoolingTest, AssignBasebandCardsWithMultipleLcgsIsCorrect){
    AsilBasebandPooling pooling;
    KeplerNidToLcgMap poolingMap;
    VectorOfLcgs lcgs{Lcg(1, 40), Lcg(2, 30), Lcg(3, 20), Lcg(4, 10)};    SetOfBasebandCards basebandCards{
        BasebandCard(0x12, {0x1230, 0x1240, 0x1250}),
                BasebandCard(0x14, {0x1430, 0x1440, 0x1450, 0x1460})};
    pooling.assignBasebandCardsWithMultipleLcgs(poolingMap, lcgs, basebandCards);

    ASSERT_EQ(7U, poolingMap.size());
    EXPECT_EQ(3U, poolingMap.at(0x1230));
    EXPECT_EQ(3U, poolingMap.at(0x1240));
    EXPECT_EQ(4U, poolingMap.at(0x1250));
    EXPECT_EQ(1U, poolingMap.at(0x1430));
    EXPECT_EQ(1U, poolingMap.at(0x1440));
    EXPECT_EQ(2U, poolingMap.at(0x1450));
    EXPECT_EQ(2U, poolingMap.at(0x1460));
}

//print functionvoid printPoolingResult(BasebandPoolingResult const& poolingResult)
{
    if(poolingResult.isSuccessful)
    {        cout << "Baseband pooling successful" << endl;
    }
    else
    {
        cout << "Baseband pooling NOT successful" << endl;
    }

    DisplayTable table;
    table.setBorders("-","|");
    unsigned int previousNid(0);
    for(KeplerNidToLcgPair const nidToLcgPair : poolingResult.keplerNidToLcgMap)
    {
        if((previousNid & 0xFF00) != (nidToLcgPair.first & 0xFF00))
        {
            table.addRow();
        }
        stringstream ss;
        ss << hex << "0x" << nidToLcgPair.first << "->LCG:" << nidToLcgPair.second;
        table.getLastRow().addCell(ss.str());
        previousNid = nidToLcgPair.first;
    }
    cout<<table.drawOutput();
}

TEST(AsilBasebandPoolingTest, PerformBasebandPoolingForAsilIsCorrect)
{
    AsilBasebandPooling pooling(
    {Lcg(1, 10), Lcg(2, 20), Lcg(3, 30), Lcg(4, 40)},
    {BasebandCard(0x13, {0x1230, 0x1240, 0x1250, 0x1260}),
     BasebandCard(0x14, {0x1330, 0x1340, 0x1350, 0x1360}),
     BasebandCard(0x15, {0x1430, 0x1440, 0x1450})});

    BasebandPoolingResult poolingResult(pooling.performBasebandPoolingForAsil());

    KeplerNidToLcgMap & poolingMap(poolingResult.keplerNidToLcgMap);
    ASSERT_EQ(11U, poolingMap.size());
    EXPECT_EQ(4U, poolingMap.at(0x1230));
    EXPECT_EQ(4U, poolingMap.at(0x1240));
    EXPECT_EQ(4U, poolingMap.at(0x1250));
    EXPECT_EQ(4U, poolingMap.at(0x1260));
    EXPECT_EQ(2U, poolingMap.at(0x1330));
    EXPECT_EQ(2U, poolingMap.at(0x1340));
    EXPECT_EQ(1U, poolingMap.at(0x1350));
    EXPECT_EQ(1U, poolingMap.at(0x1360));
    EXPECT_EQ(3U, poolingMap.at(0x1430));
    EXPECT_EQ(3U, poolingMap.at(0x1440));
    EXPECT_EQ(3U, poolingMap.at(0x1450));

    printPoolingResult(poolingResult);
}
}