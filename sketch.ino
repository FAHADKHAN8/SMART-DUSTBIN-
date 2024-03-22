// IF DUSTBIN IS FULL AS PER READING OF ULTRASONIC THEN IT SHOULDNT OOPEN ,
//  AND DISTANCE SHOULDE BE MAPPED AS PERCETANGE OF DUSTBIN FILLED
#include <ESP32Servo.h>
const int ir = 11;
const int servoPin = 10;
Servo myServo;
const int trigPin = 12;
const int echoPin = 13;
long duration;
int distance;
const int rled = 14;

void setup() {
  pinMode(ir, INPUT);
  pinMode(rled, OUTPUT); 
  Serial.begin(115200);
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  int irState = digitalRead(ir);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  int percentageFilled = map(distance, 0, 100, 100, 0);    
    myServo.write(0);

if(irState==LOW){
   Serial.print("Distance=");
  Serial.print(distance);
  Serial.print(" cm, Percentage Filled=");
  Serial.print(percentageFilled);
  Serial.println("%");
   digitalWrite(rled, LOW);
}
  else if (irState == HIGH && percentageFilled >= 90) {
   
    myServo.write(0);
    digitalWrite(rled, HIGH);
    Serial.println("DUSTBIN IS ALMOST FULL!");
  }
   else if (irState == HIGH && percentageFilled < 90) {
    digitalWrite(rled, LOW);
    myServo.write(90);
    Serial.println("DUSTBIN LID OPEN");
  }
  delay(1000);
}
