#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define IR_PIN 34
#define LED_PIN 2

// Motor pins
#define ENA 25
#define IN1 26
#define IN2 27
#define ENB 14 
#define IN3 12
#define IN4 13

int motorSpeed = 200;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Vaishnav_ESP32_CAR");
  Serial.println("IR Sensor");
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM setup
  ledcAttach(ENA, 5000, 8);
  ledcAttach(ENB, 5000, 8);

}

void forward() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void backward() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void left() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void right() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void stopCar() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  int status = 0;
  int sensorStatus = digitalRead(IR_PIN);
  if (sensorStatus == 0) {
    digitalWrite(LED_PIN, 1);
    stopCar();
    status = 1;
    Serial.println("Motion Detected");
    Serial.print("Status: ");
    Serial.println(status);
    delay(300);
    left();
    delay(600);
    forward();
  }
  else {
    digitalWrite(LED_PIN, 0);
    status = 0;
    Serial.println("NO MOTION");
    Serial.print("Status: ");
    Serial.println(status);
  }

  delay(100);

  if (SerialBT.available()) {
    char cmd = SerialBT.read();

    switch (cmd) {
      case 'U' :
        right();
        break;
      case 'D' :
        left();
        break;
      case 'L' :
        forward();
        break;
      case 'R' :
        backward();
        break;
      case 'S' :
        stopCar();
        break;
      default :
        left();
        break;
    }
  }
}
