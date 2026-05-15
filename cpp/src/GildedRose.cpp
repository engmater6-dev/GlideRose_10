#include "GildedRose.h"
#include <algorithm>

// 전역 상수
constexpr int QUALITY_MIN = 0;
constexpr int QUALITY_MAX = 50;

// 전역 함수
inline void increase_quality(Item &item, int amount = 1) {
  item.quality = std::min(QUALITY_MAX, item.quality + amount);
}

inline void decrease_quality(Item &item, int amount = 1) {
  item.quality = std::max(QUALITY_MIN, item.quality - amount);
}

inline void decrease_sellin(Item &item) { item.sellIn -= 1; }

// 추상 클래스
class ItemUpdate {
protected:
  Item &item;

public:
  ItemUpdate(Item &i) : item(i) {}
  virtual ~ItemUpdate() {}
  virtual void update_quality() = 0;
  virtual void decrease_sellin() { ::decrease_sellin(item); }
};

// AgedBrie
class AgedBrie : public ItemUpdate {
public:
  AgedBrie(Item &i) : ItemUpdate(i) {}
  void update_quality() override { increase_quality(item, 1); }
};

// BackStage
class BackStage : public ItemUpdate {
public:
  BackStage(Item &i) : ItemUpdate(i) {}
  void update_quality() override {
    int amount = (item.sellIn >= 11) ? 1 : (item.sellIn > 5 ? 2 : 3);
    increase_quality(item, amount);
    if (item.sellIn < 0)
      item.quality = QUALITY_MIN;
  }
};

// Sulfuras
class Sulfuras : public ItemUpdate {
public:
  Sulfuras(Item &i) : ItemUpdate(i) {}
  void update_quality() override { /* 변하지 않음 */ }
  void decrease_sellin() override { /* 변하지 않음 */ }
};

// Conjured
class Conjured : public ItemUpdate {
public:
  Conjured(Item &i) : ItemUpdate(i) {}
  void update_quality() override { decrease_quality(item, 2); }
};

// Food & Beverage (기본 아이템)
class FoodBeverage : public ItemUpdate {
public:
  FoodBeverage(Item &i) : ItemUpdate(i) {}
  void update_quality() override { decrease_quality(item, 1); }
};

// GildedRose 구현
GildedRose::GildedRose(std::vector<Item> &items) : items(items) {}

void GildedRose::updateQuality() {
  for (auto &item : items) {
    ItemUpdate *updater = nullptr;

    if (item.name == "Aged Brie") {
      updater = new AgedBrie(item);
    } else if (item.name == "Backstage passes to a TAFKAL80ETC concert") {
      updater = new BackStage(item);
    } else if (item.name == "Sulfuras, Hand of Ragnaros") {
      updater = new Sulfuras(item);
    } else if (item.name == "Conjured") {
      updater = new Conjured(item);
    } else {
      updater = new FoodBeverage(item);
    }

    updater->update_quality();
    updater->decrease_sellin();
    delete updater;
  }
}
