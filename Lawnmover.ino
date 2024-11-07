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
  right.run(FORWARD);
  left.run(RELEASE);
}

void moveLeft(){
  right.run(RELEASE);
  left.run(FORWARD);
}

void moveFront(){
  right.run(FORWARD);
  left.run(FORWARD);
}

void moveBack(){
  right.run(BACKWARD);
  left.run(BACKWARD);
}

void stopRun(){
  right.run(RELEASE);
  left.run(RELEASE);
}

void startBlade(){
  blade.run(FORWARD);
}

void stopBlade(){
  blade.run(RELEASE);
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
  delay(400);

  if(Serial.available()>0){
    int input;
    input = Serial.read();
    delay(100);
    if(input==STARTBUTTON){
      forceStop=false;
      spinning=true;
    }
    else if (input==STOPBUTTON){
      forceStop=true;
      spinning=false;
      if (buttonClicked!=FORCESTOP)
        storedDir=buttonClicked;
        buttonClicked=FORCESTOP;
    }
    else{
      buttonClicked=input;
    }
  }

  if(spinning){
    startBlade();
  }
  else{
    stopBlade();
  }
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
  else if (buttonClicked=FORCESTOP){
    stopRun();
  }
}