#include <RagnarokOnline.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(RagnarokOnlineShopUpdateTest, DISABLED_RetrieveBuyingShopDataFromTalonRoWebpagesAndThenSaveTheData) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveBuyingShopDataFromTalonRoWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\BuyingShops\)");

    ragnarokOnline.saveBuyingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\BuyingShopItemsCurrentData.txt)");
}

TEST(RagnarokOnlineShopUpdateTest, DISABLED_RetrieveSellingShopDataFromTalonRoWebpagesAndThenSaveTheData) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveSellingShopDataFromTalonRoWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\SellingShops\)");

    ragnarokOnline.saveSellingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\SellingShopItemsCurrentData.txt)");
}

TEST(RagnarokOnlineShopUpdateTest, DISABLED_SaveBuyingShopItemsCumulativeData) {
    string filePath(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\BuyingShopItemsCumulativeData.txt)");
    RagnarokOnline ragnarokOnline;
    ragnarokOnline.readBuyingShopItems(filePath);
    ragnarokOnline.retrieveBuyingShopDataFromTalonRoWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\BuyingShops\)");
    ragnarokOnline.saveBuyingShopItems(filePath);
}

TEST(RagnarokOnlineShopUpdateTest, DISABLED_SaveSellingShopItemsCumulativeData) {
    string filePath(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\SellingShopItemsCumulativeData.txt)");
    RagnarokOnline ragnarokOnline;
    ragnarokOnline.readSellingShopItems(filePath);
    ragnarokOnline.retrieveSellingShopDataFromTalonRoWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\SellingShops\)");
    ragnarokOnline.saveSellingShopItems(filePath);
}

TEST(RagnarokOnlineShopTest, ReadBuyingShopItemsWorks) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.readBuyingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\BuyingShopItemsCurrentData.txt)");

    EXPECT_EQ(45U, ragnarokOnline.getBuyingItemShops().size());
}
TEST(RagnarokOnlineShopTest, ReadSellingShopItemsWorks) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.readSellingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\SellingShopItemsCurrentData.txt)");

    EXPECT_EQ(1697U, ragnarokOnline.getSellingItemShops().size());
}
TEST(RagnarokOnlineShopTest, RetrieveBuyingShopDataFromTalonRoWebpagesWorks) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveBuyingShopDataFromTalonRoWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\BuyingShops\)");

    EXPECT_EQ(45U, ragnarokOnline.getBuyingItemShops().size());
}
TEST(RagnarokOnlineShopTest, RetrieveSellingShopDataFromTalonRoWebpagesWorks) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveSellingShopDataFromTalonRoWebpages(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\SellingShops\)");

    EXPECT_EQ(1697U, ragnarokOnline.getSellingItemShops().size());
}
TEST(RagnarokOnlineShopTest, RetrieveShopDataFromTalonRoWebPageWithBuyingShopTypeExample1) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveShopDataFromTalonRoWebPage(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\ForTesting\BuyingTest.html)", ShopType::BuyingShop);

    ItemNameToShopItemDetailMap const& shopItems(ragnarokOnline.getBuyingItemShops());
    ASSERT_EQ(13U, shopItems.size());
    ShopItemDetail const& shopItemDetail1(shopItems.at("Aloe"));
    EXPECT_EQ("Aloe", shopItemDetail1.itemName);
    EXPECT_DOUBLE_EQ(9000, shopItemDetail1.averagePrice);    EXPECT_EQ(23U, shopItemDetail1.totalNumber);

    ShopItemDetail const& shopItemDetail2(shopItems.at("Aloe Leaflet"));
    EXPECT_EQ("Aloe Leaflet", shopItemDetail2.itemName);
    EXPECT_DOUBLE_EQ(2600.6333122229257242, shopItemDetail2.averagePrice);
    EXPECT_EQ(1579U, shopItemDetail2.totalNumber);

    ShopItemDetail const& shopItemDetail3(shopItems.at("Aloevera"));
    EXPECT_EQ("Aloevera", shopItemDetail3.itemName);
    EXPECT_DOUBLE_EQ(25819.819819819818804, shopItemDetail3.averagePrice);
    EXPECT_EQ(333U, shopItemDetail3.totalNumber);

    ShopItemDetail const& shopItemDetail4(shopItems.at("Bao"));
    EXPECT_EQ("Bao", shopItemDetail4.itemName);
    EXPECT_DOUBLE_EQ(500, shopItemDetail4.averagePrice);
    EXPECT_EQ(1249U, shopItemDetail4.totalNumber);

    ShopItemDetail const& shopItemDetail5(shopItems.at("Bee Sting"));
    EXPECT_EQ("Bee Sting", shopItemDetail5.itemName);
    EXPECT_DOUBLE_EQ(600, shopItemDetail5.averagePrice);
    EXPECT_EQ(300U, shopItemDetail5.totalNumber);

    ShopItemDetail const& shopItemDetail6(shopItems.at("Bitter Herb"));
    EXPECT_EQ("Bitter Herb", shopItemDetail6.itemName);
    EXPECT_DOUBLE_EQ(3000, shopItemDetail6.averagePrice);
    EXPECT_EQ(77U, shopItemDetail6.totalNumber);

    ShopItemDetail const& shopItemDetail7(shopItems.at("Blue Herb"));
    EXPECT_EQ("Blue Herb", shopItemDetail7.itemName);
    EXPECT_DOUBLE_EQ(1628.9901161354089254, shopItemDetail7.averagePrice);
    EXPECT_EQ(4047U, shopItemDetail7.totalNumber);

    ShopItemDetail const& shopItemDetail8(shopItems.at("Cheese"));
    EXPECT_EQ("Cheese", shopItemDetail8.itemName);
    EXPECT_DOUBLE_EQ(2502.4789915966384797, shopItemDetail8.averagePrice);
    EXPECT_EQ(595U, shopItemDetail8.totalNumber);

    ShopItemDetail const& shopItemDetail9(shopItems.at("Chiqita's Jewelry Box"));
    EXPECT_EQ("Chiqita's Jewelry Box", shopItemDetail9.itemName);
    EXPECT_DOUBLE_EQ(175000, shopItemDetail9.averagePrice);
    EXPECT_EQ(100U, shopItemDetail9.totalNumber);

    ShopItemDetail const& shopItemDetail10(shopItems.at("Crystal Fragment"));
    EXPECT_EQ("Crystal Fragment", shopItemDetail10.itemName);
    EXPECT_DOUBLE_EQ(3500.7678737233054562, shopItemDetail10.averagePrice);
    EXPECT_EQ(2154U, shopItemDetail10.totalNumber);

    ShopItemDetail const& shopItemDetail11(shopItems.at("Denture from Dragon Mask"));
    EXPECT_EQ("Denture from Dragon Mask", shopItemDetail11.itemName);
    EXPECT_DOUBLE_EQ(2000, shopItemDetail11.averagePrice);
    EXPECT_EQ(269U, shopItemDetail11.totalNumber);

    ShopItemDetail const& shopItemDetail12(shopItems.at("Emperium"));
    EXPECT_EQ("Emperium", shopItemDetail12.itemName);
    EXPECT_DOUBLE_EQ(100000, shopItemDetail12.averagePrice);
    EXPECT_EQ(10U, shopItemDetail12.totalNumber);

    ShopItemDetail const& shopItemDetail13(shopItems.at("Flame Heart"));
    EXPECT_EQ("Flame Heart", shopItemDetail13.itemName);
    EXPECT_DOUBLE_EQ(5172.4342105263158373, shopItemDetail13.averagePrice);
    EXPECT_EQ(380U, shopItemDetail13.totalNumber);
}

TEST(RagnarokOnlineShopTest, RetrieveShopDataFromTalonRoWebPageWithSellingShopTypeExample1) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveShopDataFromTalonRoWebPage(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\ForTesting\SellingTest.html)", ShopType::SellingShop);

    ItemNameToShopItemDetailMap const& shopItems(ragnarokOnline.getSellingItemShops());
    ASSERT_EQ(2U, shopItems.size());
    ShopItemDetail const& shopItemDetail1(shopItems.at("Cross Shield [1]"));
    EXPECT_EQ("Cross Shield [1]", shopItemDetail1.itemName);
    EXPECT_DOUBLE_EQ(222078.29166666671517, shopItemDetail1.averagePrice);    EXPECT_EQ(24U, shopItemDetail1.totalNumber);

    ShopItemDetail const& shopItemDetail2(shopItems.at("Crown Parrots [1]"));
    EXPECT_EQ("Crown Parrots [1]", shopItemDetail2.itemName);
    EXPECT_DOUBLE_EQ(500000, shopItemDetail2.averagePrice);
    EXPECT_EQ(1U, shopItemDetail2.totalNumber);
}

TEST(RagnarokOnlineShopTest, RetrieveShopDataFromTalonRoWebPageWithSellingShopTypeExample2) {
    RagnarokOnline ragnarokOnline;

    ragnarokOnline.retrieveShopDataFromTalonRoWebPage(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\TalonRO\ForTesting\SellingTest2.html)", ShopType::SellingShop);

    ItemNameToShopItemDetailMap const& shopItems(ragnarokOnline.getSellingItemShops());
    ASSERT_EQ(10U, shopItems.size());
    ShopItemDetail const& shopItemDetail1(shopItems.at("Book of the Dead [2]"));
    EXPECT_EQ("Book of the Dead [2]", shopItemDetail1.itemName);
    EXPECT_DOUBLE_EQ(4000000, shopItemDetail1.averagePrice);    EXPECT_EQ(1U, shopItemDetail1.totalNumber);

    ShopItemDetail const& shopItemDetail2(shopItems.at("Boots [1]"));
    EXPECT_EQ("Boots [1]", shopItemDetail2.itemName);
    EXPECT_DOUBLE_EQ(109375, shopItemDetail2.averagePrice);
    EXPECT_EQ(8U, shopItemDetail2.totalNumber);

    ShopItemDetail const& shopItemDetail3(shopItems.at("Boreas' Doom Crate"));
    EXPECT_EQ("Boreas' Doom Crate", shopItemDetail3.itemName);
    EXPECT_DOUBLE_EQ(8363636.3636363632977, shopItemDetail3.averagePrice);
    EXPECT_EQ(11U, shopItemDetail3.totalNumber);

    ShopItemDetail const& shopItemDetail4(shopItems.at("Bottle Grenade"));
    EXPECT_EQ("Bottle Grenade", shopItemDetail4.itemName);
    EXPECT_DOUBLE_EQ(1432.2947097879630292, shopItemDetail4.averagePrice);
    EXPECT_EQ(9338U, shopItemDetail4.totalNumber);

    ShopItemDetail const& shopItemDetail5(shopItems.at("Bouquet Hat Costume"));
    EXPECT_EQ("Bouquet Hat Costume", shopItemDetail5.itemName);
    EXPECT_DOUBLE_EQ(3663333.3333333334886, shopItemDetail5.averagePrice);
    EXPECT_EQ(3U, shopItemDetail5.totalNumber);

    ShopItemDetail const& shopItemDetail6(shopItems.at("Bow Thimble"));
    EXPECT_EQ("Bow Thimble", shopItemDetail6.itemName);
    EXPECT_DOUBLE_EQ(450000, shopItemDetail6.averagePrice);
    EXPECT_EQ(2U, shopItemDetail6.totalNumber);

    ShopItemDetail const& shopItemDetail7(shopItems.at("Bow Thimble [1]"));
    EXPECT_EQ("Bow Thimble [1]", shopItemDetail7.itemName);
    EXPECT_DOUBLE_EQ(5500000, shopItemDetail7.averagePrice);
    EXPECT_EQ(1U, shopItemDetail7.totalNumber);

    ShopItemDetail const& shopItemDetail8(shopItems.at("Bow Thimble [1] [Ifrit Card]"));
    EXPECT_EQ("Bow Thimble [1] [Ifrit Card]", shopItemDetail8.itemName);
    EXPECT_DOUBLE_EQ(24000000, shopItemDetail8.averagePrice);
    EXPECT_EQ(1U, shopItemDetail8.totalNumber);

    ShopItemDetail const& shopItemDetail9(
        shopItems.at("Bow [4] [Marina Card] [Marina Card] [Marina Card] [Marina Card]"));
    EXPECT_EQ("Bow [4] [Marina Card] [Marina Card] [Marina Card] [Marina Card]", shopItemDetail9.itemName);
    EXPECT_DOUBLE_EQ(10000000, shopItemDetail9.averagePrice);
    EXPECT_EQ(1U, shopItemDetail9.totalNumber);

    ShopItemDetail const& shopItemDetail10(shopItems.at("Box of Gloom"));
    EXPECT_EQ("Box of Gloom", shopItemDetail10.itemName);
    EXPECT_DOUBLE_EQ(25000, shopItemDetail10.averagePrice);
    EXPECT_EQ(61U, shopItemDetail10.totalNumber);
}

}  // namespace alba
