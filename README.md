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