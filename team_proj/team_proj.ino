const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;
const int trigPin = 3;
const int echoPin = 11;
const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;
int IR_L_data;
int IR_M_data;
int IR_R_data;

unsigned long Timer_move = millis();

float duration, distance;

void setup() {
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
  Serial.begin(9600);
  Serial.print("Start");
}


void loop() {
  //IR 센서 값을 읽어 출력해주는 코드
  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);

  if (Timer_move + 10000 > millis()){
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    Serial.println(" 직진 ");
    forward();
    delay(100);
    }
    else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
      Serial.println(" 좌회전 ");
      left ();
      delay(100);
    }
    // else if (IR_L_data == 1 and IR_M_data == 1 and IR_R_data == 0) {
    //   Serial.println(" 좌회전 ");
    //   left ();
    //   delay(100);
    // }
    else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
      Serial.println(" 우회전 ");
      right ();
      delay(100);
    }
    // else if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 1) {
    //   Serial.println(" 우회전 ");
    //   right ();
    //   delay(100);
    // }

    else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
      Serial.println(" 정지 ");
      stop();
      delay(100);
    }
  }else if(Timer_move + 10000 < millis()){
    rightback ();
    //Timer_move = 0;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    //Serial.print("Distance: ");
    //Serial.println(distance);
    delay(100);
    if(distance > 10 && distance < 30){
      //Timer_move = 0;
      backward();
      delay(500);
      stop();
    }else if(distance > 0 && distance < 10){
      Timer_move = 0;
      stop();
    }
    //Timer_move = 0;
  }

}


void right () {
  //우
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  analogWrite(motor_B2, 150);
}
void rightback () {
  //우로 후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
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
  analogWrite(motor_A2, 150);
  digitalWrite(motor_B1, LOW);
  analogWrite(motor_B2, 150);
}

void stop() {
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}