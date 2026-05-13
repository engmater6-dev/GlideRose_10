#include "GildedRose.h"
#include <gtest/gtest.h>

TEST(GildedRoseTest, Foo) {
  std::vector<Item> items = {Item("foo", 0, 0)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ("foo", app.items[0].name);
  EXPECT_EQ(-1, app.items[0].sellIn);
  EXPECT_EQ(0, app.items[0].quality);
}

TEST(GildedRoseTest, Foo2) {
  std::vector<Item> items = {Item("foo", 2, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ("foo", app.items[0].name);
  EXPECT_EQ(1, app.items[0].sellIn);
  EXPECT_EQ(4, app.items[0].quality);
}

TEST(GildedRoseTest, Foo3) {
  std::vector<Item> items = {Item("foo", 0, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ("foo", app.items[0].name);
  EXPECT_EQ(-1, app.items[0].sellIn);
  EXPECT_EQ(3, app.items[0].quality);
}

TEST(GildedRoseTest, AgedBrie) {
  std::vector<Item> items = {Item("Aged Brie", 2, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ("Aged Brie", app.items[0].name);
  EXPECT_EQ(1, app.items[0].sellIn);
  EXPECT_EQ(6, app.items[0].quality);
}

TEST(GildedRoseTest, AgedBrie2) {
  std::vector<Item> items = {Item("Aged Brie", 0, 5)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ("Aged Brie", app.items[0].name);
  EXPECT_EQ(-1, app.items[0].sellIn);
  EXPECT_EQ(7, app.items[0].quality);
}

TEST(GildedRoseTest, AgedBrie3) {
  std::vector<Item> items = {Item("Aged Brie", 2, 50)};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ("Aged Brie", app.items[0].name);
  EXPECT_EQ(1, app.items[0].sellIn);
  EXPECT_EQ(50, app.items[0].quality);
}