#include<math.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <TinyGPS.h>

#define trigPin1 6
#define echoPin1 7
#define trigPin2 8
#define echoPin2 9

SoftwareSerial gprsSerial(2,3);//rx,tx 
int bin_number =1;
float duration;
float distance;

float lati = 17.741302;
float longi = 83.249084;

 void setup() 
{

  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  gprsSerial.begin(9600); 
  Serial.println("GPS Start");
  Serial.println("Checking module...");
  Serial.println("Module Connected");
  Serial.println("Text Mode: ON");
  Serial.println("GPS Intializing...");
  Serial.println("GPS Intialized");
  Serial.println("Location: 17.741302, 83.249084");



  
  
  delay(1000);



}

void loop() {
  float dist1=ultra(trigPin1, echoPin1);
  float dist2=ultra(trigPin2, echoPin2);

  Serial.println("distance of 1st");
  Serial.println(dist1);
  Serial.println("distance of 2nd");
  Serial.println(dist2);
  delay(5000);
if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT");
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");
  delay(1000);
 
  gprsSerial.println("AT+CREG?");
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");
  delay(1000);
 
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");
  delay(1000);
 
  gprsSerial.println("AT+CIPMUX=0");
  delay(1000);
 

 
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
 

 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(1000);
 

 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(1000);
 

 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(1000);

    
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(1000);
 


  String latitude = String(lati,6);
  String longitude = String(longi,6);
  
  if((dist1<=5)&& (dist2<=5))
  {
  Serial.println("connection to server");
  
    


 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);

  
  String str="GET https://api.thingspeak.com/update?api_key=OUHN12REWL0KPL7N&field1=" + String(bin_number) +"&field2=" +String(latitude)+"&field3="+String(longitude);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(4000);

 
  gprsSerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 

 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  

    delay(20000);
  }
}

float ultra(int trigPin,int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  return distance;

}
