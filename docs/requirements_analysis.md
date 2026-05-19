# Gilded Rose Requirements Analysis (Python QA 관점)

## 1. 아이템 타입별 비즈니스 규칙

| Item Type        | SellIn 동작                          | Quality 동작                                                                 |
|------------------|--------------------------------------|-------------------------------------------------------------------------------|
| Normal           | 하루마다 -1                          | 하루마다 -1, SellIn < 0이면 하루마다 -2                                       |
| Aged Brie        | 하루마다 -1                          | 하루마다 +1, SellIn < 0이면 하루마다 +2                                       |
| Backstage Pass   | 하루마다 -1                          | SellIn > 10 → +1<br>6~10 → +2<br>1~5 → +3<br>SellIn < 0 → 0                   |
| Sulfuras         | 변하지 않음                          | Quality 항상 80, 변하지 않음                                                  |
| Conjured         | 하루마다 -1                          | Normal 아이템 대비 2배 속도로 감소 (SellIn < 0이면 하루마다 -4)               |

---

## 2. Python 구현 시 주의점

- **문자열 비교**: `item.name == "Aged Brie"` 처럼 정확한 비교 사용.  
  `in` 연산자는 부분 문자열 매칭으로 오동작 가능 → 금지.  
- **정수 경계 처리**:  
  - Quality는 0 미만 불가, 50 초과 불가 (단 Sulfuras는 80 고정).  
  - SellIn은 음수 허용.  
- **dataclass 활용 여부**:  
  - `Item` 클래스는 수정 금지.  
  - 신규 로직/헬퍼 클래스에는 `@dataclass` 활용 가능.  
- **type hint 권장**: 함수 시그니처와 반환 타입 명시.

---

## 3. 예외/경계값 조건

- **Quality**:  
  - 최소값 = 0  
  - 최대값 = 50 (Sulfuras는 80 고정)  
- **SellIn**:  
  - 0, -1, 음수 모두 허용  
- **Sulfuras**:  
  - Quality 변하지 않음, SellIn 변하지 않음  

---

## 4. Conjured 신규 요구사항

- `"Conjured"` 아이템은 **Quality 감소율이 2배**.  
  - Normal: 하루마다 -1 → Conjured: 하루마다 -2  
  - SellIn < 0일 때 Normal: 하루마다 -2 → Conjured: 하루마다 -4  

---

## 5. pytest 기준 테스트 시나리오 목록

1. **Normal Item**  
   - SellIn > 0, Quality 감소 -1  
   - SellIn < 0, Quality 감소 -2  
   - Quality = 0 → 감소하지 않음  

2. **Aged Brie**  
   - SellIn > 0, Quality 증가 +1  
   - SellIn < 0, Quality 증가 +2  
   - Quality = 50 → 증가하지 않음  

3. **Backstage Pass**  
   - SellIn > 10 → Quality +1  
   - 6 ≤ SellIn ≤ 10 → Quality +2  
   - 1 ≤ SellIn ≤ 5 → Quality +3  
   - SellIn < 0 → Quality = 0  

4. **Sulfuras**  
   - Quality 항상 80 유지  
   - SellIn 변하지 않음  

5. **Conjured Item**  
   - SellIn > 0, Quality 감소 -2  
   - SellIn < 0, Quality 감소 -4  
   - Quality = 0 → 감소하지 않음  

6. **경계값 테스트**  
   - Quality = 0, 50  
   - SellIn = 0, -1  
   - Sulfuras Quality = 80 고정  
