const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;
const int but_1 = 3;
const int but_2 = 4;
const int but_3 = 11;
// const int IR_R = A1;
// const int IR_M = A3;
// const int IR_L = A5;
int IR_L_data;
int IR_M_data;
int IR_R_data;


void setup() {
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  // pinMode(IR_L, INPUT);
  // pinMode(IR_M, INPUT);
  // pinMode(IR_R, INPUT);
  pinMode(but_1, INPUT);
  pinMode(but_2, INPUT);
  pinMode(but_3, INPUT);
  Serial.begin(9600);
  Serial.print("Start");
}


void loop() {
  //IR 센서 값을 읽어 출력해주는 코드
  // IR_L_data = digitalRead(IR_L);
  // IR_M_data = digitalRead(IR_M);
  // IR_R_data = digitalRead(IR_R);
  if(digitalRead(but_1) == LOW){
    stop();
    delay(15);
  }
  else if(digitalRead(but_1) == HIGH){
    right ();
    delay(15);
  }
  if(digitalRead(but_2) == LOW){
    stop();
    delay(15);
  }
  else if(digitalRead(but_2) == HIGH){
    left();
    delay(15);
  }
  if(digitalRead(but_3) == LOW){
    stop();
    delay(15);
  }
  else if(digitalRead(but_3) == HIGH){
    forward();
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

void left() {
  //좌
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
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
