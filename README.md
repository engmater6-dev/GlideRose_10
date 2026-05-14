# Gilded Rose

Gilded Rose 는 게임 "World of Warcraft"에 나오는 여관 이름입니다.  
아이템은 퀄리티 속성을 가지고 있으며, 예외 사항이 있는 아이템들이 있습니다.  
- 아이템은 [아이템 이름, 퀄리티, 유통기한]의 속성을 가집니다.  
- 아이템의 퀄리티는 0 이상이고 아이템의 퀄리티는 하루가 지날 때마다 1씩 줄어듭니다.  
- 유통 기한이 지난 아이템의 퀄리티는 2배의 속도로 떨어집니다.  
- 퀄리티는 최대값이 50입니다.  

### Aged Brie, Backstage Pass, Sulfuras 의 예외적 규칙  

- Aged Brie는 하루가 지날 때마다 퀄리티가 1씩 증가합니다.  
- 유통기한이 지나면 퀄리티가 2씩 증가합니다.  
- Backstage Pass 는 유통기한(콘서트일)이 다가올수록 퀄리티가 증가합니다.  
  유통기한이 11일 이상일 때는 1, 10일 이하일 때는 2, 5일 이하일 때는 3씩 증가하지만  
  콘서트 날이 지나면 퀄리티는 0이 됩니다.  
- Sulfuras의 퀄리티는 변화가 없습니다.  
  
---------------------------------------------------------  
## 실습 목적 :  테스트 코드 작성을 통한 legacy code 이해

### 프로젝트 구조 (C++)

```
cpp/
├── CMakeLists.txt          # CMake 빌드 설정 (Google Test 자동 다운로드)
├── include/
│   ├── Item.h              # Item 클래스 (수정 불가)
│   └── GildedRose.h        # GildedRose 클래스 헤더
├── src/
│   └── GildedRose.cpp      # updateQuality() 구현
└── test/
    └── GildedRoseTest.cpp  # Google Test 기반 테스트
```

### 빌드 및 테스트 실행

```bash
cd cpp
cmake -B build
cmake --build build
ctest --test-dir build
```

### GildedRoseTest.cpp : failed test 수정
- updateQuality() 의 test case를 추가 작성해 보세요.
- unit test 내용 : 문서상에 나타난 동작들 확인

### unit test VS golden-master test 비교


### To-Do list
noname
- item 이름 변경 없음...초기...
  : ("foo", 0, 0) -> "foo" 검증
- 유통기한 1감소.. + 퀄리티 1감소
  : ("foo", 2, 5) -> (1, 4) 검증 완료
- 유통기한 over시 퀄리티 2감소
  : ("foo", 0, 5) -> (3) 검증 완료
- 품질은 0이 최소
  : ("foo", 2, 0) -> (0) 검증 완료


AgedBrie
- 퀄리티 1 증가
  : ("AgedBrie", 2, 5) -> (6) 검증 완료
- 유통기한 over시 +2
  : ("AgedBrie", 0, 5) -> (7) 검증 완료
- 퀄리티 max 50
  : ("AgedBrie", 2, 50) -> (50) 검증 완료

Backstage Pass
- 10이하 -> +2
  : ("Backstage passes to a TAFKAL80ETC concert", 6, 5) -> (7) 완료


Sulfuras
- No change
  : ("Sulfuras", 1, 5) -> (1, 5) 완료


#### AI 정리
  일반 아이템

이름 불변

sellIn 하루마다 -1

quality 하루마다 -1

유통기한 지난 경우 quality -2

quality는 최소 0

quality는 최대 50

Aged Brie

하루마다 +1

유통기한 지난 경우 +2

sellIn 감소 확인

quality 최대 50

Backstage Pass

11일 이상일 때 +1

10일 이하일 때 +2

5일 이하일 때 +3

콘서트 날 지나면 quality = 0

quality 최대 50

Sulfuras

sellIn, quality 모두 변화 없음

##### 문제점..
 - 숫자의 의미 quality 50, sellin 0
 - 중첩 if 과다 -> class로 분리
 - 중복 로직 : items[i].quality + 1, items[i].sellIn - 1 -> 함수화
 - updateQuality() 모든 규칙 처리

##### Refactoring To-Do list
 - 상수로 정의 : 오타방지 및 의미 확인
 
 - quality 증감 추출

 - class로 중첩 if문 구현
   -> Template Method 적용???
  추상 class 설정
    .updateSellin 함수와 updateQuality는 pass로 정의하고
    .자식 class에서 조건별 설정...

  item 이름으로 class 지정하고...
   -> 초기값 update -> sellin -1 실행 -> 조건에 맞추어 quality update 진행


#### 파이썬으로 우선 작성..
1단계 상수 추출
# 상수 의미 부여
QUALITY_MIN = 0
QUALITY_MAX = 50

# Item 상수화

AGED_BRIE   = "Aged Brie"
BACKSTAGE   = "Backstage passes to a TAFKAL80ETC concert"
SULFURAS    = "Sulfuras, Hand of Ragnaros"
CONJURED    = "Conjured"
FOOD       = "Food"
BEVERAGE    = "Beverage"

2단계 함수 추출
# 함수 추출
def increase_quality(item, amount=1):
   	 item.quality = min(QUALITY_MAX, item.quality + amount)

def decrease_quality(item, amount=1):
    	item.quality = max(QUALITY_MIN, item.quality - amount)

3단계 추상 클라스 작성

from abc import ABC, abstractmethod
# 부모 class
class ItemUpdate(ABC):
    	def __init__(self, item):
        	self.item = item

	def update(self):
		self.update_quality()
		self.decrease_sellin()
	
	@abstractmethod
	def update_quality(self):
		pass

	@abstractmethod
	def decrease_sellin(self):
		pass

## 자식 class
class AgedBrie(ItemUpdate):
	def update_quality(self):
		amount = 1 if self.item.sellin > 0 else 2
		decrease_quality(self.item, amount)

	def decrease_sellin(self):
		self.item.sellin -= 1

class BackstagePass(ItemUpdate):
	def update_quality(self):
		if self.item.sellin >= 11:
			amount = 1
		elif self.item.sellin > 5:
			amount = 2
		else:
			amount = 3
		increase_quality(self.item, amount)

		### sellin이 over시 0 조건 추가
		if self.item.sellin < 0:
			self.item.quality = QUALITY_MIN

	def decrease_sellin(self):
		self.item.sellin -= 1

class Sulfuras(ItemUpdate):
	def update_quality(self):
		pass

	def decrease_sellin(self):
		pass

## update_quality 단순화..
def update_quality(items):
	for item in items:
		if item.name == AGED_BRIE:
			item_update = AgedBrie(item)
		elif item.name == BACKSTAGE:
			item_update = BackStage(item)
		elif item.name == SULFURAS:
			item_update = Sulfuras(item)
		item_update.update()
    