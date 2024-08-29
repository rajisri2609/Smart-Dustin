#include <ESP32Servo.h>

#define echoPin 2             // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define trigPin 4

Servo myservo;
int servopin=26;
long duration, distance;


void setup(){
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servopin);
  myservo.write(0);
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034)/2;

  Serial.println(distance);

  if (distance<40 & distance!=0) {
  
    myservo.write(130);
    delay(3000);
    myservo.write(0);
  }

   delay(1000);
}
