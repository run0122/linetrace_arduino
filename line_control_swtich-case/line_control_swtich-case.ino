/*
millis를 이용하여 일정 시간 라인트레이서 센서 값을 받아 주행을 한 후에
일정 시간이 끝나게 되면 초음파 센서 값을 받아 후진을 하고 일정 거리가
되었으면 멈추는 코드 입니다.
*/

// 모터 핀 번호
const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;

// 초음파 센서 핀 번호
const int trigPin = 3;
const int echoPin = 11;

// 부저 핀 번호
const int buzzer = 7;

// 라인트레이서 센서 핀 번호
const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;

// 라인트레이서 센서 데이터
int IR_L_data;
int IR_M_data;
int IR_R_data;

// millis 변수 설정
unsigned long Timer_move = millis();

// 초음파 센서 거리 변수
float duration, distance;

void setup() {
  // 모터
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  
  // 초음파 센서
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // 부저
  pinMode(buzzer, OUTPUT);
  
  // 라인트레이서
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
}


void loop() {
  // 라인트레이서 센서 값 
  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);

  //초음파 센서 구동
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  delay(50);// 딜레이값으로 인해 동작의 속도 변화

  int position = map(distance, 0, 150, 0, 10);
  switch(position){
    case 0:
    stop();
    //backward();
    break;
    case 1:
    backward();
    break;
    //stop();
    case 2:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 3:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 4:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 5:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 6:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 7:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 8:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 9:
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 전진
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left ();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 우회전
    right ();
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    // 정지
    stop();
  }
  break;
    case 10:
        if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
        // 전진
        forward();
      }
      else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
        // 좌회전
        left ();
      }
      else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
        // 우회전
        right ();
      }
      else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
        // 정지
        stop();
      }
      break;
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
  analogWrite(motor_A2, 100);
  analogWrite(motor_B1, 100);
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
  analogWrite(motor_A2, 255);
  digitalWrite(motor_B1, LOW);
  analogWrite(motor_B2, 255);
}

void stop() {
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void backward_20() {
  //속도 제한 후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  analogWrite(motor_A1, 0);
  analogWrite(motor_A2, 150);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 150);
}