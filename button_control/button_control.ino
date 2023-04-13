const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;
const int but_1 = 3;
const int but_2 = 4;
const int but_3 = 11;
const int but_4 = 11;
const int but_5 = 11;
const int but_6 = 11;
int IR_L_data;
int IR_M_data;
int IR_R_data;


void setup() {
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  pinMode(but_1, INPUT);
  pinMode(but_2, INPUT);
  pinMode(but_3, INPUT);
  pinMode(but_4, INPUT);
  pinMode(but_5, INPUT);
  pinMode(but_6, INPUT);
  Serial.begin(9600);
  Serial.print("Start");
}


void loop() {
  if(digitalRead(but_1) == LOW){
    stop();
    delay(15);
  }
  //우회전
  else if(digitalRead(but_1) == HIGH){
    right ();
    delay(15);
  }
  if(digitalRead(but_2) == LOW){
    stop();
    delay(15);
  }
  //좌회전
  else if(digitalRead(but_2) == HIGH){
    left();
    delay(15);
  }
  if(digitalRead(but_3) == LOW){
    stop();
    delay(15);
  }
  //전진
  else if(digitalRead(but_3) == HIGH){
    forward();
    delay(15);
  }
  if(digitalRead(but_4) == LOW){
    stop();
    delay(15);
  }
  //후진
  else if(digitalRead(but_4) == HIGH){
    backward();
    delay(15);
  }
  if(digitalRead(but_5) == LOW){
    stop();
    delay(15);
  }
  //우로 후진
  else if(digitalRead(but_5) == HIGH){
    rightback ();
    delay(15);
  }
  if(digitalRead(but_6) == LOW){
    stop();
    delay(15);
  }
  //좌로 후진
  else if(digitalRead(but_6) == HIGH){
    leftback();
    delay(15);
  }
}


void right () {
  //우
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void rightback () {
  //우로 후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void left() {
  //좌
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}
void leftback() {
  //좌로 후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
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
