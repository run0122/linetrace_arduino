int in1 = 5;
int in2 = 6;
int in3 = 9;
int in4 = 10;

bool is_turned = false;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    char input = Serial.read();

    if (input == 'F') {
      forward();
      delay(80);
      stop();
    } else if (input == 'B') {
      backward();
      delay(80);
      stop();
    } else if (input == 'T'){
      trun_1();
    } else if (input == 'J'){
      trun_2();
    }else if (input == 'L') {
      left();
      delay(80);
      stop();
    } else if (input == 'R') {
      right();
      delay(80);
      stop();
    } else {
      stop();
    }
  }
}

void forward() {
  delay(15);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void backward() {
  delay(15);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void left() {
  delay(15);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void right() {
  delay(15);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void stop() {
  delay(15);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turn_1() {
  //왼쪽으로 우회
  millifirstleft(500);
  milliforward(700);
  milliright(500);
  milliforward(700);
  milliright(500);
  milliforward(700);
  //is_turned = true;
}

void turn_2() {
  //오른쪽으로 우회
  milliright(500);
  milliforward(1500);
  millifirstleft(500);
  milliforward(1500);
  millifirstleft(500);
  milliforward(1500);
  //is_turned = true;
}

void millifirstleft(unsigned long x) {
  unsigned long current_time = millis();
  unsigned long interval = x;
  while (millis() - current_time < interval) {
    hardleft();
  }
}
void milliright(unsigned long x) {
  unsigned long current_time = millis();
  unsigned long interval = x;
  while (millis() - current_time < interval) {
    hardright();
  }
}
void milliright(unsigned long x) {
  unsigned long current_time = millis();
  unsigned long interval = x;
  while (millis() - current_time < interval) {
    hardforward();
  }
}

void hardright() {
  //우
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
}

void hardleft() {
  //좌
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void hardforward() {
  //직진
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}
