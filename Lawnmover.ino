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


bool spinning=true; // blade should spin
bool forceStop=false; //user wants the mover to stop moving and spinning
int buttonClicked=FORCESTOP,storedDir;
float duration_us, distance_cm;

void setup()  {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration_us = pulseIn(echoPin, HIGH);
  distance_cm = 0.017 * duration_us;
  Serial.print("distance: "); // print the value to Serial Monitor
  Serial.print(distance_cm);
  Serial.println(" cm");
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
    Serial.print("Spinning ");
  }
  else{
    Serial.print("not Spinning ");
  }
  if(buttonClicked==LEFTBUTTON){
    Serial.println("LEFT");
  }
  else if (buttonClicked==RIGHTBUTTON){
    Serial.println("RIGHT");
  }
  else if(buttonClicked==UPBUTTON){
    Serial.println("UP");
  }
  else if (buttonClicked==DOWNBUTTON){
    Serial.println("DOWN");
  }
  else if (buttonClicked=FORCESTOP){
    Serial.println("STOPPED");
  }
}