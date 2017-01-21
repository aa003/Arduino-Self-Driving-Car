/*1) Go forward
2) Read sensor's informations
3) If sensor detect an obstacle
3-1) Move to the right with an angle of 10° and detect if there's any obstacle
3-1-1) If there's an obstacle: Repeat the step 3-1
3-1-2) If it's clear: Go forward*/

#include <Servo.h> 
#include <AFMotor.h>
 
int pinSensor = 11; // 5? 7?
int vSon = 59; //time value in µs of a round trip of sound on 1cm
int trigPin = 12;
int echoPin = 11;
int servoPin = 5;
int moteurPin = 7;


AF_DCMotor motor(1); // DC motor on M1

Servo myServo;
    //delay(1000);
void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  pinMode(servoPin,OUTPUT);// pin mode servo OUTPUT
  //pinMode(moteurPin,OUTPUT);// pin mode Moteur OUTPUT
  digitalWrite(servoPin,LOW); // initialisation
  pinMode(trigPin, OUTPUT); // pin mode trig OUTPUT
  digitalWrite(trigPin, LOW); // initialisation
  pinMode(echoPin, INPUT); 
  myServo.attach(servoPin);
  myServo.write(0);
  motor.setSpeed(100);//Go forward
  motor.run(RELEASE);
}

void loop() {
  motor.run(FORWARD);
  int distance=mesureDistance(); //Get distance from the function
  if (distance<10) 
  {
    motor.run(RELEASE); // STOP
    for (int i=10; i<360; i+=10) // Loop to change the angle
    {
      myServo.write(i); //angle=i;+10+10...
      int newDist=mesureDistance(); // to get the new obstacle distance
      Serial.println("New Distance : "); 
      Serial.println(newDist); 
      if (newDist>10) {break;}; // if the distance >10cm break the loop and go forward
    }
  }
  else
  {
    motor.run(FORWARD); //Go forward until sensor catch something
  }
}
//function to get distance from the sensor
int mesureDistance() {
  unsigned long measure = 0; // measure variable
  unsigned long distance = 0; // distance in cm
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  measure = pulseIn(echoPin, HIGH);
  distance = measure / vSon; 
  Serial.println("Distance : "); 
  Serial.println(distance); 
  return distance;
}
