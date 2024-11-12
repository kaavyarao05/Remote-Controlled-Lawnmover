#include<AFMotor.h>

#define trigPin 3
#define echoPin 2
#define safeDistance 20 //centimeters

#define FORCESTOP '7'

#define STARTBUTTON '1'
#define STOPBUTTON '0'
#define LEFTBUTTON '5'
#define RIGHTBUTTON '4'
#define DOWNBUTTON '3'
#define UPBUTTON '2'

AF_DCMotor blade(1);
AF_DCMotor right(3);
AF_DCMotor left(4);

bool spinning=true; // blade should spin
bool forceStop=false; //user wants the mover to stop moving and spinning
int buttonClicked=FORCESTOP,storedDir;
float duration_us, distance_cm;

void moveRight(){
  Serial.println("Right");
  right.run(FORWARD);
  left.run(RELEASE);
  delay(1000);
}

void moveLeft(){
  Serial.println("Left");
  right.run(RELEASE);
  left.run(FORWARD);
  delay(1000);
}

void moveFront(){
  Serial.println("Front");
  right.run(FORWARD);
  delay(500);
  left.run(FORWARD);
  delay(1000);
}

void moveBack(){
  Serial.println("Back");
  right.run(BACKWARD);
  delay(500);
  left.run(BACKWARD);
  delay(500);
}

void stopRun(){
  Serial.println("STOP run");
  right.run(RELEASE);
  left.run(RELEASE);
  delay(1000);
}

void startBlade(){
  Serial.println("START blade");
  blade.run(FORWARD);
  delay(1000);
}

void stopBlade(){
  Serial.println("START blade");
  blade.run(RELEASE);
  delay(1000);
}

void setup()  {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  blade.setSpeed(200);
  right.setSpeed(200);
  left.setSpeed(200);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration_us = pulseIn(echoPin, HIGH);
  distance_cm = 0.017 * duration_us;
  /*
  if(distance_cm<safeDistance){
    if (buttonClicked!=FORCESTOP)
      storedDir=buttonClicked;
      buttonClicked=FORCESTOP;
    spinning=false;
  }
  else if(forceStop==false){
    if (storedDir)
      buttonClicked=storedDir;
      storedDir=NULL;
    spinning=true;
  }
  */
  Serial.println("running");
  if(Serial.available()>0){
    int input;
    input = Serial.read();
    delay(100);
    if(input==STARTBUTTON){
      startBlade();
    }
    else if (input==STOPBUTTON){
      stopBlade();
    }
    else{
      buttonClicked=input;
      if(buttonClicked==LEFTBUTTON){
        moveLeft();
      }
      else if (buttonClicked==RIGHTBUTTON){
        moveRight();
      }
      else if(buttonClicked==UPBUTTON){
        moveFront();
      }
      else if (buttonClicked==DOWNBUTTON){
        moveBack();
      }
      else if (buttonClicked==FORCESTOP){
        stopRun();
      }
    }
  }
}