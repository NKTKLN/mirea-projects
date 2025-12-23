#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

// Настройка LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Настройка RTC
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) {
    Serial.println("RTC не найден!");
    lcd.setCursor(0, 0);
    lcd.print("RTC error!");
    while (1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // Чтение времени
  DateTime now = rtc.now();

  // Вывод времени на LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");

  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  // Вывод даты на LCD
  lcd.setCursor(0, 1);
  lcd.print("Date: ");

  if (now.day() < 10) lcd.print("0");
  lcd.print(now.day());
  lcd.print(".");
  if (now.month() < 10) lcd.print("0");
  lcd.print(now.month());
  lcd.print(".");
  lcd.print(now.year());

  delay(1000);
}
