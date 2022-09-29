#include <SoftwareSerial.h>
#include<math.h>

#include <String.h>

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
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.println("GPS Start");
  Serial.println("Checking module...");
  Serial.println("Module Connected");
  Serial.println("Text Mode: ON");
  Serial.println("GPS Intializing...");
  Serial.println("GPS Intialized");
  delay(2000);
  Serial.println("Location: 17.741302, 83.249084");

    if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT");
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");//  AT command sets the password of teh mobile device.
  delay(1000);
 
  gprsSerial.println("AT+CREG?");//ommand gives information about the registration status and access technology of the serving cell
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");//command is used to attach or detach the device to packet domain service.
  delay(1000);
 
  gprsSerial.println("AT+CIPSHUT");// will close the GPRS PDP context.
  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");//AT+CIPSTART comamnds starts a TCP or UDP connection Transmission Control Protocol a communications standard that enables application programs and computing devices to exchange messages over a network
  delay(2000);
 
  gprsSerial.println("AT+CIPMUX=0");//command is used to single IP or multi-IP connection Simcom modules
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();

  
 
 
  delay(1000);
}
 
void loop()
{
  float dist1=ultra(trigPin1, echoPin1);
  float dist2=ultra(trigPin2, echoPin2);
  delay(5000);   
         
  Serial.println("distance of 1st");
  Serial.println(dist1);
  Serial.println("distance of 2nd");
  Serial.println(dist2);  

  String latitude = String(lati,6);
  String longitude = String(longi,6);
   

  if((dist1<=5)&& (dist2<=5)){
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=3WTQRQRRID8BIWLZ&field1=" + String(bin_number) +"&field2="+String(latitude)+"&field3="+String(longitude);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
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
