#define IR_PIN 34
#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  Serial.println("IR Sensor");
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
}

void loop() {
  int status = 0;
  int sensorStatus = digitalRead(IR_PIN);
  if (sensorStatus == 0) {
    digitalWrite(LED_PIN, 1);
    status = 1;
    Serial.println("Motion Detected");
    Serial.print("Status: ");
    Serial.println(status);

  }
  else {
    digitalWrite(LED_PIN, 0);
    status = 0;
    Serial.println("NO MOTION");
    Serial.print("Status: ");
    Serial.println(status);
  }

  delay(100);
}
