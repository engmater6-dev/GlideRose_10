#include "GildedRose.h"
#include <gtest/gtest.h>

// TC01
TEST(GildedRoseTest, NormalItem) {
  std::vector<Item> items = {Item("foo", 0, 0)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ("foo", app.items[0].name);
}

// TC02 : 유통기한 내 1씩 감소
TEST(GildedRoseTest, QualityDecreaseInSellIn) {
  std::vector<Item> items = {Item("foo", 2, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(1, app.items[0].sellIn);
  EXPECT_EQ(4, app.items[0].quality);
}

// TC03 : 유통기한 지난제품 2씩 감소
TEST(GildedRoseTest, QualityDecreaseAfterSellIn) {
  std::vector<Item> items = {Item("foo", 0, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(3, app.items[0].quality);
}

// TC08 : 품질은 0이 최소
TEST(GildedRoseTest, QualityLowerBound) {
  std::vector<Item> items = {Item("foo", 2, 0)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(0, app.items[0].quality);
}

// TC04 : Aged Brie 유통기한 내 1씩 증가
TEST(GildedRoseTest, AgedBrieQualityIncreaseInSellIn) {
  std::vector<Item> items = {Item("Aged Brie", 2, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(6, app.items[0].quality);
}

// TC05 : Aged Brie 유통기한 지난제품 2씩 증가
TEST(GildedRoseTest, AgedBrieQualityIncreaseAfterSellIn) {
  std::vector<Item> items = {Item("Aged Brie", 0, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(7, app.items[0].quality);
}

// TC06 : Aged Brie 품질은 50이 최대
TEST(GildedRoseTest, AgedBrieQualityUpperBound) {
  std::vector<Item> items = {Item("Aged Brie", 2, 50)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(50, app.items[0].quality);
}

// TC09 : Backstage Passes 유통기한 10일 이하 2씩 증가
TEST(GildedRoseTest, BackstagePassesIncreaseInSellIn) {
  std::vector<Item> items = {
      Item("Backstage passes to a TAFKAL80ETC concert", 6, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(7, app.items[0].quality);
}

// TC07 : Sulfuras는 품질과 유통기한이 변하지 않음
TEST(GildedRoseTest, SulfurasNoChangeQualityAndSellIn) {
  std::vector<Item> items = {Item("Sulfuras, Hand of Ragnaros", 1, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(1, app.items[0].sellIn);
  EXPECT_EQ(5, app.items[0].quality);
}