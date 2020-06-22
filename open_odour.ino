#include<Servo.h>

Servo myservo, myservo2;
const int trigPin = 9;
const int echoPin = 10;
const int trigPin2 = 12;
const int echoPin2 = 13;
char data_rx;

long duration, duration2;
int distance, distance2, val=0;
void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
Serial.begin(9600);
myservo2.attach(9);
 myservo.attach(11);
 myservo.write(0);
 delay(500);
 myservo.detach();
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);



duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

digitalWrite(trigPin2, LOW);
delayMicroseconds(2);

digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2,LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2= duration2*0.034/2;


if(distance < 15)
{
  
 myservo.attach(11);
//  myservo.write(0);
//  delay(500);
  myservo.write(180);
  delay(3500);
//  myservo.write(0);
//  delay(500);
  
  }
  else
  { myservo.write(0);
  delay(500);
  myservo.detach();
  }

//sprinkler
val=analogRead(A2);
  Serial.println(val);
  if(val>175 )
  {
    myservo2.write(90);
    delay(1000);
  }
  else

  {
  myservo2.write(0);
}
  
  if(distance2 >40)
  {
    Serial.print("Distance: ");
    Serial.println(distance2);
    Serial.println("cm");
    Serial.println("Your DustBin is Empty");
    }
else if(distance2 <39 and distance2 >20 )
{
  Serial.print("Distance: ");
    Serial.println(distance2);
    Serial.println("cm");
    Serial.println("Your DustBin is Half Filled");
  }
else if(distance2 <10)
{
  Serial.print("Distance: ");
    Serial.println(distance2);
    Serial.println("cm");
    Serial.println("Your DustBin is Full");
    //Dc motor should run here for sealing action
  }
  else
  {Serial.print("Distance: ");
    Serial.println(distance2);
    Serial.println("cm");}
}
data_rx= Serial.read();
