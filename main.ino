#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SENSORS[8] = {26, 27, 22, 23, 24, 25, 13, 12};
const int LEDS[8] = {28, 29, 30, 31, 32, 33, 34, 35};

int ARRIVED[8] = { 0, };

int SELECTED = 0;
int DAYS = 81;

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  for(int i=0; i<8; i++) {
    pinMode(SENSORS[i], INPUT);
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], HIGH);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LONDON");
  lcd.setCursor(0, 1);
  lcd.print("81 DAYS LEFT");
}

void loop() {
  for(int i=0; i<8; i++) {
    if(digitalRead(SENSORS[i]) == HIGH) {
      if(ARRIVED[i] == 0 && i != 0) {
        switch(SELECTED) {
          // 런던 출발
          case 0: {
            switch(i) {
              case 1: { DAYS -= 7; break; }
              case 7: { DAYS -= 10; break; }
              case 6: { DAYS -= 17; break; }
              case 2: { DAYS -= 20; break; }
              case 3: { DAYS -= 23; break; }
              case 4: { DAYS -= 36; break; }
              case 5: { DAYS -= 39; break; }
            }
            break;
          }
          // 수에즈 출발
          case 1: {
            switch(i) {
              case 0: { DAYS -= 7; break; }
              case 2: { DAYS -= 13; break; }
              case 3: { DAYS -= 16; break; }
              case 7: { DAYS -= 17; break; }
              case 4: { DAYS -= 29; break; }
              case 5: { DAYS -= 35; break; }
              case 6: { DAYS -= 46; break; }
            }
            break;
          }
          // 봄베이 출발
          case 2: {
            switch(i) {
              case 3: { DAYS -= 3; break; }
              case 1: { DAYS -= 13; break; }
              case 4: { DAYS -= 16; break; }
              case 0: { DAYS -= 20; break; }
              case 5: { DAYS -= 22; break; }
              case 7: { DAYS -= 30; break; }
              case 6: { DAYS -= 44; break; }
            }
            break;
          }
          // 캘커타 출발
          case 3: {
            switch(i) {
              case 2: { DAYS -= 3; break; }
              case 4: { DAYS -= 13; break; }
              case 1: { DAYS -= 16; break; }
              case 5: { DAYS -= 19; break; }
              case 0: { DAYS -= 23; break; }
              case 7: { DAYS -= 33; break; }
              case 6: { DAYS -= 40; break; }
            }
            break;
          }
          // 홍콩 출발
          case 4: {
            switch(i) {
              case 5: { DAYS -= 6; break; }
              case 3: { DAYS -= 13; break; }
              case 2: { DAYS -= 16; break; }
              case 6: { DAYS -= 28; break; }
              case 1: { DAYS -= 29; break; }
              case 7: { DAYS -= 35; break; }
              case 0: { DAYS -= 36; break; } 
            }
            break;
          }
          // 요코하마 출발
          case 5: {
            switch(i) {
              case 4: { DAYS -= 6; break; }
              case 3: { DAYS -= 19; break; }
              case 6: { DAYS -= 22; break; }
              case 2: { DAYS -= 22; break; }
              case 7: { DAYS -= 27; break; }
              case 1: { DAYS -= 35; break; }
              case 0: { DAYS -= 37; break; }
            }
            break;
          }
          // 샌 프란시스코 출발
          case 6: {
            switch(i) {
              case 7: { DAYS -= 7; break; }
              case 0: { DAYS -= 17; break; }
              case 5: { DAYS -= 22; break; }
              case 1: { DAYS -= 24; break; }
              case 4: { DAYS -= 28; break; }
              case 2: { DAYS -= 37; break; }
              case 3: { DAYS -= 40; break; }
            }
            break;
          }
          // 뉴욕 출발
          case 7: {
            switch(i) {
              case 6: { DAYS -= 7; break; }
              case 0: { DAYS -= 10; break; }
              case 1: { DAYS -= 17; break; }
              case 5: { DAYS -= 29; break; }
              case 2: { DAYS -= 30; break; }
              case 3: { DAYS -= 33; break; }
              case 4: { DAYS -= 35; break; }
            }
            break;
          }
        }
        SELECTED = i;
        ARRIVED[i] = 1;
        digitalWrite(LEDS[i], LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        switch(i) {
          case 0: { lcd.print("LONDON"); break; }
          case 1: { lcd.print("SUEZ"); break; }
          case 2: { lcd.print("BOMBAY"); break; }
          case 3: { lcd.print("CALCUTTA"); break; }
          case 4: { lcd.print("HONG KONG"); break; }
          case 5: { lcd.print("YOKOHAMA"); break; }
          case 6: { lcd.print("SAN FRANCISCO"); break; }
          case 7: { lcd.print("NEW YORK"); break; }
        }
        Serial.println(i);
        lcd.setCursor(0, 1);
        if(DAYS < 0) {
          lcd.print(-DAYS);
          lcd.print(" DAYS OVER");
        } else {
          lcd.print(DAYS);
          lcd.print(" DAYS LEFT");
        }
      } else if(i == 0) {
        int failed = 0;
        for(int i=1; i<8; i++) {
          if(ARRIVED[i] == 0) { failed = 1; break; }
        }
        if(failed == 0) {
          ARRIVED[i] = 1;
          digitalWrite(LEDS[0], LOW);
          Serial.println(i);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("LONDON");
          lcd.setCursor(0, 1);
          switch(SELECTED) {
            case 1: { DAYS -= 7; break; }
            case 2: { DAYS -= 20; break; }
            case 3: { DAYS -= 23; break; }
            case 4: { DAYS -= 36; break; } 
            case 5: { DAYS -= 37; break; }
            case 6: { DAYS -= 17; break; }
            case 7: { DAYS -= 10; break; }
          }
          SELECTED = i;
          if(DAYS < 0) {
            lcd.print(-DAYS);
            lcd.print(" DAYS OVER");
          } else {
            lcd.print(DAYS);
            lcd.print(" DAYS LEFT");
          }
        }
      }
      delay(1000);
    }
  }
}
