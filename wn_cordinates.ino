#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
float value = 0;
int x = 0;
unsigned long y = 17.741302;
unsigned long z = 83.249084;
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Redmi Note 10 Pro Max"; // your network SSID (name)
char pass[] = "niha@123"; // your network password
//-------------------------------------------//
//----------- Channel Details -------------//
unsigned long Channel_ID = 1540622; // Channel ID
const int Field_number1 = 1; // Don't change
const int Field_number2 = 2; // Don't change
const int Field_number3 = 3; // Don't change

const char * WriteAPIKey = "3WTQRQRRID8BIWLZ"; // Your write API Key
// ----------------------------------------//
WiFiClient client;
void setup()
{
 Serial.begin(115200);
 WiFi.mode(WIFI_STA);
 ThingSpeak.begin(client);
}
void loop()
{
 internet();
 
 upload();
}
void upload()
{
 internet();
 x = ThingSpeak.writeField(Channel_ID, Field_number1, 1, WriteAPIKey);
 x = ThingSpeak.writeField(Channel_ID, Field_number2, y, WriteAPIKey);
 x = ThingSpeak.writeField(Channel_ID, Field_number3, z, WriteAPIKey);
 if (x == 200)Serial.println("Data Updated.");
 if (x != 200)
 {
 Serial.println("Data upload failed, retrying....");
 delay(15000);
 upload();
 }
}
void internet()
{
 if (WiFi.status() != WL_CONNECTED)
 {
 Serial.print("Attempting to connect to SSID: ");
 Serial.println(ssid);
 while (WiFi.status() != WL_CONNECTED)
 {
 WiFi.begin(ssid, pass);
 Serial.print(".");
 delay(5000);
 }
 Serial.println("\nConnected.");
 }
}
