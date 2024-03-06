#include <Arduino.h>
#include <Servo.h>
#define aankomstknop 2
#define vertrekknop 3
#define witlicht 4
#define rood1 5
#define rood2 6
Servo slagboom;
bool wit = 1;
bool rood = 0;
bool aankomstpiet = 0;
bool vertrekpiet = 0;
bool treiniser = 0;
void aankomst() {
  digitalWrite(witlicht, LOW);
  digitalWrite(rood1, rood);
  digitalWrite(rood2, !rood);
  slagboom.write(90);
  treiniser = 1;
  return;
}
void vertrek() {
  slagboom.write(0);
  digitalWrite(rood1, LOW);
  digitalWrite(rood2, LOW);
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
  while ((vertrekpiet == 0) && treiniser) {
    rood = !rood;
    digitalWrite(rood1, rood);
    digitalWrite(rood2, !rood);
    delay(175);
    digitalWrite(rood1, !rood);
    digitalWrite(rood2, rood);
    delay(175);
  }
  digitalWrite(rood1, LOW);
  digitalWrite(rood2, LOW);
  digitalWrite(witlicht, wit);
  delay(750);
  wit = !wit;
}