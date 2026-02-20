#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Настройка LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Пины
#define DHTPIN 11
#define DHTTYPE DHT11

const int buttonPlus = 6;
const int buttonMinus = 7;

DHT dht(DHTPIN, DHTTYPE);

int counter = 0;

// Для долгого удержания
unsigned long pressStartTime = 0;
bool plusPressed = false;

void setup() {
  pinMode(buttonPlus, INPUT_PULLUP);
    pinMode(buttonMinus, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  Serial.println("=== System Start ===");

  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.setCursor(0, 1);
  lcd.print("Count:");
}

void loop() {
  // Чтение влажности
  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Ошибка чтения DHT!");
    humidity = 0;
  }

  // Работа кнопки "+"
  if (digitalRead(buttonPlus) == LOW) {
    if (!plusPressed) {
      plusPressed = true;
      pressStartTime = millis();
    } else {
      if (millis() - pressStartTime > 3000) {
        counter += 10;
        Serial.println("Button + long press -> +10");
        plusPressed = false;
      }
    }
  } else {
    if (plusPressed && (millis() - pressStartTime < 3000)) {
      counter++;
      Serial.println("Button + short press -> +1");
    }
    plusPressed = false;
  }

  // Работа кнопки "-"
  if (digitalRead(buttonMinus) == LOW) {
    delay(200);
    counter--;
    Serial.println("Button - short press -> -1");
  }

  // Защита от отрицательных значений
  if (counter < 0) counter = 0;

  // Логирование
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Counter: ");
  Serial.println(counter);

  // Обновление дисплея
  lcd.setCursor(10, 0);
  lcd.print("     ");
  lcd.setCursor(10, 0);
  lcd.print(humidity, 1);
  lcd.print("%");

  lcd.setCursor(7, 1);
  lcd.print("     ");
  lcd.setCursor(7, 1);
  lcd.print(counter);

  delay(100);
}
