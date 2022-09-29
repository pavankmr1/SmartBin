const int Input1=2;
int State1=0;

void setup(){
  Serial.begin(9600);
  pinMode(Input1, INPUT);
}

void loop()
{
  State1= digitalRead(Input1);

  if(State1 == HIGH)
    {
      sendsms();
      delay(2000);
    }
}

void sendsms()
{
  Serial.println("AT\r");
  delay(1000);
  Serial.println("AT+CMGF=1\r");
  delay(1000);
  Serial.println("AT+CMGS=\"8897283429\"\r");
  delay(1000);
  Serial.println("ALERT");
  delay(1000);
  Serial.println((char)26);
  delay(100);
}
