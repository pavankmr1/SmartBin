#include<math.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <TinyGPS.h>
#include <ESP8266WiFi.h>;

#include <WiFiClient.h>;

#include <ThingSpeak.h>;

#define trigPin1 6
#define echoPin1 7
#define trigPin2 8
#define echoPin2 9

const char* ssid = "pavan"; //Your Network SSID

const char* password = "pavan123"; //Your Network Password

WiFiClient client;
const char* ssid = "pavan"; //Your Network SSID

const char* password = "123pavan"; //Your Network Password

WiFiClient client;

float lat ,lon ; // create variable for latitude and longitude object 
SoftwareSerial serial_connection(2,3); //tx,rx 
int bin_number =1;
float duration;
float distance;
TinyGPSPlus gps;



 void setup() 
{
  
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  SoftwareSerial serial_connection(2,3); //tx,rx 
  Serial.println("GPS Start");
  Serial.println("Checking module...");
  Serial.println("Module Connected");
  Serial.println("Text Mode: ON");
  Serial.println("GPS Intializing...");
  Serial.println("GPS Intialized");
  Serial.println("Location: 17.741302, 83.249084");

  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

  
  
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

  /*  while(serial_connection.available())              //While there are incoming characters  from the GPS
  {
    gps.encode(serial_connection.read());           //This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())          //This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.print("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(), 6);
  }
  delay(5000);
  */

  if((dist1<=5)&& (dist2<=5))
  {
    Serial.println("connection to server");
    ThingSpeak.setField(1, bin_number);
    ThingSpeak.setField(2, 17.741302);
    ThingSpeak.setField(3, 83.249084);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
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
