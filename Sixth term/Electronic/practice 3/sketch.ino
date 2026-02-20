const unsigned int ledPin = 2
const unsigned long onTime = 3000;
const unsigned long offTime = 2000;
const unsigned long totalTime = 5UL * 60UL * 1000UL;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long startTime = millis();
  while (millis() - startTime < totalTime) {
    for (int brightness = 0; brightness <= 255; brightness++) {
      analogWrite(ledPin, brightness);
      delay(onTime / 255);
    }

    for (int brightness = 255; brightness >= 0; brightness--) {
      analogWrite(ledPin, brightness);
      delay(offTime / 255);
    }
  }

  digitalWrite(ledPin, LOW);
  while (true);
}
