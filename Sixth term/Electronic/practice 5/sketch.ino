// Настройки пинов
const uint8_t digs[] = {2, 3, 4, 5};  // D0, D1, D2, D3
const uint8_t segs[] = {6, 7, 8, 9, 10, 11, 12, 13};  // A, B, C, D, E, F, G, DP

// Коды цифр
const byte digits[10] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111   // 9
};

unsigned int counter = 0;
unsigned long lastUpdate = 0;
const int updateInterval = 1000;  // шаг счётчика (мс)

void setup() {
  for (int i = 0; i < 8; i++) pinMode(segmentPins[i], OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(digitPins[i], OUTPUT);
}

void loop() {
  // обновляем счётчик каждую секунду
  if (millis() - lastUpdate > updateInterval) {
    lastUpdate = millis();
    counter++;
    if (counter > 9999) counter = 0;
  }

  displayNumber(counter);
}

void displayNumber(unsigned int num) {
  int d[4];
  d[0] = num / 1000;
  d[1] = (num / 100) % 10;
  d[2] = (num / 10) % 10;
  d[3] = num % 10;

  for (int i = 0; i < 4; i++) {
    showDigit(d[i]);
    digitalWrite(digitPins[i], LOW);  // активируем текущую цифру (LOW — общий катод)
    delay(2);
    digitalWrite(digitPins[i], HIGH); // выключаем цифру
  }
}

void showDigit(int n) {
  byte pattern = digits[n];
  for (int i = 0; i < 8; i++) {
    bool state = pattern & (1 << i);
    digitalWrite(segmentPins[i], state ? HIGH : LOW);
  }
}
