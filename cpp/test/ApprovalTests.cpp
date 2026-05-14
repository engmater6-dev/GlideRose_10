#define APPROVALS_GOOGLETEST
#include "GildedRose.h"
#include <ApprovalTests.hpp>
#include <gtest/gtest.h>

using namespace ApprovalTests;

auto defaultReporterDisposer =
    Approvals::useAsDefaultReporter(std::make_shared<QuietReporter>());

TEST(GildedRoseApprovalTest, AllCasesTogether) {
  std::vector<std::string> outputs;

  {
    std::vector<Item> items = {Item("foo", 0, 0)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back("NormalItem -> Name: " + app.items[0].name +
                      ", SellIn: " + std::to_string(app.items[0].sellIn) +
                      ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {Item("foo", 2, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back("QualityDecreaseInSellIn -> Name: " + app.items[0].name +
                      ", SellIn: " + std::to_string(app.items[0].sellIn) +
                      ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {Item("foo", 0, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "QualityDecreaseAfterSellIn -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {Item("Aged Brie", 2, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "AgedBrieQualityIncreaseInSellIn -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {
        Item("Backstage passes to a TAFKAL80ETC concert", 2, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "BackstagePassesIncreaseMoreInSellIn -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {Item("Sulfuras, Hand of Ragnaros", 1, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "SulfurasNoChangeQualityAndSellIn -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {Item("Aged Brie", 0, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "AgedBrieQualityIncreaseAfterSellIn -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {Item("Aged Brie", 2, 50)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "AgedBrieQualityUpperBound -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {
        Item("Backstage passes to a TAFKAL80ETC concert", 6, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "BackstagePassesIncreaseInSellIn -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  {
    std::vector<Item> items = {
        Item("Backstage passes to a TAFKAL80ETC concert", 0, 5)};
    GildedRose app(items);
    app.updateQuality();
    outputs.push_back(
        "BackstagePassesQualityDropAfterSellIn -> Name: " + app.items[0].name +
        ", SellIn: " + std::to_string(app.items[0].sellIn) +
        ", Quality: " + std::to_string(app.items[0].quality));
  }

  // 모든 케이스를 하나의 승인 파일로 검증
  Approvals::verifyAll("GildedRose Cases", outputs);
}
