/*
 18. Januar 2015
 
 Links:
 http://www.geekonfire.com/wiki/index.php?title=Dual_H-Bridge_Motor_Driver
 http://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
 */
 
#define ENA 5       // schwarz, PWM
#define IN1 6       // weiss
#define IN2 7       // grau
#define IN3 8       // violett
#define IN4 9       // blau
#define ENB 10      // grün, PWM
#define trigger 11  // orange
#define echo 12     // rot
#define LED 13

void setup() {
  Serial.begin (9600);
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(LED, OUTPUT);
  
  stop();
}

void loop() {
  int speed = 150;
  
  long dist = distance();
  if (dist > 30) {
    forward(speed, 500);
  } else {
    blink(3);
    tankTurnLeft(speed, 500);
    delay(1000);
  }
}

long distance() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  long duration = pulseIn(echo, HIGH);
 
  // convert the time into a distance
  long cm = (duration/2) / 29.1;
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  return cm;
}

void forward(int speed, int millis) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  delay(millis);
  stop();
}

void backward(int speed, int millis) {
  reverseA();
  reverseB();
  forward(speed, millis);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  // reset motor direction to forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void reverseA() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void reverseB() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
}

void turnLeft(int speed, int millis) {
  analogWrite(ENA, speed);
  analogWrite(ENB, 0);
  delay(millis);
  stop();
}

void turnRight(int speed, int millis) {
  analogWrite(ENA, 0);
  analogWrite(ENB, speed);
  delay(millis);
  stop();
}

void tankTurnLeft(int speed, int millis) {
  reverseB();
  forward(speed, millis);
}

void tankTurnRight(int speed, int millis) {
  reverseA();
  forward(speed, millis);
}

void blink(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
}
