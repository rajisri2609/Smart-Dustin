#include <ESP32Servo.h>
#include <Wire.h>

#define BLYNK_TEMPLATE_ID "TMPL3WO3icUEi"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin UI"
#define BLYNK_AUTH_TOKEN "gyCCdsHJyAQNvo4fP6HVI2vXBY6-OOXw"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Raji";
char pass[] = "Raji@123";

BlynkTimer timer;

#define MQ135_THRESHOLD_1   1000
//#define echoPin 2               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
//#define trigPin 4  
#define echoPin01 18               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define trigPin01 19
#define depth 50
#define AOUT_PIN 36

int _moisture,sensor_analog;
const int sensor_pin = 34;

             // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
//long duration, distance;
long duration01, distance01;
long duration02, distance02;

Servo myservo;
int servopin=26;

Servo myservo01;
int servopin01=15;

void setup(){
  Serial.begin (115200);
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  pinMode(trigPin01, OUTPUT);
  pinMode(echoPin01, INPUT);
  myservo.attach(servopin);
  myservo01.attach(servopin01);
  myservo.write(0);  
  Blynk.begin(auth, ssid, pass);
  delay(2000);
  
}
void loop(){
  Blynk.run();
  timer.run();
/*
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  
  delay(1000);
*/ 
  digitalWrite(trigPin01, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin01, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin01, LOW);  
  duration01 = pulseIn(echoPin01, HIGH);

  //distance = duration * 0.034/2;
  distance01 = duration01 * 0.034/2;

//  Serial.println(distance);

  /*
  if (distance<40) {
    myservo.write(130);
    delay(2000);
  }
  else{
    myservo.write(0);
  
  }
  */
  
  if(distance01<=(0.25*depth)){
    Serial.print("Dustbin filled less than 25%");
    Blynk.virtualWrite(V1,"Dustbin filled less than 25%");
    Blynk.virtualWrite(V2,"25");
  }
  else if(distance01<=(0.5*depth)){
    Serial.print("Dustbin filled less than 50%");
    Blynk.virtualWrite(V1,"Dustbin filled less than 50%");
    Blynk.virtualWrite(V2,"50");

  }
  else if(distance01<=(0.75*depth)){
    Serial.print("Dustbin filled less than 75%");
    Blynk.virtualWrite(V1,"Dustbin filled less than 75%");
    Blynk.virtualWrite(V2,"75");
  }
  else if(distance01<(0.9*depth)){
    Serial.print("Dustbin nearly full");
    Blynk.virtualWrite(V1,"Dustbin nearly full");
    Blynk.virtualWrite(V2,"90");
  }
  else{
    Serial.print("Overflow!!!!");
    Blynk.virtualWrite(V1,"Overflow!!!!");
    Blynk.virtualWrite(V2,"100");
  }

  int MQ135_data = analogRead(32);

  if(MQ135_data < MQ135_THRESHOLD_1){
    Serial.print("No Odour: ");
    Blynk.virtualWrite(V0,"No Odour");
    } 
  else {
    Serial.print("Bad Odour: "); 
    Blynk.virtualWrite(V0,"Bad Odour");
  }
    Serial.print(MQ135_data); // analog data
    Serial.println(" PPM"); // Unit = part per million

  int value = analogRead(AOUT_PIN);
  _moisture = ( 100 - ( (value/4095.00) * 100 ) );
  Serial.print("Moisture = ");
  Serial.print(_moisture);  /* Print Temperature on the serial window */
  Serial.println("%");
  if(_moisture>=0 & _moisture<=10){
    Serial.print("Dry Waste");
    myservo01.write(165);
    delay(3000);
    myservo01.write(90);
  }
  else if((_moisture >=20 & _moisture <=60 ) & (distance02<7)){
    Serial.print("Moist Waste ");
    myservo01.write(15);
    delay(3000);
    myservo01.write(90);
  }

  delay(1000);// delay
}
