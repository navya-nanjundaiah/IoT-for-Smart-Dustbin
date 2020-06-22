String myAPIkey = "QBAUAPCR896QUB29"; //thingSpeak API Key.
#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial ESP8266(2,3); // Rx, Tx

const int trigPin2 =11;
const int echoPin2 = 10;

long duration, duration2;
int distance, distance2;
long writingTimer = 20;
long startTime = 0;
long waitTime = 0;

boolean relay1_st = false;
String getStr ="";
void setup() {
boolean relay2_st = false;
unsigned char check_connection=0;
unsigned char times_check=0;
boolean error;
  Serial.begin(115200); //set the baud rate for Arduino serial
ESP8266.begin(115200); //set the baud rate for esp module
startTime = millis();
ESP8266.println("AT+RST");
delay(2000);
ESP8266.println("AT+CWMODE=3");
delay(2000);
Serial.println("Connecting to Wifi");
while(check_connection==0)
{
Serial.print(".");
ESP8266.print("AT+CWJAP=\"J&R's,\"allineedisjesus001\"\r\n"); //Wi-Fi SSID and Password
ESP8266.setTimeout(5000);
if(ESP8266.find("WIFI CONNECTED\r\n")==1)
{
Serial.println("WIFI CONNECTED");
break;
}
times_check++;
if(times_check>3)
{
times_check=0;
Serial.println("Trying to Reconnect..");
}
}
  // put your setup code here, to run once:
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);

}

void loop() {
waitTime = millis() - startTime;
if (waitTime > (writingTimer*1000))
{
readSensors();
writeThingSpeak();
startTime = millis();
}
}

void readSensors()
{
  // put your main code here, to run repeatedly:


digitalWrite(trigPin2, LOW);
delayMicroseconds(2);

digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2,LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2= duration2*0.034/2;
}
void writeThingSpeak(void)
{
startThingSpeakCmd();                          
Serial.print("Completed Startthingspeakcmd)");
//GET request will be sent to ThingSpeak Server
getStr = "GET /update?api_key="; //prepare GET string0
getStr += myAPIkey; //append the appropriate API key
getStr +="&field1=";
getStr += String(distance2); //append the temperature as a string(typecasting)
getStr += "\r\n\r\n";
GetThingspeakcmd(getStr);
}
void startThingSpeakCmd(void)
{
ESP8266.flush(); //Clear ESP8266 data
Serial.print("Started Things Speak Command");
String cmd = "AT+CIPSTART=\"TCP\",\"";
cmd += "http://184.106.153.149"; // api.thingspeak.com IP address**184.106.153.149
cmd += "\",80";
ESP8266.println(cmd);
Serial.print("Start Commands: ");
Serial.println(cmd);
if(ESP8266.find("Error"))
{
Serial.println("AT+CIPSTART error");
return;
}
}
String GetThingspeakcmd(String getStr)
{
String cmd = "AT+CIPSEND=";
cmd += String(getStr.length());
ESP8266.println(cmd);
Serial.println(cmd);
if(ESP8266.find(">"))
{
ESP8266.print(getStr);
Serial.println(getStr);
delay(500);
String messageBody = "";
while (ESP8266.available())
{
String line = ESP8266.readStringUntil('\n');
if (line.length() == 1)
{
messageBody = ESP8266.readStringUntil('\n');
}
}
Serial.print("MessageBody received: ");
Serial.println(messageBody);
return messageBody;
}
else
{
ESP8266.println("AT+CIPCLOSE");
Serial.println("AT+CIPCLOSE");
}
}
