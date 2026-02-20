void setup() {
  // Инициализация Serial порта со скоростью 19200 бод
  Serial.begin(19200);
  Serial.println("Arduino готов к передаче и приёму данных!");
}

void loop() {
  // Проверяем, есть ли данные в Serial буфере
  if (Serial.available() > 0) {
    // Читаем входящий байт
    char incomingByte = Serial.read();
    // Если получена '1', отправляем "Привет!"
    if (incomingByte == '1') {
      Serial.print("Привет!");
    } else {
      // Иначе отправляем полученный байт обратно
      Serial.print(incomingByte);
    }
  }
}
