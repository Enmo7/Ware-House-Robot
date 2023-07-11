#include "CytronMotorDriver.h"

// Configure the motor driver.
CytronMD motor1(PWM_DIR, 5, 4);  // PWM 1 = Pin 3, DIR 1 = Pin 4.
CytronMD motor2(PWM_DIR, 7, 6); // PWM 2 = Pin 9, DIR 2 = Pin 10.

#define left 14
#define center 15
#define right 16

int in1Pin = 17;
int in2Pin = 18;

#define echo 8    //Echo pin
#define trigger 9 //Trigger pin
float duration, distance;  

#define echo1 10   //Echo pin
#define trigger1 11 //Trigger pin
float duration1, distance1;  

void setup() {
  Serial.begin(9600);

  pinMode(left, INPUT);
  pinMode(center, INPUT);
  pinMode(right, INPUT);
  // Set the pins as outputs
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  pinMode(trigger, OUTPUT);  
  pinMode(echo, INPUT); 

  pinMode(trigger1, OUTPUT);  
  pinMode(echo1, INPUT); 

}

void loop() {
  bool leftV = digitalRead(left);
  bool centerV = digitalRead(center);
  bool rightV = digitalRead(right);
  // Measure distance using ultrasonic sensor
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.034 / 2;

  // Measure distance using ultrasonic sensor1
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);
  long duration1 = pulseIn(echo1, HIGH);
  float distance1 = duration1 * 0.034 / 2;

  while (Serial.available() > 0) {
    char data = Serial.read();
    if (data == '1') {
      delay(2000);
      Stop() ;
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
      delay(10000);
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
      break;
    }
    else if (data == '2') {
      delay(2000);
      Stop();
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
      delay(10000);
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
      break;
    } 
}
  if (distance < 20 || distance1 < 20){
    Stop();
  }
  else if (leftV == 1 && centerV == 0 && rightV == 1) {
    forward();
  }
   else if (leftV == 0 && centerV == 1 && rightV == 0) {
    forward();
  } else if (leftV == 0 && centerV == 0 && rightV == 0) {
    Stop();
  } else if (leftV == 1 && centerV == 1 && rightV == 1) {
    Stop();
  } else if (leftV == 0 && centerV == 0 && rightV == 1) {
    turnleft();
  } else if (leftV == 1 && centerV == 0 && rightV == 0) {
    turnright();
  } else if (leftV == 0 && centerV == 1 && rightV == 1) {
    turnleft();
  } else if (leftV == 1 && centerV == 1 && rightV == 0) {
    turnright();
  }
    
}
void forward(){  //forword

  motor1.setSpeed(255);  // Motor 1 runs backward at full speed.
  motor2.setSpeed(150);   // Motor 2 runs forward at full speed.
}

void backword(){ //backword

  motor1.setSpeed(-255);  // Motor 1 runs backward at full speed.
  motor2.setSpeed(-150);   // Motor 2 runs forward at full speed.
}

void turnright(){ //turnRight
  motor1.setSpeed(255);  // Motor 1 runs backward at full speed.
  motor2.setSpeed(-150);   // Motor 2 runs forward at full speed.
}

void turnleft(){ //turnLeft
  motor1.setSpeed(-255);  // Motor 1 runs backward at full speed.
  motor2.setSpeed(150);   // Motor 2 runs forward at full speed.
}

void Stop(){ //stop
  motor1.setSpeed(0);  // Motor 1 runs backward at full speed.
  motor2.setSpeed(0);   // Motor 2 runs forward at full speed.
}

void scissorup() {

  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
}
void scissordown() {

  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
}
void scissorstop() {

  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
}
