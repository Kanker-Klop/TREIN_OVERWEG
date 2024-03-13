#include <Arduino.h>
#include <Servo.h>
Servo slagboom;
bool wit = 1;
bool rood = 0;
bool treiniser = 0;
void aankomst() {
  digitalWrite(4, LOW);
  digitalWrite(5, rood);
  digitalWrite(6, !rood);
  slagboom.write(90);
  treiniser = 1;
  return;
}
void vertrek() {
  slagboom.write(0);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  treiniser = 0;
}
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  slagboom.attach(9);
  attachInterrupt(digitalPinToInterrupt(2), aankomst, RISING);
  attachInterrupt(digitalPinToInterrupt(3), vertrek, RISING);
  slagboom.write(0);
}
void loop() {
  while (treiniser) {
    rood = !rood;
    digitalWrite(5, rood);
    digitalWrite(6, !rood);
    delay(175);
    digitalWrite(5, !rood);
    digitalWrite(6, rood);
    delay(175);
  }
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(4, wit);
  delay(750);
  wit = !wit;
}