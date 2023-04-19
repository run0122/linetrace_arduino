#include <SoftwareSerial.h>

int blueTx = 12;
int blueRx = 13;
SoftwareSerial btSerial(blueTx, blueRx);

int motor_A1 = 5;
int motor_A2 = 6;

int motor_B1 = 9;
int motor_B2 = 10;

void setup(){
  Serial.begin(9600);
  btSerial.begin(9600);

  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
}

void loop(){
  if (btSerial.available()){
    char command = btSerial.read();
    switch(command){
      case 'w': // 전진
        forward();
        break;
      case 's': // 후진
        backward();
        break;
      case 'o': // 좌
        left();
        break;
      case 'p': // 우
        right();
        break;
      case 'n': // 멈춤
        stop();
        break;
    }
  }
}


void right () {
  //우
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  analogWrite(motor_B2, 150);
}

void left() {
  //좌
  digitalWrite(motor_A1, LOW);
  analogWrite(motor_A2, 150);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void forward() {
  //전진
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void backward() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
}

void stop() {
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}