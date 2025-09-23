#define LEDPIN 2

void setup() {
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  digitalWrite(LEDPIN, 1);
  delay(1000);
  digitalWrite(LEDPIN, 0);
  delay(1000);
}
